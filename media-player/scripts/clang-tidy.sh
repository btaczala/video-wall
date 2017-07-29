#!/bin/bash

tmp_build_dir=$(mktemp -d)
git_root=$(git rev-parse --show-toplevel)
mp_dir=$git_root/media-player/
mp_srcs_dir=$mp_dir/srcs

old=$(pwd)
cd $tmp_build_dir

echo "cmake $mp_dir/ -DCMAKE_BUILD_TYPE=Debug -DBUILD_WITH_EXAMPLE=OFF -DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
cmake $mp_dir/ -DCMAKE_BUILD_TYPE=Debug -DBUILD_WITH_EXAMPLE=OFF -DBUILD_WITH_UNIT_TESTS=OFF -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCEF_ROOT=/home/bata/Projects/mars-linux/cef_binaries/cef_binary_3.3071.1643.ga83b8e9_linux64 >> clang.out
cd $mp_dir
ln -s  $tmp_build_dir/compile_commands.json

/usr/share/clang/run-clang-tidy.py -header-filter=$mp_srcs_dir -checks=boost-*,clang-analyzer-*,llvm-*,performance-* -p $tmp_build_dir

rm $mp_dir/compile_commands.json

cd $old
