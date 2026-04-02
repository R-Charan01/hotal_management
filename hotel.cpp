#include <iostream>
#include "booking_operations.h"
#include "booking_manager.h"
#include "utils.h"

int main() {
    while (true) {
        std::cout << "\n=== Hotel Management ===\n";
        std::cout << "Choose one of the options: \n";
        std::cout << "1. Book Room\n";
        std::cout << "2. Display Booked Rooms\n";
        std::cout << "3. Check Out\n";
        std::cout << "4. Exit\n";
        
        int choice;
        int choiceInput = readInt("Enter choice: ",choice);
        switch (choiceInput) {
            
            case 1: bookRoom(); break;
            case 2: if(BookingManager::getInstance().empty()){
                        std::cout << "No rooms are currently booked."; }
                    else{
                        displayBookedRooms();
                    } break;
            case 3: if(BookingManager::getInstance().empty()){
                        std::cout << "No rooms are available for checkout."; }
                    else{
                        checkOut();
                    } break;
            case 4:
                     std::cout << "Exiting... Thank you!\n";
                    return 0;
            default:
                    std::cout << "Invalid option.\n";
        }
    }
}