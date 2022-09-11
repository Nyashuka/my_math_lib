
cmake_minimum_required(VERSION 3.24.1)

project(MyMathLibrary)

set(SOURCES 
	CppHelperLibrary.cpp 	
	)

set(HEADERS 
	CppHelperLibrary.h
	)

add_library(MyMathLibrary STATIC ${SOURCES} ${HEADERS})

set_target_properties(
	MyMathLibrary PROPERTIES
	CXX_STANDART 17
	CXX_STANDART_REQUIRED ON
	)

target_include_directories(
	MyMathLibrary
	PRIVATE
	${CMAKE_CURRENT_BINARY_DIR}
	)



