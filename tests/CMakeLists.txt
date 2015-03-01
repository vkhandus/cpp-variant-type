cmake_minimum_required(VERSION 2.8)

project(cpp-variant-type)

set(SOURCES
    ../src/Variant.h
    main.cpp
)

include_directories(../src)

add_executable(test ${SOURCES})

