# Copyright (C) 2018 Roch D'Amour
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


import os
import sys
import unittest
import tempfile
import json
from app import app
from ast import literal_eval


class AppTestCase(unittest.TestCase):

	def setUp(self):
		app.testing = True
		self.app = app.test_client()


	def tearDown(self):
		pass


	def test_home_endpoint(self):
		""""
		Teste que le endpoint "/" retourne "hello world"
		"""
		response = self.app.get('/')
		self.assertEqual(
			json.loads(response.get_data().decode(sys.getdefaultencoding())),
			{'hello': 'world'}
		)


	def test_buckets_get_all(self):
		""""
		Test GET => /buckets
		"""
		response = self.app.get('/buckets')
		data = json.loads(response.data)
		buckets = data['buckets']

		self.assertGreater(
			len(buckets),
			0
		)


	def test_buckets_get_by_id(self):
		""""
		Test GET => /buckets/1
		"""
		bucket_id = 1

		response = self.app.get('/buckets/' + str(bucket_id))
		data = json.loads(response.data)
		bucket = data['bucket']

		self.assertEqual(
			bucket['id'],
			1
		)


	def test_buckets_get_by_id_missing(self):
		""""
		Test GET => /buckets/9999999999
		"""
		bucket_id = 9999999999

		response = self.app.get('/buckets/' + str(bucket_id))
		data = json.loads(response.data)

		self.assertEqual(
			data['error'],
			1
		)


	def test_buckets_addremove(self):
		"""
		TEST POST => /buckets
		TEST DELETE => /buckets/<id>
		"""
		new_bucket = {
			"name": "Swaggine",
			"id_plant": 1,
			"ip_address": "9999",
		}

		#create
		response = self.app.post('/buckets',
						json=new_bucket,
						content_type="application/json")

		data = json.loads(response.data)
		print("Created bucket: ")
		print(data)
		bucket = data['bucket']

		self.assertGreater(
			bucket['id'],
			0
		)
		url = '/buckets/'+str(bucket['id'])

		# delete
		response = self.app.delete(url)
		data = json.loads(response.data)
		self.assertEqual(
			data['error'],
			0
		)

		#get
		response = self.app.get(url)
		data = json.loads(response.data)
		self.assertEqual(
			data['error'],
			1
		)

		
	def test_sensors_endpoint(self):
		""""
		Test GET => /sensors
		"""
		response = self.app.get('/sensors')
		data = json.loads(response.data)
		sensors = data['sensors']

		self.assertGreater(
			len(sensors),
			0
		)


	def test_fans_endpoint(self):
		""""
		Test GET => /fans
		"""
		response = self.app.get('/fans')
		data = json.loads(response.data)
		sensors = data['fans']

		self.assertGreater(
			len(sensors),
			0
		)


	def test_lights_endpoint(self):
		""""
		Test GET => /lights
		"""
		response = self.app.get('/lights')
		data = json.loads(response.data)
		sensors = data['lights']

		self.assertGreater(
			len(sensors),
			0
		)


	def test_update_fans(self):
		post_data = {"fanl": 255, "fanh": 255}
		#create
		response = self.app.post('/fans',
						json=post_data,
						content_type="application/json")

		self.assertEqual(
			response.status_code,
			204
		)


	def test_update_lights(self):
		post_data = {"red": 128, "blue": 255, "white": 59}
		#create
		response = self.app.post('/lights',
						json=post_data,
						content_type="application/json")

		self.assertEqual(
			response.status_code,
			204
		)


if __name__ == '__main__':
	unittest.main()
