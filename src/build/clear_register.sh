#!/bin/bash
stop_register_server
cd ../platform
make uninstall
cd ../register_server
make uninstall
cd ../register_client
make uninstall