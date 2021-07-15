DROP DATABASE IF EXISTS Base_lab_five;

CREATE DATABASE Base_lab_five;
USE Base_lab_five;

CREATE TABLE grp (
	id int primary key auto_increment,
	title varchar(255)
);

CREATE TABLE students (
	id int primary key auto_increment,					   
	lastname varchar(255),	
	groupId int,
	foreign key (groupId) references grp (id)
);

CREATE TABLE discipline (
	id int primary key auto_increment,			     
	title varchar(255)
);

CREATE TABLE progress (
	id int primary key auto_increment,
	studentId int,
    disciplineId int,
    grp varchar(255),
    kypc int,
    scores int,
    rate varchar(255),
    foreign key (studentId) references students (id),
    foreign key (disciplineId) references discipline (id)
);
