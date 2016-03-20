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

#include <mbuild/measurement.hpp>

#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

#include <iostream>

namespace
{
  template <class Writer>
  void display(Writer& writer_, const std::string& s_)
  {
    writer_.String(s_.c_str(), s_.size());
  }

  template <class Writer>
  void
  display(Writer& writer_, const std::string& key_, const std::string& value_)
  {
    writer_.Key(key_.c_str());
    display(writer_, value_);
  }

  template <class Writer>
  void display(Writer& writer_, const std::string& key_, bool value_)
  {
    writer_.Key(key_.c_str());
    writer_.Bool(value_);
  }

  template <class Writer>
  void display(Writer& writer_, const std::string& key_, double value_)
  {
    writer_.Key(key_.c_str());
    writer_.Double(value_);
  }

  template <class Writer>
  void display(Writer& writer_, const std::string& key_, long value_)
  {
    writer_.Key(key_.c_str());
    writer_.Int64(value_);
  }

  template <class Writer>
  void display(Writer& writer_, const mbuild::compiler& compiler_)
  {
    display(writer_, "compiler name", compiler_.name);
    display(writer_, "compiler version", compiler_.version);
  }

  template <class Writer>
  void display(Writer& writer_,
               const mbuild::measurement::parameters& parameters_)
  {
    display(writer_, "filename", parameters_.source_file.string());
    display(writer_, parameters_.compiler_info);
    display(writer_, "optimisation", parameters_.opt.name());
  }

  template <class Writer>
  void display(Writer& writer_, const mbuild::measurement::result& result_)
  {
    display(writer_, "compiles", result_.compiles);
    display(writer_, "stdout", result_.standard_output);
    display(writer_, "stderr", result_.standard_error);
    if (result_.compiles)
    {
      display(writer_, "user_time", result_.user_time);
      display(writer_, "memory", result_.memory);
    }
  }
}

namespace mbuild
{
  std::string to_json(const measurement::parameters& parameters_,
                      const measurement::result& result_)
  {
    rapidjson::StringBuffer s;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);

    writer.StartObject();
    display(writer, parameters_);
    display(writer, result_);
    writer.EndObject();

    return s.GetString();
  }
}
