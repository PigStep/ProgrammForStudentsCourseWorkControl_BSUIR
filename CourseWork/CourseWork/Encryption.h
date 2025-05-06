#pragma once
#include "Header.h"
#include <algorithm>
#include <ctime>
#include <random>
#include <numeric>

const int HASH_KEY = 31;

string GenerateSalt();

string SimpleHash(const string& s);

string HashPassword(const string& password, const string& salt);

string getPasswordWithMask();
