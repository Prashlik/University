DROP DATABASE IF EXISTS recording_studio;
CREATE DATABASE recording_studio;
\c recording_studio

BEGIN;
CREATE TABLE member (
	ID 				SERIAL PRIMARY KEY,
	first_name 		VARCHAR(128) NOT NULL,
	middle_name 	VARCHAR(128) NOT NULL,
	last_name 		VARCHAR(128) NOT NULL,
	gender 			CHAR(1) NOT NULL
						CONSTRAINT gender_validation CHECK (gender in ('M', 'F', 'O')),
	phone_number    VARCHAR(15) NOT NULL UNIQUE
);

CREATE TABLE role (
	ID 				SERIAL PRIMARY KEY,
	activity_kind 	VARCHAR(64) NOT NULL,
	experience 		FLOAT(1) NULL,
						CONSTRAINT if_above_zero CHECK (experience > 0)
);

CREATE TABLE member_role (
	member_id 		INT NOT NULL REFERENCES member (ID)
						ON DELETE CASCADE,
	role_id 		INT NOT NULL REFERENCES role (ID)
						ON DELETE CASCADE,
	PRIMARY KEY (member_id, role_id)
);

CREATE TABLE band (
	ID 				SERIAL PRIMARY KEY,
	name 			VARCHAR(128) NOT NULL,
	style 			VARCHAR(128) NOT NULL
);

CREATE TABLE member_band (
	member_id 		INT NOT NULL REFERENCES member (ID)
						ON DELETE CASCADE,
	band_id 		INT NOT NULL REFERENCES band (ID)
						ON DELETE CASCADE,
	PRIMARY KEY (member_id, band_id)
);

CREATE TABLE worker (
	ID 				SERIAL PRIMARY KEY,
	first_name 		VARCHAR(128) NOT NULL,
	middle_name 	VARCHAR(128) NOT NULL,
	last_name 		VARCHAR(128) NOT NULL,
	speciality 		VARCHAR(64) NOT NULL,
	phone_number    VARCHAR(15) NOT NULL UNIQUE
);

CREATE TABLE room (
	ID 				SERIAL PRIMARY KEY,
	room_number 	INT NOT NULL 
						CONSTRAINT if_above_zero_room_number CHECK (room_number > 0),
	area 			FLOAT(2) NOT NULL,
						CONSTRAINT if_above_zero_area CHECK (area > 0),
	purpose 		VARCHAR(64) NOT NULL,
	worker_id 		INT NULL REFERENCES worker (ID)
						ON DELETE RESTRICT
);

CREATE TABLE recording_session (
	ID 				SERIAL PRIMARY KEY,
	r_date 			DATE NOT NULL,
	r_time 			TIME NOT NULL,
	duration 		FLOAT(2) NOT NULL,
	session_type 	VARCHAR(64) NOT NULL,
	link 			VARCHAR(128) NULL,
	room_id 		INT NOT NULL REFERENCES room (ID)
						ON DELETE RESTRICT,
	band_id 		INT NOT NULL REFERENCES band (ID)
						ON DELETE CASCADE	
);

CREATE TABLE worker_session (
	worker_id 		INT NOT NULL REFERENCES worker (ID)
						ON DELETE CASCADE,
	session_id 		INT NOT NULL REFERENCES recording_session (ID)
						ON DELETE CASCADE,
	PRIMARY KEY (worker_id, session_id)
);

CREATE TABLE device (
	ID 				SERIAL PRIMARY KEY,
	device_number 	INT NOT NULL,
	device_type 	VARCHAR(64) NOT NULL,
	model 			VARCHAR(64) NOT NULL,
	room_id 		INT NOT NULL REFERENCES room (ID)
						ON DELETE CASCADE
);

commit;