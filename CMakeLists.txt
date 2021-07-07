cmake_minimum_required(VERSION 3.5)

project(untitled LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("/home/peter/SFML/include/")
link_directories("/home/peter/SFML/lib")

add_executable(untitled
                main.cpp
                colonymapping.cpp
                colonymapping.h
                ant.cpp
                ant.h
                point.cpp
                point.h
                pheromonetrail.cpp
                pheromonetrail.h
                route.cpp
                route.h)


target_link_libraries(untitled -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d)
