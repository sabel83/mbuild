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

#include <boost/optional.hpp>

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

  template <class Writer, class T>
  void display(Writer& writer_,
               const std::string& key_,
               const boost::optional<T>& value_)
  {
    if (value_)
    {
      display(writer_, key_, *value_);
    }
  }

  template <class Writer>
  void display(Writer& writer_, const mbuild::compiler& compiler_)
  {
    display(writer_, "compiler name", compiler_.name);
    display(writer_, "compiler version", version_of(compiler_));
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
      display(
          writer_, "template instantiations", result_.template_instantiations);
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

  template <class V>
  void append_to(std::vector<std::string>& a_, const V& b_)
  {
    a_.insert(a_.end(), b_.begin(), b_.end());
  }

  std::vector<std::string>
  compile_command(std::vector<std::string> prefix_,
                  const measurement::parameters& parameters_,
                  const boost::filesystem::path& tmp_,
                  const std::vector<std::string>& extra_compiler_args_)
  {
    prefix_.reserve(prefix_.size() +
                    parameters_.compiler_info.extra_arguments.size() +
                    parameters_.opt.size() + extra_compiler_args_.size() + 5);
    prefix_.push_back(parameters_.compiler_info.binary.string());
    append_to(prefix_, parameters_.compiler_info.extra_arguments);
    append_to(prefix_, parameters_.opt);
    prefix_.push_back("-c");
    prefix_.push_back("-o");
    prefix_.push_back((tmp_ / "test.o").string());
    prefix_.push_back(parameters_.source_file.string());
    append_to(prefix_, extra_compiler_args_);
    return prefix_;
  }
}
