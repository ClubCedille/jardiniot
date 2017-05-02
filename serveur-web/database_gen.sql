--
-- PostgreSQL database cluster dump
--

SET default_transaction_read_only = off;

SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;

--
-- Roles
--

CREATE ROLE aub;
ALTER ROLE aub WITH SUPERUSER INHERIT CREATEROLE CREATEDB LOGIN NOREPLICATION;
CREATE ROLE jardiniot;
ALTER ROLE jardiniot WITH NOSUPERUSER INHERIT NOCREATEROLE NOCREATEDB LOGIN NOREPLICATION PASSWORD 'md52ef3d517365bb7ef3745e93379621212';
CREATE ROLE postgres;
ALTER ROLE postgres WITH SUPERUSER INHERIT CREATEROLE CREATEDB LOGIN REPLICATION;






--
-- Database creation
--

CREATE DATABASE jardiniot WITH TEMPLATE = template0 OWNER = postgres;
REVOKE ALL ON DATABASE jardiniot FROM PUBLIC;
REVOKE ALL ON DATABASE jardiniot FROM postgres;
GRANT ALL ON DATABASE jardiniot TO postgres;
GRANT CONNECT,TEMPORARY ON DATABASE jardiniot TO PUBLIC;
GRANT CONNECT ON DATABASE jardiniot TO jardiniot;
REVOKE ALL ON DATABASE template1 FROM PUBLIC;
REVOKE ALL ON DATABASE template1 FROM postgres;
GRANT ALL ON DATABASE template1 TO postgres;
GRANT CONNECT ON DATABASE template1 TO PUBLIC;


\connect jardiniot

SET default_transaction_read_only = off;

--
-- PostgreSQL database dump
--

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: buckets; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE buckets (
    id integer NOT NULL,
    name character varying(255)
);


ALTER TABLE buckets OWNER TO postgres;

--
-- Name: buckets_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE buckets_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE buckets_id_seq OWNER TO postgres;

--
-- Name: buckets_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE buckets_id_seq OWNED BY buckets.id;


--
-- Name: sensors; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE sensors (
    id integer NOT NULL,
    bucket_id integer NOT NULL,
    name character varying(255),
    type character varying(255) NOT NULL
);


ALTER TABLE sensors OWNER TO postgres;

--
-- Name: sensors_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE sensors_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE sensors_id_seq OWNER TO postgres;

--
-- Name: sensors_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE sensors_id_seq OWNED BY sensors.id;


--
-- Name: values; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE "values" (
    id integer NOT NULL,
    sensor_id integer NOT NULL,
    value character varying(255) NOT NULL,
    "timestamp" bigint
);


ALTER TABLE "values" OWNER TO postgres;

--
-- Name: values_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE values_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE values_id_seq OWNER TO postgres;

--
-- Name: values_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE values_id_seq OWNED BY "values".id;


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY buckets ALTER COLUMN id SET DEFAULT nextval('buckets_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY sensors ALTER COLUMN id SET DEFAULT nextval('sensors_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY "values" ALTER COLUMN id SET DEFAULT nextval('values_id_seq'::regclass);


--
-- Data for Name: buckets; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY buckets (id, name) FROM stdin;
7	Testing Purposes
\.


--
-- Name: buckets_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('buckets_id_seq', 7, true);


--
-- Data for Name: sensors; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY sensors (id, bucket_id, name, type) FROM stdin;
1	7	Testing purposes - Température	temperature
2	7	Testing purposes - Humidité	moisture
\.


--
-- Name: sensors_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('sensors_id_seq', 2, true);


--
-- Data for Name: values; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY "values" (id, sensor_id, value, "timestamp") FROM stdin;
5	1	Ceci est le onzième test!	1488620172843
6	1	Ceci est le douzième test!	1488624588004
\.


--
-- Name: values_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('values_id_seq', 6, true);


--
-- Name: buckets_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY buckets
    ADD CONSTRAINT buckets_pkey PRIMARY KEY (id);


--
-- Name: sensors_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY sensors
    ADD CONSTRAINT sensors_pkey PRIMARY KEY (id);


--
-- Name: sensors_bucket_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY sensors
    ADD CONSTRAINT sensors_bucket_id_fkey FOREIGN KEY (bucket_id) REFERENCES buckets(id);


--
-- Name: values_sensor_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY "values"
    ADD CONSTRAINT values_sensor_id_fkey FOREIGN KEY (sensor_id) REFERENCES sensors(id);


--
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;
GRANT USAGE ON SCHEMA public TO jardiniot;


--
-- Name: buckets; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE buckets FROM PUBLIC;
REVOKE ALL ON TABLE buckets FROM postgres;
GRANT ALL ON TABLE buckets TO postgres;
GRANT SELECT,INSERT ON TABLE buckets TO jardiniot;


--
-- Name: buckets_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE buckets_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE buckets_id_seq FROM postgres;
GRANT ALL ON SEQUENCE buckets_id_seq TO postgres;
GRANT SELECT,USAGE ON SEQUENCE buckets_id_seq TO jardiniot;


--
-- Name: sensors; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE sensors FROM PUBLIC;
REVOKE ALL ON TABLE sensors FROM postgres;
GRANT ALL ON TABLE sensors TO postgres;
GRANT SELECT,INSERT ON TABLE sensors TO jardiniot;


--
-- Name: sensors_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE sensors_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE sensors_id_seq FROM postgres;
GRANT ALL ON SEQUENCE sensors_id_seq TO postgres;
GRANT SELECT,USAGE ON SEQUENCE sensors_id_seq TO jardiniot;


--
-- Name: values; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE "values" FROM PUBLIC;
REVOKE ALL ON TABLE "values" FROM postgres;
GRANT ALL ON TABLE "values" TO postgres;
GRANT SELECT,INSERT ON TABLE "values" TO jardiniot;


--
-- Name: values_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE values_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE values_id_seq FROM postgres;
GRANT ALL ON SEQUENCE values_id_seq TO postgres;
GRANT SELECT,USAGE ON SEQUENCE values_id_seq TO jardiniot;


--
-- Name: DEFAULT PRIVILEGES FOR TABLES; Type: DEFAULT ACL; Schema: public; Owner: postgres
--

ALTER DEFAULT PRIVILEGES FOR ROLE postgres IN SCHEMA public REVOKE ALL ON TABLES  FROM PUBLIC;
ALTER DEFAULT PRIVILEGES FOR ROLE postgres IN SCHEMA public REVOKE ALL ON TABLES  FROM postgres;
ALTER DEFAULT PRIVILEGES FOR ROLE postgres IN SCHEMA public GRANT SELECT,INSERT ON TABLES  TO jardiniot;


--
-- PostgreSQL database dump complete
--

\connect postgres

SET default_transaction_read_only = off;

--
-- PostgreSQL database dump
--

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- Name: postgres; Type: COMMENT; Schema: -; Owner: postgres
--

COMMENT ON DATABASE postgres IS 'default administrative connection database';


--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


--
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- PostgreSQL database dump complete
--

\connect template1

SET default_transaction_read_only = off;

--
-- PostgreSQL database dump
--

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- Name: template1; Type: COMMENT; Schema: -; Owner: postgres
--

COMMENT ON DATABASE template1 IS 'default template for new databases';


--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


--
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- PostgreSQL database dump complete
--

--
-- PostgreSQL database cluster dump complete
--

