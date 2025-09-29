#pragma once
#include <string>
#include <regex>
#include <cstdlib>

struct Student {
    std::string firstName;
    std::string lastName;
    std::string birthDate;

    bool operator==(const Student& other) const {
        return firstName == other.firstName &&
               lastName == other.lastName &&
               birthDate == other.birthDate;
    }
};

// Валидация даты DD.MM.YYYY
inline bool validateDate(const std::string& date) {
    std::regex pattern(R"((\d{2})\.(\d{2})\.(\d{4}))");
    std::smatch match;
    if (!std::regex_match(date, match, pattern)) return false;

    int d = std::stoi(match[1]);
    int m = std::stoi(match[2]);
    int y = std::stoi(match[3]);

    if (m < 1 || m > 12) return false;
    if (d < 1 || d > 31) return false;
    if (y < 1900 || y > 2100) return false;

    if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) return false;
    if (m == 2) {
        bool leap = (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0));
        if (d > (leap ? 29 : 28)) return false;
    }
    return true;
}
