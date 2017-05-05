//Ce fichier sert à démontrer comment le connecteur SQLite fonctionne.
var sq = require("./sqlite_connector.js");

//On se doit d'initialiser la BD
sq.dbInit();

//Création d'un jardin simple
sq.createBucket("Test Bucket", "0.0.0.0", function(bucketId){
  sq.createSensor("Test Bucket, humidity sensor", "humidity", bucketId, function(sensorId){
    sq.createValue("30%", sensorId);
    sq.createValue("40%", sensorId);
    sq.createValue("30%", sensorId);
  });
  sq.createSensor("Test Bucket, temp sensor", "temperature", bucketId, function(sensorId){
    sq.createValue("25C", sensorId);
    sq.createValue("30C", sensorId);
    sq.createValue("25C", sensorId);
  });
});

//Allons chercher la liste des buckets
sq.getBucketList(function(rst){
  console.log(rst);
});

//La liste des sensors du bucket avec l'ID 1
sq.getBucketInfo(1, function(rst){
  console.log(rst);
});

//La liste des valeurs pour le sensor avec l'ID 2
sq.getSensorValue(2, function(rst){
  console.log(rst);
});
