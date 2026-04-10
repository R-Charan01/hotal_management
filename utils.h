#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <ctime>

std::string normalizeHotel(std::string h);
std::string normalizeRoomType(std::string t);

char hotelCode(const std::string& hotel);
char roomCode(const std::string& roomType);

int readInt(const std::string& msg);
std::string formatTime(std::time_t t);

#endif