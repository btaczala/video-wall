#!/bin/bash

# pull image
docker pull bartekt/ubu-cef-sdl:ffmpeg-3
git_root=$(git rev-parse --show-toplevel)

old_dir=$(pwd)
cd $git_root/docker/mars-dev && docker build -t mars-dev .
cd $git_root
docker run --rm -v "$git_root":/usr/src -e USERID=$UID -it mars-dev /root/build.sh
