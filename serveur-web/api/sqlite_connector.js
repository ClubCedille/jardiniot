var out = module.exports;

var sqlite3 = require('sqlite3').verbose();
var fs = require('fs');
var db = new sqlite3.Database('jardin.db');
db.serialize(); // --> Pour empêcher les requêtes en parallèle
var sql = fs.readFileSync('sqlite_dbgen.sql', 'utf8');
db.exec(sql, function(err){
  if (err) throw err;
});

//Fonction pour ajouter un bucket dans la base de données
out.createBucket = function(_name, _ip, cb) {

  //Basic error checking because I want to be a nice guy
  if (_name === undefined || _ip === undefined) {
    console.error("createBucket --> name or ip cannot be null");
    return;
  }
  if (_name == "" || _ip == "") {
    console.error("createBucket --> name or ip cannot be empty");
    return;
  }

  //Insertion
  var requete = db.prepare("INSERT INTO buckets (name, ip) VALUES (?, ?)");
  var id;
  requete.run(_name, _ip, function(){
    cb(this.lastID);
  });
}

//Ajout d'un sensor dans la base de données
out.createSensor = function(_name, _type, _bucketId, cb) {
  if (!["humidity", "temperature"].includes(_type)) {
    console.error("createSensor --> sensor type invalid");
    return;
  }
  if (isNaN(_bucketId)) {
    console.error("createSensor --> bucket id invalid");
    return;
  }

  var requete = db.prepare("INSERT INTO sensors (bucket_id, name, type) VALUES (?, ?, ?)");
  var id;
  requete.run(_bucketId, _name, _type, function(){
    cb(this.lastID);
  });
}

//Ajout d'une valeur dans la BD
out.createValue = function(_value, _sensorId) {
  if (_value === undefined /*|| isNaN(_value)*/) {
    console.error("createValue --> value is invalid");
    return;
  }
  if (_sensorId === undefined || isNaN(_sensorId)) {
    console.error("createValue --> sensorId is invalid");
    return;
  }

  var requete = db.prepare('INSERT INTO "jardin"."values" (sensor_id, value, timestamp) VALUES (?, ?, ?)');
  requete.run(_sensorId, _value, Date.now());
}

//Dans le cas où on connaît seulement le nom du sensor (comme dans connector.js)
out.createValueWithSensorName = function(_value, _sensorName, _bucketName) {
  if (_value === undefined) {
    console.error("createValueWithSensorName --> value is invalid");
    return;
  }
  if (_sensorName === undefined || _sensorName == "") {
    console.error("createValueWithSensorName --> sensorName is invalid");
    return;
  }
  //On va chercher le ID du sensor à partir des noms.
  var requete = db.all('SELECT sensors.id FROM sensors, buckets WHERE sensors.bucket_id = buckets.id AND buckets.name = "' + _bucketName + '" AND sensors.name = "' + _sensorName + '"', function(err, rows){
    if (err) throw err;
    out.createValue(_value, rows[0].id);
  });
}


//-------Fonctions pour aller chercher les informations dans la BD-------

out.getBucketList = function(cb){
  db.all("SELECT * FROM buckets", function(err, rows){
    cb(rows);
  });
}

out.getBucketInfo = function(id, cb){
  db.all("SELECT * FROM sensors WHERE bucket_id = " + id, function(err, rows){
    cb(rows);
  });
}

out.getSensorValue = function(id, cb){
  db.all('SELECT * FROM "values" WHERE sensor_id = ' + id, function(err, rows){
    cb(rows);
  });
}
//----------------------------------------------------------------------
