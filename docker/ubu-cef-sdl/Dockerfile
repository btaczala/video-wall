FROM ubuntu:16.04
MAINTAINER Bartosz Taczała <bartosz.taczala@mobica.com>

RUN apt-get update
RUN apt-get install -y libsdl2-dev cmake clang valgrind doxygen wget libgtk2.0-dev \
            libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev libboost-all-dev libavcodec-dev \
            libavdevice-dev libnss3 libxtst-dev libgconf-2-4 git lcov

RUN mkdir -p ~/cef
RUN cd ~/cef && wget http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1652.g8c8deea_linux64.tar.bz2
RUN cd ~/cef && tar xf cef_binary_3.3112.1652.g8c8deea_linux64.tar.bz2

RUN mkdir -p ~/cef/cef_binary_3.3112.1652.g8c8deea_linux64/build/
RUN cd ~/cef/cef_binary_3.3112.1652.g8c8deea_linux64/ && sed '/^add_subdirectory[\(]tests[\/].*/d' -i CMakeLists.txt
RUN cd ~/cef/cef_binary_3.3112.1652.g8c8deea_linux64/build/ && cmake .. -DCMAKE_BUILD_TYPE=Debug
RUN cd ~/cef/cef_binary_3.3112.1652.g8c8deea_linux64/build/ && make -j$(nproc) libcef_dll_wrapper

ENV CEF_ROOT=~/cef/cef_binary_3.3112.1652.g8c8deea_linux64/
