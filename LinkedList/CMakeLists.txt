cmake_minimum_required(VERSION 3.16)
project(LinkedList)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(DoubleLinkedList)

add_executable(LinkedList
        DoubleLinkedList/DoubleLinkedList.cpp
        DoubleLinkedList/DoubleLinkedList.h
        LinkedList.cpp
        LinkedList.h)
