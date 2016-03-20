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

#include <mbuild/clang_or_gcc_version.hpp>

#include <just/process.hpp>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/filesystem.hpp>

#include <algorithm>
#include <stdexcept>

namespace
{
  bool filename_has_prefix(const boost::filesystem::path& binary_,
                           const std::vector<std::string>& prefixes_)
  {
    const auto filename = binary_.filename().string();
    return std::find_if(prefixes_.begin(), prefixes_.end(),
                        [&filename](const std::string& prefix_)
                        {
                          return boost::algorithm::starts_with(
                              filename, prefix_);
                        }) != prefixes_.end();
  }
}

namespace mbuild
{
  boost::optional<std::string>
  clang_or_gcc_version(const boost::filesystem::path& binary_,
                       const std::string& name_,
                       const std::vector<std::string>& filename_prefixes_)
  {
    if (filename_has_prefix(binary_, filename_prefixes_))
    {
      try
      {
        const auto ver =
            just::process::run(
                std::vector<std::string>{binary_.string(), "-v"}, "")
                .standard_error();

        const std::string prefix = name_ + " version ";
        const auto prefix_at = ver.find(prefix);
        if (prefix_at != std::string::npos)
        {
          const auto start = prefix_at + prefix.size();
          const auto end = ver.find('\n', start);

          return boost::algorithm::trim_copy(
              ver.substr(start, end == std::string::npos ? end : end - start));
        }
      }
      catch (const std::exception& e_)
      {
        // ignore
      }
    }
    return boost::none;
  }
}
