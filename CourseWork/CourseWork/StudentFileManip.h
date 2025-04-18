#pragma once
#include "Header.h"
#include "DeadLines.h"
#include "Encryption.h"
#include <sstream>

using namespace std;

const string THEME_DEFAULT = "NO_THEME_WAS_PROVIDED";
const string STORAGE_LINK_DEFAULT = "NO_STORAGE_LINK_WAS_PROVIDED";

const int NUM_OF_DEADLINES = 3;
const int DEFAULT_MARK = -1;
const string DEFAULT_MARK_TEXT = "����. ����� �� �������";

extern Date courseDeadLinePoints[NUM_OF_DEADLINES];

class User {
protected:
	int userLevel;
	int id;

	string login;
	string salt;
	string hashedPassword;
public:
	User();

	User(int id, int userLevel,
		string login, string salt, string password);

	void setId(int newId) { id = newId; }

	int getId() const { return id; }

	friend fstream& operator<<(fstream& stream, const User& self);

	string getLogin() const { return login; }

	bool checkPassword(const string& password);

	void hashPassword(const string& password);

	string getSalt() const { return salt; }

	string getHashedPassword() const { return hashedPassword; }
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
		string login, string salt, string password,
		string name, string secondname, string surname);


	Student(int id, int userLevel,
		string login, string salt, string password,
		string name, string secondname, string surname,
		int groupe, int course);

	void StudentEdit();

	friend fstream& operator<<(fstream& stream, const Student& self);

	// ������� ��� ���� �����

	string getName() const { return name; }

	string getSecondName() const { return secondname; }

	string getSurname() const { return surname; }

	int getGroup() const { return group; }

	int getCourse() const { return course; }

	bool isUserAdmin()const {
		if (userLevel == 1) return true;
		return false;
	}

	int getUserLevel() const { return userLevel; }

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

	//����������� ��������������
	StudentCourseWork(int id, int userLevel, 
		string login, string salt, string password,
		string name, string secondname, string surname);

	StudentCourseWork(int id, int userLevel, 
		string login, string salt, string password,
		string name, string secondname, string surname, 
		int group, int course): Student(id,userLevel,login,salt,password,name,secondname,surname, group,course){

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

	void setMark(int deadLineIndex, int mark);

	void writeInFiles(fstream& dataStream, fstream& regStream);
};

extern vector<StudentCourseWork> studentsArray;

//������� �������� ��������� �� ����� � ����������� ������
void LoadStudentsFromFile();

// ��������������� ������� ��� ���������� ������
vector<string> SplitString(const string& str, char delimiter);

//������� ����������� �������� � ������� � ����
void RegistrateStudentInFile();

//������� ���������� ����� ���������� �� ����������� ������
void StudentFileRewrite();

//������� ������ �������� �� ���������
vector<int> FindStudentByParam();

//����� ���������� ������� � ����������� ������
int AdminArrayCount();
void CreateBaseAdmin();

//������� �������� �������� �� �������
void DeleteStudentArray(int);

//������� ���������� ���� ID � ���������
void RefreshStudentsId();

//�������� � ������������ �������

//������� ������ ����������� ����� �� ������� � ����
void SaveDeadLinesInFile();

//������� �������� ����������� ����� �� ����� � ����������� ������
void LoadDeadlinesFromFile();

//������� ��������� ���� ��� ����������� ����� ����� �������
string GetDeadLines();
//������� ������ ���� ���������� ����� � ���� ������
void ShowDeadLinesList();
