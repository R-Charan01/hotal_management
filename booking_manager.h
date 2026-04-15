#ifndef BOOKING_MANAGER_H
#define BOOKING_MANAGER_H

#include <unordered_map>
#include <memory>
#include <vector>
#include <string>
#include "customer.h"

class BookingManager {
    std::unordered_map<std::string, int> inventory;
    std::unordered_map<std::string, std::unique_ptr<Customer>> bookings;

    BookingManager();

public:
    static BookingManager& getInstance();

    void showAvailability(const std::string& roomType);

    std::vector<std::string> bookRooms(
        const std::string& hotel,
        const std::string& roomType,
        const std::string& name,
        const std::string& phone,
        int days,
        int count);

    void displayBookings();
    void showRoomStatus();
    void checkout();
    bool hasBookings() const;
};

#endif
