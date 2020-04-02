--	(c) 2003 BEA Systems, Inc. All Rights Reserved.
-- echo Building Iceberg U sample demonstration tables.  Please wait.

-- CONNECT SCOTT/TIGER@2:ORCL
-- CONNECT SCOTT/TIGER

DROP TABLE REGISTRATION;
DROP TABLE COURSE;
DROP TABLE STUDENT;
DROP TABLE ACCOUNT;


Create Table STUDENT (STUD_ID   NUMBER(6,0) NOT NULL,
                        NAME VARCHAR2(30) NOT NULL,
                        ACCOUNT NUMBER(6,0) NOT NULL,
    CONSTRAINT ST_PRIMARY_KEY PRIMARY KEY (STUD_ID));

Insert Into STUDENT Values(100001, 'Joseph Mathews',  200010);
Insert Into STUDENT Values(100002, 'Robert Blodgett', 200011);
Insert Into STUDENT Values(100003, 'Ralph Martin',    200012);
Insert Into STUDENT Values(100004, 'Betsy Fedak',     200013);
Insert Into STUDENT Values(100005, 'Chris Putur',     200014);
Insert Into STUDENT Values(100006, 'Nancy Glidden',   200015);
Insert Into STUDENT Values(100007, 'Joe Atterberry',  200016);
Insert Into STUDENT Values(100008, 'Thomas Cooper',   200017);
Insert Into STUDENT Values(100009, 'Richard Dewitt',  200018);
Insert Into STUDENT Values(100010, 'Shawn O`Rielly',  200019);

Create Table COURSE (COURSE_NO NUMBER(6,0) NOT NULL,
                        TITLE     VARCHAR2(20) NOT NULL,
                        DESCR     VARCHAR2(50),
                        AMOUNT    NUMBER(7,2) NOT NULL,
                        PROFESSOR VARCHAR2(30) NOT NULL,
                        SEATS	  NUMBER(3,0) NOT NULL,
                        CREDITS   NUMBER(3,0) NOT NULL,
                        REG_STUD  NUMBER(3,0) NOT NULL,
                        START_HR  NUMBER(2,0) NOT NULL,
                        DURATION  NUMBER(3,0) NOT NULL,
                        MONDAY	  CHAR(1) DEFAULT 'N' NOT NULL,
                        TUESDAY	  CHAR(1) DEFAULT 'N' NOT NULL,
                        WEDNESDAY CHAR(1) DEFAULT 'N' NOT NULL,
                        THURSDAY  CHAR(1) DEFAULT 'N' NOT NULL,
                        FRIDAY	  CHAR(1) DEFAULT 'N' NOT NULL,
    CONSTRAINT CD_PRIMARY_KEY PRIMARY KEY (COURSE_NO));

-- Lets reserve COURSE_NO 100001 thru 100040 for Computer Science

Insert Into COURSE Values(100001, 'Fundamentals of CS',
                        'Fundamentals of Computer Science', 825.00, 'Charles Steele',
                        20, 3, 10, 18, 150, 'Y', 'N', 'N', 'N', 'N');
Insert Into COURSE Values(100002, 'Foundations of CS',
                        'Foundations of Computer Science', 1299.00, 'Charles Steele',
                        20, 3, 10, 18, 180, 'N', 'N', 'N', 'Y', 'N');
Insert Into COURSE Values(100003, 'Intro to Algorithms',
                        'Introduction to Algorithms', 965.00, 'Glenn C Smith',
                        25, 3, 10, 18, 180, 'N', 'N', 'N', 'Y', 'N');
Insert Into COURSE Values(100004, 'Advanced Algorithms',
                        'Advanced Algorithms', 999.00, 'Fred Lewis',
                        20, 4, 10, 17, 180, 'N', 'Y', 'N', 'N', 'N');
Insert Into COURSE Values(100005, 'Form Lang + Automat',
                        'Formal Languages and Automata', 965.00, 'Richard Boccuzzi',
                        20, 3, 10, 18, 180, 'N', 'N', 'Y', 'N', 'N');
