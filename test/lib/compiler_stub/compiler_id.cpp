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

#include <compiler_stub/compiler_id.hpp>

#include <boost/algorithm/string/predicate.hpp>

#include <stdexcept>

namespace compiler_stub
{
  compiler_id::compiler_id(int n_) : _id(n_) {}

  compiler_id::compiler_id(compiler_type compiler_,
                           const boost::filesystem::path& binary_)
  {
    const std::string filename = binary_.filename().string();
    const std::string prefix = compiler_stub::to_string(compiler_);
    if (boost::algorithm::starts_with(filename, prefix))
    {
      const auto id = filename.substr(prefix.size());
      _id = id == "_stub" ? 0 : stoi(filename.substr(prefix.size()));
    }
    else
    {
      throw std::runtime_error("Invalid binary name: " + filename);
    }
  }

  int compiler_id::value() const { return _id; }

  std::string to_string(compiler_id id_) { return std::to_string(id_.value()); }
}
