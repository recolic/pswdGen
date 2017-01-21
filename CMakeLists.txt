cmake_minimum_required(VERSION 3.6)
project(pswdGen)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp stdafx.h recolic_alias.h pswdGener.h picosha2.h)
add_executable(pswdGen ${SOURCE_FILES})