Insert Into COURSE Values(100006, 'Software Engg I',
                        'Software Engg I: Structured Analysis and Design', 1145.00,
                        'Jesse Heines', 20, 4, 10, 18, 150, 'N', 'N', 'Y', 'N', 'N');
Insert Into COURSE Values(100007, 'Computer Arch',
                        'Computer Architecture', 999.00, 'Thomas Cooper',
                        20, 3, 10, 18, 180, 'Y', 'N', 'N', 'N', 'N');
Insert Into COURSE Values(100008, 'Database Mgt',
                        'Database Management', 1145.00, 'Joseph Frankenstein',
                        15, 4, 10, 18, 150, 'N', 'Y', 'N', 'N', 'N');
Insert Into COURSE Values(100009, 'Ana of Prog Langs',
                        'Analysis of Prog Languages', 825.00, 'John Koegel',
                        20, 3, 10, 17, 180, 'N', 'N', 'N', 'Y', 'N');
Insert Into COURSE Values(100010, 'Data Comm I',
                        'Data Communications I', 999.00, 'Georges G Grinstein',
                        20, 3, 10, 19, 180, 'N', 'N', 'Y', 'N', 'N');
Insert Into COURSE Values(100011, 'Data Comm II',
                        'Data Communications II', 999.00, 'Raymond Gumb',
                        20, 3, 10, 17, 180, 'Y', 'N', 'N', 'N', 'N');
Insert Into COURSE Values(100012, 'Software Engg II',
                        'Software Engg II: Validation and Verification', 999.00,
                        'Robert Lechner', 20, 3, 10, 17, 180, 'N', 'Y', 'N', 'N',
                        'N');
Insert Into COURSE Values(100013, 'Software Engg III',
                        'Software Engg III: Computer Aided Design', 999.00,
                        'Robert Lechner', 20, 3, 10, 17, 150, 'N', 'N', 'N', 'Y',
                        'N');
Insert Into COURSE Values(100014, 'Operating Systems',
                        'Operating Systems', 965.00, 'Giampiero Pecelli',
                        20, 3, 10, 18, 180, 'N', 'N', 'Y', 'N', 'N');
Insert Into COURSE Values(100015, 'Prog Lang Design',
                        'Programming Language Design', 999.00, 'Patrick Krolak',
                        20, 4, 10, 18, 180, 'N', 'N', 'N', 'Y', 'N');
Insert Into COURSE Values(100016, 'Compiler Construct',
                        'Compiler Construction', 1145.00, 'William Moloney',
                        18, 4, 10, 18, 180, 'N', 'Y', 'N', 'N', 'N');
Insert Into COURSE Values(100017, 'Computer NWs',
                        'Computer Networks', 999.00, 'Byung-Guk Kim',
                        20, 3, 10, 18, 150, 'N', 'N', 'Y', 'N', 'N');
Insert Into COURSE Values(100018, 'Vision + Imag Sys',
                        'Vision and Imaging Systems', 825.00, 'Steve Smith',
                        20, 3, 10, 18, 150, 'N', 'N', 'Y', 'N', 'N');
Insert Into COURSE Values(100019, 'Computer Graphics',
                        'Computer Graphics', 1145.00, 'Robert Lechner',
                        20, 4, 10, 18, 180, 'Y', 'N', 'N', 'N', 'N');
Insert Into COURSE Values(100020, 'Artif Intelligence',
                        'Artificial Intelligence', 999.00, 'Patrick Krolak',
                        20, 4, 10, 18, 180, 'N', 'Y', 'N', 'N', 'N');
Insert Into COURSE Values(100021, 'Knowledge Based Sys',
                        'Knowledge Based Systems', 825.00, 'John Koegel',
                        20, 3, 10, 17, 180, 'Y', 'N', 'N', 'N', 'N');
Insert Into COURSE Values(100022, 'Robotics',
                        'Theory of Robotics Control and Manipulation', 825.00,
                        'Steve Smith', 22, 3, 10, 18, 180, 'N', 'N', 'N', 'Y', 'N');
