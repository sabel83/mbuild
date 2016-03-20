#ifndef MBUILD_COMPILER_QUERY_HPP
#define MBUILD_COMPILER_QUERY_HPP

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

#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>

#include <functional>

namespace mbuild
{
  typedef std::function<boost::optional<compiler>(
      const boost::filesystem::path&)> compiler_query;
}

#endif
