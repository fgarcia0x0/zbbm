message(STATUS ${PROJECT_SOURCE_DIR})
file(GLOB_RECURSE ZBBM_TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")

set(ZBBM_LIBS 
	${ZBBM_BASE_DIR}/src/book_manager.cpp
)

add_executable(zbbm_test ${ZBBM_LIBS} ${ZBBM_TEST_SRCS})
target_include_directories(zbbm_test PUBLIC ${ZBBM_BASE_DIR}/include)

set_target_properties(zbbm_test
PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
)