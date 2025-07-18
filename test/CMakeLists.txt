# ~~~
# Copyright (c) 2017, Sylvain Corlay, Johan Mabille, and Loic Gouarin
#
# Distributed under the terms of the BSD 3-Clause License.
#
# The full license is in the file LICENSE, distributed with this software.
# ~~~

cmake_minimum_required(VERSION 3.24)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    project(xwidgets-test)

    find_package(xwidgets REQUIRED CONFIG)
    set(XWIDGETS_INCLUDE_DIR ${xwidgets_INCLUDE_DIRS})
endif()

# Dependencies
# ============

find_package(doctest REQUIRED)
find_package(nlohmann_json_schema_validator REQUIRED)
find_package(Threads)

# Source files
# ============

set(XWIDGETS_TESTS main.cpp test_xholder.cpp test_xwidgets.cpp test_widget_model.cpp)

# Output
# ======

add_executable(test_xwidgets ${XWIDGETS_TESTS})

target_compile_features(test_xwidgets PRIVATE cxx_std_17)

target_compile_definitions(
    test_xwidgets PRIVATE XWIDGETS_MODELS_FILE="${CMAKE_CURRENT_SOURCE_DIR}/jupyterwidgetmodels.latest.json"
)

target_link_libraries(
    test_xwidgets
    PRIVATE xwidgets xeus doctest::doctest nlohmann_json_schema_validator ${CMAKE_THREAD_LIBS_INIT}
)
target_include_directories(test_xwidgets PRIVATE XWIDGETS_INCLUDE_DIR)

add_test(NAME test_xwidgets COMMAND test_xwidgets)
