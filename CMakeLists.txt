cmake_minimum_required(VERSION 3.30)

set(PROJECT_NAME glfw_shape_demo)

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(3rdparty/glew-cmake)
add_subdirectory(3rdparty/glfw)

set(
    HEADERS
    ./src/common/shape_demo_utils.h
    ./src/shape_factory/abstract_shape_factory.h
    ./src/shape_factory/triangle_shape_factory.h
    ./src/shape_factory/rectangle_shape_factory.h
    ./src/shape_factory/circle_shape_factory.h
    ./src/world/world_model.h
    ./src/world/world_view.h
    ./src/world/rotated_world_view.h
)

set(
    SOURCES
    ./src/main.cpp
    ./src/shape_factory/triangle_shape_factory.cpp
    ./src/shape_factory/rectangle_shape_factory.cpp
    ./src/shape_factory/circle_shape_factory.cpp
    ./src/world/world_model.cpp
    ./src/world/world_view.cpp
    ./src/world/rotated_world_view.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE libglew_static glfw)
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
