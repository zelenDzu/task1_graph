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

include_directories(include/task1_graph)

add_executable(task1_graph
        include/task1_graph/2d_space/point.h
        include/task1_graph/2d_space/shape.h
        include/task1_graph/drawer/drawer_commands/drawer_command.h
        include/task1_graph/drawer/drawer_commands/drawer_command_factory.h
        include/task1_graph/drawer/graph_drawer.h
        include/task1_graph/drawer/graph_drawer_engine.h
        include/task1_graph/drawer/render_frame.h
        include/task1_graph/graph/edge.h
        include/task1_graph/graph/edge_data.h
        include/task1_graph/graph/graph.h
        include/task1_graph/graph/node.h
        include/task1_graph/other/algorithm.h
        src/task1_graph/algorithm.cpp
        src/task1_graph/graph.cpp
        src/task1_graph/drawer_command.cpp
        src/task1_graph/graph_drawer_engine.cpp
        src/task1_graph/graph_drawer.cpp
        src/task1_graph/drawer_command_factory.cpp
        src/main.cpp)

target_link_libraries(task1_graph PRIVATE sfml-graphics)

target_compile_features(task1_graph PRIVATE cxx_std_17)