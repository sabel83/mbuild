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

#include "arg_parser.hpp"

#include <string>
#include <stdexcept>

arg_parser::arg_parser(int argc_, const char* argv_[], bool templight_enabled_)
  : _argc(argc_),
    _argv(argv_),
    _files(),
    _use_templight(false),
    _display_version(false)
{
  for (int i = 1; i < _argc; ++i)
  {
    const std::string arg(_argv[i]);
    if (arg == "-v")
    {
      _display_version = true;
    }
    else if (arg == "-c")
    {
      // ignore
    }
    else if (templight_enabled_ && arg == "-Xtemplight")
    {
      const std::string val = value_of(i);
      if (val == "-profiler")
      {
        _use_templight = true;
      }
      else
      {
        throw std::runtime_error("Unknown Templight argument: " + arg);
      }
    }
    else if (!arg.empty() && arg[0] == '-')
    {
      throw std::runtime_error("Unknown argument: " + arg);
    }
    else
    {
      _files.push_back(arg);
    }
  }
}

std::string arg_parser::value_of(int& i_) const
{
  ++i_;
  if (i_ < _argc)
  {
    return _argv[i_];
  }
  else
  {
    throw std::runtime_error("Value of argument " + std::string(_argv[i_]) +
                             " is missing");
  }
}

const std::vector<boost::filesystem::path>& arg_parser::files() const
{
  return _files;
}

bool arg_parser::use_templight() const { return _use_templight; }

bool arg_parser::display_version() const { return _display_version; }
