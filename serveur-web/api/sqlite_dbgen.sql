PRAGMA foreign_keys = ON;
ATTACH "jardin.db" AS "jardin";
BEGIN;
CREATE TABLE IF NOT EXISTS "jardin"."buckets"(
  "id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
  "name" VARCHAR(45),
  "ip" VARCHAR(45) NOT NULL
);
CREATE TABLE IF NOT EXISTS "jardin"."sensors"(
  "id" INTEGER PRIMARY KEY NOT NULL,
  "bucket_id" INTEGER NOT NULL,
  "name" VARCHAR(45),
  "type" VARCHAR(45) NOT NULL,
  CONSTRAINT "bucket_id"
    FOREIGN KEY("bucket_id")
    REFERENCES "buckets"("id")
);
CREATE INDEX IF NOT EXISTS "jardin"."sensors.bucket_id_idx" ON "sensors" ("bucket_id");
CREATE TABLE IF NOT EXISTS "jardin"."values"(
  "id" INTEGER PRIMARY KEY NOT NULL,
  "sensor_id" INTEGER NOT NULL,
  "value" VARCHAR(255) NOT NULL,
  "timestamp" INTEGER NOT NULL,
  CONSTRAINT "sensor_id"
    FOREIGN KEY("sensor_id")
    REFERENCES "sensors"("id")
);
CREATE INDEX IF NOT EXISTS "jardin"."values.sensor_id_idx" ON "values" ("sensor_id");
COMMIT;
