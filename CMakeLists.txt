cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)

project(Raytracing)

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

# compiler commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add all Source Files
file(GLOB_RECURSE SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# Add all Header Files (now in the 'include' directory)
file(GLOB_RECURSE HEADER_FILES
    ${CMAKE_SOURCE_DIR}/include/*.h
    ${CMAKE_SOURCE_DIR}/include/*.hpp
)

# Add the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# Set the output directory for the executable based on the build type
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/release
)

# Variables for Paths of External Libraries
set(SDL2_ROOT_DIR external/SDL2)

# Add the External Libraries / Files Directory
add_subdirectory(${SDL2_ROOT_DIR})

# Add the Include Directories for the Libraries / Files
target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_SOURCE_DIR}/include  
    PUBLIC ${SDL2_ROOT_DIR}/include
)

# Add the Link Directories for the Libraries / Files
target_link_directories(${PROJECT_NAME}
    PRIVATE ${SDL2_ROOT_DIR}/src
)

# Link SDL2 library to the target
target_link_libraries(${PROJECT_NAME} 
    PRIVATE SDL2
)

