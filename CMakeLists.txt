cmake_minimum_required(VERSION 3.13)
project(testrender)

set(CMAKE_CXX_STANDARD 11)

add_executable(testrender
        main.cpp
        ObjParser.cpp
        ObjParser.h
        Vector3d.cpp
        Vector3d.h
        Vertex3d.cpp
        Vertex3d.h
        Logger.hpp
        RObject.cpp
        RObject.h
        defines.h
        Vector2d.cpp
        Vector2d.h Video.cpp Video.h Matrix4x4.cpp Matrix4x4.h AngleConverter.hpp)

target_link_libraries(testrender sfml-window sfml-system sfml-graphics)