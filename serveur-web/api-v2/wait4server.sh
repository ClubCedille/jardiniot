#!/bin/bash

while [ "$(curl -s -I http://127.0.0.1:5000/buckets 2>/dev/null | head -n 1 | cut -d$' ' -f2)" != "200" ]
do
	echo "waiting for server to start"
	echo $(curl -s -I http://127.0.0.1:5000/buckets | head -n 1 | cut -d$' ' -f2)
	echo $(curl -s -I http://127.0.0.1:5050/buckets | head -n 1 | cut -d$' ' -f2)
	echo $(curl -I http://127.0.0.1:5000/buckets)
	echo $(curl -I http://127.0.0.1:5000/buckets)
	echo "==============="
	curl -I http://127.0.0.1:5000/buckets
	curl -I http://127.0.0.1:5000/buckets
	echo "==============="
	ip a
	echo $(curl -I http://localhost:5000/buckets)
	sleep 1
done
