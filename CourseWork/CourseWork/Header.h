#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

//extern для избегания ошибки линковки
extern fstream studentsFileReg; 
extern fstream studentsFileData;
extern fstream studentsFileDeadLines;

// константы файлов
const string STUD_REG_FILE = "REG_STUDENTS.txt";
const string STUD_DATA_FILE = "DATA_STUDENTS.txt";
const string DEAD_LINES_FILE = "StudentsDeadLines.txt";

//константы ошибок и предупреждений
const string ERR_CHOICE_INP = "";
const string ENTER_INP_WAIT = "Нажмите Enter для продолжения";
const string REG_AUTH_FAIL = "Ошибка, пользователь с такими данными не найден!";

//даты
const string EMPTY_DEADLINES_FILE_WARN = "ВНИМАНИЕ, ФАЙЛ С КОНТРОЛЬНЫМИ ТОЧКАМИ ПУСТ";

//Fuctions prototypes 
//EnteringMenu.cpp

void FilePreparation();
void InitializeMenuLoginEntering();
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

void ShowStudentsDataTable();

void SetCourseDeadlines();

void SetStudentsMarks();
