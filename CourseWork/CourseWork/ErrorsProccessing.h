#pragma once
#include "Header.h"
#include "StudentFileManip.h"

class Student;
class User;
class StudentCourseWork;

const int MIN_COURSE = 100000;

//в рецензировани и установке тем сломались индексы
//табуляции и прочее в пароле

bool IsInteger(const std::string& s);
bool IsNumber(const std::string& s);
bool IsLikelyUrl(const std::string& str);

bool IsEmptyString(const std::string& s);

bool IsInRange(int value, int min, int max);

bool IsAlphaString(const std::string& s);

int GetIntegerInput(int min = INT_MIN, int max = INT_MAX, const std::string & prompt = "");

std::string GetStringInput(const std::string& prompt, bool allowEmpty = false, bool checkAlphaString = false);

std::string GetPasswordInput(const std::string& prompt);
std::string GetLinkInput(const std::string& prompt);

bool CheckRegistration(bool isAdmin, std::string& login, std::string& password);
void CheckAdmins();

bool IsLoginExist(const std::string& login);

bool CheckIsManipulatingAdmin(Student student);

bool GetUserApprove();

bool CheckDates();


