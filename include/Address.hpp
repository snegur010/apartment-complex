#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include <iostream>
#include <string>
#include "json.hpp"

struct Address { //class
    
    std::string street;
    int house_number;
    int number_of_flat;

    nlohmann::json to_json() const {
        return nlohmann::json{{"street", street}, {"house_number", house_number}, {"number_of_flat", number_of_flat}};
    }

    Address(std::string street_, int house_number_, int number_of_flat_) : street(street_), house_number(house_number_), number_of_flat(number_of_flat_) {}
    Address() = default;

    bool operator==(const Address& other) {
        return (street == other.street && house_number == other.house_number && number_of_flat == other.number_of_flat);
    }

    Address(const Address& other) 
        : street(other.street), house_number(other.house_number), number_of_flat(other.number_of_flat) {}

    Address& operator=(const Address& other) = default;

    Address(Address&& other) = default;

    Address& operator=(Address && other) = default;

    ~Address() = default;
};

#endif
 