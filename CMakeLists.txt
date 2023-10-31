cmake_minimum_required(VERSION 3.27)
project(Labwork_3)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "")

add_executable(Labwork_3 main.cpp
        lib/Types.cpp lib/Types.h
        lib/TSVParser.cpp lib/TSVParser.h
        lib/Sandpile.cpp lib/Sandpile.h
        lib/Stack.cpp lib/Stack.h
        lib/ErrorMessage.cpp lib/ErrorMessage.h
        lib/ArgumentParser.cpp lib/ArgumentParser.h
)
