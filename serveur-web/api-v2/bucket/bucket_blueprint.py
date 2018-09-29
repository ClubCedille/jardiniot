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

from flask import Blueprint
from flask import request
from bucket.bucket import Bucket
import json
from database.database import Database

from datetime import datetime, timezone

# Create a bucket_bluprint, which make it exportable for other modules to use.
# We bind new routes to this blueprint, which will then be used by the
# main Flask process when handling requests.
bucket_blueprint = Blueprint("bucket_blueprint", __name__)

# The following three functions are used to create modification commands
def createCommandLight(white, blue, red):
	# The sensor ID (1) is hardcoded for now, same for the pins (9, 10 and 11) which are hardcoded.
	return "id 1 c 2 200 i " + str(9 * 256 + int(white)) + " " + str(10 * 256 + int(blue)) + " " + str(11 * 256 + int(red))

def createCommandLateralFan(value):
	return "id 5 c 4 250 i " + str(5 * 256 + int(value))

def createCommandHeatsinkFan(value):
	return "id 6 c 4 250 i " + str(6 * 256 + int(value))

"""
INDEX
C'est ici qu'on enverra la liste des buckets.
"""
@bucket_blueprint.route("/bucket", methods=["GET"])
def index():
	print("Acces a /bucket avec GET")

	buckets = Bucket.get_all()
	if buckets is not None:
		return [bucket.to_detailed_json() for bucket in buckets]
	else:
		response = {
			"error":1,
			"message":"No bucket found"
			}
		return (response, 404)


"""
CREATE
C'est ici qu'on recoit les informations pour enregistrer un nouveau bucket
"""
@bucket_blueprint.route("/bucket", methods=["POST"])
def create():
	print("Acces a /bucket avec POST")
	try:
		if request.headers['Content-Type'] != 'application/json':
			response = {
				"error":1,
				"message":"Content-Type is not application/json"
				}
			return (response, 400)
		elif request.is_json:

			name = request.data['name']
			if name is None: raise Exception()

			try:
				id_plant = request.data['id_plant']
			except Exception:
				id_plant = 0

			ip_address = request.data['ip_address']
			if ip_address is None: raise Exception()

			new_bucket = Bucket(None, id_plant, name, ip_address)

			new_bucket = new_bucket.save()
			return new_bucket.to_detailed_json()
		else:
			raise Exception()
	except Exception as e:
		print("ERROR: Request is not JSON or has missing fields.")
		print(e)
		response = {
			"error":1,
			"message":"Missing fields in JSON"
			}
		return (response, 404)


"""
/bucket/id
C'est ici qu'on enverra la liste des buckets.
"""
@bucket_blueprint.route("/bucket/<id>")
def id(id):
	bucket = Bucket.get(id)
	if bucket is not None:
		return bucket.to_detailed_json()
	else:
		response = {
			"error":1,
			"message":"bucket id "+str(id)+" not found"
			}
		return (response, 404)

"""
GET SENSORS
C'est la requête à faire pour recevoir une liste de senseurs avec leurs noms
"""
@bucket_blueprint.route("/sensors")
def get_sensor_names():
	print("Acces a /sensors")

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

	return senseurs

