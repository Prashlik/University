INSERT INTO member (first_name, middle_name, last_name, gender, phone_number) VALUES
('Alyona','Dmitrievna','Kovalova','F','80445678925'),
('Evgeniy','Konstantinovich','Belousov','M','80445678926'),
('Arina','Sergeevna','Anokhina','F','80445678927'),
('Denis','Kirillovich','Borisov','O','80445678928'),
('Mikhail','Borisovich','Isaev','M','80445678929'),
('Mikhail','Grigorievich','Gerasimov','M','80445678930'),
('Daniil','Glebovich','Makarov','M','80445678931'),
('Konstantin','Zakharovich','Fadeev','M','80445678932');

INSERT INTO role (activity_kind, experience) VALUES
('bass player',2),
('solo guitarist',1),
('rythm gyitatist',2.5),
('drummer',5),
('lead singer',3),
('back singer',2),
('keyboard player',1.2),
('drummer',1);

INSERT INTO band (name, style) VALUES
('The Cold Trees','Doom metal'),
('Cute Rabbit','Soft rock'),
('After Radical','Alternative rock'),
('Elegant Prince','Pop'),
('Dear Kitties Are Old','Synth pop'),
('Shadow Ray','Rap'),
('Beyond Anarchist','Punk'),
('Thor And The Cows','Metal');

INSERT INTO worker (first_name, middle_name, last_name, speciality, phone_number) VALUES
('Milana','Zaharovna','Sokolova','Director','80445678933'),
('Ali','Romanovich','Belyaev','Sound engineer','80445678934'),
('Kirill','Markovich','Tumanov','Administrator','80445678935'),
('Alisa','Aleksandrovna','Mikhailova','Sound engineer','80445678936'),
('Evgeniya','Alekseevna','Safonova','Vice Director','80445678937'),
('Aleksey','Alievich','Pastuhov','Specialist in working with customers','80445678938'),
('Arseniy','Bogdanovich','Popov','Sound engineer','80445678939'),
('Vera','Danielievna','Pokrovskaya','Sound engineer','80445678940');

INSERT INTO room (room_number, area, purpose, worker_id) VALUES
(11,20.5,'Director room',1),
(12,19.5,'Engineer room',2),
(13,15.5,'Other',3),
(14,10.20,'Stock room',4),
(21,17.5,'Studio room',5),
(22,18.56,'Studio room',6),
(23,11.38,'Studio room',7),
(24,12.25,'Studio room',8);

INSERT INTO recording_session (r_date, r_time, duration, session_type, link, band_id, room_id) VALUES
('2022-9-1','10:11',0.5,'Vocal recording','https://123.com/voice1',8,5),
('2022-9-2','11:12',1,'Instrumental recording','https://123.com/instr1',1,6),
('2022-10-3','12:13',1.5,'Studio recording','https://123.com/studio1',7,7),
('2022-10-4','13:14',2,'Concert recording','https://123.com/concert1',2,8),
('2022-11-5','14:15',2.5,'Vocal recording','https://123.com/voice2',6,8),
('2022-11-6','15:16',3,'Instrumental recording','https://123.com/instr2',3,7),
('2022-12-7','16:17',3.5,'Studio recording','https://123.com/studio2',5,6),
('2022-12-8','17:18',4,'Concert recording','https://123.com/concert2',4,5);

INSERT INTO device (device_number, device_type, model, room_id) VALUES
(1,'Micro','xftYJM-6c',4),
(2,'Guitar','RFVbnh6 ULTRA',5),
(3,'Acoustic piano','Samick JS043D EBHP',5),
(4,'Spikerphone','Yamaha YVC-1000',6),
(5,'Mixer','Allen & Heath XONE:464',4),
(6,'Acoustic system','Beringer F1320D, 12` + 1`',4),
(7,'Acoustic controller','Vector-4000',7),
(8,'Drums','PL-45-432',8);

INSERT INTO member_role (member_id, role_id) VALUES
(1,6),
(2,1),
(3,2),
(4,7),
(5,8),
(6,3),
(7,4),
(8,5);

INSERT INTO member_band (member_id, band_id) VALUES
(1,6),
(2,1),
(3,2),
(4,7),
(5,8),
(6,3),
(7,4),
(8,5);

INSERT INTO worker_session (worker_id, session_id) VALUES
(1,6),
(2,1),
(3,2),
(4,7),
(5,8),
(6,3),
(7,4),
(8,5);
