# Copyright (C) 2018 Roch D'Amour <roch.damour@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

# Fix de compatibilité des imports pour "Migration"
global path_database
try:
	from database.sqlite_connection import SqliteConnection
	path_database = "database/JardinIoT.db"
except:
	from sqlite_connection import SqliteConnection
	path_database = "./JardinIoT.db"

class Database(object):
	"""
	Unique Database handler
	Redirect query to it's connection and make sur there is only
	one instance of database.
	"""

	instance = None

	def __init__(self):
		"""
		Create a new database connection.
		"""
		# SQLITE
		self.connection = SqliteConnection.get_instance(path_database)


	@staticmethod
	def get_instance():
		"""
		Return the database instance
		"""
		if Database.instance is	 None:
			Database.instance = Database()

		return Database.instance


	def execute(self, query):
		"""
		Execute a database query and return
		"""
		return self.connection.execute(query)

	def executeparam(self, query, parameters):
		"""
		Execute a database query with parameters and return
		It expects a tuple
		"""
		return self.connection.executemany(query, (parameters,))

	def get_version(self):
		"""
		Return the current database version
		"""
		data = self.connection.execute("SELECT version FROM meta")
		if data is None:
			return

		version = data[0][0] # Data s tuple list. [0][0] extracts the information we need
		return version


	def update_version(self, version):
		"""
		Update the current database version
		"""
		self.connection.execute("UPDATE meta SET version = '"+str(version)+"'")
