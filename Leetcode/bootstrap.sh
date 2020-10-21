#!/bin/bash

# Bootstrap script to kick start writing normal solution

if [ -z "$1" ]; then
    echo "Error: require target problem number"
    echo "Usage: ./bootstrap.sh <problem-number>"
    return 1
fi

if [ -d "$1" ]; then
    echo "Target problem exists. Cannot create new"
    return 1
fi

mkdir "$1"
cp Makefile-template "$1/Makefile"
cp template-main.cpp "$1/main.cpp"
touch "$1/testcases.txt"
