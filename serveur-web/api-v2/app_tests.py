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

	def test_buckets_endpoint(self):
		""""
		Test GET => /bucket
		"""
		response = self.app.get('/bucket')
		data = json.loads(response.data)
		buckets = data['buckets']

		self.assertGreater(
			len(buckets), 0
		)

	def test_bucket_endpoint(self):
		""""
		Test GET => /bucket/1
		"""
		bucket_id = 1

		response = self.app.get('/bucket/' + str(bucket_id))
		data = json.loads(response.data)
		bucket = data['bucket']

		self.assertEqual(
			bucket['id'],
			1
		)

	def test_bucket_missing(self):
		""""
		Test GET => /bucket/9999999999
		"""
		bucket_id = 9999999999

		response = self.app.get('/bucket/' + str(bucket_id))
		data = json.loads(response.data)

		self.assertEqual(
			data['error'],
			1
		)

	def test_bucket_addremove(self):
		"""
		TEST POST => /bucket
		TEST DELETE => /bucket/<id>
		"""
		new_bucket = {
			"name": "Swaggine",
			"id_plant": 1,
			"ip_address": "9999",
		}

		#create
		response = self.app.post('/bucket',
						   json=new_bucket,
						   content_type="application/json")

		data = json.loads(response.data)
		print(data)
		bucket = data['bucket']

		self.assertGreater(
			bucket['id'],
			0
		)
		url = '/bucket/'+str(bucket['id'])

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


if __name__ == '__main__':
	unittest.main()
