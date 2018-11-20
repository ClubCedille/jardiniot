# copyright (C) 2018 Roch D'Amour <roch.damour@gmail.com>
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

import json
from database.database import Database

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
		"""
		Create or update a bucket
		"""
		if self.id is None:
			return Bucket.create(self)
		else:
			Bucket.update(self)
			return self

	"""
	Static Methods
	"""

	@classmethod
	def get(cls,id):
		"""
		Retreive a bucket's data and return it
		"""
		db = Database.get_instance()
		bucket_data = db.execute("SELECT * FROM BUCKET WHERE ID='"+str(id)+"'")
		if bucket_data:
			return cls.transform(bucket_data[0])
		else:
			return None

	@classmethod
	def get_all(cls):
		"""
		Retreive a bucket's data and return it
		"""
		db = Database.get_instance()
		bucket_data = db.execute("SELECT * FROM BUCKET")
		if bucket_data:
			return [cls.transform(b) for b in bucket_data]
		else:
			return None

	@staticmethod
	def create(bucket):
		db = Database.get_instance()
		sql1 = "INSERT INTO bucket('name', 'id_plant', 'ip_address') VALUES"
		sql2 = "('" + str(bucket.name) + "', '" + str(bucket.id_plant) + "', '" + str(bucket.ip_address) + "');"

		db.execute(sql1+sql2)
		bucket_data = db.execute("SELECT * FROM BUCKET ORDER BY ID DESC LIMIT 1")
		if bucket_data:
			return Bucket.transform(bucket_data[0])
		else:
			return None


	@staticmethod
	def update(bucket):
		db = Database.get_instance()
		sql = (
			"UPDATE bucket " +
			"set name = '"+ str(bucket.name) + "', " +
			"id_plant = '"+ str(bucket.id_plant) + "', " +
			"ip_address = '"+ str(bucket.ip_address) + "' " +
			" WHERE id='" + str(bucket.id) + "' "
			)
		db.execute(sql)
		return bucket

	@staticmethod
	def delete(bucket):
		try:
			db = Database.get_instance()
			sql = (
				"delete from bucket " +
				" WHERE id='" + str(bucket.id) + "' "
				)

			db.execute(sql)
			return True
		except:
			return False
