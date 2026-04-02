#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <ctime>

int readInt(const std::string& prompt,int& value);
bool isAlphaSpace(const std::string& s);
bool isDigits(const std::string& s);
int readStayDays();
std::string formatTime(std::time_t t);

#endif