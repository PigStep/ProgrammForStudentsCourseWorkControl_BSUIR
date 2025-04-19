#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <fstream>
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

void ShowStudentsDataTable();

void SetCourseDeadlines();

void SetStudentsMarks();

void SetStudentCourseTheme();
