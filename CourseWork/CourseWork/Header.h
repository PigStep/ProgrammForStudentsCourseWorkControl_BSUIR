#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <cstdlib>
#include <iomanip>
#include<vector>
#include <fstream>

using namespace std;

//extern ��� ��������� ������ ��������
extern fstream studentsFileReg; 
extern fstream studentsCorseDeadLines;

// ��������� ������
const string STUD_REG_FILE = "StudentsDB.txt";
const string DEAD_LINES_FILE = "StudentsDeadLines.txt";

//��������� ������ � ��������������
const string ERR_CHOICE_INP = "";
const string ENTER_INP_WAIT = "������� Enter ��� �����������";

//����
const string EMPTY_DEADLINES_FILE = "��������, ���� � ������������ ������� ����";

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
