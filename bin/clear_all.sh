#!/bin/bash
stop_register_server
stop_config_server
cd ../src/platform
make uninstall

cd ../orion_link_db
make uninstall

cd ../api_gateway
make uninstall

cd ../register_server
make uninstall

cd ../register_client
make uninstall

cd ../config_server
make uninstall

cd ../config_client
make uninstall