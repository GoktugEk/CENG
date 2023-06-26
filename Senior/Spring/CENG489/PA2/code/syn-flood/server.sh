#!/bin/bash

echo "Starting server on the port 5555"
python3 -m http.server -b 192.168.56.20 5555
