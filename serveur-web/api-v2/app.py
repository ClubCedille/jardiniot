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

from flask_api import FlaskAPI
from bucket.bucket_blueprint import bucket_blueprint

__name__ = "JardinIoT"

# Initiate Flask application
app = FlaskAPI(__name__)

# Register blueprints, which act as controllers
app.register_blueprint(bucket_blueprint)

"""
Exemple d'une route simple
"""
@app.route("/")
def exemple():
	return { "hello" : "world" }

