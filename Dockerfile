FROM ubuntu:latest

RUN apt-get update && apt-get -y install cmake ninja-build git clang

COPY . /app
WORKDIR /app

RUN cmake -S . -B ./build/Debug -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++
RUN cmake --build ./build/Debug --config Debug --target all
CMD cmake --build ./build/Debug --config Debug --target test
