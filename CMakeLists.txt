cmake_minimum_required(VERSION 3.10)
project(stud_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PC_ZMQ REQUIRED libzmq)
include_directories(${PC_ZMQ_INCLUDE_DIRS})
link_directories(${PC_ZMQ_LIBRARY_DIRS})

# Сервер
add_executable(server
    src/server.cpp
    src/utils/FileReader.cpp
)

target_link_libraries(server ${PC_ZMQ_LIBRARIES} pthread)

# Клиент
add_executable(client
    src/client.cpp
    src/utils/FileReader.cpp
)

target_link_libraries(client ${PC_ZMQ_LIBRARIES} pthread)
