#include "utils.h"
#include <iostream>
#include <limits>
#include <iomanip>
#include <sstream>
#include <cctype>

std::string normalizeHotel(std::string h) {
    for (char& c : h) c = std::tolower(c);
    if (h == "ram" || h == "r") return "Ram";
    if (h == "charan" || h == "c") return "Charan";
    return "";
}

std::string normalizeRoomType(std::string t) {
    for (char& c : t) c = std::tolower(c);
    if (!t.empty() && t[0] == 'd') return "Delux";
    if (!t.empty() && t[0] == 'n') return "Non-Delux";
    return "";
}

char hotelCode(const std::string& hotel) {
    return std::tolower(hotel[0]);
}

char roomCode(const std::string& roomType) {
    return std::tolower(roomType[0]);
}

int readInt(const std::string& msg) {
    int x;
    while (true) {
        std::cout << msg;
        if (std::cin >> x && x > 0) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return x;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Try again.\n";
    }
}

std::string formatTime(std::time_t t) {
    std::tm* tmPtr = std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(tmPtr, "%d-%m-%Y");
    return oss.str();
}