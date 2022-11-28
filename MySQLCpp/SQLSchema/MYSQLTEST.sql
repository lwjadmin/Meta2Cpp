/*------------------------------------------
SHOW DATABASES;

USE SAKILA;

DESC ACTOR;

DESC ADDRESS;

SELECT * FROM ADDRESS ORDER BY ADDRESS ASC;

CREATE DATABASE GUESTBOOK;

DROP DATABASE GUESTBOOK;

DROP DATABASE IF EXISTS GUESTBOOK;

CREATE DATABASE IF NOT EXISTS GUESTBOOK;

USE GUESTBOOK;
------------------------------------------*/
USE GUESTBOOK;

DROP TABLE IF EXISTS SHEET1;
#테이블 생성
CREATE TABLE SHEET1
(
	`IDX`     INT      PRIMARY KEY AUTO_INCREMENT,   #인덱스
    `NAME`    CHAR(30) NULL,                         #이름
    `CONTENT` CHAR(30) NULL                          #내용
);

INSERT INTO SHEET1(`NAME`,`CONTENT`) VALUES('A1','HELLO1');
INSERT INTO SHEET1(`NAME`,`CONTENT`) VALUES('A2','HELLO2');
INSERT INTO SHEET1(`NAME`,`CONTENT`) VALUES('A3','HELLO3');
INSERT INTO SHEET1(`NAME`,`CONTENT`) VALUES('A4','HELLO4');
INSERT INTO SHEET1(`NAME`,`CONTENT`) VALUES('A5','HELLO5');

ALTER TABLE SHEET1 ADD COLUMN COUNT INT NOT NULL DEFAULT '0';

ALTER TABLE SHEET1 MODIFY COLUMN COUNT BIGINT NOT NULL DEFAULT '0';

ALTER TABLE SHEET1 CHANGE COLUMN COUNT COUNT2 BIGINT;

ALTER TABLE SHEET1 DROP COLUMN COUNT2;

ALTER TABLE SHEET1 RENAME SHEET2


UPDATE SHEET1 SET 
	CONTENT = 'HELLOWORLD'
WHERE IDX = 1;

DELETE FROM SHEET1 WHERE IDX = 1;

SELECT 
	* 
FROM GUESTBOOK.SHEET1
ORDER BY IDX ASC;

