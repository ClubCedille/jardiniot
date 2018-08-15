#! /bin/bash

if command -v virtualenv >/dev/null 2>&1 ; then
	virtualenv -p python3 env
	source env/bin/activate
	pip install -r requirements.txt
else
	echo "Virtualenv est nécessaire afin de poursuivre l'installation"
fi


