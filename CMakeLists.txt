cmake_minimum_required(VERSION 3.10)

project(program
    VERSION 0.1
    DESCRIPTION "Let's test OpenGL and CMake!"
    LANGUAGES CXX
)

# Always produce compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Adding main target
add_executable(${PROJECT_NAME} main.cxx)

# Add these directories to search path
include_directories(${PROJECT_NAME} PRIVATE
    dependencies
    src
)

# Process CMakeLists.txt in these directory
add_subdirectory(src)
add_subdirectory(dependencies)

# Find dependencies
find_library(GLEW REQUIRED
    NAMES glew32
    PATHS ${CMAKE_SOURCE_DIR}/dependencies/lib
)

find_library(GLFW REQUIRED
    NAMES glfw3
    PATHS ${CMAKE_SOURCE_DIR}/dependencies/lib
)

find_library(OPENGL REQUIRED
    NAMES opengl32
    PATHS ${CMAKE_SOURCE_DIR}/dependencies/lib
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    glStuff sources
    ${GLEW} ${GLFW} ${OPENGL}
)

