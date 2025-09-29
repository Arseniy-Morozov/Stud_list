#include "utils/Student.h"
#include <zmq.hpp>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>
#include <algorithm>
#include <mutex>
#include <chrono>

std::mutex mtx;

void subscriberThread(std::vector<Student>& students) {
    zmq::context_t context(1);
    zmq::socket_t socket(context, zmq::socket_type::sub);
    socket.connect("tcp://localhost:5555");
    socket.set(zmq::sockopt::subscribe, "");

    auto start = std::chrono::steady_clock::now();
    while (true) {
        zmq::message_t message;
        auto res = socket.recv(message, zmq::recv_flags::dontwait); // неблокирующий
        if (res) {
            std::string msg(static_cast<char*>(message.data()), message.size());
            std::istringstream iss(msg);
            Student s;
            if (!(iss >> s.firstName >> s.lastName >> s.birthDate)) continue;

            std::lock_guard<std::mutex> lock(mtx);
            students.push_back(s);
        }

        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now - start).count() > 5) {
            break; // ждём 5 секунд и считаем, что все сообщения пришли
        }
    }
}

int main() {
    std::vector<Student> students;

    std::thread subThread(subscriberThread, std::ref(students));
    subThread.join();

    std::sort(students.begin(), students.end(),
              [](const Student& a, const Student& b) {
                  if (a.lastName != b.lastName) return a.lastName < b.lastName;
                  return a.firstName < b.firstName;
              });

    std::cout << "\n===== Отсортированный список студентов =====\n";
    for (auto& s : students)
        std::cout << s.firstName << " " << s.lastName << " " << s.birthDate << "\n";
    std::cout << "===========================================\n";

    return 0;
}
