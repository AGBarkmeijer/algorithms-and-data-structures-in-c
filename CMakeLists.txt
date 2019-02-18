cmake_minimum_required(VERSION 3.8)
project(algorithms_and_data_structures_in_c)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES

        # WEEK 1
        cmake-build-debug/assignment1code/LibList.c
        cmake-build-debug/assignment1code/LibList.h
        cmake-build-debug/assignment1code/LibQueue.c
        cmake-build-debug/assignment1code/LibQueue.h
        cmake-build-debug/assignment1code/LibStack.c
        cmake-build-debug/assignment1code/LibStack.h
        #cmake-build-debug/assignment1code/signals.c

        # WEEK 2
        #cmake-build-debug/assignment2code/evalExp.c
        #cmake-build-debug/assignment2code/evalExp.h
        #cmake-build-debug/assignment2code/mainEvalExp.c
        #cmake-build-debug/assignment2code/mainRecog.c
        #cmake-build-debug/assignment2code/mainScan.c
        cmake-build-debug/assignment2code/assignment2.c
        cmake-build-debug/assignment2code/recognizeExp.c
        cmake-build-debug/assignment2code/recognizeExp.h
        cmake-build-debug/assignment2code/scanner.c
        cmake-build-debug/assignment2code/scanner.h


        cmake-build-debug/Algorithms_Data_Structures.cbp
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/CMakeCache.txt
        cmake-build-debug/Makefile
        README.md)

add_executable(algorithms_and_data_structures_in_c ${SOURCE_FILES})