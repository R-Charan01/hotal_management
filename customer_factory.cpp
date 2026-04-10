#include "customer_factory.h"

std::unique_ptr<Customer> CustomerFactory::createCustomer(
    const std::string& name,
    const std::string& hotel,
    const std::string& roomType,
    const std::string& phone,
    int days)
{
    return std::make_unique<Customer>(
        name, hotel, roomType, phone, days);
}
