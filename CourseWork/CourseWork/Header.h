#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <cstdlib>
#include <iomanip>
#include<vector>
#include <fstream>

using namespace std;

//extern для избегания ошибки линковки
extern fstream studentsFileReg; 
extern fstream studentsCorseDeadLines;

// константы файлов
const string STUD_REG_FILE = "StudentsDB.txt";
const string DEAD_LINES_FILE = "StudentsDeadLines.txt";

//константы ошибок и предупреждений
const string ERR_CHOICE_INP = "";
const string ENTER_INP_WAIT = "Нажмите Enter для продолжения";

//даты
const string EMPTY_DEADLINES_FILE = "ВНИМАНИЕ, ФАЙЛ С КОНТРОЛЬНЫМИ ТОЧКАМИ ПУСТ";

//Fuctions prototypes 
//EnteringMenu.cpp
void FilePreparation();
void InitializeMenuLoginEntering();
bool UserAuthorizationMenu(bool);

//AdministratorMenu
extern void AdminFunctionsMenu();
void RefreshMenu(const string, int);

void StudentsListOperations();
void PrintStudentsFromFile();
void AddStudentFromArrayMenu();
void EditStudentsFromArrayMenu();
void DeleteStudentsFromArrayMenu();

void ShowStudentsDataTable();

void SetCourseDeadlines();
