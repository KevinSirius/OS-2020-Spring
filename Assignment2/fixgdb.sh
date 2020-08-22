#!/bin/bash

if [ "$(hostname)" != 'os3224' ]; then
    echo 'is this being run on the vm?'
    exit 1
fi

cd /opt/pwndbg
sudo git pull
