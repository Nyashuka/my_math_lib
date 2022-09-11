cmake_minimum_required(VERSION 3.24.1)

project(LibraryClientTest)

add_executable(LibTestClient Source.cpp)

set_target_properties(
	LibTestClient PROPERTIES
	CXX_STANDART 17
	CXX_STANDART_REQUIRED ON
	)

target_include_directories(
    LibTestClient
    PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    )

target_include_directories(
	LibTestClient
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/../lib
	)

target_link_libraries(LibTestClient MyMathLibrary)