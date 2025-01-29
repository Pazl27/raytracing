#!/bin/bash

build() {
    if [ ! -d "build" ]; then
        mkdir build
    fi
    cd build
    cmake ..
    make
}

run() {
    build
    ./target/Raytracing
}

if [ "$1" == "run" ]; then
    run

elif [ "$1" == "clean" ]; then
    rm -rf build
    echo "Cleaned build directory"

else
    build
fi

