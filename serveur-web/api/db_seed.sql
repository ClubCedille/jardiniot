PRAGMA foreign_keys = ON;
ATTACH "jardin.db" AS "jardin";
BEGIN;

-- Enlever les commentaires de ce script pour "seedé" la base de données. 
INSERT OR IGNORE INTO buckets ( "name", "ip") VALUES ("test", "127.0.0.1");

INSERT OR IGNORE INTO sensors (bucket_id, name, type) VALUES ("1", "humidity", "humidity");
INSERT OR IGNORE INTO sensors (bucket_id, name, type) VALUES ("1", "temperature", "temperature");

INSERT OR IGNORE INTO "values" (sensor_id, value, timestamp) VALUES ("1", "40" ,DateTime('now') );
INSERT OR IGNORE INTO "values" (sensor_id, value, timestamp) VALUES ("1", "50" , DateTime('now'));
INSERT OR IGNORE INTO "values" (sensor_id, value, timestamp) VALUES ("2", "50" , DateTime('now'));

COMMIT;
