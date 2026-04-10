#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <ctime>

class Customer {
    std::string name;
    std::string hotel;
    std::string roomType;
    std::string phone;
    int stayDays;
    std::time_t checkIn;

public:
    Customer(std::string n, std::string h, std::string r,
             std::string p, int d);

    std::string getName() const;
    std::string getHotel() const;
    std::string getRoomType() const;
    std::string getPhone() const;
    std::time_t getCheckIn() const;
    std::time_t getCheckOut() const;
};

#endif