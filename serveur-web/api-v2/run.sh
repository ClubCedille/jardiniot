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

echo "Initialise les variables d'environnement..."
FLASK_APP=app.py
FLASK_ENV=development
FLASK_DEBUG=1

if command -v pipenv >/dev/null &2>1; then
	pipenv run flask run
elif command -v virtualenv >/dev/null &2>1; then
	echo "Source l'environnement..."
	source env/bin/activate
	flask run
else
	echo "Pipenv et virtualenv non trouvé! Roule le truc toi-même."
fi
