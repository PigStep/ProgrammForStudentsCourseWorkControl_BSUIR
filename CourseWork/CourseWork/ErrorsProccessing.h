#pragma once
#include "Header.h"
#include "StudentFileManip.h"

class Student;
class User;
class StudentCourseWork;

//проверка строки с символами сломалась (странная хуйня ток при первом запуске)
//проверка WaitEnterInput на энтер
//проверка, удаляется ли админ

bool IsInteger(const std::string& s);
bool IsNumber(const std::string& s);

bool IsEmptyString(const std::string& s);

bool IsInRange(int value, int min, int max);

bool IsAlphaString(const std::string& s);

int GetIntegerInput(int min = INT_MIN, int max = INT_MAX, const std::string & prompt = "");

std::string GetStringInput(const std::string& prompt, bool allowEmpty = false, bool checkAlphaString = false);

bool CheckRegistration(bool isAdmin, std::string& login, std::string& password);\

bool IsLoginExist(const std::string& login);

bool CheckIsManipulatingAdmin(Student student);

bool GetUserApprove();



