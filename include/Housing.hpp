#ifndef HOUSING_HPP
#define HOUSING_HPP

#include <vector>
#include <string>
#include <iostream>
#include "json.hpp"
#include "House.hpp"
#include "MyClass.hpp"
#include "Room.hpp"


class Housing {
    private:
        ViewableTable<Address, House*> table_; 
    public:
        Housing() = default;
        void register_new(House* house);
        void register_old(Address& address);
        std::vector<House*> get_info();
        std::vector<House*> find_low_cost(); 
        House* find_min_for_category(const std::string& category);
        
        ~Housing() {
            for (auto& entry : table_) {
                delete entry.value;
            }
        }
};

#endif



