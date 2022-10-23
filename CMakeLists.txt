cmake_minimum_required(VERSION 3.15)
project(zbbm VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
string(TOLOWER ${CMAKE_BUILD_TYPE} ZBBM_BUILD_TYPE)
set(ZBBM_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ZBBM_BASE_DIR}/bin/${ZBBM_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ZBBM_BASE_DIR}/bin/${ZBBM_BUILD_TYPE})

file(GLOB_RECURSE ZBBM_SRCS RELATIVE ${ZBBM_BASE_DIR} "src/*.cpp")
add_compile_options(-Wall -Wextra -Wpedantic -Wno-unused-parameter -Wno-unused-function -Wdouble-promotion -Wformat-overflow -Wformat-security -Wnull-dereference -Wmisleading-indentation -Wconversion -Wshadow -Wcast-qual -Wcast-align -Waddress)

add_executable(zebigods_book_manager ${ZBBM_SRCS})
target_include_directories(zebigods_book_manager PUBLIC ${PROJECT_SOURCE_DIR}/include)

set_target_properties(zebigods_book_manager
PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
)