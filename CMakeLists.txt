
cmake_minimum_required(VERSION 2.8)

project(RBE)

set(LIBSOURCES
		${RBE_SOURCE_DIR}/src/ringbuffer.h
		${RBE_SOURCE_DIR}/src/ringbuffer.c
		)

set(ALL_INCLUDES_DIRS
		${RBE_SOURCE_DIR}/src
		)

include_directories( ${ALL_INCLUDES_DIRS} )
add_library(librbe SHARED ${LIBSOURCES})

add_executable(sample1 ../tests/sample1.c)
add_executable(sample2 ../tests/sample2.c)
add_executable(sample3 ../tests/sample3.c)
add_executable(sample4 ../tests/sample4.c)
add_executable(sample5 ../tests/sample5.c)
add_executable(sample6 ../tests/sample6.c)
add_executable(sample7 ../tests/sample7.c)
target_link_libraries(sample1 librbe)
target_link_libraries(sample2 librbe)
target_link_libraries(sample3 librbe)
target_link_libraries(sample4 librbe)
target_link_libraries(sample5 librbe)
target_link_libraries(sample6 librbe)
target_link_libraries(sample7 librbe)

SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_BUILD_TYPE Release)

enable_testing()
add_test(SAMPLE1 sample1)
add_test(SAMPLE2 sample2)
add_test(SAMPLE3 sample3)
add_test(SAMPLE4 sample4)
add_test(SAMPLE5 sample5)
add_test(SAMPLE6 sample6)
add_test(SAMPLE7 sample7)

add_definitions(
			-W
			-Wall
			-Werror
			-Winline
			-Wshadow
			-Wcast-qual
			-Wpointer-arith
		)
