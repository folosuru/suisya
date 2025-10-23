project(suisya_test CXX)

add_executable(suisya_test main.cpp)

enable_testing()
if (WIN32)
    # To ignore WSL's bash
    find_program(BASH_EXE bash PATHS
            "C:/Program Files/Git/usr/bin"
            "C:/Program Files/Git/bin"
            "C:/msys64/usr/bin"
            "C:/cygwin64/bin"
            NO_DEFAULT_PATH
    )
else ()
find_program (BASH_EXE bash)
endif ()

if (BASH_EXE)
    add_test(NAME mytest
            COMMAND ${BASH_EXE} 
            ${CMAKE_CURRENT_SOURCE_DIR}/test.sh
            ${CMAKE_SOURCE_DIR}/artifact/suisyac ${CMAKE_CURRENT_SOURCE_DIR}/test.sui
            ${CMAKE_BINARY_DIR}/test/integration/suisya_test ${CMAKE_CURRENT_SOURCE_DIR}/test_out.txt
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
    set_property(TEST mytest PROPERTY FIXTURES_SETUP  suisya_test)
else ()
    message("bash not found")
endif (BASH_EXE)

