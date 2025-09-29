#include "FileReader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>

std::vector<Student> readFile(const std::string& filename) {
    std::vector<Student> students;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return students;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Student s;
        int id;
        if (!(iss >> id >> s.firstName >> s.lastName >> s.birthDate)) {
            std::cerr << "Ошибка парсинга строки: " << line << std::endl;
            continue;
        }

        if (!validateDate(s.birthDate)) {
            std::cerr << "Некорректная дата: " << s.birthDate 
                      << " для студента " << s.firstName << " " << s.lastName << std::endl;
            continue;
        }

        students.push_back(s);
    }
    return students;
}

std::vector<Student> mergeStudents(const std::vector<Student>& a,
                                   const std::vector<Student>& b) {
    std::vector<Student> result = a;

    for (const auto& s : b) {
        bool exists = false;
        for (const auto& r : result) {
            if (s == r) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            result.push_back(s);
        }
    }
    return result;
}
