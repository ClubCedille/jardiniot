# Copyright (C) 2018 Roch D'Amour <roch.damour@gmail.com>
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

from flask import Blueprint
from flask import request
import json

from datetime import datetime, timezone

from controller.bucket import BucketController

# Create a bucket_bluprint, which make it exportable for other modules to use.
# We bind new routes to this blueprint, which will then be used by the
# main Flask process when handling requests.
bucket_blueprint = Blueprint("bucket_blueprint", __name__)

# The following three functions are used to create modification commands


@bucket_blueprint.route("/buckets", methods=["GET"])
def index():
    """
    GET => /buckets
    Envoie la liste des buckets.
    """
    return BucketController.index()


@bucket_blueprint.route("/buckets", methods=["POST"])
def create():
    """
    POST => /buckets
    Recoit les informations pour enregistrer un nouveau bucket
    """
    print("Acces a /bucket avec POST")
    try:
        if request.headers['Content-Type'] != 'application/json':
            response = {
                "error": 1,
                "message": "Content-Type is not application/json"
            }
            return (response, 400)
        elif request.is_json:
            return BucketController.create(request)
        else:
            raise Exception()
    except Exception as e:
        print("ERROR: Request is not JSON or has missing fields.")
        print(e)
        response = {
            "error": 1,
            "message": "Missing fields in JSON"
        }
        return (response, 404)


@bucket_blueprint.route("/buckets/<id>", methods=["GET"])
def id(id):
    """
    GET => /buckets/id
    Renvoie un bucket spécifique.
    """
    return BucketController.get(id)


@bucket_blueprint.route("/buckets/<id>", methods=["POST"])
def update(id):
    """
    POST => /buckets/id
    Met a jours les informations d'un bucket
    """
    print("Acces a /bucket/id avec POST")
    try:
        if request.headers['Content-Type'] != 'application/json':
            response = {
                "error": 1,
                "message": "Content-Type is not application/json"
            }
            return (response, 400)
        elif request.is_json:
            return BucketController.update(request)
        else:
            raise Exception()
    except Exception as e:
        print("ERROR: Request is not JSON or has missing fields.")
        response = {
            "error": 1,
            "message": "Missing fields in JSON"
        }
        print(response)
        return (response, 404)


@bucket_blueprint.route("/buckets/<id>", methods=["DELETE"])
def delete(id):
    """
    DELETE => /buckets/id
    Supprime un bucket
    """
    return BucketController.delete(id)
