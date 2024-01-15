#!/bin/bash
cd ./src/platform
make clean
make -j8
make install

cd ../register_server
make clean
make -j8
make watch_register_server
make install

cd ../register_client
make clean
make -j8

cd ../config_server
make clean
make -j8
make install

cd ../config_client
make clean
make -j8





