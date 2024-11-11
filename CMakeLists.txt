cmake_minimum_required(VERSION 3.29)
project(task1_graph LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/x64)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

include_directories(2d_space)
include_directories(drawer)
include_directories(drawer/drawer_commands)
include_directories(graph)
include_directories(other)

add_executable(task1_graph
        2d_space/edge_shape.h
        2d_space/node_shape.h
        2d_space/point.h
        2d_space/shape.h
        drawer/drawer_commands/drawer_command.h
        drawer/drawer_commands/drawer_command_factory.h
        drawer/drawer_commands/drawer_create_command.h
        drawer/drawer_commands/drawer_delete_command.h
        drawer/drawer_commands/drawer_recolor_command.h
        drawer/graph_drawer.h
        drawer/graph_drawer_engine.h
        drawer/render_frame.h
        graph/edge.h
        graph/edge_data.h
        graph/edge_data_flow.h
        graph/edge_data_single.h
        graph/edge_type.h
        graph/graph.h
        graph/node.h
        other/algorithm.cpp
        other/algorithm.h
        main.cpp)

target_link_libraries(task1_graph PRIVATE sfml-graphics)
target_compile_features(task1_graph PRIVATE cxx_std_17)