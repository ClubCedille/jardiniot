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

# fakejardin.py
# Used to emulate the garden for testing

# Requires: `pip3 install paho-mqtt`

import paho.mqtt.client as mqtt
import time
import random

# Globals
TOPIC_SEND = "jardin_out"
TOPIC_RECEIVE = "jardin_in"
process = True

# The callback for when the client receives a CONNACK response from the server.


def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe(TOPIC_RECEIVE, 2)

# The callback for when a PUBLISH message is received from the server.


def on_message(client, userdata, msg):
    print(msg.topic + " " + str(msg.payload))
    if msg.topic == TOPIC_SEND and msg.payload.decode("utf-8") == "die":
        client.disconnect()
        global process
        process = False


client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("127.0.0.1", 1883, 30)

# Subscribe with QOS 2 (info: https://www.hivemq.com/blog/mqtt-essentials-part-6-mqtt-quality-of-service-levels)
client.subscribe(TOPIC_SEND, 2)

print("  **** JARDIN EMULATOR STARTED ****  ")

while process:
    time.sleep(1)
    temp = str(random.randint(28, 33))
    humi = str(random.randint(30, 55))
    client.publish(
        TOPIC_SEND,
        payload="{\"temperature\": \"" +
        temp +
        "°\", \"humidite\": \"" +
        humi +
        "%\"}",
        qos=0,
        retain=False)
    client.loop_start()
