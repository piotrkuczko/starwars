cmake_minimum_required(VERSION 3.10)
project(starwars)

set(CMAKE_CXX_STANDARD 17)


add_executable(main main.cpp imperialfleet.h rebelfleet.h battle.h)
#add_executable(example starwars_example.cc rebelfleet.h imperialfleet.h battle.h)