
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

import json
from database.database import Database
from bucket.model import BucketModel

class Bucket(object):

	def __init__(self):
		self.id = 0
		self.id_plant = 0
		self.name = ""
		self.ip_address = ""


	def __init__(self, id, id_plant, name, ip_address):
		self.id = id
		self.id_plant = id_plant
		self.name = name
		self.ip_address = ip_address


	def to_detailed_json(self):
		serialized = {
				"id" : self.id,
				"id_plant" : self.id_plant,
				"name" : self.name,
				"ip_address" : self.ip_address
			}

		return serialized


	def transform(bucket_data):
		bucket = Bucket(bucket_data[0],
				bucket_data[1],
				bucket_data[2],
				bucket_data[3])

		return bucket


	def save(self):
		if self.id is None:
			bucket = BucketModel.create(self)
			return Bucket.transform(bucket)
		else:
			BucketModel.update(self)
			return self

	@staticmethod
	def get_all():
		"""
		Retreive all bucket data and return it as a Bucket instance
		"""
		buckets_data = BucketModel.get_all()
		if buckets_data is None:
			return None
		return [Bucket.transform(b) for b in buckets_data]


	@staticmethod
	def get(id):
		"""
		Retreive a bucket's data and return it as a Bucket instance
		"""
		bucket_data = BucketModel.find_by_id(id)
		if bucket_data is None:
			return None
		return Bucket.transform(bucket_data)
