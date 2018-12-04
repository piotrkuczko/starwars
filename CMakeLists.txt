cmake_minimum_required(VERSION 3.10)
project(starwars)

set(CMAKE_CXX_STANDARD 17)
#SET(CMAKE_C_COMPILER /usr/bin/clang)
#SET(CMAKE_CXX_COMPILER /usr/bin/clang++)



#add_executable(main main.cpp imperialfleet.h rebelfleet.h battle.h)
add_executable(example starwars_example.cc rebelfleet.h imperialfleet.h battle.h)
add_executable(testAsercje TestSpeedAndTick.cpp rebelfleet.h imperialfleet.h battle.h)
add_executable(testWypisywanie TestResultPrinting.cpp rebelfleet.h imperialfleet.h battle.h)


#clang -Wall -Wextra -std=c++17 -O2 -lstdc++ starwars_example.cc -o starwars
