#include "booking_manager.h"

BookingManager::BookingManager() {}

BookingManager& BookingManager::getInstance() {
    static BookingManager instance;
    return instance;
}

bool BookingManager::empty() const {
    return customers.empty();
}

bool BookingManager::isRoomBooked(const std::string& roomType, int room) {
    auto hotelIt = customers.find(roomType);
    if (hotelIt == customers.end())
        return false;

    return hotelIt->second.count(room) > 0;
}


void BookingManager::addCustomer(const std::string& roomType,int room,std::unique_ptr<Customer> customer){
    customers[roomType][room] = std::move(customer);
}

bool BookingManager::removeCustomer(const std::string& roomType, int room) {
    auto hotelIt = customers.find(roomType);
    if (hotelIt == customers.end())
        return false;

    if (hotelIt->second.erase(room) == 0)
        return false;

    if (hotelIt->second.empty()) {
        customers.erase(hotelIt);
    }

    return true;
}
std::unordered_map<std::string,std::unordered_map<int, std::unique_ptr<Customer>>>& BookingManager::getAllCustomers() {
    return customers;
}
