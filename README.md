# MBuild

A utility that helps doing C++ compilation-related measurements. It detects the
compilers available on the system and compiles the code using them. It outputs
the results in a JSON document.

## Supported platforms

It is tested on Ubuntu.

## Compilation

The utility is implemented in C++. It can be compiled using the `build.sh`
script.

## Usage

The `mbuild` binary detects compilers installed on the system and can compile
one or more source files using them. The output is a JSON document, containing
all the measurement results.

### Compiler detection

The utility detect the compilers the following way:

* It checks the entries of the `PATH` environment variable.
* It checks the following directories as well: `/bin`, `/usr/bin`,
  `/usr/local/bin`, `$HOME/bin`

It checks the following binaries in the above directories:

* `clang*`: checks if they are Clang compilers
* `gcc*`, `g++*`: check is they are GCC compilers

To see which compilers were found by the utility, run `mbuil --compilers`

### Running the measurements

The files to compile can be provided as positional arguments. More files can be
provided and all of them will be measured using all compilers. For example:
`mbuild test.cpp other_test.cpp`

### Output format

The output format is a JSON document. It is displayed on standard output and
can be redirected. The JSON document contains a list of objects. Each object
represents one measurement. It has the following fields:

* `filename`: the name of the source file. For example: `"test.cpp"`
* `compiler name`: the name of the compiler measured. For example: `"gcc"`
* `compiler version`: the version of the compiler. For example: `"5.3.0"`
* `optimisation`: the optimisation level used for the compilation. It is a
  string, its values are compiler-dependent.
* `compiles`: was the compilation successful? For example: `true`.
* `stdout`: the standard output of the compiler.
* `stderr`: the standard error of the compiler.
* `user_time`: the number of seconds (user time output of the `time` command),
  the compilation took. For example: `1.234`. Note that this is present for
  successful compilations only.
* `memory`: the maximum memory consumption of the compiler (in Kb). For example:
  `12345`. Note that this is present for successful compilations only.

## License

Metashell is published under the
[GNU General Public License, version 3](http://www.gnu.org/licenses/gpl.html).
