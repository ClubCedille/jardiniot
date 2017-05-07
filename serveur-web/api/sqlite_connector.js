var out = module.exports;

out.dbInit = function(dbname) {
  out.sqlite3 = require('sqlite3').verbose();
  out.fs = require('fs');
  out.db = new out.sqlite3.Database('jardin.db');
  out.db.serialize();
  var sql = out.fs.readFileSync('sqlite_dbgen.sql', 'utf8');
  out.db.exec(sql, function(err){
    if (err) throw err;
  });
}

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

  var requete = out.db.prepare("INSERT INTO buckets (name, ip) VALUES (?, ?)");
  var id;
  requete.run(_name, _ip, function(){
    cb(this.lastID);
  });
  //requete.finalize(function(){});
}

out.createSensor = function(_name, _type, _bucketId, cb) {
  if (!["humidity", "temperature"].includes(_type)) {
    console.error("createSensor --> sensor type invalid");
    return;
  }
  if (isNaN(_bucketId)) {
    console.error("createSensor --> bucket id invalid");
    return;
  }

  var requete = out.db.prepare("INSERT INTO sensors (bucket_id, name, type) VALUES (?, ?, ?)");
  var id;
  requete.run(_bucketId, _name, _type, function(){
    cb(this.lastID);
  });
  //requete.finalize(function(){});
}

out.createValue = function(_value, _sensorId) {
  if (_value === undefined /*|| isNaN(_value)*/) {
    console.error("createValue --> value is invalid");
    return;
  }
  if (_sensorId === undefined || isNaN(_sensorId)) {
    console.error("createValue --> sensorId is invalid");
    return;
  }

  var requete = out.db.prepare('INSERT INTO "jardin"."values" (sensor_id, value, timestamp) VALUES (?, ?, ?)');
  var id;
  requete.run(_sensorId, _value, Date.now());
  //requete.finalize();

}

out.getBucketList = function(cb){
  out.db.all("SELECT * FROM buckets", function(err, rows){
    cb(rows);
  });
}

out.getBucketInfo = function(id, cb){
  out.db.all("SELECT * FROM sensors WHERE bucket_id = " + id, function(err, rows){
    cb(rows);
  });
}

out.getSensorValue = function(id, cb){
  out.db.all('SELECT * FROM "values" WHERE sensor_id = ' + id, function(err, rows){
    cb(rows);
  });
}
