#pragma once
#include <vector>
#include <string>
#include "Student.h"

std::vector<Student> readFile(const std::string& filename);
std::vector<Student> mergeStudents(const std::vector<Student>& a,
                                   const std::vector<Student>& b);
