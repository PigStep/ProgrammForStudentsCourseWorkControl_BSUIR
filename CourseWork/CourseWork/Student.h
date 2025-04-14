#pragma once
#include "Header.h"
#include "Date.h"

class Student {
protected:
	string login;
	string password;

	string name;
	string secondname;
	string surname;

	int group;
	int course;
public:
	Student() {
		name = "NO_NAME";
		secondname = "";
		surname = "";

		group = -1;
		course = -1;
	}

	Student(string name, string secondname, string surname, int group, int course) {
		this->name = name;
		this->secondname = secondname;
		this->surname = surname;
		this->group = group;
		this->course = course;
	}

};

class StudentCourseWork : Student {
	string courseWorkTheme;

	static Date* corseDeadLines;
	string courseWorkStorageLink;

public:
	StudentCourseWork() {
		courseWorkTheme = "NO_THEME";

		string courseWorkStorageLink = "NO_STORAGE_LINK_HAS_PROVIDED";
	}

	StudentCourseWork(string name, string secondname, string surname, int group, int course)
		: Student(name, secondname, surname, group, course) {
		courseWorkStorageLink = "NO_STORAGE_LINK_HAS_PROVIDED";
		courseWorkTheme = "NO_THEME";
	}

	friend fstream& operator<<(fstream& stream, const StudentCourseWork& self) {
		stream << self.name<<endl;
		stream << self.secondname<<endl;
		stream << self.surname<<endl;
		stream << self.group<<endl;
		stream << self.course<<endl;
		stream << self.courseWorkTheme<<endl;
		stream << self.courseWorkStorageLink<<endl;

		return stream;
	}


};