#include "utils/Student.h"
#include "utils/FileReader.h"
#include <zmq.hpp>
#include <iostream>
#include <thread>
#include <sstream>
#include <vector>

void publisherThread(std::vector<Student> students) {
    zmq::context_t context(1);
    zmq::socket_t socket(context, zmq::socket_type::pub);
    socket.bind("tcp://*:5555");

    std::this_thread::sleep_for(std::chrono::seconds(1)); // дать клиенту подключиться

    for (auto& s : students) {
        std::ostringstream oss;
        oss << s.firstName << " " << s.lastName << " " << s.birthDate;
        std::string msg = oss.str();

        zmq::message_t message(msg.size());
        memcpy(message.data(), msg.c_str(), msg.size());
        socket.send(message, zmq::send_flags::none);

        std::cout << "Отправлено: " << msg << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    auto students1 = readFile("../data/student_file_1.txt");
    auto students2 = readFile("../data/student_file_2.txt");

    auto merged = mergeStudents(students1, students2);

    std::thread pubThread(publisherThread, merged);
    pubThread.join();

    return 0;
}
