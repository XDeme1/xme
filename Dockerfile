FROM archlinux:latest

WORKDIR /app

COPY . .

USER root

RUN pacman -Syu --noconfirm --needed cmake clang gcc ninja git gtest
RUN cmake -S . -B ./build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ && cmake --build ./build --config Debug --target all

CMD cd ./build && ctest