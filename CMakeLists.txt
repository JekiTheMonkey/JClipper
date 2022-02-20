cmake_minimum_required(VERSION 3.0.0)

# Set project name
project(JClipper)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

IF (WIN32)
    # Set C/C++ compilers
    set(CMAKE_CXX_COMPILER "F:/programs/msys2/mingw64/bin/g++.exe")
    set(CMAKE_C_COMPILER "F:/programs/msys2/mingw64/bin/gcc.exe")
ENDIF()

# Enable debug symbols by default
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug
		CACHE STRING
		"Choose the type of build (Debug or Release)" FORCE)
endif()

# # If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

IF (WIN32)
    # Tell CMake where SFML is located
    set(SFML_DIR "D:/dev/lib/SFML-2.5.1/lib/cmake/SFML")
ENDIF()

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(${PROJECT_NAME}
    src/Main.cpp
    src/Application.cpp
    src/KeysBuffer.cpp
    src/DoubleKeysBuffer.cpp
    src/Framerate.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE include/)

target_compile_options(
    ${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)

target_link_libraries(${PROJECT_NAME} sfml-graphics)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
