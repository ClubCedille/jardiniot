PRAGMA foreign_keys = ON;
ATTACH "jardin.db" AS "jardin";
BEGIN;

-- Enlever les commentaires de ce script pour "seedé" la base de données. 
INSERT INTO buckets ( "name", "ip") VALUES ("grosse bouette loleo", "127.0.0.1");

INSERT INTO sensors (bucket_id, name, type) VALUES ("1", "humidity", "humidity");
INSERT INTO sensors (bucket_id, name, type) VALUES ("1", "temperature", "temperature");

INSERT INTO "values" (sensor_id, value, timestamp) VALUES ("1", "40" ,DateTime('now') );
INSERT INTO "values" (sensor_id, value, timestamp) VALUES ("1", "50" , DateTime('now'));
INSERT INTO "values" (sensor_id, value, timestamp) VALUES ("2", "50" , DateTime('now'));

COMMIT;
