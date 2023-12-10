#!/bin/bash

MODULE_NAME="simple_char_driver"

# Load the module
sudo insmod $MODULE_NAME.ko

# Check if the module was loaded successfully
if [ $? -eq 0 ]; then
    echo "Module loaded successfully"
    
    # Create a device node
    sudo mknod /dev/simple_char_driver c $(grep $MODULE_NAME /proc/devices | awk '{print $1}') 0
    
    # Change permissions on the device node
    sudo chmod 666 /dev/simple_char_driver
else
    echo "Failed to load module"
    exit 1
fi
