cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

project(sge)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions("-g -Wall")

file(GLOB_RECURSE CPP_SOURCES
"./src/*.cpp")
file(GLOB_RECURSE PRIVATE_HEADERS
".src/*hpp")


add_library(${PROJECT_NAME} ${CPP_SOURCES} ${PRIVATE_HEADERS} "src/Rendering/ShaderProgram")

add_custom_target(
    res
    COMMAND ${CMAKE_COMMAND} -E make_directory
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
    COMMAND ${CMAKE_COMMAND} -E rm -R
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/res
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
)
add_dependencies(${PROJECT_NAME} res)

target_include_directories(${PROJECT_NAME} PUBLIC include)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(external/glm)
target_link_libraries(${PROJECT_NAME} glm)

add_subdirectory(external/assimp)
target_link_libraries(${PROJECT_NAME} assimp)
