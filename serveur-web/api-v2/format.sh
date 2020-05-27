#! /bin/bash

find **/*.py -exec autopep8 --in-place --aggressive {} \;
