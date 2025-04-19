#pragma once
#include "Header.h"
#include "DeadLines.h"
#include <sstream>

using namespace std;

const string THEME_DEFAULT = "NO_THEME_WAS_PROVIDED";
const string STORAGE_LINK_DEFAULT = "NO_STORAGE_LINK_WAS_PROVIDED";

const int NUM_OF_DEADLINES = 3;
const int DEFAULT_MARK = -1;
const string DEFAULT_MARK_TEXT = "Кнтр. точка не оценена";

extern Date courseDeadLinePoints[NUM_OF_DEADLINES];

class User {
protected:
	int user_level;
	int id;

	string login;
	string soltedPassword;
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
	int deadLinePointsMarks[NUM_OF_DEADLINES];

	string courseWorkTheme;
	string courseWorkStorageLink;

protected:
	void setMarksDefault();

public:
	StudentCourseWork() {
		courseWorkTheme = THEME_DEFAULT;
		courseWorkStorageLink = STORAGE_LINK_DEFAULT;
		setMarksDefault();
	}

	//Конструктор Администратора
	StudentCourseWork(int id, int userLevel, 
		string password, string login, 
		string name, string secondname, string surname);

	StudentCourseWork(int id, int userLevel, 
		string password, string login,
		string name, string secondname, string surname, 
		int group, int course) : Student(id, userLevel, password, login, name, secondname, surname, group, course) {

		courseWorkStorageLink = STORAGE_LINK_DEFAULT;
		courseWorkTheme = THEME_DEFAULT;
		setMarksDefault();
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

	int getMark(int index);

	void setDeadLineMark(int deadLineIndex, int mark);
};

extern vector<StudentCourseWork> studentsArray;

void GetStudentsFromFile();
void RegistrateStudentInFile();
void StudentFileRewrite();
vector<int> FindStudentInFile();
void DeleteStudentArray(int);
void RefreshStudentsId();

//Операции с контрольными точками

void SaveDeadLinesInFile();
void LoadDeadlinesFromFile();

string GetDeadLines();