#pragma once
#include "Header.h"

class Date {
	int day;
	int month;
	int year;

public:
	Date() {
		day = 0;
		month = 0;
		year = 0;
	}

	void SetUpDate() {
		cout << "\t¬ведите день приема на работу: ";
		cin >> day;

		cout << "\tмес€ц :";
		cin >> month;

		cout << "\tгод: ";
		cin >> year;
	}
	string GetDate() {
		string ret = "";

		if (day < 10)
			ret += "0";
		ret += to_string(day);
		ret += ".";

		if (month < 10)
			ret += "0";
		ret += to_string(month);
		ret += ".";

		ret += to_string(year);

		return ret;
	}
};

class StudentInfo {
	string name;
	string secondname;
	string surname;

	int group;
	int course;

public:
	StudentInfo() {
		name = "";
		secondname = "";
		surname = "";

		group = 0;
		course = 0;
	}
};

class Student {
	StudentInfo student;
	string courseWorkTheme;

	Date corseDeadLines;
	string courseWorkStorageLink;

public:
	Student() {
		//student = new StudentInfo();
	}
};