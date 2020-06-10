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

from model.bucket import Bucket
import json

from datetime import datetime, timezone


class BucketController(object):

    def index():
        """
        INDEX
        C'est ici qu'on enverra la liste des buckets.
        """
        buckets = Bucket.get_all()
        if buckets is not None:
            return {"buckets": [bucket.to_detailed_json() for bucket in buckets]}
        else:
            response = {
                "error": 1,
                "message": "No bucket found"
            }
            return (response, 404)

    def create(request):
        """
        CREATE
        C'est ici qu'on recoit les informations pour enregistrer un nouveau bucket
        """
        name = request.data['name']
        if name is None:
            raise Exception()

        try:
            id_plant = request.data['id_plant']
        except Exception:
            id_plant = 0

        ip_address = request.data['ip_address']
        if ip_address is None:
            raise Exception()

        new_bucket = Bucket(None, id_plant, name, ip_address)
        new_bucket = new_bucket.save()

        return {"bucket": new_bucket.to_detailed_json()}

    def get(id):
        """
        /bucket/id
        C'est ici qu'on enverra la liste des buckets.
        """
        bucket = Bucket.get(id)
        if bucket is not None:
            return {"bucket": bucket.to_detailed_json()}
        else:
            response = {
                "error": 1,
                "message": "bucket not found"
            }
            return (response, 404)

    def update(id):
        """
        POST => /bucket/id
        C'est ici qu'on met a jours les informations d'un bucket
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

                name = request.data['name']
                if name is None:
                    raise Exception()

                try:
                    id_plant = request.data['id_plant']
                except Exception:
                    id_plant = 0

                ip_address = request.data['ip_address']
                if ip_address is None:
                    raise Exception()

                id = request.data['id']
                if id is None:
                    raise Exception()

                updated_bucket = Bucket(id, id_plant, name, ip_address)

                updated_bucket.save()

                return {"bucket": updated_bucket.to_detailed_json()}
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

    def delete(id):
        """
        /bucket/id
        C'est ici qu'on supprime un bucket
        """
        bucket = Bucket.get(id)
        if bucket is not None:
            deleted = Bucket.delete(bucket)
            response = {
                "error": 0,
                "deleted": str(deleted)
            }
            return (response, 200)
        else:
            response = {
                "error": 1,
                "message": "bucket not found"
            }
            return (response, 404)
