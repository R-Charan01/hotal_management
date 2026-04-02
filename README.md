oops--customer,bookingmanager,customerfactory classes-- i separated to multiple classes. Each class has a clear purpose and hides its internal data using private. Objects interact only through public methods

encapsulation---private members+getters

abstraction-----customerfactory,bookingmanger--user never how a customer function is working

design pattern(singletone)--used in bookingmanger--only one instance exist (getinstance())--global access point

design pattern(factory)--all validation and object creation happen here--it improves maintainability and support future extensions

smart pointer(unique pointer)--customer objects are owned by bookingmanger and destroyed automatically -- it reduces memory leaks

move--transfers owership of customer into map without copying

exception handling -- validate name,room,phone -- invalid objects are never created and program remains stable during errors

input validation -- readInt,isAlpha,isDigit -- prevents qundefined behavior and inputs

stl containers(unordered_map) -- booking storage --fastloopup of rooms and roomtype

const -- allows safe use of objects in read only type

formatted ouput -- converts time into human readable formate

g++ hotel.cpp utils.cpp customer.cpp customer_factory.cpp \
   booking_manager.cpp booking_operations.cpp -o hotel