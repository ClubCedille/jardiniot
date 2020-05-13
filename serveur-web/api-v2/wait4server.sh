#!/bin/bash

while [ "$(curl -I http://127.0.0.1:5000/buckets 2>/dev/null | head -n 1 | cut -d$' ' -f2)" != "200" ]
do
	echo "waiting for server to start"
	echo $(curl -I http://127.0.0.1:5000/buckets 2>/dev/null | head -n 1 | cut -d$' ' -f2)
	sleep 1
done
