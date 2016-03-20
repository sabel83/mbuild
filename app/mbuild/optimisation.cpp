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

#include <mbuild/optimisation.hpp>

#include <boost/algorithm/string/join.hpp>

namespace mbuild
{
  optimisation::optimisation(std::vector<std::string> arguments_)
    : _arguments(move(arguments_))
  {
  }

  optimisation::iterator optimisation::begin() const
  {
    return _arguments.begin();
  }

  optimisation::iterator optimisation::end() const { return _arguments.end(); }

  std::string optimisation::name() const
  {
    return boost::algorithm::join(_arguments, " ");
  }

  size_t optimisation::size() const { return _arguments.size(); }
}
