#ifndef CUSTOMER_FACTORY_H
#define CUSTOMER_FACTORY_H

#include <memory>
#include "customer.h"

class CustomerFactory {
public:
    static std::unique_ptr<Customer> createCustomer(
        const std::string& name,
        int room,
        const std::string& phone,
        const std::string& roomType,
        int days,
        std::time_t time);
};

#endif