#!/bin/sh
set -e
SCRIPT_DIR=$(dirname "$0")

# sh does not support pushd/popd
ORIG_WD=$(pwd)
cd ${SCRIPT_DIR}

mkdir -p build
cd build
cmake .. \
    -DCMAKE_INSTALL_PREFIX=${OUTDIR} \
    -DBOOST_ROOT=/opt/boost/boost_1_70_0/ \
    -DCMAKE_CXX_COMPILER=clang++
cmake --build . && ctest

cd ${ORIG_WD}