Insert Into COURSE Values(100023, 'Parallel Algorithms',
                        'Parallel Algorithms', 999.00, 'Byung-Guk Kim',
                        20, 4, 10, 17, 150, 'N', 'Y', 'N', 'N', 'N');
Insert Into COURSE Values(100024, 'RT + Embed Systems',
                        'Real Time and Embedded Systems', 1145.00, 'Thomas Cooper',
                        20, 4, 10, 19, 180, 'N', 'Y', 'N', 'N', 'N');
Insert Into COURSE Values(100025, 'Systems Prog',
                        'Systems Programming', 965.00, 'Joseph Frankenstein',
                        20, 3, 10, 19, 150, 'N', 'N', 'N', 'Y', 'N');
Insert Into COURSE Values(100026, 'Performance Eval',
                        'Performance Evaluation', 965.00, 'Raymond Gumb',
                        20, 3, 10, 18, 180, 'N', 'N', 'Y', 'N', 'N');
Insert Into COURSE Values(100027, 'Project Management',
                        'Project Management', 825.00, 'William Moloney',
                        18, 3, 10, 18, 180, 'N', 'N', 'N', 'N', 'Y');
Insert Into COURSE Values(100028, 'Computational Logic',
                        'Computational Logic', 999.00,  'Giampiero Pecelli',
                        20, 3, 10, 18, 180, 'N', 'N', 'N', 'Y', 'N');
Insert Into COURSE Values(100029, 'Scientific Visual',
                        'Scientific Visualization', 1145.00, 'Byung-Guk Kim',
                        18, 3, 10, 18, 180, 'Y', 'N', 'N', 'N', 'N');
Insert Into COURSE Values(100030, 'Comp Algebra',
                        'Computational Algebra', 1145.00, 'Fred Lewis',
                        15, 4, 10, 18, 150, 'Y', 'N', 'N', 'N', 'N');
Insert Into COURSE Values(100031, 'Comp Algebra',
                        'Distributed Objects and CORBA', 1180.00, 'Paul Patrick',
                        15, 4, 10, 18, 180, 'Y', 'N', 'N', 'N', 'N');

-- Lets reserve COURSE_NO 100041 thru 100080 for Criminal Justice

Insert Into COURSE Values(100041, 'Foundation of CJ',
                        'Foundation of Criminal Justice', 825.00, 'James M Byrne',
                        20, 3, 10, 18, 150, 'N', 'N', 'N', 'Y', 'N');
Insert Into COURSE Values(100042, 'Res Methods in CJ',
                        'Research Methods in Criminal Justice', 1145.00,
                        'Renee G Kasinsky', 20, 4, 10, 18, 180, 'N', 'N', 'Y', 'N',
                        'N');
Insert Into COURSE Values(100043, 'Technology and Law',
                        'Technology and the Law', 825.00, 'James M Byrne',
                        20, 3, 10, 18, 180, 'N', 'Y', 'N', 'N', 'N');
Insert Into COURSE Values(100044, 'Qual Analysis in CJ',
                        'Qualitative Analysis in Criminal Justice', 999.00,
                        'Larry J Siegel', 20, 3, 10, 18, 180, 'Y', 'N', 'N', 'N',
                        'N');
Insert Into COURSE Values(100045, 'CJ Info Systems',
                        'Criminal Justice Information Systems', 965.00, 'Alan J Lincoln',
                        15, 3, 10, 17, 180, 'N', 'N', 'N', 'Y', 'N');
Insert Into COURSE Values(100046, 'Comp Crime and Sec',
                        'Computer Crime and Security', 1125.00, 'Joseph Lipchitz',
                        15, 4, 10, 19, 150, 'N', 'N', 'Y', 'N', 'N');
Insert Into COURSE Values(100047, 'Adv Qual Analysis',
                        'Advanced Qualitative Analysis', 885.00, 'Renee G Kasinsky',
                        20, 3, 10, 17, 180, 'N', 'Y', 'N', 'N', 'N');
