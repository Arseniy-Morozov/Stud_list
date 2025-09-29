Программа обработки и передачи информации о студентах клиентам от сервера по протоколу ZeroMQ.
Действия сервера:
 - Сформировать обобщенный список студентов. В качестве исходных данных использовать 2 файла 
 	student_file_1.txt и student_file_2.txt в следующем формате:
		 student_file_1.txt
		----
		1 Ivan Ivanovich 01.01.1988
		2 Petr Petrov 04.07.1988
		3 Denis Denisov 43.01.1988
		4 Vladimir Jukov 04.5.1987
		5 Vladimir Kochkin 11.10.1989
		----
	
		student_file_2.txt
		----
		34 Ivan Ivanovich 01.01.1988
		54 Petr Kazakov 05.07.1986
		23 Denis Denisov 04.03.1988
		12 Vladimir Jukov 04.5.1987
		43 Vladimir Kochkin 11.11.1989
		----
 - Объединить одинаковых студентов по ФИО и дате рождения
 - Отправить полученный список на клиент по протоколу ZeroMQ pub
 
Действия клиента (sub):
 - Принять все полученные данные от сервера по протоколу ZeroMQ sub
 - Отсортировать студентов по ФИО
 - Отобразить отсортированный список студентов на экране




Стурктура проекта
```

│
├── stud/
│   ├── src/
│   │   ├── main.cpp
│   │   ├── ConfigurationManager.cpp
│   │   ├── ConfigurationManager.hpp
│   │   ├── ApplicationObject.cpp
│   │   ├── ApplicationObject.hpp
│   ├── CMakeLists.txt
│
│   ├── src/
│   │   ├── client.cpp
│   │   ├── server.cpp
│   │   ├── utils/
│   │   │   ├── FileReader.h
│   │   │   ├── FileReader.cpp
│   │   │   ├── Student.h
│   │   │   ├── Student.cpp
├── 
```
