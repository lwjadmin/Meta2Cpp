DROP TABLE IF EXISTS BOARD;
#게시판
CREATE TABLE BOARD
(
	ID_BOARD          BIGINT        NOT NULL PRIMARY KEY AUTO_INCREMENT, #게시판ID
	TITLE             VARCHAR(300)  NOT NULL,                            #제목
	CONTENT           VARCHAR(4000) NULL,                                #내용
	REGUSER_ID        BIGINT        NULL,                                #계정ID
    REGDATE           DATETIME      NOT NULL,                            #등록일시
    VIEWCNT           INT           NOT NULL,                            #조회수
    LIKECNT           INT           NOT NULL,                            #추천수
    DISLIKECNT        INT           NOT NULL,                            #반대수
    THUMBNAIL_FILE_ID BIGINT        NULL,                                #섬네일파일ID
	DEL_YN            CHAR(1)       NOT NULL                             #삭제여부 
);

ALTER TABLE BOARD ALTER DEL_YN SET DEFAULT('N');
 
ALTER TABLE BOARD ALTER VIEWCNT SET DEFAULT('0');
 
ALTER TABLE BOARD ALTER LIKECNT SET DEFAULT('0');

ALTER TABLE BOARD ALTER DISLIKECNT SET DEFAULT('0');

ALTER TABLE BOARD ALTER REGDATE SET DEFAULT(CURRENT_TIMESTAMP);

INSERT INTO BOARD(`TITLE`,`CONTENT`) VALUES('HELLO','NICE TO MEET YOU!');

SELECT 
	ID_BOARD,
	TITLE,
	REGUSER_ID,
	REGDATE,
	VIEWCNT,
	LIKECNT,
	DISLIKECNT
FROM BOARD
WHERE DEL_YN = 'N'
ORDER BY ID_BOARD DESC




