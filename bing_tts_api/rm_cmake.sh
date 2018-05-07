#/bin/sh

RM="rm -rvf"
PWD=$(pwd)

FILES=$(find . -name CMakeFiles)
if [ ! -z "$FILE" ]; then
    $RM $PWD/$FILES
fi

FILES=$(find . -name cmake_install.cmake)
if [ ! -z "$FILE" ]; then
    $RM $PWD/$FILES
fi

FILES=$(find . -name Makefile)
if [ ! -z "$FILE" ]; then
    $RM $PWD/$FILES
fi

$RM $PWD/CMakeCache.txt
$RM $PWD/CMakeFiles
$RM $PWD/cmake_install.cmake
$RM $PWD/Makefile

$RM $PWD/bin/*
