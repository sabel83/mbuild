#ifndef COMPILER_STUB_ARG_PARSER_HPP
#define COMPILER_STUB_ARG_PARSER_HPP

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

#include <boost/filesystem/path.hpp>

#include <vector>

class arg_parser
{
public:
  arg_parser(int argc_, const char* argv_[], bool templight_enabled_);

  const std::vector<boost::filesystem::path>& files() const;
  bool use_templight() const;
  bool display_version() const;

private:
  int _argc;
  const char** _argv;

  std::vector<boost::filesystem::path> _files;
  bool _use_templight;
  bool _display_version;

  std::string value_of(int& i_) const;
};

#endif
