#include "booking_operations.h"
#include "booking_manager.h"
#include "utils.h"
#include <iostream>

void bookRoom() {
    std::string name, roomType, hotel, phone;

    std::cout << "Enter customer name: ";
    std::getline(std::cin, name);

    std::cout << "Select room type (Delux / Non-Delux): ";
    std::getline(std::cin, roomType);
    roomType = normalizeRoomType(roomType);

    BookingManager::getInstance().showAvailability(roomType);

    std::cout << "Select hotel: ";
    std::getline(std::cin, hotel);
    hotel = normalizeHotel(hotel);

    // ✅ FIX 1: INVALID HOTEL CHECK
    if (hotel.empty()) {
        std::cout << "Invalid hotel selection.\n";
        return;
    }

    int roomCount = readInt("Enter number of rooms required: ");

    std::cout << "Enter phone: ";
    std::cin >> phone;
    std::cin.ignore();

    int days = readInt("Enter stay days: ");

    auto keys = BookingManager::getInstance().bookRooms(
        hotel, roomType, name, phone, days, roomCount);

    if (keys.empty()) {
        std::cout << "Not enough rooms available.\n";
    } else {
        std::cout << "\nBooking Keys:\n";
        for (auto& k : keys)
            std::cout << k << "\n";
    }
}