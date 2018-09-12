# Copyright (C) 2018 Roch D'Amour <roch.damour@gmail.com> 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

try:
	from database import Database
except:
	from database.database import Database

from datetime import datetime, timezone

# Recouvre l'instance de la DB
db = Database.get_instance()

# Recouvre la version.
current_version = db.get_version()

print("     _               _ _       ___    _____")
print("    | | __ _ _ __ __| (_)_ __ |_ _|__|_   _|")
print(" _  | |/ _` | '__/ _` | | '_ \ | |/ _ \| |")
print("| |_| | (_| | | | (_| | | | | || | (_) | |")
print(" \___/ \__,_|_|  \__,_|_|_| |_|___\___/|_|")

print("Current database version is " + str(current_version))


"""
Copy/paste the example block to create a new database "version".

DO NOT MODIFY OLD MIGRATIONS BLOCK.
"""


"""
New database
"""
DATABASE_VERSION = 0
if current_version is None:
	print("NO DATABASE FOUND.")
	db.execute("CREATE TABLE meta(version integer); ")
	db.execute("INSERT INTO meta values ('"+str(DATABASE_VERSION)+"')")
	print("DATABASE CREATED.")
	current_version = db.get_version()

DATABASE_VERSION = 1
if current_version < DATABASE_VERSION:
	print("migrating to " + str(DATABASE_VERSION))
	db.execute("CREATE TABLE valeurs (date text, senseur text, valeur text);")
	datenow = str(datetime.now(timezone.utc))
	db.execute("INSERT INTO valeurs(date, senseur, valeur) VALUES ('" + datenow + "', 'Temperature', 'N/A');")
	db.execute("INSERT INTO valeurs(date, senseur, valeur) VALUES ('" + datenow + "', 'Humidite', 'N/A');")
	db.update_version(DATABASE_VERSION)
	print("DB updated to version " + str(db.get_version()))

"""
Migration example
"""
# DATABASE_VERSION = 1
# if current_version < DATABASE_VERSION:
# 	print("migrating to " + str(DATABASE_VERSION))
# 	db.execute("CREATE TABLE example(teste Nvarchar); ")
# 	db.update_version(DATABASE_VERSION)
# 	print("DB updated to version " + str(db.get_version()))
"""
Migration example end here
"""

print("most recent version is "+ str(DATABASE_VERSION))
print("done.")
