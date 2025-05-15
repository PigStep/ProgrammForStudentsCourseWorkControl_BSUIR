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

void FilePreparation(); //Загрузить необходимые для старта файлы
void InitializeMenuLoginEntering(); //Меню выбора роли для входа
void CheckAdmins(); //Проверить, сколько админов в системе
bool UserAuthorizationMenu(bool); //Меню ввода пароля/логина
bool CheckRegistration(bool isAdmin, string& login, string& password); //Проверить, существует ли побдобная запись

extern void AdminFunctionsMenu(); //Вывести функционал администратора
void RefreshMenu(const string, int); //Обновить заголовок

void AccountsListOperations(); //Предоставить возможные операции с учетными записями
void PrintAccountssFromFile(); //Вывести информацию об учетных записях
void AddAccountMenu(); //Меню добавления учетной записи
void EditAccountsFromArrayMenu(); //Меню изменения учетной записи
void DeleteAccountsFromArrayMenu(); //Меню удаления учетной записи
void GiveAccesStudents(); //Меню предоставления доступа для входа


void ShowStudentsDataTable(); //Показать таблицу студентов

void SetCourseDeadlines(); //Меню установки дедлайнов

void SetStudentsMarks(); //Меню рецензирования студента

void SetStudentCourseTheme(); //Меню установки темы курсовой

void IndividualTask(); //Индивидуальное задание

extern void UserFunctionsMenu(); //Меню пользователя
void PrintAccountData(); //Вывести данные текущей учетной записи
void EditAccountData(); //Изменить данные текущей учетной записи

void SetCourseWorkLink(); //Меню установки ссылки на курсовую

void GetStudentByParam(); //Поиск студента по параметрам