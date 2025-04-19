#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

//extern ��� ��������� ������ ��������
extern fstream studentsFileReg; 
extern fstream studentsFileData;
extern fstream studentsFileDeadLines;

// ��������� ������
const string STUD_REG_FILE = "REG_STUDENTS.txt";
const string STUD_DATA_FILE = "DATA_STUDENTS.txt";
const string DEAD_LINES_FILE = "StudentsDeadLines.txt";

//��������� ������ � ��������������
const string ERR_CHOICE_INP = "";
const string ENTER_INP_WAIT = "������� Enter ��� �����������";
const string REG_AUTH_FAIL = "������, ������������ � ������ ������� �� ������!";

//����
const string EMPTY_DEADLINES_FILE_WARN = "��������, ���� � ������������ ������� ����";

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
