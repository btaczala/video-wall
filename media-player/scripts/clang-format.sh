#!/bin/bash

git_root=$(git rev-parse --show-toplevel)
old_dir=$(pwd)

cd $git_root

files=$(find $git_root -name *.cxx -o -name *.h -o -name *.hpp | grep -v 3rdParty | xargs clang-format -i)

