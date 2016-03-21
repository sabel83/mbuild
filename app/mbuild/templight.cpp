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

#include <mbuild/templight.hpp>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>

#include <just/process.hpp>

#include <templight/ProtobufReader.h>

#include <fstream>

namespace
{
  boost::optional<boost::filesystem::path>
  a_pbf_file_in(const boost::filesystem::path& dir_)
  {
    for (boost::filesystem::directory_iterator i(dir_), e; i != e; ++i)
    {
      if (boost::algorithm::ends_with(i->path().string(), ".pbf"))
      {
        return i->path();
      }
    }
    return boost::none;
  }

  bool is_memoization(int instantiation_kind_)
  {
    return instantiation_kind_ == 8;
  }

  long int
  number_of_template_instantiations(const boost::filesystem::path& trace_)
  {
    long int counter = 0;

    std::ifstream f(trace_.string().c_str());

    templight::ProtobufReader reader;
    for (reader.startOnBuffer(f);
         reader.LastChunk != templight::ProtobufReader::EndOfFile;
         reader.next())
    {
      switch (reader.LastChunk)
      {
      case templight::ProtobufReader::BeginEntry:
        if (!is_memoization(reader.LastBeginEntry.InstantiationKind))
        {
          ++counter;
        }
        break;
      case templight::ProtobufReader::EndEntry:
      case templight::ProtobufReader::EndOfFile:
      case templight::ProtobufReader::Other:
      case templight::ProtobufReader::Header:
      default:
        break;
      }
    }
    return counter;
  }
}

namespace mbuild
{
  boost::optional<long int>
  template_instantiations(mbuild::measurement::parameters parameters_,
                          const boost::filesystem::path& tmp_,
                          std::vector<std::string> extra_compiler_args_)
  {
    if (parameters_.compiler_info.has_templight)
    {
      extra_compiler_args_.reserve(extra_compiler_args_.size() + 2);
      extra_compiler_args_.push_back("-Xtemplight");
      extra_compiler_args_.push_back("-profiler");

      parameters_.source_file = canonical(parameters_.source_file);

      just::process::run(
          compile_command(parameters_, tmp_, extra_compiler_args_), "",
          tmp_.string());

      if (const auto trace_path = a_pbf_file_in(tmp_))
      {
        return number_of_template_instantiations(*trace_path);
      }
    }
    return boost::none;
  }
}
