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
        if (!iswdigit(s[i])) {
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
    
    locale loc("Russian");

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

//Замаскировать вводимый пароль
string getPasswordWithMask() {
    string password;
    char ch;

    while (true) {
        ch = _getch(); // Читаем символ без отображения

        if (ch == '\r' || ch == '\n') { // Enter - завершение ввода
            cout << endl;
            break;
        }
        else if (ch == '\b') { // Backspace - удаление символа
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; // Удаляем звёздочку из консоли
            }
        }
        else {
            password.push_back(ch);
            cout << '*'; // Выводим звёздочку вместо символа
        }
    }

    return password;
}
//Безопасный ввод пароля
string GetPasswordInput(const string& prompt) {
    string input;
    do {
        cout << left << setw(INPUT_PADDING) << prompt;
        input = getPasswordWithMask();

        if (input.size() < 5) {
            cout << "Слишком короткий пароль! Попробуйте еще раз" << endl;
        }
    } while (input.size() < 5);

    return input;
}
// Простая проверка на наличие ключевых элементов URL
bool IsLikelyUrl(const string& str) {
    return str.find("http://") == 0 ||
        str.find("https://") == 0 ||
        str.find("www.") == 0 ||
        str.find(".com") != string::npos || //string::npos - некорректная позиция
        str.find(".ru") != string::npos ||
        str.find(".net") != string::npos ||
        str.find(".org") != string::npos;
}

string GetLinkInput(const string& prompt) {
    string input;
    while (true) {
        input = GetStringInput(prompt);

        if (IsLikelyUrl(input))
            break;
        else {
            cout << "Предупреждение: Это не похоже на ссылку. "
                << "Пример корректной ссылки: https://example.com\n";
        }
    }

    return input;
}

//Проверка, зарегистрирован ли пользователь
bool CheckRegistration(bool isAdmin, string& login, string& password) {
    for (int i = 0; i < studentsArray.size(); i++) {
        if (studentsArray[i].getLogin() == login
            && studentsArray[i].checkPassword(password)
            && (bool)studentsArray[i].getUserLevel() == isAdmin) 
        {
            userAccountLink = &studentsArray[i];
            if (!studentsArray[i].getAcces()) {
                cout << "Эта учетная запись еще не получила подтверждения на доступ к системе. Повторите попытку позже\n";
                return false;
            }

            return true;
        }
    }

    cout << "Ошибка, пользователь с такими данными не найден!" << endl;

    if (!isAdmin) {
        cout << "Возможна регистрация пользователя с логином: " << login << endl;
        if (GetUserApprove()) {
            RegistrateStudentInFile(false, login);
            string successMessage = "УСПЕШНО, ОЖИДАЙТЕ ПОДТВЕРЖДЕНИЕ АДМИНИСТРАТОРОМ";
        }
        
    }

    return false;
}

//проверка, хочет ли пользователь провести нежелательноую манипуляцию с администратором
bool CheckIsManipulatingAdmin(Student student) {
    if (student.getId() == 1)
    {
        cout << "Ошибка, подобную операцию невозможно провести с администратором!" << endl;
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

//Проверка, существует ли полльзователь с таким логином
bool IsLoginExist(const string& login) {
    for (int i = 0; i < studentsArray.size(); i++) {
        if (studentsArray[i].getLogin() == login){

            userAccountLink = &studentsArray[i];
            cout << "Ошибка. Пользователь с подобным логином уже существует! Попробуйте другой\n";

            return true;
        }
    }
    return false;
}

//Проверка порядка дат
bool CheckDates() {
    for (int i = 1; i < NUM_OF_DEADLINES; i++) {
        if (courseDeadLinePoints[i - 1] > courseDeadLinePoints[i]) {
            cout << "Ошибка. Даты неупорядочены. Повторите ввод\n";
            return false;
        }
    }
    return true;
}