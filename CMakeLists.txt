cmake_minimum_required(VERSION 3.21)
project(minesweeper CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(minesweeper
        main.cpp
        Game.h Game.cpp
        GUI.h GUI.cpp)

# MinGW: собираем со статическими рантаймами, чтобы .exe запускался без libwinpthread-1.dll
if (MINGW)
    target_link_options(minesweeper PRIVATE -static-libstdc++ -static-libgcc -static)
endif ()

# Игра читает mine.txt и choose.txt из рабочей директории,
# поэтому кладём их рядом с собранным .exe
foreach (RESOURCE mine.txt choose.txt)
    configure_file(${RESOURCE} ${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE} COPYONLY)
endforeach ()
