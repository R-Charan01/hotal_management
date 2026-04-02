#include "utils.h"
#include <iostream>
#include <limits>
#include <cctype>
#include <iomanip>
#include <sstream>

int readInt(const std::string& prompt, int& value) {
    while (true) {
        std::cout << prompt;

        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;   // ✅ always returns
        }

        std::cout << "Invalid input. Please enter an integer.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}


bool isAlphaSpace(const std::string& s) {
    if (s.empty()) return false;
    for (unsigned char ch : s)
        if (!std::isalpha(ch) && !std::isspace(ch))
            return false;
    return true;
}

bool isDigits(const std::string& s) {
    if (s.empty()) return false;
    for (unsigned char ch : s)
        if (!std::isdigit(ch))
            return false;
    return true;
}
int readStayDays() {
    int day;
    while (true) {
        int days = readInt("Enter number of days to stay: ",day);
        if (days >= 1 && days <= 10)
            return days;
        std::cout << "Days must be between 1 and 10.\n";
    }
}

std::string formatTime(std::time_t t) {
    std::tm* tmPtr = std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(tmPtr, "%d-%m-%Y");
    return oss.str();
}