## g++ hotel.cpp utils.cpp customer.cpp customer_factory.cpp \ booking_manager.cpp booking_operations.cpp -o hotel

--------------------------------------

# Hotel Management System (C++)
## Project Overview 
The project focuses on **clean design**, **object-oriented principles**, **memory management using smart pointers**, and **design patterns** such as **Factory** and **Singleton**.

The system allows:
- Booking hotel rooms
- Viewing all booked rooms
- Checking out customers

---

## Concepts Used (Function-wise)

### readInt
**Concepts Used:**
- Input handling using 
- Input validation
- Reference passing
- Stream error handling 
**Purpose:**
- Safely reads integer input while handling invalid user input.

---

### isAlphaSpace
**Concepts Used:**
- String traversal
- Character validation
- Boolean logic

**Purpose:**
- Validates whether a string contains only alphabets and spaces.

---

### isDigits
**Concepts Used:**
- String traversal
- Input validation

**Purpose:**
- Ensures a string contains only numeric digits (used for phone validation).

---

## Pointer & Memory Management Concepts

- std::unique_ptr
- Dynamic memory allocation
- Ownership transfer using move
- Automatic resource cleanup (RAII)
- Pointer dereferencing (`->`)

---

## Class: Customer

### Concepts Used:
- **Encapsulation** (private data members)
- **Constructors**
- **Const correctness**
- **Exception handling**
- **Static member functions**

### Key Responsibilities:
- Stores customer details
- Validates input data
- Calculates checkout time using date arithmetic

---

### Getter Functions 
**Concepts Used:**
- Const member functions
- Encapsulation
- Read-only data access

---

## Factory Design Pattern
### Class: CustomerFactory
### createCustomer(...)
**Concepts Used:**
- Factory Design Pattern
- Smart pointers
- Dynamic object creation

**Purpose:**
- Centralizes object creation logic
- Ensures safe memory ownership transfer
- supports future extenstions
---

## Singleton Design Pattern
### Class: BookingManager
**Concepts Used:**
- Singleton Design Pattern
- Private constructor
- Deleted copy constructor and assignment operator
- Static instance creation

---

### Internal Data Structure
**Concepts Used:**
- std::unordered_map
- Nested containers
- Key‑value storage

---

### readStayDays()
**Concepts Used:**
- Loops
- Input validation
- Function reuse

---

### bookRoom()
**Concepts Used:**
- Function decomposition
- Smart pointers
- Exception handling
- Input validation
- Interaction with Singleton and Factory

**Purpose:**
- Collects user data
- Creates customer object
- Stores booking securely

---

### displayBookedRooms()
**Concepts Used:**
- Iteration over nested containers
- Pointer dereferencing
- Const references
- Formatted output

---

### checkOut()
**Concepts Used:**
- Conditional logic
- Container modification
- User input handling

---

