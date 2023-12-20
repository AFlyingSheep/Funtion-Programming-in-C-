cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

project(Funtional_Programming
        VERSION 0.0.1
        LANGUAGES CXX)

#目标编译器的特性设置
# target_compile_features(Funtional_Programming PRIVATE cxx_std_20)
include_directories(include)

add_subdirectory(chp1)
add_subdirectory(chp2)