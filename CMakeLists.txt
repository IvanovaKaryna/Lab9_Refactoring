cmake_minimum_required(VERSION 3.16)
project(Lab9_Refactoring LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/utf-8)   
endif()

add_executable(library_before library/before/main.cpp)

add_library(library_core library/after/src/Library.cpp)
target_include_directories(library_core PUBLIC library/after/include)

add_executable(library_after library/after/src/main.cpp)
target_link_libraries(library_after PRIVATE library_core)

add_executable(library_swap_demo library/after/src/main_swap.cpp)
target_link_libraries(library_swap_demo PRIVATE library_core)

add_executable(library_tests library/after/tests/library_tests.cpp)
target_include_directories(library_tests PRIVATE common)
target_link_libraries(library_tests PRIVATE library_core)

add_library(gildedrose_core
    kata/src/GildedRose.cc
    kata/src/ItemUpdater.cc
    kata/src/ItemUpdaters.cc
    kata/src/ItemUpdaterRegistry.cc)
target_include_directories(gildedrose_core PUBLIC kata/include)

add_library(gildedrose_legacy kata/legacy/GildedRoseLegacy.cc)
target_include_directories(gildedrose_legacy PUBLIC kata/legacy kata/include)

add_executable(gildedrose_demo kata/src/main_demo.cpp)
target_link_libraries(gildedrose_demo PRIVATE gildedrose_core)

add_executable(gildedrose_tests kata/tests/gilded_rose_tests.cpp)
target_include_directories(gildedrose_tests PRIVATE common)
target_link_libraries(gildedrose_tests PRIVATE gildedrose_core gildedrose_legacy)
