cmake_minimum_required(VERSION 3.21)
project(LAB05)

set(CMAKE_CXX_STANDARD 14)

include_directories(include test/include  include/calerf)
add_executable(LAB05 main.cpp src/matrix/matrix.cpp src/matrix/matrixCalc.cpp
        src/matrix_dec/LU/operation.cpp src/matrix_dec/LU/luDecomp.cpp  src/equationSolver/triangularSolver.cpp
        src/equationSolver/thomasSolver.cpp  src/matrix/view/tripleDiagView.cpp
        src/equationSolver/iteration/equationIterativeSolver.cpp  src/equationSolver/iteration/jacobEquationSolver.cpp
        src/equationSolver/iteration/gausSeidelEquationSolver.cpp src/equationSolver/iteration/SOREquationSolver.cpp
        src/utils/intervals/closedInterval.cpp src/differentialEquationsSolver/mesh.cpp
        src/differentialEquationsSolver/ordinary/secondOrder/secondOrderDifferentialEquationSolver.cpp
        src/differentialEquationsSolver/partial/secondOrder/KMBSolver.cpp
        src/differentialEquationsSolver/partial/secondOrder/LaasonenSolver.cpp
        include/calerf/calerf.cpp)
