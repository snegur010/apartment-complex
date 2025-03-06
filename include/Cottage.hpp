#ifndef COTTAGE_HPP
#define COTTAGE_HPP

#include <vector>
#include <string>
#include "json.hpp"
#include "House.hpp"
#include "Structure.hpp"

class Cottage : public House {

    private:

        std::vector<Structure> structures_;
        int number_of_structures_;
        
    public:

        Cottage(State state, Address address, int cost, std::vector<Structure> structures, int number_of_structures);
        std::string get_type() const override;
        nlohmann::json get_info() const override;
        State get_state() override;
        void set_state(State state) override;
        int get_value() override;
        Address get_address() const override;
        double get_square() const override;
        ~Cottage() = default;
};

#endif

