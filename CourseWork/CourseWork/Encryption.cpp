#include "Encryption.h"

// Генерация случайной соли (16 символов)
string GenerateSalt() {
    const string chars =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    mt19937 gen(random_device{}());
    uniform_int_distribution<size_t> dist(0, chars.size() - 1);

    string salt;
    salt.reserve(16);
    for (int i = 0; i < 16; ++i) {
        salt += chars[dist(gen)];
    }
    return salt;
}

//хеш-функция
string SimpleHash(const string& s) {
    return to_string(
        accumulate(s.begin(), s.end(), 0,
            [](int sum, char c) { return sum + c * HASH_KEY; }
        )
    );
}

// Хеширование пароля с солью
string HashPassword(const string& password, const string& salt) {
    return SimpleHash(password + salt);
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
        else if (ch == ' ' || ch == '\t') {
            // Игнорируем пробелы и табуляции
            continue;
        }
        else {
            password.push_back(ch);
            cout << '*'; // Выводим звёздочку вместо символа
        }
    }

    return password;
}