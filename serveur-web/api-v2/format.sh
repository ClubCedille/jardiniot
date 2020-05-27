#! /bin/bash

find **/*.py -exec autopep8 --in-place --global-config pyproject.toml --aggressive {} \;
