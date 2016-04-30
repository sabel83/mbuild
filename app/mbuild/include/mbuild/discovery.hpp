#ifndef MBUILD_DISCOVERY_HPP
#define MBUILD_DISCOVERY_HPP

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

#include <mbuild/compiler_query.hpp>

#include <boost/filesystem/path.hpp>

#include <vector>
#include <set>

namespace mbuild
{
  std::set<compiler>
  discover_compilers(const std::vector<compiler_query>& query_functors,
                     bool hardcoded_dirs_enabled_,
                     const std::vector<boost::filesystem::path>& blacklist_);

  boost::filesystem::path find_time_command();
}

#endif
