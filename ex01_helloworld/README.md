
## Guide to build and run binding library(5 steps)
1. Download and Build Boost library by **Visual studio developer cmd** by this commend:
```commandline
bootstramp
.\b2 --with-python --user-config=user-config.jam --toolset=msvc-12.0 --build-type=complete architecture=x86 address-model=64 link=shared
```

2. Create a C library akind:
```cpp
#include <boost/python.hpp>
#include <string>

/**
 * Print greeting
 * 
 * Args:
 *  name: str, name that receives greeting
*/
std::string greet(std::string name)
{
  return std::string("Hello, ") + name;
}

// ! This MODULE must have the exactly same name as defined in CMakeLists.txt
BOOST_PYTHON_MODULE(hello_ext)
{
  using namespace boost::python;
  def("greet", greet);
}
```

3. Create CMakeLists.txt to config building library:
```cmake
cmake_minimum_required(VERSION 3.13)

set(BOOST_ROOT "E:/WORKSPACES/boost_1_68_0")

project(HelloExtension)
# Set the module name(this name must exactly same the name defined in the C source)
set(MODULE_NAME hello_ext)
# Set the source C file of the module
set(SOURCE hello_ext.cpp)

# Set version of library
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)

# Find default python libraries and interpreter
find_package(Boost REQUIRED)
find_package(PythonInterp 3 REQUIRED)
find_package(PythonLibs 3 REQUIRED)

include_directories(${Boost_INCLUDE_DIR} ${PYTHON_INCLUDE_DIRS})
SET(Boost_USE_STATIC_LIBS     OFF)
SET(Boost_USE_MULTITHREADED    ON)
SET(Boost_USE_STATIC_RUNTIME     OFF)
find_package(Boost 1.68 REQUIRED COMPONENTS python36)

# Check whether find enough libraries
message(STATUS "PYTHON_LIBRARIES = ${PYTHON_LIBRARIES}")
message(STATUS "PYTHON_EXECUTABLE = ${PYTHON_EXECUTABLE}")
message(STATUS "PYTHON_INCLUDE_DIRS = ${PYTHON_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}")

# Build and link the C module(here is hello_ext)
add_library(${MODULE_NAME} MODULE ${SOURCE})
set_target_properties(${MODULE_NAME} PROPERTIES SUFFIX .pyd)
target_link_libraries(${MODULE_NAME} ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
```

4. Build by CMake Tool of VSCode, with mode is Release(not Debug; choose by >CMake ...variant)

    This process will create lib of *.pyd(in Windows) *.so(Linux). These files are directly imported by python programs like normal python libraries.

5. Using: to use built lib, you MUST do 2 steps:
   - Copy `boost_python.dll` to your running folder(smt akind: `boost_python36-vc120-mt-x64-1_68.dll`)
   - Then import and call like normal python library.
>!Notice: when you import lib to python program, you still can not see docstring of the functions.
To see the docstring of functions also, copy the `boost_python.dll` to the folder of built lib too.

# ============================
### A litte changing to bind existed libs easier:
> this idea is from [Source](https://feralchicken.wordpress.com/2013/12/07/boost-python-hello-world-example-using-cmake/)

from existed C++ lib
```cpp
// greet.h
#ifndef GREET_H
#define GREET_H
char const* greet( );
#endif // GREET_H
```

```cpp
// greet.cpp
#include "greet.h";
 
char const* greet( )
{
    return "Hello world";
}
```

Just add one wrapper that calling funcs of previous lib
```cpp
// greet_ext
#include "greet.h";
#include <boost/python.hpp>;
 
BOOST_PYTHON_MODULE(greet_ext)
{
    using namespace boost::python;
    def( "greet", greet );
}
```

And at the CMakeLists, just change a litte the final step to build lib and wrapper.
```cmake
...
# Build and link the C module(here is hello_ext)
# Build our library
add_library(greet SHARED greet.cpp)
# Define the wrapper library that wraps our library
add_library(greet_ext SHARED greet_ext.cpp)

target_link_libraries(greet_ext ${Boost_LIBRARIES} greet) # don't prepend wrapper library name with lib
set_target_properties(greet_ext PROPERTIES PREFIX "")
```

## Good samples:
https://github.com/TNG/boost-python-examples/blob/master/CMakeLists.txt

and

https://www.boost.org/doc/libs/1_63_0/libs/python/doc/html/tutorial/tutorial/exposing.html