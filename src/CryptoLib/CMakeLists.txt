cmake_minimum_required(VERSION 3.14)

project(CryptoLib LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(CryptoLib SHARED
  CryptoLib_global.h
  cryptolib.cpp
  cryptolib.h
)

target_compile_definitions(CryptoLib PRIVATE CRYPTOLIB_LIBRARY)
