-- !!! IL DOIT Y AVOIR UN USER jardiniot SUR LE SERVEUR POSTGRESQL !!!

--
-- PostgreSQL database dump
--

-- Dumped from database version 9.4.10
-- Dumped by pg_dump version 9.4.10
-- Started on 2017-03-04 08:34:28 EST

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

DROP DATABASE jardiniot;
--
-- TOC entry 2027 (class 1262 OID 16386)
-- Name: jardiniot; Type: DATABASE; Schema: -; Owner: postgres
--

CREATE DATABASE jardiniot WITH TEMPLATE = template0 ENCODING = 'UTF8' LC_COLLATE = 'en_CA.UTF-8' LC_CTYPE = 'en_CA.UTF-8';


ALTER DATABASE jardiniot OWNER TO postgres;

\connect jardiniot

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- TOC entry 1 (class 3079 OID 11861)
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- TOC entry 2030 (class 0 OID 0)
-- Dependencies: 1
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- TOC entry 174 (class 1259 OID 16389)
-- Name: buckets; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE buckets (
    id integer NOT NULL,
    name character varying(255)
);


ALTER TABLE buckets OWNER TO postgres;

--
-- TOC entry 173 (class 1259 OID 16387)
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
-- TOC entry 2032 (class 0 OID 0)
-- Dependencies: 173
-- Name: buckets_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE buckets_id_seq OWNED BY buckets.id;


--
-- TOC entry 176 (class 1259 OID 16413)
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
-- TOC entry 175 (class 1259 OID 16411)
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
-- TOC entry 2035 (class 0 OID 0)
-- Dependencies: 175
-- Name: sensors_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE sensors_id_seq OWNED BY sensors.id;


--
-- TOC entry 178 (class 1259 OID 16429)
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
-- TOC entry 177 (class 1259 OID 16427)
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
-- TOC entry 2038 (class 0 OID 0)
-- Dependencies: 177
-- Name: values_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE values_id_seq OWNED BY "values".id;


--
-- TOC entry 1899 (class 2604 OID 16392)
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY buckets ALTER COLUMN id SET DEFAULT nextval('buckets_id_seq'::regclass);


--
-- TOC entry 1900 (class 2604 OID 16416)
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY sensors ALTER COLUMN id SET DEFAULT nextval('sensors_id_seq'::regclass);


--
-- TOC entry 1901 (class 2604 OID 16432)
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY "values" ALTER COLUMN id SET DEFAULT nextval('values_id_seq'::regclass);


--
-- TOC entry 2029 (class 0 OID 0)
-- Dependencies: 7
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;
GRANT USAGE ON SCHEMA public TO jardiniot;


--
-- TOC entry 2031 (class 0 OID 0)
-- Dependencies: 174
-- Name: buckets; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE buckets FROM PUBLIC;
REVOKE ALL ON TABLE buckets FROM postgres;
GRANT ALL ON TABLE buckets TO postgres;
GRANT SELECT,INSERT ON TABLE buckets TO jardiniot;


--
-- TOC entry 2033 (class 0 OID 0)
-- Dependencies: 173
-- Name: buckets_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE buckets_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE buckets_id_seq FROM postgres;
GRANT ALL ON SEQUENCE buckets_id_seq TO postgres;
GRANT SELECT,USAGE ON SEQUENCE buckets_id_seq TO jardiniot;


--
-- TOC entry 2034 (class 0 OID 0)
-- Dependencies: 176
-- Name: sensors; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE sensors FROM PUBLIC;
REVOKE ALL ON TABLE sensors FROM postgres;
GRANT ALL ON TABLE sensors TO postgres;
GRANT SELECT,INSERT ON TABLE sensors TO jardiniot;


--
-- TOC entry 2036 (class 0 OID 0)
-- Dependencies: 175
-- Name: sensors_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE sensors_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE sensors_id_seq FROM postgres;
GRANT ALL ON SEQUENCE sensors_id_seq TO postgres;
GRANT SELECT,USAGE ON SEQUENCE sensors_id_seq TO jardiniot;


--
-- TOC entry 2037 (class 0 OID 0)
-- Dependencies: 178
-- Name: values; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE "values" FROM PUBLIC;
REVOKE ALL ON TABLE "values" FROM postgres;
GRANT ALL ON TABLE "values" TO postgres;
GRANT SELECT,INSERT ON TABLE "values" TO jardiniot;


--
-- TOC entry 2039 (class 0 OID 0)
-- Dependencies: 177
-- Name: values_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE values_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE values_id_seq FROM postgres;
GRANT ALL ON SEQUENCE values_id_seq TO postgres;
GRANT SELECT,USAGE ON SEQUENCE values_id_seq TO jardiniot;


-- Completed on 2017-03-04 08:34:28 EST

--
-- PostgreSQL database dump complete
--

