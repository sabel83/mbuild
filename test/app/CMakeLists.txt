# MBuild - compilation measurement tool
# Copyright (C) 2016, Abel Sinkovics (abel@sinkovics.hu)
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# mbuild_test

aux_source_directory(mbuild_test MBUILD_TEST_SOURCES)
add_executable(mbuild_test ${MBUILD_TEST_SOURCES})

target_include_directories(mbuild_test PRIVATE "mbuild_test/include")
target_include_directories(mbuild_test PRIVATE SYSTEM
  "${CMAKE_SOURCE_DIR}/test/lib/compiler_stub/include"
  "${CMAKE_SOURCE_DIR}/3rd/just_test/include"
  "${CMAKE_SOURCE_DIR}/3rd/just_process/include"
  "${CMAKE_SOURCE_DIR}/3rd/just_environment/include"
  "${CMAKE_SOURCE_DIR}/3rd/just_temp/include"
)

target_link_libraries(mbuild_test
  boost_system
  boost_filesystem
  boost_program_options
  compiler_stub
)

# stubs

aux_source_directory(compiler_stub COMPILER_STUB_SOURCES)

foreach(STUB gcc_stub clang_stub)
  add_executable(${STUB} ${COMPILER_STUB_SOURCES})
  
  target_include_directories(${STUB} PRIVATE SYSTEM
    "${CMAKE_SOURCE_DIR}/test/lib/compiler_stub/include"
    "${CMAKE_SOURCE_DIR}/3rd/just_environment/include"
  )
  
  target_link_libraries(${STUB}
    boost_system
    boost_filesystem
    boost_program_options
    compiler_stub
  )
endforeach(STUB)

enable_warnings()
use_cpp11()

