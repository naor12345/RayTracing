cmake_minimum_required(VERSION 3.6)
project(OwnGI)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    Cylinder.cpp
    Cylinder.h
    CylinderInf.cpp
    CylinderInf.h
    Geometry.cpp
    Geometry.h
    Hexahedron.cpp
    Hexahedron.h
    IntersectResult.h
    main.cpp
    Plane.cpp
    Plane.h
    Polyhedron.cpp
    Polyhedron.h
    Ray.cpp
    Ray.h
    RecPlane.cpp
    RecPlane.h
    Sphere.cpp
    Sphere.h
    Union.cpp
    Union.h
    Util.cpp
    Util.h
    Vec.cpp
    Vec.h)

add_executable(OwnGI ${SOURCE_FILES})