/*1. Вывести подсчитанное количество кабинетов разного типа.*/

WITH room_count AS (
SELECT purpose AS "Room purpose", 
	   COUNT(*) AS "Rooms"
FROM room
GROUP BY purpose
ORDER BY purpose
)
SELECT * from room_count;

/*2. Вывести статистику времени сессии записи звука:
   максимальное и среднее время сессии. */

SELECT MAX(duration) AS "Maximum time",
	   TRUNC(AVG(duration)) AS "Average time"
FROM recording_session;

/*3. Вывести члена группы с максимальным опытом, его стаж и роль в группе.*/

SELECT member.last_name AS "Surname",
	   role.experience AS "Experience",
	   role.activity_kind AS "Kind of activity"
FROM member_role
JOIN role ON member_role.role_id = role.id
JOIN member ON member_role.member_id = member.id
WHERE role.experience = (SELECT MAX(role.experience) 
						 FROM role);

/*4. Вывести идентификаторы сессий записи, их дата и время
   длительность сессии меньше среднего.*/

SELECT recording_session.id AS "Session ID",
	   recording_session.r_date AS "Date",
	   recording_session.r_time AS "Time",
	   recording_session.duration AS "Duration"
FROM recording_session
WHERE duration < (SELECT AVG(duration) FROM recording_session)
ORDER BY duration DESC;

/*5. Вывести фамилии и имена работников с должностью "звукорежиссёр".*/

SELECT worker.id AS "Worker ID",
	   worker.first_name AS "Name",
	   worker.last_name AS "Surname",
	   worker.speciality AS "Speciality"
	   FROM worker
	   WHERE speciality = 'Sound engineer';

/*6. Вывести информацию о всех сеансах звукозаписи,
    в которых участвовали работники, имеющие должность «Звукорежиссёр».*/

WITH session_info AS (
SELECT recording_session.id AS "Session ID",
	   recording_session.duration AS "Duration",
	   recording_session.session_type AS "Type",
	   worker.last_name AS "Surname",
	   worker.speciality AS "Speciality"
FROM worker_session
JOIN worker ON worker_session.worker_id = worker.id
JOIN recording_session ON worker_session.session_id = recording_session.id
WHERE worker.id IN (SELECT worker.id
			    	FROM worker
				WHERE speciality = 'Sound engineer')
)
SELECT * FROM session_info;

/*7. Вывести полный список фамилий всех людей,
    относящихся к студии звукозаписи (и работников, и участников групп).*/						 

SELECT last_name AS list_of_people 
		FROM member
	UNION
SELECT last_name AS list_of_people 
		FROM worker
ORDER BY list_of_people ASC;

/*8. Найти общую последовательность символов в именах работников и членов групп.
    Вывести идентификаторы таких совпадений.*/

SELECT id AS intersected_id
		FROM worker 
		WHERE last_name LIKE '%ov%'
	INTERSECT
SELECT id AS intersected_id
		FROM member
		WHERE last_name LIKE '%ov%'
ORDER BY intersected_id ASC;

/*9. Вывести только те идентификаторы работников, чьи имена содержат 
	последовательность символов, не совпадающую с той же последовательностью 
	символов в соответствующих именах членов групп.*/

SELECT id AS worker_id 
		FROM worker
		WHERE last_name LIKE '%ov%'
	EXCEPT
SELECT id AS worker_id 
		FROM member
		WHERE last_name LIKE '%ov%'
ORDER BY worker_id ASC;
