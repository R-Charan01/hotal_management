#include <iostream>
#include "booking_operations.h"
#include "booking_manager.h"
#include "utils.h"

int main() {
    while (true) {
        std::cout << "\n=== HOTEL MANAGEMENT ===\n";
        std::cout << "1. Book Room\n";
        std::cout << "2. Display Booked Rooms\n";
        std::cout << "3. Check Out\n";
        std::cout << "4. Show Room Status\n";
        std::cout << "5. Exit\n";

        int choice = readInt("Enter choice: ");

        if (choice == 1)
            bookRoom();
        else if (choice == 2)
            BookingManager::getInstance().displayBookings();
        else if (choice == 3)
            BookingManager::getInstance().checkout();
        else if (choice == 4)
            BookingManager::getInstance().showRoomStatus();
        else
            break;
    }
    return 0;
}