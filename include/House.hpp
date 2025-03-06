#ifndef HOUSE_HPP
#define HOUSE_HPP

#include <vector>
#include <string>
#include "json.hpp"
#include "House.hpp"
#include "Structure.hpp"

enum class State {
    occupied,
    unoccupied
};

class House {

    protected:
        Address address_;
        State state_;
        double price_per_sq_meter_;

    public:
        virtual nlohmann::json get_info() const = 0;
        virtual std::string get_type() const = 0;
        virtual State get_state()  = 0;
        virtual int get_value()  = 0;
        virtual Address get_address() const = 0;
        virtual double get_square() const = 0;
        virtual void set_state(State state) = 0;
        virtual ~House() = default;
};

#endif

