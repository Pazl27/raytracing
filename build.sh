#!/bin/bash

build() {
    if [ ! -d "build" ]; then
        mkdir build 
    fi
    cd build
    cmake -DCMAKE_BUILD_TYPE=Debug ..
    cmake --build . --config Debug
}

run() {
    build
    ./debug/Raytracing
}

if [ "$1" == "run" ]; then
    run

elif [ "$1" == "clean" ]; then
    rm -rf build
    echo "Cleaned build directory"

else
    build
fi

