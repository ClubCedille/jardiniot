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
import sqlite3
from datetime import datetime, timezone

# Globals
TOPIC_RECEIVE = "jardin_out"
TOPIC_SEND = "jardin_in"
DBNAME = "database/JardinIoT.db"


def main():
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect("127.0.0.1", 1883, 30)

    # Create the database
    conn = sqlite3.connect(DBNAME)
    c = conn.cursor()
    # Check if table doesn't exist
    c.execute("SELECT name FROM sqlite_master WHERE type='table' AND name='valeurs'")
    if not c.fetchone():
        # Create table
        c.execute("CREATE TABLE valeurs (date text, senseur text, valeur text)")
    # Close the connection
    conn.close()

    # Blocking call that processes network traffic, dispatches callbacks and
    # handles reconnecting.
    # Other loop*() functions are available that give a threaded interface and a
    # manual interface.
    client.loop_forever()


def on_connect(client, userdata, flags, rc):
    """
    The callback for when the client receives a CONNACK response from the server.
    """
    print("Connected with result code " + str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    # Subscribe with QOS 2 (info: https://www.hivemq.com/blog/mqtt-essentials-part-6-mqtt-quality-of-service-levels)
    client.subscribe(TOPIC_RECEIVE, 2)


def on_message(client, userdata, msg):
    """
    The callback for when a PUBLISH message is received from the server.
    """
    print(msg.topic + " " + str(msg.payload))
    if msg.topic == TOPIC_RECEIVE:
        try:
            message = msg.payload.decode("utf-8")  # Convert to string
            print(message)
            contents = json.loads(message)
            print(contents)

            try:
                print(contents["temperature"])
                print(contents["humidite"])

                # Insert into database
                conn = sqlite3.connect(DBNAME)
                c = conn.cursor()
                element = [(str(datetime.now(timezone.utc)), "Temperature", contents["temperature"])]
                c.executemany("INSERT INTO valeurs VALUES (?, ?, ?)", element)
                element = [(str(datetime.now(timezone.utc)), "Humidite", contents["humidite"])]
                c.executemany("INSERT INTO valeurs VALUES (?, ?, ?)", element)
                # Flush the transaction to disk
                conn.commit()
                conn.close()

                # Check for commands to send to the bucket
                conn = sqlite3.connect(DBNAME)
                c = conn.cursor()
                c.execute("SELECT date, command FROM filecommandes ORDER BY date ASC LIMIT 1;")
                command = c.fetchone()
                if command:
                    print("Database: Send a command to the bucket: " + str(command[1]))

                    # Delete this last command
                    c.execute("DELETE FROM filecommandes WHERE date=(?)", (str(command[0]),))
                    conn.commit()

                    # Count the remaining number of commands
                    c.execute("SELECT count(*) FROM filecommandes;")
                    count = c.fetchone()
                    if count:
                        print("Database: There are now " + str(count[0]) + " commands remaining in the queue.")
                else:
                    print("Database: Command queue is empty")
                conn.close()

                # Publish to the bucket
                client.publish(TOPIC_SEND, payload=str(command[0]), qos=0, retain=False)

            except KeyError:
                pass

        except ValueError as e:
            print("ValueError: " + str(e))


main()
