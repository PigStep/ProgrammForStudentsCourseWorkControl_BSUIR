#pragma once
#include "Header.h"
#include "Date.h"
#include <sstream>

using namespace std;

class User {
protected:
	int user_level;
	int id;

	string login;
	string password;
public:
	void setId(int newId) {
		id = newId;
	}
};
class Student : public User {
protected:
	string name;
	string secondname;
	string surname;

	int group;
	int course;
public:
	Student();

	Student(int id, int userLevel,
		string login, string password, string name, string secondname, string surname, 
		int group, int course);

	void StudentEdit();

	// Геттеры для всех полей
	string getLogin() const { return login; }

	string getPassword() const { return password; }

	string getName() const { return name; }

	string getSecondName() const { return secondname; }

	string getSurname() const { return surname; }

	int getGroup() const { return group; }

	int getCourse() const { return course; }

	bool isUserAdmin()const {
		if (user_level == 1) return true;
		return false;
	}

	int getUserLevel() const { return user_level; }

	int getId() const { return id; }

};

class StudentCourseWork : public Student {
	string courseWorkTheme;
	string courseWorkStorageLink;

public:
	StudentCourseWork() {
		courseWorkTheme = "NO_THEME";

		string courseWorkStorageLink = "NO_STORAGE_LINK_HAS_PROVIDED";
	}

	//Конструктор Администратора
	StudentCourseWork(int id, int userLevel, 
		string password, string login, 
		string name, string secondname, string surname);

	StudentCourseWork(int id, int userLevel, 
		string password, string login,
		string name, string secondname, string surname, 
		int group, int course) : Student(id, userLevel, password, login, name, secondname, surname, group, course) {

		courseWorkStorageLink = "NO_STORAGE_LINK_HAS_PROVIDED";
		courseWorkTheme = "NO_THEME";
	}

	void SetCourseWorkTheme(string courseWorkTheme) {
		this->courseWorkTheme = courseWorkTheme;
	}
	void SetCourseWorkStorageLink(string courseWorkStorageLink) {
		this->courseWorkStorageLink = courseWorkStorageLink;
	}
	friend fstream& operator<<(fstream& stream, const StudentCourseWork& self);

	string getCourseWorkTheme() {
		return courseWorkTheme;
	}
	string getCourseWorkLink() {
		return courseWorkStorageLink;
	}
};

extern vector<StudentCourseWork> studentsArray;

void GetStudentsFromFile();
void RegistrateStudentInFile();
void StudentFileRewrite();
vector<int> FindStudentInFile();
void DeleteStudentArray(int);
void RefreshStudentsId();
