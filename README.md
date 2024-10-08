# Hobby C++ project to explore CI
- created from ModernCppStarter https://github.com/TheLartians/ModernCppStarter

## Features

- hello world

git@github.com:Claude-Mally-cpp/testRepo

-[![Actions Status](https://github.com/Claude-Mally-cpp/testRepo/workflows/MacOS/badge.svg)](https://github.com/Claude-Mally-cpp/testRepo/actions)
-[![Actions Status](https://github.com/Claude-Mally-cpp/testRepo/workflows/Windows/badge.svg)](https://github.com/Claude-Mally-cpp/testRepo/actions)
-[![Actions Status](https://github.com/Claude-Mally-cpp/testRepo/workflows/Ubuntu/badge.svg)](https://github.com/Claude-Mally-cpp/testRepo/actions)
-[![Actions Status](https://github.com/Claude-Mally-cpp/testRepo/workflows/Style/badge.svg)](https://github.com/Claude-Mally-cpp/testRepo/actions)
-[![Actions Status](https://github.com/Claude-Mally-cpp/testRepo/workflows/Install/badge.svg)](https://github.com/Claude-Mally-cpp/testRepo/actions)
-[![codecov](https://codecov.io/gh/Claude-Mally-cpp/testRepo/branch/master/graph/badge.svg)](https://codecov.io/gh/Claude-Mally-cpp/testRepo)

-<p align="center">
-  <img src="https://repository-images.githubusercontent.com/254842585/4dfa7580-7ffb-11ea-99d0-46b8fe2f4170" height="175" width="auto" />
-</p>
-
-# ModernCppStarter
## Usage

### Build and run the standalone target

Use the following command to build and run the executable target.

```bash
cmake -S standalone -B build/standalone -DUSE_STATIC_ANALYZER="clang-tidy|cppcheck"
cmake --build build/standalone
./build/standalone/Hobby -d 144
```

Or

```bash
./buildProject.sh
./runProject.sh
```

### Build and run test suite

Use the following commands from the project's root directory to run the test suite.
```bash
cmake -S test -B build/test -DUSE_STATIC_ANALYZER="clang-tidy|cppcheck"
cmake --build build/test
CTEST_OUTPUT_ON_FAILURE=1 cmake --build build/test --target test

# or simply call the executable: 
./build/test/HobbyTests
```

Or

```bash
./buildAndRunTests.sh
```

To collect code coverage information, run CMake with the `-DENABLE_TEST_COVERAGE=1` option.

### Run clang-format

Use the following commands from the project's root directory to check and fix C++ and CMake source style.
This requires _clang-format_, _cmake-format_ and _pyyaml_ to be installed on the current system.

```bash
./formatProject.sh
```

### Build the documentation

The documentation is automatically built and [published](https://thelartians.github.io/ModernCppStarter) whenever a [GitHub Release](https://help.github.com/en/github/administering-a-repository/managing-releases-in-a-repository) is created.
To manually build documentation, call the following command.

```bash
cmake -S documentation -B build/doc
cmake --build build/doc --target GenerateDocs
# view the docs
open build/doc/doxygen/html/index.html
```

To build the documentation locally, you will need Doxygen, jinja2 and Pygments installed on your system.

### Build everything at once

The project also includes an `all` directory that allows building all targets at the same time.
This is useful during development, as it exposes all subprojects to your IDE and avoids redundant builds of the library.

```bash
cmake -S all -B build
cmake --build build

# run tests
./build/test/HobbyTests
# format code
cmake --build build --target fix-format
# run standalone
./build/standalone/Hobby --help
# build docs
cmake --build build --target GenerateDocs
```

### Additional tools

The test and standalone subprojects include the [tools.cmake](cmake/tools.cmake) file which is used to import additional tools on-demand through CMake configuration arguments.
The following are currently supported.

#### Sanitizers

Sanitizers can be enabled by configuring CMake with `-DUSE_SANITIZER=<Address | Memory | MemoryWithOrigins | Undefined | Thread | Leak | 'Address;Undefined'>`.

#### Static Analyzers

Static Analyzers can be enabled by setting `-DUSE_STATIC_ANALYZER=<clang-tidy | iwyu | cppcheck>`, or a combination of those in quotation marks, separated by semicolons.
By default, analyzers will automatically find configuration files such as `.clang-format`.
Additional arguments can be passed to the analyzers by setting the `CLANG_TIDY_ARGS`, `IWYU_ARGS` or `CPPCHECK_ARGS` variables.

#### Ccache

Ccache can be enabled by configuring with `-DUSE_CCACHE=<ON | OFF>`.

## FAQ

> Can I use this for header-only libraries?

Yes, however you will need to change the library type to an `INTERFACE` library as documented in the [CMakeLists.txt](CMakeLists.txt).
See [here](https://github.com/TheLartians/StaticTypeInfo) for an example header-only library based on the template.

> I don't need a standalone target / documentation. How can I get rid of it?

Simply remove the standalone / documentation directory and according github workflow file.

> Can I build the standalone and tests at the same time? / How can I tell my IDE about all subprojects?

To keep the template modular, all subprojects derived from the library have been separated into their own CMake modules.
This approach makes it trivial for third-party projects to re-use the projects library code.
To allow IDEs to see the full scope of the project, the template includes the `all` directory that will create a single build for all subprojects.
Use this as the main directory for best IDE support.

> I see you are using `GLOB` to add source files in CMakeLists.txt. Isn't that evil?

Glob is considered bad because any changes to the source file structure [might not be automatically caught](https://cmake.org/cmake/help/latest/command/file.html#filesystem) by CMake's builders and you will need to manually invoke CMake on changes.
  I personally prefer the `GLOB` solution for its simplicity, but feel free to change it to explicitly listing sources.

> I want create additional targets that depend on my library. Should I modify the main CMakeLists to include them?

Avoid including derived projects from the libraries CMakeLists (even though it is a common sight in the C++ world), as this effectively inverts the dependency tree and makes the build system hard to reason about.
Instead, create a new directory or project with a CMakeLists that adds the library as a dependency (e.g. like the [standalone](standalone/CMakeLists.txt) directory).
Depending type it might make sense move these components into a separate repositories and reference a specific commit or version of the library.
This has the advantage that individual libraries and components can be improved and updated independently.

> You recommend to add external dependencies using CPM.cmake. Will this force users of my library to use CPM.cmake as well?

[CPM.cmake](https://github.com/TheLartians/CPM.cmake) should be invisible to library users as it's a self-contained CMake Script.
If problems do arise, users can always opt-out by defining the CMake or env variable [`CPM_USE_LOCAL_PACKAGES`](https://github.com/cpm-cmake/CPM.cmake#options), which will override all calls to `CPMAddPackage` with the according `find_package` call.
This should also enable users to use the project with their favorite external C++ dependency manager, such as vcpkg or Conan.

> Can I configure and build my project offline?

No internet connection is required for building the project, however when using CPM missing dependencies are downloaded at configure time.
To avoid redundant downloads, it's highly recommended to set a CPM.cmake cache directory, e.g.: `export CPM_SOURCE_CACHE=$HOME/.cache/CPM`.
This will enable shallow clones and allow offline configurations dependencies are already available in the cache.

> Can I use CPack to create a package installer for my project?

As there are a lot of possible options and configurations, this is not (yet) in the scope of this template. See the [CPack documentation](https://cmake.org/cmake/help/latest/module/CPack.html) for more information on setting up CPack installers.

> This is too much, I just want to play with C++ code and test some libraries.

Perhaps the [MiniCppStarter](https://github.com/TheLartians/MiniCppStarter) is something for you!

## Recommended usage

It is easier to develop code without warnings from scratch than to refactor it later. So initially the set of enabled warnings should be as extensive as possible. Specific warnings can be disabled later in the development process if it is decided that it makes sense for the project or if they trigger false positives.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments
* **[Craig Scott](https://crascit.com/)** - [Professional CMake](https://crascit.com/professional-cmake/)
* **[Jason Turner](https://github.com/lefticus)** - [C++ Best Practices](https://lefticus.gitbooks.io/cpp-best-practices/)
* **[Peter Kolbus](https://github.com/pkolbus)** - [Compiler Warnings](https://github.com/pkolbus/compiler-warnings)
* **[José Ángel Soler Ortiz](https://github.com/joseasoler)** -[cmake_compiler_warnings](https://github.com/joseasoler/cmake_cpp_warnings)

