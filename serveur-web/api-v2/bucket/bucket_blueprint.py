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
import json
from database.database import Database

# Create a bucket_bluprint, which make it exportable for other modules to use.
# We bind new routes to this blueprint, which will then be used by the
# main Flask process when handling requests.
bucket_blueprint = Blueprint("bucket_blueprint", __name__)

"""
INDEX
C'est ici qu'on enverra la liste des buckets.
"""
@bucket_blueprint.route("/bucket")
def index():
	print("Acces a /bucket")

	buckets = [
		{
			"id" : 1,
			"name" : "orange"
		},
		{
			"id" : 2,
			"name" : "vert"
		}
		]

	return buckets

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
			"date" : temperature[0][0],
			"name" :  temperature[0][1],
			"value" : temperature[0][2]
		}
		]

	return senseurs

"""
UPDATE LIGHTS
C'est la requête à faire pour modifier la luminosité de chaque couleur de DEL

Peut être testé avec ce JSON:
{
"blue": 255,
"red": 128,
"white": 59
}
"""
@bucket_blueprint.route("/lights", methods=["POST"])
def update_lights():
	print("Acces a /lights")

	if request.headers['Content-Type'] != 'application/json':
		print("ERROR: Content type is not JSON in HTTP header.")
	elif request.is_json:
		print("header: ", request.headers['Content-Type'])

		# S'il manque des virgules (,) au JSON, il ce peut que le code s'arrête ici.
		print("data: ", request.data)

		red = request.data['red']
		blue = request.data['blue']
		white = request.data['white']

		# TODO: Générer une commande de mise à jour de la couleur des lumières à mettre dans la base de données
		print("red:", red, ", blue:", blue, ", white:", white)
	else:
		print("ERROR: Request is not JSON.")

	return ('', 204)

