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

#include <just/process.hpp>

#include <boost/filesystem.hpp>

#include <cassert>

namespace
{
  const int max_compiler_number = 2;

  boost::filesystem::path mbuild_binary;
  boost::filesystem::path temp_dir;

  boost::filesystem::path stub(const std::string& name_)
  {
    return mbuild_binary.parent_path() / name_;
  }

  boost::filesystem::path binary(const boost::filesystem::path& name_)
  {
#ifdef _WIN32
    return name_.string() + ".exe";
#else
    return name_;
#endif
  }

  boost::filesystem::path
  compiler_filename(compiler_stub::compiler_type compiler_,
                    compiler_stub::compiler_id n_)
  {
    assert(n_.value() >= 0);
    assert(n_.value() < max_compiler_number);

    return to_string(compiler_) + to_string(n_);
  }

  boost::filesystem::path stub(compiler_stub::compiler_type compiler_,
                               compiler_stub::compiler_id n_,
                               bool dir_only_)
  {
    const auto filename = compiler_filename(compiler_, n_);
    const boost::filesystem::path dir = temp_dir / filename;
    return dir_only_ ? dir : dir / binary(filename);
  }
}

namespace mbuild_test
{
  output_t run_mbuild(std::vector<std::string> args_)
  {
    std::vector<std::string> args{
        mbuild_binary.string(), "--no_hardcoded_dirs"};
    args.insert(args.end(), args_.begin(), args_.end());
    const auto out = just::process::run(args, "");
    return {out.standard_output(), out.standard_error()};
  }

  void init(const boost::filesystem::path& test_binary_,
            const boost::filesystem::path& mbuild_binary_,
            const boost::filesystem::path& temp_dir_)
  {
    mbuild_binary = mbuild_binary_;
    temp_dir = temp_dir_;

    const auto bin = test_binary_.parent_path();

    for (const auto compiler : compiler_stub::all_types())
    {
      for (int n = 0; n < max_compiler_number; ++n)
      {
        compiler_stub::compiler_id id(n);

        create_directories(stub(compiler, id, true));
        copy_file(bin / binary(to_string(compiler) + "_stub"),
                  stub(compiler, id, false));
      }
    }
  }

  boost::filesystem::path gcc_stub(compiler_stub::compiler_id n_,
                                   bool dir_only_)
  {
    return stub(compiler_stub::compiler_type::gcc, n_, dir_only_);
  }

  boost::filesystem::path clang_stub(compiler_stub::compiler_id n_,
                                     bool dir_only_)
  {
    return stub(compiler_stub::compiler_type::clang, n_, dir_only_);
  }
}