"""
UPDATE LIGHTS et GET LIGHTS
POST: C'est la requête à faire pour modifier la luminosité de chaque couleur de DEL
GET: C'est la requête à faire pour obtenir les valeurs de luminosité de chaque couleur de DEL

Le POST peut être testé avec ce JSON:
{
"blue": 255,
"red": 128,
"white": 59
}
"""
@bucket_blueprint.route("/lights", methods=['GET', 'POST'])
def update_lights():
	print("Acces a /lights")

	if request.method == 'POST':
		if request.headers['Content-Type'] != 'application/json':
			print("ERROR: Content type is not JSON in HTTP header.")
		elif request.is_json:
			print("header: ", request.headers['Content-Type'])

			# S'il manque des virgules (,) au JSON, il ce peut que le code s'arrête ici.
			print("data: ", request.data)

			red = request.data['red']
			blue = request.data['blue']
			white = request.data['white']
			print("red:", red, ", blue:", blue, ", white:", white)

			# Mettre à jour leur valeur dans la base de données
			db = Database.get_instance()
			datenow = str(datetime.now(timezone.utc))
			db.execute("INSERT INTO valeurs(date, senseur, valeur) VALUES ('" + datenow + "', 'Red', '" + str(red) + "');")
			db.execute("INSERT INTO valeurs(date, senseur, valeur) VALUES ('" + datenow + "', 'Blue', '" + str(blue) + "');")
			db.execute("INSERT INTO valeurs(date, senseur, valeur) VALUES ('" + datenow + "', 'White', '" + str(white) + "');")

			# Command
			command = createCommandLight(white, blue, red)
			print(command)
			db.execute("INSERT INTO filecommandes(date, command) VALUES ('" + datenow + "', '" + command + "');")
		else:
			print("ERROR: Request is not JSON.")

		return ('', 204)

	else:
		db = Database.get_instance()
		# Sélectionner les dernières données de luminosité
		red = db.execute("SELECT * FROM valeurs WHERE senseur='Red' ORDER BY date DESC LIMIT 1;")
		blue = db.execute("SELECT * FROM valeurs WHERE senseur='Blue' ORDER BY date DESC LIMIT 1;")
		white = db.execute("SELECT * FROM valeurs WHERE senseur='White' ORDER BY date DESC LIMIT 1;")

		senseurs = [
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

		return senseurs

"""
UPDATE FANS et GET FANS
POST: C'est la requête à faire pour modifier la vitesse d'un ventilateur
GET: C'est la requête à faire pour obtenir la vitesse d'un ventilateur

Le POST peut être testé avec ce JSON:
{
"fanl": 255,
"fanh": 255
}
"""
@bucket_blueprint.route("/fans", methods=['GET', 'POST'])
def update_fans():
	print("Acces a /fans")

	if request.method == 'POST':
		if request.headers['Content-Type'] != 'application/json':
			print("ERROR: Content type is not JSON in HTTP header.")
		elif request.is_json:
			print("header: ", request.headers['Content-Type'])

			# S'il manque des virgules (,) au JSON, il ce peut que le code s'arrête ici.
			reqdata = request.data
			print("data: ", request.data)

			fanl = reqdata.get('fanl')
			fanh = reqdata.get('fanh')
			print("fanl:", fanl, ", fanh:", fanh)

			datenow = str(datetime.now(timezone.utc))

			# Ventilateur latéral
			if fanl is not None:
				# Mettre à jour leur valeur dans la base de données
				db = Database.get_instance()
				db.execute("INSERT INTO valeurs(date, senseur, valeur) VALUES ('" + datenow + "', 'FanL', '" + str(fanl) + "');")
				# Command
				command = createCommandLateralFan(fanl)
				print(command)
				db.execute("INSERT INTO filecommandes(date, command) VALUES ('" + datenow + "', '" + command + "');")

			# Ventilateur du heatsink
			if fanh is not None:
				# Mettre à jour leur valeur dans la base de données
				db = Database.get_instance()
				db.execute("INSERT INTO valeurs(date, senseur, valeur) VALUES ('" + datenow + "', 'FanH', '" + str(fanh) + "');")
				# Command
				command = createCommandHeatsinkFan(fanh)
				print(command)
				db.execute("INSERT INTO filecommandes(date, command) VALUES ('" + datenow + "', '" + command + "');")
		else:
			print("ERROR: Request is not JSON.")

		return ('', 204)

	else:
		db = Database.get_instance()
		# Sélectionner les dernières données de luminosité
		fanl = db.execute("SELECT * FROM valeurs WHERE senseur='FanL' ORDER BY date DESC LIMIT 1;")
		fanh = db.execute("SELECT * FROM valeurs WHERE senseur='FanH' ORDER BY date DESC LIMIT 1;")

		senseurs = [
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

		return senseurs
