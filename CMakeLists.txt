cmake_minimum_required(VERSION 2.8)

project(nano)

find_package(OPENGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(nanovg)

# Directory where exe,dll and static library saved
set(NANO_BINARY_DIR ${CMAKE_BINARY_DIR}/bin-${CMAKE_CXX_COMPILER_ID}-${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${NANO_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${NANO_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${NANO_BINARY_DIR})

# Copy icons for example application
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/icons DESTINATION ${NANO_BINARY_DIR})

add_executable(nano "main.cpp")
target_link_libraries(nano glfw3  nanovg glew32 ${OPENGL_LIBRARIES})
