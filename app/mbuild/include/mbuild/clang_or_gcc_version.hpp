#ifndef MBUILD_CLANG_OR_GCC_VERSION_HPP
#define MBUILD_CLANG_OR_GCC_VERSION_HPP

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

#include <boost/filesystem/path.hpp>
#include <boost/optional.hpp>

#include <vector>
#include <string>

namespace mbuild
{
  boost::optional<std::string>
  clang_or_gcc_version(const boost::filesystem::path& binary_,
                       const std::string& name_,
                       const std::vector<std::string>& filename_prefixes_);
}

#endif
