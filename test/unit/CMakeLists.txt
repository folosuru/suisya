project(suisya_UnitTest CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
if(CMAKE_EXPORT_COMPILE_COMMANDS)
  set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES 
      ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif()



add_executable(suisya_UnitTest main.cpp stream_reader.cpp)

target_compile_definitions(suisya_UnitTest
        PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
)
target_include_directories(suisya_UnitTest PRIVATE ${CMAKE_SOURCE_DIR}/lib/)
target_link_libraries(suisya_UnitTest PRIVATE suisya)
