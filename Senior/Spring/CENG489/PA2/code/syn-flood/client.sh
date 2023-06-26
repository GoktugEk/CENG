#!/bin/bash

DELAY=1
SERVER_IP="192.168.56.20"
SERVER_PORT=5555

while true
do
  STATUS_CODE=$(curl -o /dev/null -s -w "%{http_code}\n" http://${SERVER_IP}:${SERVER_PORT})
  echo $STATUS_CODE
  sleep $DELAY
done
