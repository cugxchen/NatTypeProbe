cmake_minimum_required(VERSION 2.13)
project(NatTypeProb)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(Source/Startup/ FILE)
aux_source_directory(Source/Nat/ FILE)
aux_source_directory(Source/Nat/Stun FILE)

add_executable(NatTypeProb ${FILE})