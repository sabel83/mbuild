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

#include <mbuild_test/mbuild.hpp>
#include <mbuild_test/path_override.hpp>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>

#include <just/test.hpp>
#include <just/temp.hpp>

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

namespace
{
  void show_help(const boost::program_options::options_description& desc_,
                 std::ostream& out_)
  {
    out_ << "Usage:\n"
         << "  mbuild_system_test <options> -- <test framework args>\n"
         << "\n" << desc_ << std::endl;
  }
}

int main(int argc_, char* argv_[])
{
  boost::program_options::options_description desc("options");
  std::string mbuild_binary;
  std::string gcc;
  {
    using boost::program_options::value;

    // clang-format off
    desc.add_options()
      ("help", "Display help")
      ("mbuild", value(&mbuild_binary), "The path of the MBuild binary")
      ;
    // clang-format on
  }

  try
  {
    const auto arg_end = argv_ + argc_;
    const auto arg_sep_at = std::find(argv_, arg_end, std::string("--"));
    std::vector<char*> test_fw_args(
        arg_sep_at == arg_end ? arg_end : arg_sep_at + 1, arg_end);

    boost::program_options::variables_map vm;
    store(boost::program_options::command_line_parser(arg_sep_at - argv_, argv_)
              .options(desc)
              .run(),
          vm);
    notify(vm);

    if (vm.count("help"))
    {
      show_help(desc, std::cout);
    }
    else if (mbuild_binary.empty())
    {
      throw std::runtime_error("mbuild binary not specified (use --mbuild)");
    }
    else
    {
      just::temp::directory tmp;

      mbuild_test::init(argv_[0], mbuild_binary, tmp.path());

      mbuild_test::path_override p({});
      return ::just::test::run(test_fw_args.size(), test_fw_args.data());
    }
  }
  catch (const std::exception& e_)
  {
    std::cerr << e_.what() << "\n\n";
    show_help(desc, std::cerr);
  }
}
