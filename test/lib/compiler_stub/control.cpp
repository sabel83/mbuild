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

#include <compiler_stub/control.hpp>

#include <just/environment.hpp>

namespace compiler_stub
{
  control::control(const boost::filesystem::path& binary_)
    : _type(compiler_type_from_filename(binary_)), _id(_type, binary_)
  {
  }

  control::control(compiler_type type_, compiler_id id_)
    : _type(type_), _id(id_)
  {
  }

  std::string control::env_var_name(const std::string& name_) const
  {
    return to_string(_type) + to_string(_id) + name_;
  }

  void control::set(const std::string& name_, const std::string& value_)
  {
    _overrides.push_back(std::unique_ptr<env_var_override>(
        new env_var_override(env_var_name(name_), value_)));
  }

  std::string control::get(const std::string& name_) const
  {
    return just::environment::get(env_var_name(name_));
  }

  control& control::version(const std::string& version_)
  {
    set("VERSION", version_);
    return *this;
  }

  std::string control::version() const { return get("VERSION"); }

  control& control::templight(bool supported_)
  {
    assert(_type == compiler_type::clang);

    set("TEMPLIGHT", supported_ ? "1" : "0");
    return *this;
  }

  bool control::templight() const { return get("TEMPLIGHT") == "1"; }
}
