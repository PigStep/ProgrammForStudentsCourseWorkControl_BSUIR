#pragma once
#include "Header.h"
#include "Date.h"

class StudentInfo {
	string name;
	string secondname;
	string surname;

	int group;
	int course;

public:
	StudentInfo() {
		name = "NO NAME";
		secondname = "";
		surname = "";

		group = -1;
		course = -1;
	}
};

class Student {
	StudentInfo student;
	string courseWorkTheme;

	static Date* corseDeadLines;
	string courseWorkStorageLink;

public:
	Student() {
		student;
		courseWorkTheme = "NO THEME";

		string courseWorkStorageLink = "NO STORAGE LINK HAS PROVIDED";
	}
};