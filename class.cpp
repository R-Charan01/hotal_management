#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cctype>
#include <limits>
#include <algorithm>
#include <memory>
#include <ctime>
#include <iomanip>

static int readInt(const std::string& prompt,int value) {
    std::cout << prompt;
    if (std::cin >> value) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;   
    }

    std::cout << "Invalid input. Please enter an integer.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

bool isAlphaSpace(const std::string& s) {
    if (s.empty()) return false;
    for (unsigned char ch : s) {
        if (!(std::isalpha(ch) || std::isspace(ch)))
            return false;
    }
    return true;
}

bool isDigits(const std::string& s) {
    if (s.empty()) return false;
    for (unsigned char ch : s) {
        if (!std::isdigit(ch))
            return false;
    }
    return true;
}

class Customer {
private:
    std::string name;
    std::string room_type;
    int room;
    std::string phone;
    std::time_t checkin_time;
    int stay_days;

    static void validateName(const std::string& n) {
        if (!isAlphaSpace(n)) {
            throw std::invalid_argument("Name must contain only letters and spaces.");
        }
    }
    static void validateRoom(int r) {
        if (r <= 0) {
            throw std::invalid_argument("Room number must be a positive integer.");
        }
    }
    static void validatePhone(const std::string& p) {
        if (!isDigits(p) || p.size() < 10 || p.size() > 15) {
            throw std::invalid_argument("Phone must be digits only, length 10–15.");
        }
    }

public:
    Customer() = default;
    Customer(const std::string n, int r, const std::string p,const std::string t,int days, std::time_t inTime)
    {
        validateName(n);
        validateRoom(r);
        validatePhone(p);
        name = n;
        room = r;
        phone = p;
        room_type = t;
        stay_days = days;
        checkin_time = inTime;

    }
    std::string getname() const { return name; }
    int getroom() const { return room; }
    std::string getphone() const {return phone; }
    std::string getroom_type() const {return room_type; }
    std::time_t getCheckInTime() const { return checkin_time; }
    int getStayDays() const { return stay_days; }
    std::time_t getCheckOutTime() const { return checkin_time + (stay_days * 24 * 60 * 60);
}

};
/*class BookingManager {
private:
    BookingManager() {}  // Private constructor

    std::unordered_map<int, std::unique_ptr<Customer>> customers;
}
*/

std::unordered_map<std::string,std::unordered_map<int,Customer>> customers;

bool isRoomBooked(const std::string roomType, int room) {
    auto hotel = customers.find(roomType);
    if(hotel == customers.end())
        return false;
    const auto rooms = hotel->second;
    return rooms.find(room) != rooms.end();
}
int readStayDays() {
    int day;
    int days = readInt("Enter number of days to stay: ",day);
    if (days > 0 && days < 11)
        return days;
    std::cout << "Days must be in b\\w 1-10.\n";
    }
std::string formatTime(std::time_t t) {
    std::tm* tmPtr = std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(tmPtr, "%d-%m-%Y");
    return oss.str();
}
void bookRoom() {
    std::cout << "\n--- Book Room ---\n";
    std::string phone;
    std::string nameInput;
    std::string room_typeInput;
    // NAME
    while (true) {
        std::cout << "Enter customer name: ";
        std::getline(std::cin, nameInput);
        if (isAlphaSpace(nameInput))
        break;
    std::cout << "Invalid name: Name must contain only letters and spaces. Try again.\n";
}

    // ROOM NUMBER
    int value;
    int roomInput = readInt("Enter room number: ",value);
    while (roomInput <= 0 || isRoomBooked(room_typeInput, roomInput) || roomInput >=100 ) {
        if (roomInput <= 0 && roomInput >= 100)
            roomInput = readInt("Room must be positive and lessthan 100. Enter again: ",value);
        else
            roomInput = readInt("Room already booked. Enter another: ",value);
    }

    // PHONE
        while (true) {
        try {
            std::cout << "Enter phone number: ";
            std::cin >> phone; 
            if (!isDigits(phone) || phone.size() < 10 || phone.size() > 15) {
                throw std::invalid_argument("Phone must be digits only, length 10–15.");
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;
        } catch (const std::exception& ex) {
            std::cout << "Invalid phone: " << ex.what() << " Try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    // rooom_type
    while (true) {
    std::cout << "Enter room type (Delux / Non-Delux): ";
    std::getline(std::cin, room_typeInput);
    if (room_typeInput.empty()) {
        std::cout << "Invalid room type. Please enter Delux or Non-Delux.\n";
        continue;
    }

    if (room_typeInput[0] == 'D' || room_typeInput[0] == 'd' ) {
            room_typeInput= "delux";
            break;
        }

    if (room_typeInput[0] == 'n' || room_typeInput[0] == 'N') {
            room_typeInput="Non-Delux";
            break;
        }

    std::cout << "Invalid room type. Please enter Delux or Non-Delux.\n";
}
    //staydays
    int stayDays = readStayDays();
    std::time_t checkinTime = std::time(nullptr);


    customers[room_typeInput].emplace(roomInput,Customer(nameInput, roomInput, phone,room_typeInput,stayDays,checkinTime));

    std::cout << "Room successfully booked.\n";
    
}

void displayBookedRooms() {
    std::cout << "\n--- Booked Rooms ---\n";

    if (customers.empty()) {
        std::cout << "No rooms are currently booked.\n";
        return;
    }

    for (const auto& hotel : customers) {
        const std::string& hotelType = hotel.first;
        const auto& roomMap = hotel.second;

        std::cout << "\nHotel Type: " << hotelType << "\n";

        for (const auto& kv : roomMap) {
            int room = kv.first;
            const auto& c = kv.second;

            std::cout << "Name: " << c.getname()
                      << " | Room: " << room
                      << " | Phone: " << c.getphone()
                      << " | Check-in: " << formatTime(c.getCheckInTime())
                      << " | Checkout: " << formatTime(c.getCheckOutTime())
                      << "\n";
        }
    }
}

void checkOut() {
    std::cout << "\n--- Check Out ---\n";

    std::string roomType;
    int room;

    std::cout << "Enter room type (Delux / Non-Delux): ";
    std::cin >> roomType;

    if (!roomType.empty()) {
        if (roomType[0] == 'D' || roomType[0] == 'd')
            roomType = "delux";
        else if (roomType[0] == 'N' || roomType[0] == 'n')
            roomType = "Non-Delux";
    }
    if (customers.find(roomType) == customers.end()) {
        std::cout << "Room is vacant.\n";
        return;
    }

    std::cout << "Enter room number: ";
    std::cin >> room;

    auto& roomMap = customers[roomType];
    auto erased = roomMap.erase(room);

    if (erased)
        std::cout << "Room successfully checked out.\n";
    else
        std::cout << "Room is vacant.\n";
}

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
        switch (choice) {
            case 1: bookRoom(); break;
            case 2: if(customers.empty()){std::cout << "No rooms are currently booked."; }
                    else {displayBookedRooms();} break;
            case 3: if(customers.empty()){std::cout << "No rooms are available for checkout."; }
                    else {checkOut();} break;
            case 4:
                std::cout << "Exiting... Thank you!\n";
                return 0;
            default:
                std::cout << "Invalid option.\n";
        }
    }
}
