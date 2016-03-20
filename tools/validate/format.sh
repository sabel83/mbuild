#!/bin/bash
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

set -e

if [ ! -d cmake ]
then
  echo "Please run this script from the root directory of the MBuild source code"
  exit 1
fi

CLANG_FORMAT="$(tools/find/clang_format.sh)"

for f in $(tools/list/cpp_files.sh)
do
  ("${CLANG_FORMAT}" "${f}" | diff "${f}" -) || ( \
    echo "Invalid code formatting in ${f}. Please run tools/reformat.sh to fix it." \
    ; exit 1 \
  )
done
