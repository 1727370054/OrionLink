#!/bin/bash
cd ../src/platform
make clean
make proto
make -j8
make install

cd ../orion_link_db
make clean
make -j8
make install

cd ../register_client
make clean
make -j8
make install

cd ../config_client
make clean
make -j8
make install

cd ../api_gateway
make clean
make watch_api_gateway
make -j8
make install

cd ../register_server
make clean
make -j8
make watch_register_server
make install

cd ../config_server
make clean
make -j8
make watch_config_server
make install





