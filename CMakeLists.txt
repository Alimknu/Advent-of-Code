cmake_minimum_required(VERSION 3.16)
project(AdventOfCode LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/*.cpp")
foreach(src IN LISTS SRC_FILES)
  get_filename_component(bin ${src} NAME_WE)

  get_filename_component(src_dir ${src} PATH)
  file(RELATIVE_PATH rel_dir ${CMAKE_SOURCE_DIR} ${src_dir})

  add_executable(${bin} ${src})

  if(rel_dir STREQUAL ".")
    set(target_out_dir "${CMAKE_BINARY_DIR}/bin")
  else()
    set(target_out_dir "${CMAKE_BINARY_DIR}/bin/${rel_dir}")
  endif()

  set_target_properties(${bin} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${target_out_dir}"
  )
endforeach()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
