#include "booking_operations.h"
#include "booking_manager.h"
#include "customer_factory.h"
#include "utils.h"

#include <iostream>
#include <limits>
#include <ctime>
#include <cctype>

// -------------------- Book Room --------------------
void bookRoom() {
    std::cout << "\n--- Book Room ---\n";

    std::string name;
    std::string roomType;
    std::string phone;

    // Name input
    while (true) {
        std::cout << "Enter customer name: ";
        std::getline(std::cin, name);
        if (isAlphaSpace(name))
            break;
        std::cout << "Invalid name. Use letters and spaces only.\n";
    }

    // Room type input
    while (true) {
        std::cout << "Enter room type (Delux / Non-Delux): ";
        std::getline(std::cin, roomType);

        if (roomType.empty()) {
            std::cout << "Room type cannot be empty.\n";
            continue;
        }

        char c = std::tolower(roomType[0]);
        if (c == 'd') {
            roomType = "delux";
            break;
        } else if (c == 'n') {
            roomType = "Non-Delux";
            break;
        }

        std::cout << "Invalid room type. Try again.\n";
    }

    // Room number
    int value;
    int roomInput = readInt("Enter room number: ", value);

    while (roomInput < 1 || roomInput > 100 || BookingManager::getInstance().isRoomBooked(roomType, roomInput)) {
    if (roomInput < 1 || roomInput > 100)
        roomInput = readInt("Room must be between 1 and 100. Enter again: ", value);
    else
        roomInput = readInt("Room already booked. Enter another: ", value);
}
    // Phone number
    while (true) {
        std::cout << "Enter phone number: ";
        std::cin >> phone;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (isDigits(phone) && phone.size() >= 10 && phone.size() <= 15)
            break;

        std::cout << "Invalid phone number. Digits only (10–15).\n";
    }

    // Stay days
    int stayDays = readStayDays();
    std::time_t checkinTime = std::time(nullptr);

    // Create and store customer
    auto customer = CustomerFactory::createCustomer(
        name, roomInput, phone, roomType, stayDays, checkinTime);

    BookingManager::getInstance().addCustomer(
        roomType, roomInput, std::move(customer));

    std::cout << " Room successfully booked.\n";
}

// -------------------- Display Booked Rooms --------------------
void displayBookedRooms() {
    std::cout << "\n--- Booked Rooms ---\n";

    auto& customers = BookingManager::getInstance().getAllCustomers();
    if (customers.empty()) {
        std::cout << "No rooms are currently booked.\n";
        return;
    }

    for (const auto& hotel : customers) {
        std::cout << "\nRoom Type: " << hotel.first << "\n";

        for (const auto& roomPair : hotel.second) {
            const auto& customer = roomPair.second;

            std::cout << "Name: " << customer->getname()
                      << " | Room: " << customer->getroom()
                      << " | Phone: " << customer->getphone()
                      << " | Check-in: " << formatTime(customer->getCheckInTime())
                      << " | Check-out: " << formatTime(customer->getCheckOutTime())
                      << "\n";
        }
    }
}

// -------------------- Check Out --------------------
void checkOut() {
    std::cout << "\n--- Check Out ---\n";

    std::string roomType;
    int room;

    std::cout << "Enter room type (Delux / Non-Delux): ";
    std::cin >> roomType;

    char c = std::tolower(roomType[0]);
    if (c == 'd')
        roomType = "delux";
    else if (c == 'n')
        roomType = "Non-Delux";
    else {
        std::cout << "Invalid room type.\n";
        return;
    }

    room = readInt("Enter room number: ",room);

    bool removed = BookingManager::getInstance().removeCustomer(roomType, room);
    if (removed)
        std::cout << "Room successfully checked out.\n";
    else
        std::cout << "Room is already vacant or invalid.\n";
}