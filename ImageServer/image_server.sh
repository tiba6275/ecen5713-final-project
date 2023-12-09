#!/bin/bash

cleanup() {
    echo "Caught SIGINT, exiting..."
    exit 0
}

ip=$(ip addr show enp0s3 | grep 'inet ' | awk '{print $2}' | cut -d/ -f1)
n=0
while true; do
    fileName="diff${n}.jpg"
    gst-launch-1.0 tcpserversrc host=$ip port=9000 ! filesink location="$fileName"
    ((n++))
done

