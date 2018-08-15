echo "Source l'environnement..."
source env/bin/activate
echo "initialize les variables d'environnements..."
FLASK_APP=app.py
FLASK_ENV=developent

flask run
