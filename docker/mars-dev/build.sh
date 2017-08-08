#!/bin/bash

src_dir=/usr/src/
media_player_dir=$src_dir/media-player
build_dir=$(mktemp -d)

cd $build_dir
cmake $media_player_dir -DCMAKE_BUILD_TYPE=Debug -DBUILD_WITH_EXAMPLES=ON -DBUILD_WITH_INTEGRATION_TESTS=OFF -DCEF_ROOT=$CEF_ROOT -DBUILD_WITH_COVERAGE=ON
make -j$(nproc) && make test
