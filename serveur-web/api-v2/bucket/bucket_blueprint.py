from flask import Blueprint

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

