FROM archlinux:latest

USER root

RUN pacman -Syu --noconfirm --needed sudo base base-devel cmake clang gcc ninja git gtest go

WORKDIR /app

COPY . .

USER fernando

RUN sudo chown --recursive fernando /app

#RUN git clone https://aur.archlinux.org/yay.git && cd yay && makepkg -si && cd -

RUN cmake -S . -B ./build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ && cmake --build ./build --config Debug --target all

CMD cd ./build && ctest