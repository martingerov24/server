cmake_minimum_required(VERSION 3.16)

project(server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#apt install PkgConfig
find_package(PkgConfig)

find_package(cppzmq)
# pkg_check_modules(PC_ZeroMQ QUIET zmq)

set(SOURCES
	#code
	main.cpp
	src/Server.h

	src/cppFiles/Server.cpp
)

add_executable(server ${SOURCES})

target_link_directories(${PROJECT_NAME} PUBLIC
	)

target_include_directories(${PROJECT_NAME} PUBLIC
	cppzmq-static
)

target_link_libraries(${PROJECT_NAME} PUBLIC
	cppzmq-static
	${CMAKE_DL_LIBS}
)

# target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:MSVC>:>)
target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CLANG>:>)