#include "Encryption.h"

// Генерация случайной соли (16 символов)
string GenerateSalt() {
    const string chars =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    mt19937 gen(std::random_device{}());
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
