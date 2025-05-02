#pragma once
#include "Header.h"
#include "StudentFileManip.h"

class Student;
class User;
class StudentCourseWork;

//проверка, существует ли логин
//проверка, удаляется ли админ

bool IsInteger(const std::string& s);
bool IsNumber(const std::string& s);

bool IsEmptyString(const std::string& s);

bool IsInRange(int value, int min, int max);

bool IsAlphaString(const std::string& s);

int GetIntegerInput(int min = INT_MIN, int max = INT_MAX, const std::string & prompt = "");

std::string GetStringInput(const std::string& prompt, bool allowEmpty = false, bool checkAlphaString = true);

bool CheckRegistration(bool isAdmin, std::string& login, std::string& password);

bool CheckIsManipulatingAdmin(Student student);

bool GetUserApprove();

