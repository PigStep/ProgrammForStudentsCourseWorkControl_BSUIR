#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <cstdlib>
#include <iomanip>
#include <fstream>

using namespace std;

extern fstream studentsFileDB; //to avoid multi linking (TManips.h & Header.h)

#define DB_FILE_NAME "StudentsDB.txt"

//Fuctions prototypes 
//EnteringMenu.cpp
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