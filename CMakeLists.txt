cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(ARCH "x86_64")
if(WIN32 OR WIN64)
	add_definitions(-DWINDOWS)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -std=c++17 -Wall -Wextra -Wpedantic -Wformat-security -Wno-unused")
	if(CMAKE_BUILD_TYPE MATCHES Release)
		set(ARCH "x86_64")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows -D_FORTIFY_SOURCE=2 -mmitigate-rop -fPIE")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--high-entropy-va -Wl,--dynamicbase -Wl,--nxcompat -Wl,--export-all-symbols")
	elseif(CMAKE_BUILD_TYPE MATCHES Debug)
		message(STATUS "Hardening disabled for debug build")
	endif()
elseif(UNIX)
	add_definitions(-DLINUX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Wpedantic -Wformat-security -Wno-unused")
	if(CMAKE_BUILD_TYPE MATCHES Release)
		set(ARCH "x86_64")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_FORTIFY_SOURCE=2 -mmitigate-rop -fstack-protector-strong -fPIE")
		set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,high-entropy-va")
	elseif(CMAKE_BUILD_TYPE MATCHES Debug)
		message(STATUS "Hardening disabled for debug build")
	endif()
endif()
if(CMAKE_BUILD_TYPE MATCHES Release)
	set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")
	add_definitions(-DRELEASE)
elseif(CMAKE_BUILD_TYPE MATCHES Debug)
	set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0")
	add_definitions(-DDEBUG)
endif()

add_subdirectory(gcdvd)

project(mpio)
include_directories(include)
set(SRC
		src/util.hh
		src/datatypes/fourCC.hh
		src/datatypes/vector3f.hh
		src/datatypes/quaternion.hh
		src/datatypes/aaBox.hh
		src/datatypes/color4i.hh
		src/datatypes/color4f.hh
		src/pak.hh
		src/in.cc src/in.hh
		src/out.cc src/out.hh)
add_library(${PROJECT_NAME} STATIC ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC gcdvd/include)
add_dependencies(${PROJECT_NAME} gcdvd)
if(WIN32 OR WIN64)
	set(LIBS
			${CMAKE_SOURCE_DIR}/libs/libz.a
			${CMAKE_SOURCE_DIR}/gcdvd/libs/libgcdvd.a)
elseif(UNIX)
	set(LIBS z ${CMAKE_SOURCE_DIR}/gcdvd/libs/libgcdvd.so)
endif()
target_link_libraries(${PROJECT_NAME} ${LIBS})
