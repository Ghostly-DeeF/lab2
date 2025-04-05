cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

project(sge)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE CPP_SOURCES
"./src/*.cpp")
file(GLOB_RECURSE PRIVATE_HEADERS
".src/*hpp")


add_library(${PROJECT_NAME} ${CPP_SOURCES} ${PRIVATE_HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC include)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(external/glm)
target_link_libraries(${PROJECT_NAME} glm)

add_subdirectory(external/assimp)
target_link_libraries(${PROJECT_NAME} assimp)
