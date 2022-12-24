/*1. Вывести данные о всех участниках всех музыкальных групп.*/

SELECT * 
	FROM member;
	
/*2. Вывести фамилии и номера всех участников всех музыкальных групп.*/

SELECT 
	last_name AS "Surname",
	phone_number AS "Phone" 
FROM member;

/*3. Вывести список работников, фамилии отсортированы в алфавитном порядке.*/

SELECT * 
	FROM worker
	ORDER BY last_name ASC;

/*4. Вывести список всех должностей работников.*/

SELECT DISTINCT speciality 
	FROM worker 
	ORDER BY speciality;

/*5. Вывести список участников групп женского пола.*/

SELECT * 
	FROM member 
	WHERE gender = 'F';

/*6. Вывести список сессий звукозаписи, длительность которых меньше трёх часов,
сессии были после 1-го сентября.*/

SELECT * FROM recording_session 
	   WHERE duration < 3  AND r_date > '2022-09-01';

/*7. Вывести всю информацию о сессиях звукозаписи и группах, которые в них участвуют.*/

SELECT 	   recording_session.id AS "Session ID",
	   to_char(recording_session.r_date, 'DD Month YYYY') AS "Recording date", 
	   r_time AS "Recording time",
	   duration AS "Recording duration",
	   session_type AS "Recording type",
	   link AS "Link to record",
	   band.id AS "Band ID",
	   band.name AS "Band name",
	   band.style AS "Band style"
FROM recording_session
JOIN band ON recording_session.band_id = band.id;

/*8. Вывести участников групп, телефонные номера которых содержат в себе "892".*/

SELECT * 
	FROM member 
	WHERE phone_number LIKE '%892%';

/*9. Вывести тип сессии звукозаписи, группу и помещение, в котором оно проходит, при условии,
что группа играет в стиле рок.*/

SELECT 	   recording_session.id AS "Session ID",
	   recording_session.session_type AS "Recording type",
	   band.id AS "Band ID",
	   band.name AS "Band name",
	   band.style AS "Band style",
	   room.id AS "Room ID",
	   room.room_number AS "Room number"
FROM recording_session
JOIN room ON recording_session.room_id = room.id
JOIN band ON recording_session.band_id = band.id
WHERE band.style LIKE '%rock%';

/*10. Вывести количество знаков в графе номер телефона у работников.*/

SELECT phone_number,
	LENGTH(phone_number)
	FROM worker;

/*11. Вывести информацию о участниках группы и ролях в группе.*/

SELECT     member.first_name AS "First name",
	   member.middle_name AS "Middle name",
	   member.last_name AS "Last name",
	   member.phone_number AS "Phone number",
	   role.activity_kind AS "Kind of activity",
	   role.experience AS "Experience"
FROM member_role
JOIN member ON member_role.member_id = member.id
JOIN role ON member_role.role_id = role.id;