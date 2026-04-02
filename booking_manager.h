#ifndef BOOKING_MANAGER_H
#define BOOKING_MANAGER_H

#include <unordered_map>
#include <memory>
#include <string>
#include "customer.h"

class BookingManager {
private:
    std::unordered_map<
        std::string,
        std::unordered_map<int, std::unique_ptr<Customer>>
    > customers;

    BookingManager();

public:
    static BookingManager& getInstance();

    bool empty() const;
    bool isRoomBooked(const std::string& roomType, int room);
    void addCustomer(
        const std::string& roomType,
        int room,
        std::unique_ptr<Customer> customer
    );
    bool removeCustomer(const std::string& roomType, int room);

    // ✅ FIX IS HERE
    std::unordered_map<
        std::string,
        std::unordered_map<int, std::unique_ptr<Customer>>
    >& getAllCustomers();
};

#endif