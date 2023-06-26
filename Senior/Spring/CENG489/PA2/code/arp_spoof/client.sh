#!/bin/bash

DELAY=1
SERVER_IP="192.168.56.20"
SERVER_PORT=5555

while true
do
  STATUS_CODE=$(curl -s -o /dev/null -w "%{http_code}" ${SERVER_IP}:${SERVER_PORT})
  echo Request is sent. Response is $STATUS_CODE
  sleep $DELAY
done
