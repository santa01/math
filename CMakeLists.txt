#
# Copyright (c) 2013 Pavlo Lavrenenko
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

cmake_minimum_required (VERSION 2.8.9)
project (MATH)

if (CMAKE_COMPILER_IS_GNUCC)
    execute_process (COMMAND ${CMAKE_CXX_COMPILER} -dumpversion
                     OUTPUT_VARIABLE GCC_VERSION)
    string (STRIP ${GCC_VERSION} GCC_VERSION)
endif ()

if (DEFINED GCC_VERSION AND GCC_VERSION VERSION_GREATER 4.7.0)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=gnu++11")
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
    set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    set (CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} -Os")
    set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -g -O3")
else ()
    message (FATAL_ERROR "GCC 4.7.0 or higher is required!")
endif ()

file (GLOB_RECURSE MATH_SOURCES src/*.cpp)
file (GLOB_RECURSE MATH_HEADERS src/*.h)
include_directories (src)

set (MATH_NAME Math)
set (MATH_DESCRIPTION "Discrete math library")
set (MATH_VERSION 0.1.6)

set (MATH_LIBRARY math)
set (MATH_STATIC ${MATH_LIBRARY}-static)
set (MATH_SHARED ${MATH_LIBRARY}-shared)
set (MATH_DOCS OFF CACHE BOOL "Build HTML documentation")

configure_file (math.pc.in math.pc @ONLY)
install (FILES ${PROJECT_BINARY_DIR}/math.pc DESTINATION lib/pkgconfig)

if (MATH_DOCS)
    find_package (Doxygen)
    if (DOXYGEN_FOUND)
        configure_file (Doxyfile.in Doxyfile @ONLY)
        install (DIRECTORY ${PROJECT_BINARY_DIR}/html
                 DESTINATION share/doc/${MATH_LIBRARY}-${MATH_VERSION})
        add_custom_target (doxygen ALL doxygen)
    else ()
        message(FATAL_ERROR "Failed to locate doxygen!")
    endif ()
endif ()

add_library (${MATH_LIBRARY} OBJECT ${MATH_SOURCES})
add_library (${MATH_STATIC} STATIC $<TARGET_OBJECTS:${MATH_LIBRARY}>)
add_library (${MATH_SHARED} SHARED $<TARGET_OBJECTS:${MATH_LIBRARY}>)

# Required to reuse OBJECT for SHARED target, cmake version 2.8.9
set_property (TARGET ${MATH_LIBRARY} PROPERTY POSITION_INDEPENDENT_CODE 1)
set_target_properties (${MATH_STATIC} ${MATH_SHARED} PROPERTIES
                       OUTPUT_NAME ${MATH_LIBRARY})
set_target_properties (${MATH_SHARED} PROPERTIES
                       VERSION ${MATH_VERSION} SOVERSION ${MATH_VERSION})

install (TARGETS ${MATH_STATIC} ${MATH_SHARED} DESTINATION lib)
install (FILES ${MATH_HEADERS} DESTINATION include/${MATH_LIBRARY})
