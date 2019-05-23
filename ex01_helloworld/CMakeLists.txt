cmake_minimum_required(VERSION 3.13)

set(BOOST_ROOT "E:/WORKSPACES/boost_1_68_0")

project(hello_ext)
# Set the module name(this name must exactly same the name defined in the C source)
set(MODULE_NAME hello_ext)
# Set the source C file of the module
set(SOURCE hello_ext.cpp)

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