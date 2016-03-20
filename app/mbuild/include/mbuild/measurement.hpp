#ifndef MBUILD_MEASUREMENT_HPP
#define MBUILD_MEASUREMENT_HPP

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

#include <mbuild/compiler.hpp>
#include <mbuild/optimisation.hpp>

#include <boost/filesystem/path.hpp>

#include <iosfwd>

namespace mbuild
{
  struct measurement
  {
    struct parameters
    {
      boost::filesystem::path source_file;
      compiler compiler_info;
      optimisation opt;
    };

    struct result
    {
      bool compiles;
      std::string standard_output;
      std::string standard_error;

      double user_time;
      long memory;
    };
  };

  std::string to_json(const measurement::parameters& parameters_,
                      const measurement::result& result_);
}

#endif
