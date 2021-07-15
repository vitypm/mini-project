


-- before trigger
DROP TRIGGER IF EXISTS `before_update_progress`;

DELIMITER |
CREATE TRIGGER `before_update_progress` before INSERT ON `progress`
FOR EACH ROW BEGIN 

Declare kyrc_grp int;
Declare progress_rate int;
Declare grp_exist varchar(255);

/* Правда ли студент является этой именной этой группы, проверка
set grp_exist = (select grp.title from students join grp on (students.groupId = grp.id) where students.id = new.studentId and grp.title = new.grp); 

 */
set kyrc_grp = right(YEAR(now()),2) - (select LEFT(SUBSTRING(title,LOCATE('-',title)+1),2) from grp where title = new.grp);
/* Если 5 курс, то вернет null*/
IF kyrc_grp < 5 THEN
	set new.kypc =  kyrc_grp;

END IF;



/* 2.2.	При внесении количества баллов вносит оценку  */
IF new.scores >= 91 THEN
	set new.rate = 'Отлично';
ELSEIF new.scores >= 76 THEN
	set new.rate = 'Хорошо';
ELSEIF new.scores >= 61 THEN
	set new.rate = 'Удовлетворительно';
ELSEIF new.scores < 61 THEN
	set new.rate = 'Не аттестован';
END IF;

END;
|


-- after trigger


-- 3 триггер

DROP TEMPORARY TABLE IF EXISTS Average|
DROP TRIGGER IF EXISTS Performance_Average|
CREATE TRIGGER `Performance_Average` AFTER INSERT ON `progress` FOR EACH ROW
BEGIN
DECLARE i VARCHAR(255);
set i = (select grp.title from students 
join grp on (students.groupId = grp.id) 
where students.id = new.studentId);
-- SELECT Ave INTO i from Average;
CREATE TEMPORARY TABLE IF NOT EXISTS Average (Ave INT, GR varchar(255));
INSERT INTO Average
set GR = (select grp.title from students 
join grp on (students.groupId = grp.id) 
where students.id = new.studentId);
UPDATE Average
set Ave = (select avg(progress.scores) from progress
			join students on (progress.studentId = students.id)
			where progress.grp = i )
where GR = i;
-- INSERT INTO Average(Ave) VALUES (i);
END;|

select * from Average group by GR; |



-- 4 триггер
DROP TEMPORARY TABLE IF EXISTS Average_subject|
DROP TRIGGER IF EXISTS Average_subject|
CREATE TRIGGER `Average_subject` AFTER INSERT ON `progress` FOR EACH ROW
BEGIN
DECLARE j VARCHAR(255);
set j = (select title from discipline where discipline.id = new.disciplineId);
CREATE TEMPORARY TABLE IF NOT EXISTS Average_subject (Ave INT, Sub varchar(255));
INSERT INTO Average_subject
set Sub = (select discipline.title from discipline where discipline.id = new.disciplineId);
UPDATE Average_subject
set Ave = (select avg(progress.scores) from progress
			join discipline on (progress.disciplineId = discipline.id)
			where discipline.title = j)
where Sub = j;
END;|

select * from Average_subject group by Sub; |




/* 

Чтобы данный триггер сработал, 
 SET SQL_SAFE_UPDATES = 0;ы
необходимо запустить before_update_progress, а потом добавить count_students

*/



-- 5 триггер

DROP TEMPORARY TABLE IF EXISTS count_students|
DROP TRIGGER IF EXISTS count_students|
CREATE TRIGGER `count_students` AFTER INSERT ON `progress` FOR EACH ROW
BEGIN
CREATE TEMPORARY TABLE IF NOT EXISTS count_students (Count INT, Course INT);
iF (select count(*) from count_students where (Course = NEW.kypc) > 0) then
	UPDATE count_students
set count = (select count(studentId) from progress
			join students on (progress.studentId = students.id)
			where scores < 61 and progress.kypc = NEW.kypc)
where Course = NEW.kypc;
ELSE
INSERT INTO count_students
set Course = NEW.kypc;
UPDATE count_students
set Count = (select count(studentId) from progress
			join students on (progress.studentId = students.id)
			where scores < 61 and progress.kypc = NEW.kypc)
where Course = NEW.kypc;
END IF;


END;|

select * from count_students; |

