# Copyright (C) 2018 Roch D'Amour <roch.damour@gmail.com>
# Copyright (C) 2018 Alexandre-Xavier Labonté-Lamoureux
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

# Fix de compatibilite des imports pour "Migration"
try:
    from database import Database
except BaseException:
    from database.database import Database

from datetime import datetime, timezone

# Recouvre l'instance de la DB
db = Database.get_instance()

# Recouvre la version.
current_version = db.get_version()

banner = r"""
     _               _ _       ___    _____
    | | __ _ _ __ __| (_)_ __ |_ _|__|_   _|
 _  | |/ _` | '__/ _` | | '_ \ | |/ _ \| |
| |_| | (_| | | | (_| | | | | || | (_) | |
 \___/ \__,_|_|  \__,_|_|_| |_|___\___/|_|
"""

print(banner)
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
    db.executeparam("INSERT INTO meta values (?);", [str(DATABASE_VERSION)])
    print("DATABASE CREATED.")
    current_version = db.get_version()

DATABASE_VERSION = 1
if current_version < DATABASE_VERSION:
    print("migrating to " + str(DATABASE_VERSION))
    db.execute("CREATE TABLE valeurs (date text, senseur text, valeur text);")
    datenow = str(datetime.now(timezone.utc))
    db.executeparam("INSERT INTO valeurs(date, senseur, valeur) VALUES (?, 'Temperature', 'N/A');", [datenow])
    db.executeparam("INSERT INTO valeurs(date, senseur, valeur) VALUES (?, 'Humidite', 'N/A');", [datenow])
    db.update_version(DATABASE_VERSION)
    print("DB updated to version " + str(db.get_version()))

DATABASE_VERSION = 2
if current_version < DATABASE_VERSION:
    print("migrating to " + str(DATABASE_VERSION))
    datenow = str(datetime.now(timezone.utc))
    db.executeparam("INSERT INTO valeurs(date, senseur, valeur) VALUES (?, 'Red', '255');", [datenow])
    db.executeparam("INSERT INTO valeurs(date, senseur, valeur) VALUES (?, 'Blue', '255');", [datenow])
    db.executeparam("INSERT INTO valeurs(date, senseur, valeur) VALUES (?, 'White', '255');", [datenow])
    db.update_version(DATABASE_VERSION)
    print("DB updated to version " + str(db.get_version()))

DATABASE_VERSION = 3
if current_version < DATABASE_VERSION:
    print("migrating to " + str(DATABASE_VERSION))
    db.execute("CREATE TABLE filecommandes (date text, command text);")
    db.executeparam("INSERT INTO valeurs(date, senseur, valeur) VALUES (?, 'FanL', '255');", [datenow])
    db.executeparam("INSERT INTO valeurs(date, senseur, valeur) VALUES (?, 'FanH', '255');", [datenow])
    db.update_version(DATABASE_VERSION)
    print("DB updated to version " + str(db.get_version()))

DATABASE_VERSION = 4
if current_version < DATABASE_VERSION:
    print("migrating to " + str(DATABASE_VERSION))
    db.execute("create table bucket(id INTEGER PRIMARY KEY AUTOINCREMENT, id_plant number, name Nvarchar, ip_address Nvarchar ); ")
    db.update_version(DATABASE_VERSION)

    db.execute("INSERT INTO bucket('id_plant', 'name', 'ip_address') VALUES (1, 'jaune', '100.100.100.100'); ")
    db.execute("INSERT INTO bucket('id_plant', 'name', 'ip_address') VALUES (1, 'JardinIoT', '127.0.0.1'); ")
    db.execute("INSERT INTO bucket('id_plant', 'name', 'ip_address') VALUES (1, 'Orange julius', '127.0.0.1' ); ")
    db.update_version(DATABASE_VERSION)
    print("db updated to version " + str(db.get_version()))


"""
Migration example
"""
# DATABASE_VERSION = 1
# if current_version < DATABASE_VERSION:
#     print("migrating to " + str(DATABASE_VERSION))
#     db.execute("CREATE TABLE example(teste Nvarchar); ")
#     db.update_version(DATABASE_VERSION)
#     print("DB updated to version " + str(db.get_version()))
"""
Migration example end here
"""

print("most recent version is " + str(DATABASE_VERSION))
print("done.")
