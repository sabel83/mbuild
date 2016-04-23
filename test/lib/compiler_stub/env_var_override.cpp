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

#include <compiler_stub/env_var_override.hpp>

#include <just/environment.hpp>

namespace compiler_stub
{
  env_var_override::env_var_override(const std::string& name_,
                                     const std::string& value_)
    : _name(name_), _old_value(just::environment::get(name_))
  {
    just::environment::set(_name, value_);
  }

  env_var_override::~env_var_override()
  {
    just::environment::set(_name, _old_value);
  }
}
