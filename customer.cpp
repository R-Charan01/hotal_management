#include "customer.h"
#include <ctime>

Customer::Customer(std::string n, std::string h,
                   std::string r, std::string p, int d)
    : name(n), hotel(h), roomType(r),
      phone(p), stayDays(d),
      checkIn(std::time(nullptr)) {}

std::string Customer::getName() const { return name; }
std::string Customer::getHotel() const { return hotel; }
std::string Customer::getRoomType() const { return roomType; }
std::string Customer::getPhone() const { return phone; }
std::time_t Customer::getCheckIn() const { return checkIn; }

std::time_t Customer::getCheckOut() const {
    return checkIn + stayDays * 24 * 60 * 60;
}
