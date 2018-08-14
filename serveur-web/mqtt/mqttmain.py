# Copyright (C) 2018 Alexandre-Xavier Labonté-Lamoureux
#
# JardinIoT is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# JardinIoT is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with JardinIoT.  If not, see <http://www.gnu.org/licenses/>.

# mqttmain.py
# MQTT component of the API
# Talks with the ESP8266 on the garden to change the sensor configuration
# Updates the database with information comming from the garden

# Requires: `pip3 install paho-mqtt`

import paho.mqtt.client as mqtt
import json

# Globals
TOPIC = "jardin"

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
	print("Connected with result code " + str(rc))

	# Subscribing in on_connect() means that if we lose the connection and
	# reconnect then subscriptions will be renewed.
	# Subscribe with QOS 2 (info: https://www.hivemq.com/blog/mqtt-essentials-part-6-mqtt-quality-of-service-levels)
	client.subscribe(TOPIC, 2)

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
	print(msg.topic + " " + str(msg.payload))
	if msg.topic == TOPIC:
		try:
			message = msg.payload.decode("utf-8")	# Convert to string
			print(message)
			stuff = json.loads(message)
			print(stuff)
		except ValueError as e:
			print("ValueError: " + str(e))

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("127.0.0.1", 1883, 30)

# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
client.loop_forever()

