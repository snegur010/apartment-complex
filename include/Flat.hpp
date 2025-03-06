#ifndef FLAT_HPP
#define FLAT_HPP

#include <vector>
#include <string>
#include "json.hpp"
#include "House.hpp"
#include "Structure.hpp"
#include "Room.hpp"


class Flat : public House {
    private:
        std::array<Room, 4> rooms_;
    public:
        Flat(State state, double price_per_sq_meter, Address& address, std::array<Room, 4> rooms);
        std::string get_type() const override;
        State get_state() override;
        int get_value() override;
        Address get_address() const override;
        double get_square() const override;
        nlohmann::json get_info() const override;
        void set_state(State state) override;
        ~Flat() = default;
};

#endif