/* Copyright 2018 Roch D'Amour
 * Copyright 2017 Aubert Guillemette
 *
 * JardinIoT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * JardinIoT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with JardinIoT. If not, see <http://www.gnu.org/licenses/>.
 */

var out = module.exports;

var sqlite3 = require('sqlite3').verbose();
var fs = require('fs');
var db = new sqlite3.Database(__dirname + '/jardin.db');
db.serialize(); // --> Pour empêcher les requêtes en parallèle
var sql = fs.readFileSync(__dirname + '/sqlite_dbgen.sql', 'utf8');
db.exec(sql, function(err){
    if (err) throw err;
});

//Fonction pour ajouter un bucket dans la base de données
out.createBucket = function(_name, _ip, cb) {

    //Basic error checking because I want to be a nice guy
    if (_name === undefined || _ip === undefined) {
        console.warn("");
        console.warn("WARNING: In sqlite_connector::createBucket()");
        console.warn("       : The name or ip of the bucket cannot be null.")
        console.warn("       : Bucket creation cancelled.");
        console.warn("");
        return;
    }
    if (_name == "" || _ip == "") {
        console.warn("");
        console.warn("WARNING: In sqlite_connector::createBucket()");
        console.warn("       : The name or ip of the bucket cannot be empty.")
        console.warn("       : Bucket creation cancelled.");
        console.warn("");
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
        console.warn("");
        console.warn("WARNING: In sqlite_connector::createSensor()");
        console.warn("       : The type of the sensor is invalid.");
        console.warn("       : Sensor creation cancelled.");
        console.warn("");
        return;
    }
    if (isNaN(_bucketId)) {
        console.warn("");
        console.warn("WARNING: In sqlite_connector::createSensor()");
        console.warn("       : The ID of the bucket is invalid.");
        console.warn("       : Sensor creation cancelled.");
        console.warn("");
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
    if (_value === undefined) {
        console.warn("");
        console.warn("WARNING: In sqlite_connector::createValue()");
        console.warn("       : The value cannot be null.");
        console.warn("       : Value creation cancelled.");
        console.warn("");
        return;
    }
    if (_sensorId === undefined || isNaN(_sensorId)) {
        console.warn("");
        console.warn("WARNING: In sqlite_connector::createValue()");
        console.warn("       : The sensor ID is invalid.");
        console.warn("       : Value creation cancelled.");
        console.warn("");
        return;
    }

    var requete = db.prepare('INSERT INTO "jardin"."values" (sensor_id, value, timestamp) VALUES (?, ?, ?)');
    requete.run(_sensorId, _value, Date.now());
}

//Dans le cas où on connaît seulement le nom du sensor (comme dans connector.js)
out.createValueWithSensorName = function(_value, _sensorName, _bucketName) {
    if (_value === undefined) {
        console.warn("");
        console.warn("WARNING: In sqlite_connector::createValueWithSensorName()");
        console.warn("       : The value cannot be null.");
        console.warn("       : Value creation cancelled.");
        console.warn("");
        return;
    }
    if (_sensorName === undefined || _sensorName == "") {
        console.warn("");
        console.warn("WARNING: In sqlite_connector::createValue()");
        console.warn("       : The sensor name is invalid.");
        console.warn("       : Value creation cancelled.");
        console.warn("");
        return;
    }
    //On va chercher le ID du sensor à partir des noms.
    var requete = db.all('SELECT sensors.id FROM sensors, buckets WHERE sensors.bucket_id = buckets.id AND buckets.name = "' + _bucketName + '" AND sensors.name = "' + _sensorName + '"', function(err, rows){
        if (err) throw err;
        if (rows.length == 0){
            console.warn("");
            console.warn("WARNING: In sqlite_connector::createValue()");
            console.warn("       : There seems to be no sensor named " + _sensorName + " registered in the db.");
            console.warn("       : Value creation cancelled.");
            console.warn("");
        } else {
            out.createValue(_value, rows[0].id);
        }
    });
}


//-------Fonctions pour aller chercher les informations dans la BD-------

out.getBucketList = function(cb){
    var statement = db.prepare("SELECT * FROM buckets");
    statement.all(function(err, rows){
        cb(err, rows);
    });
}

out.getBucketInfo = function(id, cb){
    var statement = db.prepare("SELECT * FROM buckets WHERE id = ?")
    statement.get(id, function(err, row){
        var bucket = row;
        var statement = db.prepare("SELECT * FROM sensors WHERE bucket_id = ?")
        statement.all(id, function(err, rows){
            if(!bucket){
                cb("no bucket", null);
            } else {
                bucket.sensors = rows;
                cb(err, bucket);
            }
        });
    });
}

out.getSensorValue = function(id, cb){
    var statement = db.prepare('SELECT * FROM "values" WHERE sensor_id = ?')
    statement.all(id, function(err, rows){
        cb(err, rows);
    });
}

out.getLatestSensorValue = function(id, cb){
    var statement = db.prepare('SELECT * FROM "values" WHERE sensor_id = ? ORDER BY id desc LIMIT 1')
    statement.get(id, function(err, rows){
        cb(err, rows);
    });
}

out.getBucketById = function(id, cb){
    var statement = db.prepare("SELECT * FROM buckets WHERE id = ?")
    statement.all(id, function(err, rows){
        cb(err, rows[0].name);
    });
}
//----------------------------------------------------------------------
