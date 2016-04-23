#ifndef MBUILD_TEST_MBUILD_HPP
#define MBUILD_TEST_MBUILD_HPP

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

#include <mbuild_test/output_t.hpp>

#include <compiler_stub/compiler_id.hpp>

#include <boost/filesystem/path.hpp>

#include <string>
#include <vector>

namespace mbuild_test
{
  output_t run_mbuild(std::vector<std::string> args_);

  void init(const boost::filesystem::path& test_binary_,
            const boost::filesystem::path& mbuild_binary_,
            const boost::filesystem::path& temp_dir_);

  boost::filesystem::path gcc_stub(compiler_stub::compiler_id id_,
                                   bool dir_only_ = true);
  boost::filesystem::path clang_stub(compiler_stub::compiler_id id_,
                                     bool dir_only_ = true);
}

#endif
