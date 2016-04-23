#ifndef COMPILER_STUB_ENV_VAR_OVERRIDE_HPP
#define COMPILER_STUB_ENV_VAR_OVERRIDE_HPP

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

#include <boost/noncopyable.hpp>

#include <string>

namespace compiler_stub
{
  class env_var_override : boost::noncopyable
  {
  public:
    env_var_override(const std::string& name_, const std::string& value_);
    ~env_var_override();

  private:
    std::string _name;
    std::string _old_value;
  };
}

#endif
