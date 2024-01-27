#!/bin/bash
stop_register_server
stop_config_server
stop_api_gateway
stop_auth
stop_log
cd ../src/platform
make uninstall

cd ../orion_link_db
make uninstall

cd ../log
make uninstall

cd ../auth
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

cd ../disk_proto
make uninstall

cd ../dir_service
make uninstall

cd ../build_conf
make uninstall

cd ../ol_add_user
make uninstall