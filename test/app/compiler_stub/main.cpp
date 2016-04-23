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

#include "arg_parser.hpp"

#include <compiler_stub/compiler_type.hpp>
#include <compiler_stub/control.hpp>

#include <boost/filesystem.hpp>

#include <just/environment.hpp>

#include <iostream>
#include <fstream>

namespace
{
  void write(const boost::filesystem::path& path_, const std::string& content_)
  {
    std::ofstream f(path_.c_str());
    f << content_;
  }

  void compile(const boost::filesystem::path& src_, bool use_templight_)
  {
    write(change_extension(src_, ".o"), "");
    if (use_templight_)
    {
      write(change_extension(src_, ".o.trace.pbf"), "");
    }
  }
}

int main(int argc_, const char* argv_[])
{
  const boost::filesystem::path binary(argv_[0]);
  const compiler_stub::compiler_type my_type =
      compiler_stub::compiler_type_from_filename(binary);
  const compiler_stub::control control(binary);

  try
  {
    const arg_parser args(argc_, argv_, control.templight());

    if (args.display_version())
    {
      std::cerr << to_string(my_type) << " version " << control.version()
                << std::endl;
    }
    else
    {
      for (const auto& filename : args.files())
      {
        compile(filename, args.use_templight());
      }
    }
  }
  catch (const std::exception& e_)
  {
    std::cerr << e_.what() << std::endl;
  }
}
