#!/bin/bash

rm -rf ./objs/*

sed -ri "s:.*(AUX_MODULES.*valid):\1:" modules.cfg &&

sed -r "s:.*(#.*SUBPIXEL_RENDERING) .*:\1:" \
    -i include/freetype/config/ftoption.h  &&

./configure --prefix=/usr --enable-freetype-config --disable-shared --enable-static --with-pic &&
make -j$(cat /proc/cpuinfo | awk '/^processor/{print $3}' | wc -l)
