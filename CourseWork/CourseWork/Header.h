#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <cstdlib>
#include <iomanip>

using namespace std;

//Fuctions prototypes 
//EnteringMenu.cpp
void InitializeMenuLoginEntering();
bool UserAuthorizationMenu(bool);

//AdministratorMenu
extern void AdminFunctionsMenu();
void RegistrateStudents();
void StudentsListOperations();