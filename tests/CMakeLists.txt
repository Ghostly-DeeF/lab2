if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/googletest/CMakeLists.txt")
    message(FATAL_ERROR "GoogleTest is missing.")
endif()

set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

add_subdirectory("${PROJECT_SOURCE_DIR}/external/googletest"
                 "${CMAKE_BINARY_DIR}/external/googletest"
                 EXCLUDE_FROM_ALL)

include(GoogleTest)

set(SRC
    GlContext.cpp
    ShaderManagerTest.cpp
)

add_executable(sge_tests ${SRC})

target_include_directories(sge_tests PRIVATE
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(sge_tests PRIVATE
    sge
    GTest::gtest_main
)

target_compile_definitions(sge_tests PRIVATE SGE_TEST_SHADERS_DIR="${PROJECT_SOURCE_DIR}/res/shaders")

gtest_discover_tests(sge_tests)
