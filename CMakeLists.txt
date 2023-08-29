cmake_minimum_required(VERSION 3.25)
project(tokennizer)

set(CMAKE_CXX_STANDARD 17)

add_executable(tokennizer BasicTokennizer.h utils.h WordpieceTokenizer.h FullTokenizer.h Container.h test.cpp)
