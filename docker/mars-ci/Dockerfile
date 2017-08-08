FROM bartekt/ubu-cef-sdl
MAINTAINER Bartosz Taczała <bartosz.taczala@mobica.com>

ARG GIT_USERNAME
ARG GIT_PASSWORD

RUN echo machine gitlab.mobica.com > /root/.netrc
RUN echo "  login $GIT_USERNAME" >> /root/.netrc
RUN echo "  password $GIT_PASSWORD" >> /root/.netrc

ENV CEF_ROOT=/root/cef/cef_binary_3.3112.1652.g8c8deea_linux64

ARG CACHEBUST=1

RUN mkdir ~/repo
RUN cd ~/repo && git clone --depth 1 https://gitlab.mobica.com/bartosz.taczala/mars-linux.git
RUN cd /root/repo/mars-linux/media-player && git submodule update --init
RUN cd /root/repo/mars-linux/media-player && mkdir build
RUN cd /root/repo/mars-linux/media-player/build && cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_WITH_EXAMPLES=ON -DBUILD_WITH_INTEGRATION_TESTS=OFF -DCEF_ROOT=$CEF_ROOT -DBUILD_WITH_COVERAGE=ON

RUN cd /root/repo/mars-linux/media-player/build && make -j$(nproc) && make tests && make coverage
