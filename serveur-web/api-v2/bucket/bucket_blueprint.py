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

from flask import Blueprint

# Create a bucket_bluprint, which make it exportable for other modules to use.
# We bind new routes to this blueprint, which will then be used by the
# main Flask process when handling requests.
bucket_blueprint = Blueprint("bucket_blueprint", __name__)

"""
INDEX
C'est ici qu'on enverra la liste des buckets.
"""
@bucket_blueprint.route("/bucket")
def index():
	print("Acces a /bucket")

	buckets = [
		{
			"id" : 1,
			"name" : "orange"
		},
		{
			"id" : 2,
			"name" : "vert"
		}
		]

	return buckets

