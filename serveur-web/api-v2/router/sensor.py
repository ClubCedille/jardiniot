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

from flask import Blueprint
from flask import request
import json
from datetime import datetime, timezone

from controller.sensor import SensorController

# Create a bucket_bluprint, which make it exportable for other modules to use.
# We bind new routes to this blueprint, which will then be used by the
# main Flask process when handling requests.
sensor_blueprint = Blueprint("sensor_blueprint", __name__)


"""
GET => /sensor
Renvoies une liste de senseurs avec leurs noms
"""
@sensor_blueprint.route("/sensors")
def get_sensors():
	return SensorController.get_sensors()

"""
POST => /lights
Modifier la luminosité de chaque couleur de DEL

Le POST peut être testé avec ce JSON:
{
"red": 128,
"blue": 255,
"white": 59
}
"""
@sensor_blueprint.route("/lights", methods=['POST'])
def update_lights():
	if request.headers['Content-Type'] != 'application/json':
		print("ERROR: Content type is not JSON in HTTP header.")
	elif request.is_json:
		return SensorController.update_lights(request)
	else:
		print("ERROR: Request is not JSON.")
		return ('', 204)



"""
GET => /lights
Renvoie les valeurs de luminosité de chaque couleur de DEL
"""
@sensor_blueprint.route("/lights", methods=['GET'])
def get_lights():
	return SensorController.get_lights()


"""
UPDATE FANS et GET FANS
POST: C'est la requête à faire pour modifier la vitesse d'un ventilateur

Le POST peut être testé avec ce JSON:
{
"fanl": 255,
"fanh": 255
}
"""
@sensor_blueprint.route("/fans", methods=['POST'])
def update_fans():
	if request.headers['Content-Type'] != 'application/json':
		print("ERROR: Content type is not JSON in HTTP header.")
	elif request.is_json:
		return SensorController.update_fans(request)
	else:
		print("ERROR: Request is not JSON.")

	return ('', 204)

"""
GET => /fans
Retourne la vitesse d'un ventilateur
"""
@sensor_blueprint.route("/fans", methods=['GET'])
def get_fans():
	return SensorController.get_fans()
