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

#include <mbuild/compiler.hpp>

namespace mbuild
{
  std::string display_name(const compiler& compiler_)
  {
    return compiler_.name + " " + version_of(compiler_);
  }

  std::string version_of(const compiler& compiler_)
  {
    return compiler_.has_templight ? compiler_.version + " with Templight" :
                                     compiler_.version;
  }

  bool operator<(const compiler& a_, const compiler& b_)
  {
    return display_name(a_) < display_name(b_);
  }

  bool operator==(const compiler& a_, const compiler& b_)
  {
    return display_name(a_) == display_name(b_);
  }
}
