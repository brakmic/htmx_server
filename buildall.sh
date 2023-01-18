#!/bin/bash
rm -rf builddir
meson setup builddir --native-file native.build
meson compile -C builddir