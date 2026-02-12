#pragma once
#include <string>

struct Contact {
    std::string last;
    std::string first;
    std::string middle;
    std::string phone;
};

struct Task {
    //флаг для остановки рабочих потоков, когда producer закончит свою работу и не будет больше задач для обработки
    bool stop = false; 
    Contact c;
};

struct Result {
    bool stop = false;
    char key = '#';
    Contact c;
};
