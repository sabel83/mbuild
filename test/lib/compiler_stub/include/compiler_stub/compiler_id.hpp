#ifndef COMPILER_STUB_COMPILER_ID_HPP
#define COMPILER_STUB_COMPILER_ID_HPP

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

#include <boost/filesystem/path.hpp>

#include <string>

namespace compiler_stub
{
  class compiler_id
  {
  public:
    compiler_id(compiler_type compiler_,
                const boost::filesystem::path& binary_);
    explicit compiler_id(int n_);

    int value() const;

  private:
    int _id;
  };

  std::string to_string(compiler_id id_);
}

#endif
