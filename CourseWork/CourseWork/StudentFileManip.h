#pragma once
#include "DeadLines.h"
#include "Encryption.h"
#include <sstream>

using namespace std;

class User;
class Student;
class StudentCourseWork;

//Ссылка на текущую учетную запись
extern StudentCourseWork* userAccountLink;

const string THEME_DEFAULT = "Тема курсовой не установлена";
const string STORAGE_LINK_DEFAULT = "Работа не опубликована";

const int NUM_OF_DEADLINES = 3;
const int DEFAULT_MARK = -1;
const string DEFAULT_MARK_TEXT = "Кнтр. точка не оценена";

extern Date courseDeadLinePoints[NUM_OF_DEADLINES];

extern vector<StudentCourseWork> studentsArray;

//Функция загрузки студентов из файла в оперативную память
void LoadStudentsFromFile();

// Вспомогательная функция для разделения строки
vector<string> SplitString(const string& str, char delimiter);

//Функция регистрации студента с записью в файл
void RegistrateStudentInFile();

//Функция перезаписи файла студентами из оперативной памяти
void StudentFileRewrite();

//Функция поиска студента по параметру
vector<int> FindUserByParam();
vector<int> SortIndexes();

//Найти количество админов в оперативной памяти
int AdminArrayCount();
void CreateBaseAdmin();

//Функция удаления студента из вектора
void DeleteStudentArray(int);

//Функция обновления всей ID у студентов
void RefreshStudentsId();

//Операции с контрольными точками

//Функция записи контрольных точек из консоли в файл
void SaveDeadLinesInFile();
void LoadDeadlinesFromFile();
string GetDeadLines();
void ShowDeadLinesList();


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

	// Геттеры для всех полей

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

	//Конструктор Администратора
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

	void setCourseWorkTheme();

	void writeInFiles(fstream& dataStream, fstream& regStream);
};