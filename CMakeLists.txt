cmake_minimum_required(VERSION 3.26.4)
project(DA_PROJ2)

set(CMAKE_CXX_STANDARD 17)

add_executable(DA_PROJ2 src/main.cpp
        src/Graph.h
        src/Node.h
        src/Utilities.cpp
        src/Utilities.h
        src/Edge.h
        src/Menu.h
        src/backtracking.cpp
        src/backtracking.h
        src/triangular_approx.h
        src/triangular_approx.cpp
        src/BranchAndBound.cpp
        src/BranchAndBound.h
)
