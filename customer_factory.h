#ifndef CUSTOMER_FACTORY_H
#define CUSTOMER_FACTORY_H

#include <memory>
#include <string>
#include "customer.h"

class CustomerFactory {
public:
    static std::unique_ptr<Customer> createCustomer(
        const std::string& name,
        const std::string& hotel,
        const std::string& roomType,
        const std::string& phone,
        int days);
};

#endif
