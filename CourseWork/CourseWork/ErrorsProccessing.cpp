#include "ErrorsProccessing.h"

using namespace std;

// Проверка, является ли строка целым числом
bool IsInteger(const string& s) {
    if (s.empty()) return false;
    
    size_t start = 0;
    if (s[0] == '-') {
        if (s.length() == 1) return false; // только минус
        start = 1;
    }
    
    for (size_t i = start; i < s.length(); i++) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

// Проверка, является ли строка числом (целым или вещественным)
bool IsNumber(const string& s) {
    return IsInteger(s);
}

// Проверка на пустую строку
bool IsEmptyString(const string& s) {
    return s.empty();
}

// Проверка, находится ли число в заданном диапазоне
bool IsInRange(int value, int min, int max) {
    return value >= min && value <= max;
}

// Проверка, является ли строка алфавитной (только буквы)
bool IsAlphaString(const string& s) {
    if (s.empty()) return false;
    
    locale loc("");

    for (char c : s) {
        if (c == ' ')
            return false; // запрещаем пробелы
        if (!isalpha(c, loc)) { 
            return false;
        }
    }
    return true;
}

// Безопасный ввод целого числа с проверкой
int GetIntegerInput(int min, int max, const string& prompt) {
    int value;
    string input;
    
    while (true) {

        if(!prompt.empty())
            cout << left << setw(INPUT_PADDING) << prompt;

        getline(cin, input);
        
        if (IsEmptyString(input)) {
            cout << "Ошибка: введена пустая строка. Повторите ввод.\n";
            continue;
        }
        
        if (!IsInteger(input)) {
            cout << "Ошибка: введено не целое число. Повторите ввод.\n";
            continue;
        }
        
        istringstream iss(input);
        iss >> value;
        
        if (iss.fail()) {
            cout << "Ошибка при преобразовании ввода. Повторите ввод.\n";
            continue;
        }
        
        if (!IsInRange(value, min, max)) {
            cout << "Ошибка: число должно быть в диапазоне от " << min 
                      << " до " << max << ". Повторите ввод.\n";
            continue;
        }
        
        break;
    }
    
    return value;
}

// Безопасный ввод строки с проверкой
string GetStringInput(const string& prompt, bool allowEmpty , bool checkAlphaString) {
    string input;
    
    while (true) {
        cout << left << setw(INPUT_PADDING) << prompt;
        getline(cin, input);
        
        if (!allowEmpty && IsEmptyString(input)) {
            cout << "Ошибка: введена пустая строка. Повторите ввод.\n";
            continue;
        }
        
        if (checkAlphaString && !IsAlphaString(input))
        {
            cout << "Ошибка: в строке обнаружены посторонние символы. Повторите ввод.\n";
            continue;
        }

        break;
    }
    
    return input;
}

//Проверка, зарегистрирован ли пользователь
bool CheckRegistration(bool isAdmin, string& login, string& password) {
    for (int i = 0; i < studentsArray.size(); i++) {
        if (studentsArray[i].getLogin() == login
            && studentsArray[i].checkPassword(password)
            && (bool)studentsArray[i].getUserLevel() == isAdmin) {
            userAccount = &studentsArray[i];
            return true;
        }
    }

    cout << "Ошибка, пользователь с такими данными не найден!" << endl;

    return false;
}

//проверка, хочет ли пользователь провести нежелательноую манипуляцию с администратором
bool CheckIsManipulatingAdmin(Student student) {
    if (student.getId() == 1)
    {
        cout << "Ошибка, подобную операцию невозможно провести с администратором!" << endl;
        cin.ignore();
        return true;
    }
}

//Функция провери и создания Админа в случае его отсутвия
void CheckAdmins() {
    if (AdminArrayCount() == 0) {
        CreateBaseAdmin();
        cout << "ВНИМАНИЕ, В ФАЙЛЕ ДАННЫХ НЕ НАЙДЕН АДМИНИСТРАТОР, БЫЛ СОЗДАН АДМИНИСТРАТОР ПО УМОЛЧАНИЮ (admin admin)" << endl;
    }
}

//Получить потверждение пользователя
bool GetUserApprove() {
    int delChoise;

    cout << "Вы уверены? (1 - да, 0 - я передумал)" << setw(INPUT_PADDING) << ": ";
    delChoise = GetIntegerInput(0, 1);
    
    return (bool)delChoise;
}

bool IsLoginExist(const string& login) {
    for (int i = 0; i < studentsArray.size(); i++) {
        if (studentsArray[i].getLogin() == login){

            userAccount = &studentsArray[i];
            cout << "Ошибка. Пользователь с подобным логином уже существует! Попробуйте другой\n";

            return true;
        }
    }
    return false;
}