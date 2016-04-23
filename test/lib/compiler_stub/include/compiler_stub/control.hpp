#ifndef COMPILER_STUB_CONTROL_HPP
#define COMPILER_STUB_CONTROL_HPP

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
#include <compiler_stub/compiler_id.hpp>
#include <compiler_stub/env_var_override.hpp>

#include <boost/filesystem/path.hpp>

#include <string>
#include <memory>
#include <vector>

namespace compiler_stub
{
  class control
  {
  public:
    explicit control(const boost::filesystem::path& binary_);
    control(compiler_type type_, compiler_id id_);

    control& version(const std::string& version_);
    std::string version() const;

    control& templight(bool supported_);
    bool templight() const;

  private:
    compiler_type _type;
    compiler_id _id;

    std::vector<std::unique_ptr<env_var_override>> _overrides;

    std::string env_var_name(const std::string& name_) const;
    void set(const std::string& name_, const std::string& value_);
    std::string get(const std::string& name_) const;
  };
}

#endif
