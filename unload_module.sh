#!/bin/bash

MODULE_NAME="simple_char_driver"

# Unload the module
sudo rmmod $MODULE_NAME

# Check if the module was unloaded successfully
if [ $? -eq 0 ]; then
    # Remove the device node
    sudo rm /dev/simple_char_driver
    
    echo "Module unloaded successfully"
else
    echo "Failed to unload module"
    exit 1
fi
