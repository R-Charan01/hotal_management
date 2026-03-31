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
#include <sstream>

/* ---------- Utility Functions ---------- */

static int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Invalid input. Please enter an integer.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
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

std::string formatTime(std::time_t t) {
    std::tm* tmPtr = std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(tmPtr, "%d-%m-%Y");
    return oss.str();
}

/* ---------- Customer Base Class ---------- */
// Used by Factory Method

class Customer {
protected:
    std::string name;
    std::string phone;
    int room;
    std::time_t checkin_time;
    int stay_days;

public:
    virtual ~Customer() = default;

    std::string getName() const { return name; }
    std::string getPhone() const { return phone; }
    int getRoom() const { return room; }
    std::time_t getCheckInTime() const { return checkin_time; }
    int getStayDays() const { return stay_days; }

    std::time_t getCheckOutTime() const {
        return checkin_time + (stay_days * 24 * 60 * 60);
    }

    virtual std::string getRoomType() const = 0;
};

/* ---------- Concrete Customers ---------- */

class DeluxCustomer : public Customer {
public:
    DeluxCustomer(const std::string& n, int r, const std::string& p,
                  int days, std::time_t time) {
        name = n;
        room = r;
        phone = p;
        stay_days = days;
        checkin_time = time;
    }

    std::string getRoomType() const override {
        return "Delux";
    }
};

class NonDeluxCustomer : public Customer {
public:
    NonDeluxCustomer(const std::string& n, int r, const std::string& p,
                     int days, std::time_t time) {
        name = n;
        room = r;
        phone = p;
        stay_days = days;
        checkin_time = time;
    }

    std::string getRoomType() const override {
        return "Non-Delux";
    }
};

/* ---------- Factory Method ---------- */

class CustomerFactory {
public:
    static std::unique_ptr<Customer> createCustomer(
        const std::string& type,
        const std::string& name,
        int room,
        const std::string& phone,
        int days,
        std::time_t time
    ) {
        if (type == "Delux") {
            return std::make_unique<DeluxCustomer>(
                name, room, phone, days, time);
        }
        else if (type == "Non-Delux") {
            return std::make_unique<NonDeluxCustomer>(
                name, room, phone, days, time);
        }
        throw std::invalid_argument("Invalid room type");
    }
};

/* ---------- Singleton Booking Manager ---------- */

class BookingManager {
private:
    std::unordered_map<
        std::string,
        std::unordered_map<int, std::unique_ptr<Customer>>
    > customers;

    BookingManager() {}

public:
    BookingManager(const BookingManager&) = delete;
    BookingManager& operator=(const BookingManager&) = delete;

    static BookingManager& getInstance() {
        static BookingManager instance;
        return instance;
    }

    bool isRoomBooked(const std::string& type, int room) {
        return customers[type].count(room) > 0;
    }

    void addBooking(const std::string& type, int room,
                    std::unique_ptr<Customer> customer) {
        customers[type][room] = std::move(customer);
    }

    void removeBooking(const std::string& type, int room) {
        customers[type].erase(room);
    }

    const auto& getBookings() const {
        return customers;
    }

    bool empty() const {
        return customers.empty();
    }
};

/* ---------- Core Functions ---------- */

int readStayDays() {
    while (true) {
        int days = readInt("Enter number of days to stay (1–10): ");
        if (days >= 1 && days <= 10)
            return days;
        std::cout << "Days must be between 1 and 10.\n";
    }
}

void bookRoom() {
    BookingManager& manager = BookingManager::getInstance();

    std::string name, phone, roomType;
    int room;

    std::cout << "\n--- Book Room ---\n";

    do {
        std::cout << "Enter customer name: ";
        std::getline(std::cin, name);
    } while (!isAlphaSpace(name));

    room = readInt("Enter room number (1–100): ");
    if (room < 1 || room > 100) {
        std::cout << "Invalid room number.\n";
        return;
    }

    std::cout << "Enter phone number: ";
    std::cin >> phone;
    std::cin.ignore();

    std::cout << "Enter room type (Delux / Non-Delux): ";
    std::getline(std::cin, roomType);

    if (roomType == "delux" || roomType == "Delux")
        roomType = "Delux";
    else if (roomType == "non-delux" || roomType == "Non-Delux")
        roomType = "Non-Delux";
    else {
        std::cout << "Invalid room type.\n";
        return;
    }

    if (manager.isRoomBooked(roomType, room)) {
        std::cout << "Room already booked.\n";
        return;
    }

    int stayDays = readStayDays();
    std::time_t now = std::time(nullptr);

    auto customer = CustomerFactory::createCustomer(
        roomType, name, room, phone, stayDays, now);

    manager.addBooking(roomType, room, std::move(customer));

    std::cout << "Room booked successfully.\n";
}

void displayBookedRooms() {
    BookingManager& manager = BookingManager::getInstance();

    if (manager.empty()) {
        std::cout << "No rooms are currently booked.\n";
        return;
    }

    for (const auto& hotel : manager.getBookings()) {
        std::cout << "\nRoom Type: " << hotel.first << "\n";
        for (const auto& kv : hotel.second) {
            const auto& c = kv.second;
            std::cout << "Name: " << c->getName()
                      << " | Room: " << c->getRoom()
                      << " | Phone: " << c->getPhone()
                      << " | Check-in: " << formatTime(c->getCheckInTime())
                      << " | Check-out: " << formatTime(c->getCheckOutTime())
                      << "\n";
        }
    }
}

void checkOut() {
    BookingManager& manager = BookingManager::getInstance();

    std::string type;
    int room;

    std::cout << "Enter room type: ";
    std::cin >> type;
    std::cout << "Enter room number: ";
    std::cin >> room;

    manager.removeBooking(type, room);
    std::cout << "Checkout successful.\n";
}

/* ---------- Main ---------- */

int main() {
    while (true) {
        std::cout << "\n=== Hotel Management System ===\n";
        std::cout << "1. Book Room\n";
        std::cout << "2. Display Booked Rooms\n";
        std::cout << "3. Check Out\n";
        std::cout << "4. Exit\n";

        int choice = readInt("Enter choice: ");

        switch (choice) {
        case 1: bookRoom(); break;
        case 2: displayBookedRooms(); break;
        case 3: checkOut(); break;
        case 4: std::cout << "Thank you!\n"; return 0;
        default: std::cout << "Invalid choice.\n";
        }
    }
}