#ifndef APARTMENT_HPP
#define APARTMENT_HPP

#include <vector>
#include <string>
#include "json.hpp"
#include "House.hpp"
#include "Room.hpp"

class Apartment : public House {
    private:
        std::vector<Room> rooms_;
        int number_of_rooms_;  
    public:

        Apartment(State state, double price_per_sq_meter, Address& address, std::vector<Room> &rooms, int number_of_rooms);
        std::string get_type() const override;
        State get_state() override;
        int get_value() override;
        Address get_address() const override;
        double get_square() const override;
        nlohmann::json get_info() const override;
        void set_state(State state) override;
        ~Apartment() = default;
};

#endif