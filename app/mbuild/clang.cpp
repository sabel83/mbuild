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

#include <mbuild/gcc.hpp>
#include <mbuild/clang_or_gcc_version.hpp>

#include <just/process.hpp>

#include <boost/filesystem.hpp>

#include <vector>
#include <fstream>
#include <cassert>

namespace
{
  bool has_templight(const boost::filesystem::path& clang_,
                     const boost::filesystem::path& tmp_dir_)
  {
    const boost::filesystem::path src_file = tmp_dir_ / "test.cpp";

    {
      std::ofstream f(src_file.c_str());
      f << "template <class T> struct t {}; t<int> x;\n";
    }

    just::process::run(std::vector<std::string>{clang_.string(), "-Xtemplight",
                                                "-profiler", "-c", "test.cpp"},
                       "", tmp_dir_.string());

    return exists(tmp_dir_ / "test.o.trace.pbf");
  }

  bool templight_of_metashell(const boost::filesystem::path& binary_)
  {
    return binary_.filename() == "templight_metashell";
  }

  boost::filesystem::path
  clang_headers_of_templight_metashell(const boost::filesystem::path& binary_)
  {
    assert(templight_of_metashell(binary_));
    return binary_.parent_path().parent_path() / "include/metashell/templight";
  }
}

namespace mbuild
{
  boost::optional<compiler> clang_info(const boost::filesystem::path& binary_,
                                       const boost::filesystem::path& tmp_dir_)
  {
    if (const auto ver =
            clang_or_gcc_version(binary_, "clang", {"clang", "templight"}))
    {
      compiler info;
      info.name = "clang";
      info.binary = binary_;
      info.version = *ver;
      info.optimisations = {optimisation({}), optimisation({"-O1"}),
                            optimisation({"-O2"}), optimisation({"-O3"}),
                            optimisation({"-Os"})};
      info.has_templight = has_templight(binary_, tmp_dir_);

      if (templight_of_metashell(binary_))
      {
        info.extra_arguments.push_back(
            "-I" + clang_headers_of_templight_metashell(binary_).string());
      }

      return info;
    }
    return boost::none;
  }
}
