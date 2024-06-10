cmake_minimum_required(VERSION 3.20)
project(VectorModule LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler-specific flags for C++20 modules
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(MODULE_COMPILE_FLAGS "-fmodules-ts")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(MODULE_COMPILE_FLAGS "-fmodules-ts")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(MODULE_COMPILE_FLAGS "/experimental:module")
endif()

# Define the module interface file
set(MODULE_INTERFACE_FILE ${CMAKE_SOURCE_DIR}/VectorModule.cppm)

# Custom command to compile the module interface file
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/VectorModule.cppm.o
    COMMAND ${CMAKE_CXX_COMPILER} ${MODULE_COMPILE_FLAGS} -c ${MODULE_INTERFACE_FILE} -o ${CMAKE_BINARY_DIR}/VectorModule.cppm.o
    DEPENDS ${MODULE_INTERFACE_FILE}
    COMMENT "Compiling VectorModule.cppm"
)

# Add custom target to build the module interface
add_custom_target(compile_vector_module
    DEPENDS ${CMAKE_BINARY_DIR}/VectorModule.cppm.o
)

# Add the module interface file as a library
add_library(vector_module STATIC ${CMAKE_BINARY_DIR}/VectorModule.cppm.o ${CMAKE_SOURCE_DIR}/dummy.cpp)
add_dependencies(vector_module compile_vector_module)

# Add the main executable
add_executable(main ${CMAKE_SOURCE_DIR}/main.cpp)
target_link_libraries(main PRIVATE vector_module)
