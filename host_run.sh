#!/bin/bash

set -e

OPTIONS=$(getopt -o '' -l 'serial_number:,' -- "$@")
if [ $? -ne 0 ]; then
    echo "Failed to parse options."
    exit 1
fi
eval set -- $OPTIONS

while true; do
    case "$1" in
    --serial_number)
        SERIAL_NUMBER="$2"
        shift 2
        ;;
    --)
        shift
        break
        ;;
    *)
        break
        ;;
    esac
done

if [ -z $SERIAL_NUMBER ]; then
    echo "Serial number is required."
    exit 1
fi

PICO_MOUNT_PATH="/media/$USER/pico"

# Stop pico by setting the baud rate to 1200
sudo stty -F $PICO_COM_DIR 1200

# Mount it as storage
PICO_DEV_PATH=$(blkid | awk -F ':| ' '/LABEL="RPI-RP2"/{print $1}')
sudo mount $PICO_DEV_PATH $PICO_MOUNT_PATH

# Load the program
mv drone.uf2 $PICO_MOUNT_PATH