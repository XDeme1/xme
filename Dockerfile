FROM ubuntu:latest
RUN apt-get update && apt-get -y install software-properties-common && add-apt-repository universe
RUN apt-get update && apt-get -y install cmake ninja-build git
RUN apt-get -y install clang-11

COPY . /app
WORKDIR /app

#RUN cmake -S . -B ./build/clang-10/Debug -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=/usr/lib/llvm-10/bin/clang -DCMAKE_CXX_COMPILER=/usr/lib/llvm-10/bin/clang++ && cmake --build ./build/clang-10/Debug --config Debug --target all
RUN cmake -S . -B ./build/clang-11/Debug -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=/usr/lib/llvm-11/bin/clang -DCMAKE_CXX_COMPILER=/usr/lib/llvm-11/bin/clang++ \
    && cmake --build ./build/clang-11/Debug --config Debug --target all

CMD cmake --build ./build/clang-11/Debug --config Debug --target test
