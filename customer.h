#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <ctime>

class Customer {
private:
    std::string name;
    std::string room_type;
    int room;
    std::string phone;
    std::time_t checkin_time;
    int stay_days;

    static void validateName(const std::string& n);
    static void validateRoom(int r);
    static void validatePhone(const std::string& p);

public:
    Customer(const std::string& n, int r, const std::string& p,
             const std::string& t, int days, std::time_t inTime);

    std::string getname() const;
    int getroom() const;
    std::string getphone() const;
    std::string getroom_type() const;
    std::time_t getCheckInTime() const;
    std::time_t getCheckOutTime() const;
};

#endif