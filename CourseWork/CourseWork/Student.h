#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Date.h"
#include <vector>
#include <sstream>

using namespace std;

class User {
protected:
	int user_level;
	int id;

	string login;
	string password;
};
class Student : public User {
protected:

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
		
		id = -1;
		group = -1;
		course = -1;
		user_level = 0;
	}

	Student(int id, int userLevel, string login, string password,string name, string secondname, string surname, int group, int course) {

		this->user_level = userLevel;
		this->name = name;
		this->secondname = secondname;
		this->surname = surname;
		this->group = group;
		this->course = course;

		this->id = id;
		this->password = password;
		this->login = login;
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
	StudentCourseWork(int id, int userLevel, string password, string login, string name, string secondname, string surname) { //Админимтратор

		this->id = id;
		this->user_level = userLevel;
		this->password = password;
		this->login = login;

		this->name = name;
		this->secondname = secondname;
		this->surname = surname;

		courseWorkStorageLink = "NO_STORAGE_LINK_HAS_PROVIDED";
		courseWorkTheme = "NO_THEME";
		group = -1;
		course = -1;
	}
	StudentCourseWork(int id, int userLevel, string password, string login,string name, string secondname, string surname, int group, int course)
		: Student(id, userLevel, password, login, name, secondname, surname, group, course) {
		courseWorkStorageLink = "NO_STORAGE_LINK_HAS_PROVIDED";
		courseWorkTheme = "NO_THEME";
	}

	void SetCourseWorkTheme(string courseWorkTheme) {
		this->courseWorkTheme = courseWorkTheme;
	}
	void SetCourseWorkStorageLink(string courseWorkStorageLink) {
		this->courseWorkStorageLink = courseWorkStorageLink;
	}
	friend fstream& operator<<(fstream& stream, const StudentCourseWork& self) {

		stream <<self.id<<";"
		 << self.user_level << ";"
		 << self.login<< ';'
		 << self.password<< ';'
		 << self.name<<';'
		 << self.secondname<< ';'
		 << self.surname<< ';'
		 << self.group<< ';'
		 << self.course<< ';'
		 << self.courseWorkTheme<< ';'
		 << self.courseWorkStorageLink<< ';'<<endl;

		return stream;
	}

	// Геттеры для всех полей
	string getLogin() const {
		return login;
	}

	string getPassword() const {
		return password;
	}

	string getName() const {
		return name;
	}

	string getSecondName() const {
		return secondname;
	}

	string getSurname() const {
		return surname;
	}

	int getGroup() const {
		return group;
	}

	int getCourse() const {
		return course;
	}

	bool isUserAdmin()const{
		if (user_level == 1)
			return true;
		return false;
	}
	int getUserLevel() const {
		return user_level;
	}

	int getId() const {
		return id;
	}

};
extern vector<StudentCourseWork> students_data;

void getStudentsFromFile(const string&);