cmake_minimum_required(VERSION 3.10)
project(ucc VERSION 1.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER clang)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic -fsanitize=address")

# Include directories
include_directories(include)

# Source directories
file(GLOB_RECURSE SRCS src/*.cpp)
list(APPEND SRCS src/ast/lexer.yy.cpp src/ast/parser.tab.cpp)

# Flex and Bison
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

FLEX_TARGET(Lexer src/ast/lexer.l ${CMAKE_CURRENT_SOURCE_DIR}/src/ast/lexer.yy.cpp)
BISON_TARGET(Parser src/ast/parser.y ${CMAKE_CURRENT_SOURCE_DIR}/src/ast/parser.tab.cpp DEFINES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/include/parser.tab.hpp)
ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

# Add executable
add_executable(ucc ${SRCS} ${FLEX_Lexer_OUTPUTS} ${BISON_Parser_OUTPUTS})

# Link libraries
target_link_libraries(ucc asan)

# Custom target for running
add_custom_target(run
    COMMAND ucc -Stestsrc.c -otestout.s
    DEPENDS ucc
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

# Custom target for gdb
add_custom_target(gdb
    COMMAND gdb --args ./ucc -Stestsrc.c -otestout.s
    DEPENDS ucc
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

add_custom_target(cleanall
    COMMAND ${CMAKE_COMMAND} -E rm -r ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_outputs/
	COMMENT "Cleaning Up"
)


# Clean custom target
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES 
    "
	${CMAKE_CURRENT_SOURCE_DIR}/src/ast/lexer.yy.cpp;
	${CMAKE_CURRENT_SOURCE_DIR}/include/parser.tab.hpp;
	${CMAKE_CURRENT_SOURCE_DIR}/src/ast/parser.tab.cpp;
	"
)

