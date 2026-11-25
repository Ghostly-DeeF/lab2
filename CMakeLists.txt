cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

project(sge VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions("-g -Wall -Wextra")

macro(sge_set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

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
target_compile_options(glfw PRIVATE -w)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(external/glm)
target_link_libraries(${PROJECT_NAME} glm)

# Examples
sge_set_option(SGE_BUILD_EXAMPLES ON BOOL "ON to build the SGE examples, OFF to ignore them")
if(SGE_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Tests
sge_set_option(SGE_BUILD_TESTS ON BOOL "ON to build the SGE tests, OFF to ignore them")
if(SGE_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

#add_subdirectory(external/assimp)
#target_link_libraries(${PROJECT_NAME} assimp)
#target_compile_options(assimp PRIVATE -Wno-error=implicit-fallthrough
#                                      -Wno-error=ignored-qualifiers
#                                      -Wno-error=calloc-transposed-args)
