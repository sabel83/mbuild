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

#include <mbuild/discovery.hpp>

#include <just/environment.hpp>

#include <boost/algorithm/string/split.hpp>
#include <boost/filesystem.hpp>

#include <stdexcept>

namespace
{
  void search_for_compilers_in(
      const boost::filesystem::path& path_,
      const std::vector<mbuild::compiler_query>& query_functors_,
      std::set<mbuild::compiler>& out_,
      const std::vector<boost::filesystem::path>& blacklist_)
  {
    if (is_directory(path_))
    {
      typedef boost::filesystem::directory_iterator di;
      for (di i(path_), e; i != e; ++i)
      {
        if (std::find(blacklist_.begin(), blacklist_.end(), i->path()) ==
            blacklist_.end())
        {
          for (const auto& f : query_functors_)
          {
            if (const auto info = f(i->path()))
            {
              out_.insert(*info);
            }
          }
        }
      }
    }
  }

  bool is_path_separator(char c_) { return c_ == ':'; }

  template <class Container>
  void populate_with_path(Container& out_)
  {
    const std::string path = just::environment::get("PATH");
    boost::algorithm::split(out_, path, is_path_separator);
  }

  std::set<std::string>
  dirs_to_visit_for_compilers(bool hardcoded_dirs_enabled_)
  {
    std::set<std::string> dirs;

    if (hardcoded_dirs_enabled_)
    {
      dirs.insert("/bin");
      dirs.insert("/usr/bin");
      dirs.insert("/usr/local/bin");
      dirs.insert(
          (boost::filesystem::path(just::environment::get("HOME")) / "bin")
              .string());
    }

    populate_with_path(dirs);

    return dirs;
  }
}

namespace mbuild
{
  std::set<compiler>
  discover_compilers(const std::vector<compiler_query>& query_functors,
                     bool hardcoded_dirs_enabled_,
                     const std::vector<boost::filesystem::path>& blacklist_)
  {
    std::set<compiler> result;

    const auto dirs = dirs_to_visit_for_compilers(hardcoded_dirs_enabled_);
    for (const auto& dir : dirs)
    {
      search_for_compilers_in(dir, query_functors, result, blacklist_);
    }

    return result;
  }

  boost::filesystem::path find_time_command()
  {
    std::vector<boost::filesystem::path> path;
    populate_with_path(path);

    for (const auto& dir : path)
    {
      const boost::filesystem::path time = dir / "time";
      if (exists(time))
      {
        return time;
      }
    }

    throw std::runtime_error("time command not found");
  }
}
