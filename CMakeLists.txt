cmake_minimum_required(VERSION 3.6)
project(projekt_IFJ)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    materialy/ilist.c
    materialy/ilist.h
    materialy/interpret.c
    materialy/interpret.h
    materialy/main.c
    materialy/makefile
    materialy/parser.c
    materialy/parser.h
    materialy/scaner.c
    materialy/scaner.h
    materialy/stable.c
    materialy/stable.h
    materialy/str.c
    materialy/str.h
    defs.h
    ial.c
    ial.h
    lex.c
    lex.h
    list.c
    list.h
    main.c
    Makefile
    parser.c
    parser.h
    stack.c
    stack.h materialy/error.c materialy/error.h builtin.h)

add_executable(projekt_IFJ ${SOURCE_FILES})