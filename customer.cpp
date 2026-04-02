#include "customer.h"
#include <stdexcept>
#include <cctype>

static bool isAlphaSpaceInternal(const std::string& s) {
    for (unsigned char ch : s)
        if (!std::isalpha(ch) && !std::isspace(ch))
            return false;
    return true;
}

static bool isDigitsInternal(const std::string& s) {
    for (unsigned char ch : s)
        if (!std::isdigit(ch))
            return false;
    return true;
}

void Customer::validateName(const std::string& n) {
    if (!isAlphaSpaceInternal(n))
        throw std::invalid_argument("Invalid name");
}

void Customer::validateRoom(int r) {
    if (r <= 0)
        throw std::invalid_argument("Invalid room number");
}

void Customer::validatePhone(const std::string& p) {
    if (!isDigitsInternal(p) || p.size() < 10 || p.size() > 15)
        throw std::invalid_argument("Invalid phone");
}

Customer::Customer(const std::string& n, int r, const std::string& p,
                   const std::string& t, int days, std::time_t inTime) {
    validateName(n);
    validateRoom(r);
    validatePhone(p);

    name = n;
    room = r;
    phone = p;
    room_type = t;
    stay_days = days;
    checkin_time = inTime;
}

std::string Customer::getname() const { return name; }
int Customer::getroom() const { return room; }
std::string Customer::getphone() const { return phone; }
std::string Customer::getroom_type() const { return room_type; }
std::time_t Customer::getCheckInTime() const { return checkin_time; }
std::time_t Customer::getCheckOutTime() const {
    return checkin_time + stay_days * 24 * 60 * 60;
}