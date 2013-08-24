cmake_minimum_required (VERSION 2.6)
project (MATH)

if (CMAKE_COMPILER_IS_GNUCC)
    execute_process (COMMAND ${CMAKE_CXX_COMPILER} -dumpversion
                     OUTPUT_VARIABLE GCC_VERSION)
    string (STRIP ${GCC_VERSION} GCC_VERSION)

    if (GCC_VERSION VERSION_GREATER 4.4.0)
        set (CMAKE_CXX_FLAGS "-Wall -pedantic")
    else ()
        message(FATAL_ERROR "GCC 4.4.0 or higher is required!")
    endif ()
endif ()

file (GLOB_RECURSE MATH_SOURCES "src/*.cpp")
include_directories ("src")

set (MATH_LIBRARY "math")
set (MATH_VERSION 0.0.1)

add_library ("static" STATIC ${MATH_SOURCES})
add_library ("shared" SHARED ${MATH_SOURCES})

set_target_properties ("static" "shared" PROPERTIES OUTPUT_NAME ${MATH_LIBRARY})
set_target_properties ("shared" PROPERTIES VERSION ${MATH_VERSION} SOVERSION ${MATH_VERSION})
