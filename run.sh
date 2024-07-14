#!/bin/bash

set -e

source .env
USE_SSH=false

OPTIONS=$(getopt -o '' -l 'use_ssh' -- "$@")
if [ $? -ne 0 ]; then
    echo "Failed to parse options."
    exit 1
fi
eval set -- $OPTIONS

while true; do
    case "$1" in
    --use_ssh)
        USE_SSH=true
        shift
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

PROJECT_DIR=$(realpath $(dirname $0))
BUILD_DIR=$(realpath build)

# Compile the .uf2
cd $BUILD_DIR
cmake .. -DPICO_SDK_PATH="$PICO_SDK_PATH"
make -j$(nproc)

if [ $USE_SSH = true ]; then
    # Upload to the ssh server and run

    SCP_DEST_DIR="/home/$SSH_USER/dron"

    scp "$PROJECT_DIR/host_run.sh" \
        "$BUILD_DIR/drone.uf2" \
        "$BUILD_DIR/controller.uf2" \
        "$SSH_USER@$SSH_HOST:$SCP_DEST_DIR"

    ssh "$SSH_USER@$SSH_HOST" << EOF
        cd $SCP_DEST_DIR
        ./host_run.sh
    EOF

else
    # Run locally
    ./host_run.sh
fi