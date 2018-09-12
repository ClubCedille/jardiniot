# Copyright (C) 2018 Roch D'Amour <roch.damour@gmail.com>

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.


# Fix de compatibilité des imports pour "Migration"
try:
	from database.connection import Connection
except:
	from connection import Connection

import sqlite3


class SqliteConnection(Connection):
	"""
	Extends Connection to use a SQLite3 database connection
	"""
	# Class Variables
	instance = None

	# Object Variables
	def __init__(self,db_path):
		self.conn = sqlite3.connect(db_path)

	@staticmethod
	def get_instance(db_path):
		"""
		Return a SQLite3 Connection singleton
		"""
		if SqliteConnection.instance is None:
			SqliteConnection.instance = SqliteConnection(db_path)

		return SqliteConnection.instance

	def execute(self, query):
		"""
		Execute a SQLite query
		"""
		data = None

		try:
			cur = self.conn.cursor()
			cur.execute(query)
			data = cur.fetchall()
			if not data:
				self.conn.commit()
		except sqlite3.Error as e:
			print("Database error: %s" % e)
		except Exception as e:
			print("Exception in _query: %s" % e)

		return data

	def open(self):
		pass

	def close(self):
		pass
