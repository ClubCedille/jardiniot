#! /bin/bash

# Copyright (C) 2018 Roch D'Amour <roch.damour@gmail.com>

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

if command -v pipenv >/dev/null 2>&1 ; then
	pipenv --three --site-packages install --dev
	cd database
	pipenv run python migration.py
	cd -
elif command -v virtualenv >/dev/null 2>&1 ; then
	echo "Pipenv indisponible, utilisation de virtualenv"
	virtualenv -p python3 env
	source env/bin/activate
	pip install -r requirements.txt
	cd database
	python migration.py
	cd -
else
	echo "Pipenv est nécessaire afin de poursuivre l'installation"
fi
