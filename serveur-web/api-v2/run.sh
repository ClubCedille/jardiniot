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

echo "Source l'environnement..."
source env/bin/activate
echo "initialize les variables d'environnements..."
FLASK_APP=app.py FLASK_ENV=developent FLASK_DEBUG=1 flask run
