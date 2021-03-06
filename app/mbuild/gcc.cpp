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

namespace mbuild
{
  boost::optional<compiler> gcc_info(const boost::filesystem::path& binary_)
  {
    if (const auto ver = clang_or_gcc_version(binary_, "gcc", {"gcc", "g++"}))
    {
      compiler info;
      info.name = "gcc";
      info.binary = binary_;
      info.version = *ver;
      info.optimisations = {optimisation({}), optimisation({"-O1"}),
                            optimisation({"-O2"}), optimisation({"-O3"}),
                            optimisation({"-Os"})};
      info.has_templight = false;

      return info;
    }
    return boost::none;
  }
}
