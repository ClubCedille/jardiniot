from flask_api import FlaskAPI
from bucket.bucket_blueprint import bucket_blueprint

__name__ = "JardinIoT"

app = FlaskAPI(__name__)

app.register_blueprint(bucket_blueprint)

"""
Exemple d'une route simple
"""
@app.route("/")
def exemple():
	return { "hello" : "world" }

