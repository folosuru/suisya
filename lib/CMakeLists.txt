project(plexr_lib CXX)


file(GLOB LIST LIST_DIRECTORIES false "*.cpp" "*.hpp")

add_library(suisya Tokenizer.cpp generator.cpp
        Token.cpp
        script/CompileContext.hpp
        script/CompileContext.cpp
        error/ErrorReport.cpp
        script/value/ContentValue.cpp
        script/value/ValueBase.cpp
        script/statement/Statement.hpp
        script/statement/Statement.cpp
        script/statement/Literal.cpp
        script/statement/ValueNode.cpp
        script/RootNode.cpp
        tokenize/StreamReader.cpp

)
target_include_directories(suisya PRIVATE ../ ./)
target_compile_definitions(suisya
        PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
)

set_property(TARGET suisya PROPERTY CXX_STANDARD 20)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(suisya PRIVATE
            -Wall -Weverything
            -Wno-c++98-compat -Wno-padded -Wno-exit-time-destructors -Wno-global-constructors -g
    )
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(suisya PRIVATE
            -Wall -Wextra
    )
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(suisya PRIVATE
            /Wall
    )
endif()
