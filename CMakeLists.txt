cmake_minimum_required(VERSION 3.15)
project(suisya)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
if(CMAKE_EXPORT_COMPILE_COMMANDS)
  set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES 
      ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

add_subdirectory(lib)
add_subdirectory(test/integration)
add_subdirectory(test/unit)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/artifact)
add_executable(suisyac main.cpp)
target_link_libraries(suisyac PRIVATE suisya)
target_include_directories(suisyac PRIVATE lib)


enable_testing()
