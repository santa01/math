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

cmake_minimum_required (VERSION 3.3)
project (MATH)

set (MATH_NAME Math)
set (MATH_DESCRIPTION "Discrete math library")
set (MATH_VERSION 0.1.7)

set (MATH_LIBRARY math)
set (MATH_STATIC ${MATH_LIBRARY}-static)
set (MATH_SHARED ${MATH_LIBRARY}-shared)

set (MATH_DOCS OFF CACHE BOOL "Build HTML documentation")

if (MATH_DOCS)
    find_package (Doxygen REQUIRED dot)
    add_custom_target (${MATH_LIBRARY}-docs ALL ${DOXYGEN_EXECUTABLE})
endif ()

file (GLOB_RECURSE MATH_SOURCES src/*.cpp)
file (GLOB_RECURSE MATH_HEADERS src/*.h)
include_directories (src)

add_library (${MATH_LIBRARY} OBJECT ${MATH_SOURCES})
set_target_properties (${MATH_LIBRARY} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE YES
)
target_compile_options (${MATH_LIBRARY} PUBLIC
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -pedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/WX>
)
target_compile_definitions (${MATH_LIBRARY} PUBLIC MATH_EXPORT)

add_library (${MATH_STATIC} STATIC $<TARGET_OBJECTS:${MATH_LIBRARY}>)
add_library (${MATH_SHARED} SHARED $<TARGET_OBJECTS:${MATH_LIBRARY}>)
set_target_properties (${MATH_SHARED} PROPERTIES VERSION ${MATH_VERSION} SOVERSION ${MATH_VERSION})

if (WIN32)
    # Dedicated library names for Win32 platform (dynamic library target outputs .lib as well)
    set_target_properties (${MATH_STATIC} PROPERTIES OUTPUT_NAME ${MATH_STATIC})
    set_target_properties (${MATH_SHARED} PROPERTIES OUTPUT_NAME ${MATH_SHARED})
elseif (UNIX)
    set_target_properties (${MATH_STATIC} ${MATH_SHARED} PROPERTIES OUTPUT_NAME ${MATH_LIBRARY})
endif ()

install (TARGETS ${MATH_STATIC} ${MATH_SHARED} DESTINATION lib)
install (FILES ${MATH_HEADERS} DESTINATION include/${MATH_LIBRARY})

if (UNIX)
    configure_file (math.pc.in math.pc @ONLY)
    install (FILES ${PROJECT_BINARY_DIR}/math.pc DESTINATION lib/pkgconfig)
endif ()

if (DOXYGEN_FOUND)
    configure_file (Doxyfile.in Doxyfile @ONLY)
    install (DIRECTORY ${PROJECT_BINARY_DIR}/html
             DESTINATION $<IF:$<BOOL:UNIX>,share/doc/${MATH_LIBRARY}-${MATH_VERSION},docs>)
endif ()
