message(STATUS ${PROJECT_SOURCE_DIR})
file(GLOB_RECURSE ZBBM_TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")

add_executable(zbbm_book_manager_test ${ZBBM_BASE_DIR}/src/book_manager.cpp ${ZBBM_TEST_SRCS})
target_include_directories(zbbm_book_manager_test PUBLIC ${ZBBM_BASE_DIR}/include)

set_target_properties(zbbm_book_manager_test
PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
)