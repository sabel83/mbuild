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

#include <mbuild_test/mbuild.hpp>
#include <mbuild_test/path_override.hpp>

#include <compiler_stub/control.hpp>

#include <just/test.hpp>

using mbuild_test::run_mbuild;

JUST_TEST_CASE(test_blacklisting_a_compiler)
{
  const compiler_stub::compiler_id id0(0);
  const compiler_stub::compiler_id id1(1);
  mbuild_test::path_override p(
      {mbuild_test::clang_stub(id0), mbuild_test::clang_stub(id1)});

  compiler_stub::control control0(compiler_stub::compiler_type::clang, id0);
  control0.version("3.5.0");

  compiler_stub::control control1(compiler_stub::compiler_type::clang, id1);
  control1.version("3.6.0");

  const std::string path0 = mbuild_test::clang_stub(id0, false).string();
  const std::string path1 = mbuild_test::clang_stub(id1, false).string();

  JUST_ASSERT_EQUAL("clang 3.5.0 (\"" + path0 + "\")\n",
                    run_mbuild({"--compilers", "--blacklist", path1}).std_out);
}
