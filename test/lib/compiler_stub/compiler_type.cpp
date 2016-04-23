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

#include <compiler_stub/compiler_type.hpp>

#include <boost/algorithm/string/predicate.hpp>

#include <stdexcept>
#include <cassert>
#include <algorithm>

namespace compiler_stub
{
  bool in_all_types(compiler_type type_)
  {
    const auto all = all_types();
    return std::find(all.begin(), all.end(), type_) != all.end();
  }

  std::string to_string(compiler_type type_)
  {
    assert(in_all_types(type_));

    switch (type_)
    {
    case compiler_type::gcc:
      return "gcc";
    case compiler_type::clang:
      return "clang";
    default:
      throw std::runtime_error("Invalid compiler type");
    }
  }

  compiler_type
  compiler_type_from_filename(const boost::filesystem::path& binary_)
  {
    const std::string filename = binary_.filename().string();

    for (const auto type : all_types())
    {
      if (boost::algorithm::starts_with(filename, to_string(type)))
      {
        return type;
      }
    }
    throw std::runtime_error("Invalid filename: " + filename);
  }

  std::vector<compiler_type> all_types()
  {
    return {compiler_type::gcc, compiler_type::clang};
  }
}
