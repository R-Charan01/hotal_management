#include "customer_factory.h"

std::unique_ptr<Customer> CustomerFactory::createCustomer(
    const std::string& name,
    int room,
    const std::string& phone,
    const std::string& roomType,
    int days,
    std::time_t time)
{
    return std::make_unique<Customer>(
        name, room, phone, roomType, days, time);
}