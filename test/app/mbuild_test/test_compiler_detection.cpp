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

JUST_TEST_CASE(test_no_compilers_are_found_with_empty_path)
{
  JUST_ASSERT_EQUAL("", run_mbuild({"--compilers"}).std_out);
}

JUST_TEST_CASE(test_path_entries_are_checked)
{
  const compiler_stub::compiler_id id0(0);
  mbuild_test::path_override p({mbuild_test::gcc_stub(id0)});

  compiler_stub::control control0(compiler_stub::compiler_type::gcc, id0);
  control0.version("4.8.0");

  JUST_ASSERT_EQUAL(
      "gcc 4.8.0 (\"" + mbuild_test::gcc_stub(id0, false).string() + "\")\n",
      run_mbuild({"--compilers"}).std_out);
}

JUST_TEST_CASE(test_multiple_path_entries)
{
  const compiler_stub::compiler_id id0(0);
  const compiler_stub::compiler_id id1(1);
  mbuild_test::path_override p(
      {mbuild_test::gcc_stub(id0), mbuild_test::gcc_stub(id1)});

  compiler_stub::control control0(compiler_stub::compiler_type::gcc, id0);
  control0.version("4.8.0");

  compiler_stub::control control1(compiler_stub::compiler_type::gcc, id1);
  control1.version("4.9.2");

  JUST_ASSERT_EQUAL("gcc 4.8.0 (\"" +
                        mbuild_test::gcc_stub(id0, false).string() +
                        "\")\n"
                        "gcc 4.9.2 (\"" +
                        mbuild_test::gcc_stub(id1, false).string() + "\")\n",
                    run_mbuild({"--compilers"}).std_out);
}

JUST_TEST_CASE(test_finding_clang_compiler)
{
  const compiler_stub::compiler_id id0(0);
  mbuild_test::path_override p({mbuild_test::clang_stub(id0)});

  compiler_stub::control control0(compiler_stub::compiler_type::clang, id0);
  control0.version("3.5.0");

  JUST_ASSERT_EQUAL("clang 3.5.0 (\"" +
                        mbuild_test::clang_stub(id0, false).string() + "\")\n",
                    run_mbuild({"--compilers"}).std_out);
}

JUST_TEST_CASE(test_finding_clang_with_templight)
{
  const compiler_stub::compiler_id id0(0);
  mbuild_test::path_override p({mbuild_test::clang_stub(id0)});

  compiler_stub::control control0(compiler_stub::compiler_type::clang, id0);
  control0.version("3.5.0");
  control0.templight(true);

  JUST_ASSERT_EQUAL("clang 3.5.0 with Templight (\"" +
                        mbuild_test::clang_stub(id0, false).string() + "\")\n",
                    run_mbuild({"--compilers"}).std_out);
}
