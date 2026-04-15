#include "booking_manager.h"
#include "customer_factory.h"
#include "utils.h"

#include <iostream>

//Constructor
BookingManager::BookingManager() {
    inventory["Ram_Delux"] = 10;
    inventory["Ram_Non-Delux"] = 10;
    inventory["Charan_Non-Delux"] = 10;
}

//Singleton
BookingManager& BookingManager::getInstance() {
    static BookingManager instance;
    return instance;
}

//Show Availability
void BookingManager::showAvailability(const std::string& roomType) {
    std::cout << "\nAvailable " << roomType << " rooms:\n";

    for (auto& i : inventory) {
        auto pos = i.first.find('_');
        std::string hotel = i.first.substr(0, pos);
        std::string type  = i.first.substr(pos + 1);

        if (type == roomType) {
            std::cout << hotel << " Hotel → "
                      << i.second << " rooms\n";
        }
    }
}

//Book Multiple Rooms
std::vector<std::string> BookingManager::bookRooms(
    const std::string& hotel,
    const std::string& roomType,
    const std::string& name,
    const std::string& phone,
    int days,
    int count)
{
    std::vector<std::string> keys;
    std::string invKey = hotel + "_" + roomType;

    if (inventory[invKey] < count)
        return keys;

    static int keyCounter = 1;

    for (int i = 0; i < count; ++i) {
        inventory[invKey]--;

        std::string key;
        key += hotelCode(hotel);
        key += "_";
        key += roomCode(roomType);
        key += "_";
        key += std::to_string(keyCounter++);

        bookings[key] =
            CustomerFactory::createCustomer(
                name, hotel, roomType, phone, days);

        keys.push_back(key);
    }

    return keys;
}

//Display Bookings
void BookingManager::displayBookings() {
    if (bookings.empty()) {
        std::cout << "No bookings.\n";
        return;
    }

    for (auto& b : bookings) {
        auto& c = b.second;
        std::cout << "Key: " << b.first
          << " | Name: " << c->getName()
          << " | Hotel: " << c->getHotel()
          << " | Room: " << c->getRoomType()
          << " | Phone: " << c->getPhone()
          << " | Check-in: " << formatTime(c->getCheckIn())
          << " | Checkout: " << formatTime(c->getCheckOut())
          << '\n';

    }
}

//Show Room Status 
void BookingManager::showRoomStatus() {
    std::unordered_map<std::string, int> bookedCount;

    for (auto& b : bookings) {
        auto& c = b.second;
        bookedCount[c->getHotel() + "_" + c->getRoomType()]++;
    }

    std::cout << "\n--- ROOM STATUS ---\n";
    for (auto& i : inventory) {
        auto pos = i.first.find('_');
        std::string hotel = i.first.substr(0, pos);
        std::string type  = i.first.substr(pos + 1);

        std::cout << hotel << " Hotel | " << type
                  << " → Available: " << i.second
                  << " | Booked: " << bookedCount[i.first]
                  << "\n";
    }
}

//Checkout
void BookingManager::checkout() {
    std::string key;
    std::cout << "Enter booking key: ";
    std::cin >> key;

    if (!bookings.count(key)) {
        std::cout << "Invalid booking key.\n";
        return;
    }

    auto& c = bookings[key];
    inventory[c->getHotel() + "_" + c->getRoomType()]++;
    bookings.erase(key);

    std::cout << "Checkout successful.\n";
}
bool BookingManager::hasBookings() const {
    return !bookings.empty();
}