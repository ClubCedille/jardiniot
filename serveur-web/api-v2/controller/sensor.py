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
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

from flask import request
import json
from database.database import Database
from datetime import datetime, timezone

class SensorController(object):

	# The following three functions are used to create modification commands
	def createCommandLight(white, blue, red):
		# The sensor ID (1) is hardcoded for now, same for the pins (9, 10 and 11) which are hardcoded.
		return "id 1 c 2 200 i " + str(9 * 256 + int(white)) + " " + str(10 * 256 + int(blue)) + " " + str(11 * 256 + int(red))

	def createCommandLateralFan(value):
		return "id 5 c 4 250 i " + str(5 * 256 + int(value))

	def createCommandHeatsinkFan(value):
		return "id 6 c 4 250 i " + str(6 * 256 + int(value))


	"""
	GET SENSORS
	Renvoie une liste de senseurs avec leurs noms
	"""
	def get_sensors():
		db = Database.get_instance()
		# Sélectionner les dernières données des senseurs
		temperature = db.execute("SELECT * FROM valeurs WHERE senseur='Temperature' ORDER BY date DESC LIMIT 1;")
		humidite = db.execute("SELECT * FROM valeurs WHERE senseur='Humidite' ORDER BY date DESC LIMIT 1;")

		senseurs = [
			{
				"id" : 1,
				"date" : temperature[0][0],
				"name" : temperature[0][1],
				"value" : temperature[0][2]
			},
			{
				"id" : 2,
				"date" : humidite[0][0],
				"name" :  humidite[0][1],
				"value" : humidite[0][2]
			}
		]

		return {"sensors": senseurs }


	"""
	UPDATE LIGHTS
	Modifier la luminosité de chaque couleur de DEL
	"""
	def update_lights(request):
		red = request.data['red']
		blue = request.data['blue']
		white = request.data['white']

		# Mettre à jour leur valeur dans la base de données
		db = Database.get_instance()
		datenow = str(datetime.now(timezone.utc))
		db.executeparam("INSERT INTO valeurs(date, senseur, valeur) VALUES (?, ?, ?);", [datenow, 'Red', str(red)])
		db.executeparam("INSERT INTO valeurs(date, senseur, valeur) VALUES (?, ?, ?);", [datenow, 'Blue', str(blue)])
		db.executeparam("INSERT INTO valeurs(date, senseur, valeur) VALUES (?, ?, ?);", [datenow, 'White', str(white)])

		# Command
		command = SensorController.createCommandLight(white, blue, red)
		db.executeparam("INSERT INTO filecommandes(date, command) VALUES (?, ?);", [datenow, command])
		return ('', 204)


	"""
	GET LIGHTS
	Renvoie les valeurs de luminosité de chaque couleur de DEL
	"""
	def get_lights():
		db = Database.get_instance()
		# Sélectionner les dernières données de luminosité
		red = db.execute("SELECT * FROM valeurs WHERE senseur='Red' ORDER BY date DESC LIMIT 1;")
		blue = db.execute("SELECT * FROM valeurs WHERE senseur='Blue' ORDER BY date DESC LIMIT 1;")
		white = db.execute("SELECT * FROM valeurs WHERE senseur='White' ORDER BY date DESC LIMIT 1;")

		lights = [
			{
				"id" : 1,
				"date" : red[0][0],
				"name" : red[0][1],
				"value" : red[0][2]
			},
			{
				"id" : 2,
				"date" : blue[0][0],
				"name" :  blue[0][1],
				"value" : blue[0][2]
			},
			{
				"id" : 3,
				"date" : white[0][0],
				"name" :  white[0][1],
				"value" : white[0][2]
			}
		]

		return {"lights": lights}


	"""
	UPDATE FANS
	Modifier la vitesse d'un ventilateur
	"""
	def update_fans(request):
		# S'il manque des virgules (,) au JSON, il ce peut que le code s'arrête ici.
		reqdata = request.data

		fanl = reqdata.get('fanl')
		fanh = reqdata.get('fanh')

		datenow = str(datetime.now(timezone.utc))

		# Ventilateur latéral
		if fanl is not None:
			# Mettre à jour leur valeur dans la base de données
			db = Database.get_instance()
			db.executeparam("INSERT INTO valeurs(date, senseur, valeur) VALUES (?, ?, ?);", [datenow, 'FanL', str(fanl)])
			# Command
			command = SensorController.createCommandLateralFan(fanl)
			db.executeparam("INSERT INTO filecommandes(date, command) VALUES (?, ?);", [datenow, command])

		# Ventilateur du heatsink
		if fanh is not None:
			# Mettre à jour leur valeur dans la base de données
			db = Database.get_instance()
			db.executeparam("INSERT INTO valeurs(date, senseur, valeur) VALUES (?, ?, ?);", [datenow, 'FanH', str(fanh)])
			# Command
			command = SensorController.createCommandHeatsinkFan(fanh)
			db.executeparam("INSERT INTO filecommandes(date, command) VALUES (?, ?);", [datenow, command])

		return ('', 204)


	"""
	GET FANS
	Renvoie la vitesse d'un ventilateur
	"""
	def get_fans():

		db = Database.get_instance()
		# Sélectionner les dernières données de luminosité
		fanl = db.execute("SELECT * FROM valeurs WHERE senseur='FanL' ORDER BY date DESC LIMIT 1;")
		fanh = db.execute("SELECT * FROM valeurs WHERE senseur='FanH' ORDER BY date DESC LIMIT 1;")

		fans = [
			{
				"id" : 1,
				"date" : fanl[0][0],
				"name" : fanl[0][1],
				"value" : fanl[0][2]
			},
			{
				"id" : 2,
				"date" : fanh[0][0],
				"name" :  fanh[0][1],
				"value" : fanh[0][2]
			}
		]

		return {"fans": fans}
