#pragma once
#include <iostream>
#include <string>
#include <locale>
#include <Windows.h>
#include <iomanip>
#include <vector>
#include <fstream>
#include <conio.h>
#include "ErrorsProccessing.h"

using namespace std;

//extern для избегания ошибки линковки
extern fstream studentsFileReg; 
extern fstream studentsFileData;
extern fstream studentsFileDeadLines;

// константы файлов
const string STUD_REG_FILE = "REG_STUDENTS.txt";
const string STUD_DATA_FILE = "DATA_STUDENTS.txt";
const string DEAD_LINES_FILE = "StudentsDeadLines.txt";

// табличные константы
const int BORDERS_WIDTH = 80;   // Общая ширина таблицы
const int OPTIONS_PADDING = 5; // Отступ для значений
const int HEADER_WIDTH = 10;  // Ширина левой колонки
const int INPUT_PADDING = 10;   // Отступ для полей ввода

//Fuctions prototypes 
//EnteringMenu.cpp

void FilePreparation();
void InitializeMenuLoginEntering();
void CheckAdmins();
bool UserAuthorizationMenu(bool);
bool CheckRegistration(bool isAdmin, string& login, string& password);

//AdministratorMenu

extern void AdminFunctionsMenu();
void RefreshMenu(const string, int);

void StudentsListOperations();
void PrintStudentsFromFile();
void AddStudentMenu();
void EditStudentsFromArrayMenu();
void DeleteStudentsFromArrayMenu();
void GiveAccesStudents();

void ShowStudentsDataTable();

void SetCourseDeadlines();

void SetStudentsMarks();

void SetStudentCourseTheme();

//Меню пользователя
extern void UserFunctionsMenu();
void PrintAccountData();

void SetCourseWorkLink();

void GetStudentByParam();