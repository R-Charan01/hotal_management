#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include <limits>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cctype>

// ================= HELPER FUNCTIONS =================

// Normalize hotel input (ram/r → Ram, charan/c → Charan)
std::string normalizeHotel(std::string h) {
    for (char& c : h) c = std::tolower(c);
    if (h == "ram" || h == "r") return "Ram";
    if (h == "charan" || h == "c") return "Charan";
    return "";
}

// Normalize room type input
std::string normalizeRoomType(std::string t) {
    for (char& c : t) c = std::tolower(c);
    if (!t.empty() && t[0] == 'd') return "Delux";
    if (!t.empty() && t[0] == 'n') return "Non-Delux";
    return "";
}

// Convert hotel name to short code
char hotelCode(const std::string& hotel) {
    return std::tolower(hotel[0]); // Ram -> r, Charan -> c
}

// Convert room type to short code
char roomCode(const std::string& roomType) {
    return std::tolower(roomType[0]); // Delux -> d, Non -> n
}

// Safe integer input
int readInt(const std::string& msg) {
    int x;
    while (true) {
        std::cout << msg;
        if (std::cin >> x && x > 0) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return x;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Try again.\n";
    }
}

// Format date
std::string formatTime(std::time_t t) {
    std::tm* tmPtr = std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(tmPtr, "%d-%m-%Y");
    return oss.str();
}

// ================= CUSTOMER CLASS =================
class Customer {
    std::string name;
    std::string hotel;
    std::string roomType;
    std::string phone;
    int stayDays;
    std::time_t checkIn;

public:
    Customer(std::string n, std::string h, std::string r,
             std::string p, int d)
        : name(n), hotel(h), roomType(r),
          phone(p), stayDays(d),
          checkIn(std::time(nullptr)) {}

    std::string getName() const { return name; }
    std::string getHotel() const { return hotel; }
    std::string getRoomType() const { return roomType; }
    std::string getPhone() const { return phone; }
    std::time_t getCheckIn() const { return checkIn; }
    std::time_t getCheckOut() const {
        return checkIn + stayDays * 24 * 60 * 60;
    }
};

// ================= FACTORY DESIGN PATTERN =================
class CustomerFactory {
public:
    static std::unique_ptr<Customer> createCustomer(
        const std::string& name,
        const std::string& hotel,
        const std::string& roomType,
        const std::string& phone,
        int days)
    {
        return std::make_unique<Customer>(
            name, hotel, roomType, phone, days);
    }
};

// ================= SINGLETON BOOKING MANAGER =================
class BookingManager {
    std::unordered_map<std::string, int> inventory;
    std::unordered_map<std::string, std::unique_ptr<Customer>> bookings;

    BookingManager() {
        inventory["Ram_Delux"] = 10;
        inventory["Ram_Non-Delux"] = 10;
        inventory["Charan_Non-Delux"] = 5;
    }

public:
    static BookingManager& getInstance() {
        static BookingManager instance;
        return instance;
    }

    // Show availability (including 0 rooms)
    void showAvailability(const std::string& roomType) {
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

    // Book multiple rooms → multiple keys
    std::vector<std::string> bookRooms(
        const std::string& hotel,
        const std::string& roomType,
        const std::string& name,
        const std::string& phone,
        int days,
        int count)
    {
        std::vector<std::string> keys;
        std::string invKey = hotel + "_" + roomType;
        if (inventory[invKey] < count) return keys;

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

    void displayBookings() {
        if (bookings.empty()) {
            std::cout << "No bookings.\n";
            return;
        }

        for (auto& b : bookings) {
            auto& c = b.second;
            std::cout << "\nKey: " << b.first
                      << "\nName: " << c->getName()
                      << "\nHotel: " << c->getHotel()
                      << "\nRoom Type: " << c->getRoomType()
                      << "\nPhone: " << c->getPhone()
                      << "\nCheck-in: " << formatTime(c->getCheckIn())
                      << "\nCheckout: " << formatTime(c->getCheckOut())
                      << "\n";
        }
    }

    void showRoomStatus() {
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
                      << " | Booked: " << bookedCount[i.first] << "\n";
        }
    }

    void checkout() {
        std::string key;
        std::cout << "Enter booking key: ";
        std::cin >> key;

        if (!bookings.count(key)) {
            std::cout << "Invalid key.\n";
            return;
        }

        auto& c = bookings[key];
        inventory[c->getHotel() + "_" + c->getRoomType()]++;
        bookings.erase(key);
        std::cout << "Checkout successful.\n";
    }
};

// ================= BOOK ROOM FLOW =================
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

    int roomCount = readInt("Enter number of rooms required: ");

    std::cout << "Enter phone number: ";
    std::cin >> phone;
    std::cin.ignore();

    int stayDays = readInt("Enter stay days: ");

    auto keys = BookingManager::getInstance().bookRooms(
        hotel, roomType, name, phone, stayDays, roomCount);

    if (keys.empty()) {
        std::cout << "Not enough rooms available.\n";
    } else {
        std::cout << "\nRooms booked successfully!\nBooking Keys:\n";
        for (auto& k : keys)
            std::cout << k << "\n";
    }
}

// ================= MAIN =================
int main() {
    while (true) {
        std::cout << "\n=== Hotel Management ===\n";
        std::cout << "1. Book Room\n";
        std::cout << "2. Display Booked Rooms\n";
        std::cout << "3. Check Out\n";
        std::cout << "4. Show Room Status\n";
        std::cout << "5. Exit\n";

        int choice = readInt("Enter choice: ");

        if (choice == 1) bookRoom();
        else if (choice == 2) BookingManager::getInstance().displayBookings();
        else if (choice == 3) BookingManager::getInstance().checkout();
        else if (choice == 4) BookingManager::getInstance().showRoomStatus();
        else break;
    }
    return 0;
}