Insert Into COURSE Values(100048, 'Adv Qual Analysis',
                        'Advanced Qualitative Analysis', 985.00, 'Donald Cochran',
                        20, 3, 10, 18, 180, 'Y', 'N', 'N', 'N', 'N');
Insert Into COURSE Values(100049, 'Law of Admin Proc',
                        'Law of Administrative  Procedures', 1185.00, 'Alan J Lincoln',
                        20, 4, 10, 18, 180, 'N', 'N', 'Y', 'N', 'N');
Insert Into COURSE Values(100050, 'Issues in Corr Admin',
                        'Issues in Correctional Administration', 1105.00,
                        'Donald Cochran', 22, 4, 10, 18, 150, 'N', 'N', 'N', 'Y',
                        'N');
Insert Into COURSE Values(100051, 'Family Violence - SR',
                        'Family Violence - System Response', 985.00, 'Joseph Lipchitz',
                        18, 3, 10, 18, 180, 'N', 'Y', 'N', 'N', 'N');
Insert Into COURSE Values(100052, 'Personnel Admin',
                        'Personnel Administration', 1185.00, 'Ronald Corbett',
                        20, 4, 10, 18, 180, 'Y', 'N', 'N', 'N', 'N');
Insert Into COURSE Values(100053, 'Public Policy',
                        'Public Policy and the Criminal Justice System', 1045.00,
                        'Gerald Hotaling', 20, 3, 10, 18, 150, 'N', 'N', 'N', 'Y',
                        'N');
Insert Into COURSE Values(100054, 'Victimology',
                        'Victimology in Criminal Justice', 945.00, 'Ronald Corbett',
                        20, 3, 10, 18, 150, 'N', 'N', 'Y', 'N', 'N');
Insert Into COURSE Values(100055, 'Constitution Rights',
                        'Constitutional Rights', 825.00, 'Larry J Siegel',
                        18, 3, 10, 18, 180, 'N', 'Y', 'N', 'N', 'N');
Insert Into COURSE Values(100056, 'Crime Prevention',
                        'Crime and Crime Prevention in Public', 985.00,
                        'Joseph Lipchitz', 20, 3, 10, 18, 180, 'Y', 'N', 'N', 'N',
                        'N');

Create Table REGISTRATION (STUD_ID   NUMBER(6,0) NOT NULL,
                           COURSE_NO NUMBER(6,0) NOT NULL,
    CONSTRAINT TC_FOREIGN_KEY1 FOREIGN KEY (STUD_ID)
                        REFERENCES STUDENT (STUD_ID),
    CONSTRAINT TC_FOREIGN_KEY2 FOREIGN KEY (COURSE_NO)
                        REFERENCES COURSE (COURSE_NO),
    CONSTRAINT TC_PRIMARY_KEY PRIMARY KEY (STUD_ID,COURSE_NO));

Insert Into REGISTRATION Values(100001, 100001);
Insert Into REGISTRATION Values(100003, 100004);
Insert Into REGISTRATION Values(100003, 100006);
Insert Into REGISTRATION Values(100003, 100007);
Insert Into REGISTRATION Values(100003, 100008);
Insert Into REGISTRATION Values(100003, 100010);

Create Table ACCOUNT(ACCOUNT_NO   NUMBER(6,0) NOT NULL,
                     CURR_BALANCE NUMBER(7,2) );

Insert Into ACCOUNT Values (200010,   825.00);
Insert Into ACCOUNT Values (200011, 11000.00);
Insert Into ACCOUNT Values (200012,  5287.00);
Insert Into ACCOUNT Values (200013,     0.00);
Insert Into ACCOUNT Values (200014,     0.00);
Insert Into ACCOUNT Values (200015,     0.00);
Insert Into ACCOUNT Values (200016,     0.00);
Insert Into ACCOUNT Values (200017,     0.00);
Insert Into ACCOUNT Values (200018,     0.00);
Insert Into ACCOUNT Values (200019,     0.00);

COMMIT;
EXIT;
