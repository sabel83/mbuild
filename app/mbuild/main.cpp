// MBuild - compilation measurement tool
// Copyright (C) 2016, Abel Sinkovics (abel@sinkovics.hu)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <mbuild/discovery.hpp>
#include <mbuild/gcc.hpp>
#include <mbuild/clang.hpp>
#include <mbuild/measurement.hpp>
#include <mbuild/logger.hpp>
#include <mbuild/templight.hpp>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>

#include <just/temp.hpp>
#include <just/process.hpp>

#include <iostream>
#include <sstream>
#include <set>
#include <algorithm>

namespace
{
  std::set<mbuild::compiler>
  discover_compilers(const boost::filesystem::path& tmp_dir_,
                     bool hardcoded_dirs_enabled_)
  {
    return mbuild::discover_compilers(
        {mbuild::gcc_info,
         [&tmp_dir_](const boost::filesystem::path& binary_)
         {
           return mbuild::clang_info(binary_, tmp_dir_);
         }},
        hardcoded_dirs_enabled_);
  }

  void show_compiler_info(std::ostream& out_,
                          const std::set<mbuild::compiler>& compilers_)
  {
    for (const auto& c : compilers_)
    {
      out_ << display_name(c) << " (" << c.binary;
      for (const auto& a : c.extra_arguments)
      {
        out_ << " \"" << a << "\"";
      }
      out_ << ')' << std::endl;
    }
  }

  void show_help(const boost::program_options::options_description& desc_,
                 std::ostream& out_)
  {
    out_ << "Usage:\n"
         << "  mbuild <options> <source files> -- <extra compiler arguments>\n"
         << "\n" << desc_
         << "\nThe <extra compiler arguments> will be passed to all compilers."
         << std::endl;
  }

  mbuild::measurement::result
  measure(const mbuild::measurement::parameters& parameters_,
          const boost::filesystem::path& time_,
          const boost::filesystem::path& tmp_,
          mbuild::logger log_,
          const std::vector<std::string>& extra_compiler_args_)
  {
    log_("Measuring ", parameters_.source_file, " with ",
         display_name(parameters_.compiler_info));

    mbuild::measurement::result result;

    const auto normal_build = just::process::run(
        mbuild::compile_command(parameters_, tmp_, extra_compiler_args_), "");
    result.compiles = normal_build.exit_code() == 0;
    result.standard_output = normal_build.standard_output();
    result.standard_error = normal_build.standard_error();

    result.user_time = 0;
    result.memory = 0;
    result.template_instantiations = boost::none;

    if (result.compiles)
    {
      int measure_count = 0;
      for (int i = 0; i < 5; ++i)
      {
        const auto time = just::process::run(
            mbuild::compile_command({time_.string(), "--format=%U %M"},
                                    parameters_, tmp_, extra_compiler_args_),
            "");
        double user = 0;
        decltype(result.memory) mem = 0;
        std::istringstream s(time.standard_error());
        if (s >> user >> mem)
        {
          result.user_time += user;
          ++measure_count;
          if (mem > result.memory)
          {
            result.memory = mem;
          }
        }
      }
      if (measure_count > 0)
      {
        result.user_time /= measure_count;
      }
      result.template_instantiations = mbuild::template_instantiations(
          parameters_, tmp_, extra_compiler_args_);
    }

    return result;
  }
}

int main(int argc_, char* argv_[])
{
  boost::program_options::options_description desc("options");
  std::vector<std::string> files;
  {
    using boost::program_options::value;

    // clang-format off
    desc.add_options()
      ("help", "Display help")
      ("compilers", "Display the discovered compilers")
      ("time_command", "Display the path of the time command")
      ("verbose", "Display current action on stderr")
      ("src", value(&files), "Measure compiling this file")
      ("no_hardcoded_dirs", "Don't use hard-coded paths in compiler discovery")
      ;
    // clang-format on
  }
  boost::program_options::positional_options_description positional_options;
  positional_options.add("src", -1);

  try
  {
    const auto arg_end = argv_ + argc_;
    const auto arg_sep_at = std::find(argv_, arg_end, std::string("--"));
    const std::vector<std::string> extra_compiler_args(
        arg_sep_at == arg_end ? arg_end : arg_sep_at + 1, arg_end);

    boost::program_options::variables_map vm;
    store(boost::program_options::command_line_parser(arg_sep_at - argv_, argv_)
              .options(desc)
              .positional(positional_options)
              .run(),
          vm);
    notify(vm);

    if (vm.count("help"))
    {
      show_help(desc, std::cout);
    }
    else if (vm.count("compilers"))
    {
      show_compiler_info(
          std::cout, discover_compilers(just::temp::directory().path(),
                                        !vm.count("no_hardcoded_dirs")));
    }
    else if (vm.count("time_command"))
    {
      std::cout << mbuild::find_time_command() << std::endl;
    }
    else if (files.empty())
    {
      throw std::runtime_error("No source files provided.");
    }
    else
    {
      just::temp::directory tmp;
      const auto compilers =
          discover_compilers(tmp.path(), !vm.count("no_hardcoded_dirs"));
      if (compilers.empty())
      {
        throw std::runtime_error("No compilers were found.");
      }
      else
      {
        const auto time = mbuild::find_time_command();

        mbuild::logger log(vm.count("verbose") ? &std::cerr : nullptr);

        std::cout << "[";
        bool first = true;
        for (const auto& source_file : files)
        {
          for (const auto& compiler : compilers)
          {
            for (const auto& optimisation : compiler.optimisations)
            {
              const mbuild::measurement::parameters parameters{
                  source_file, compiler, optimisation};
              if (first)
              {
                first = false;
              }
              else
              {
                std::cout << ",";
              }
              std::cout << "\n" << to_json(parameters,
                                           measure(parameters, time, tmp.path(),
                                                   log, extra_compiler_args));
            }
          }
        }
        std::cout << "\n]" << std::endl;
      }
    }
  }
  catch (const std::exception& e_)
  {
    std::cerr << e_.what() << "\n\n";
    show_help(desc, std::cerr);
  }
}
