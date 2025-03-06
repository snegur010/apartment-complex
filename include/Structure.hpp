#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP

#include <vector>
#include "json.hpp"
#include "Room.hpp"

class Structure {
    private:

        int building_number_;
        int number_of_rooms_;
        std::vector<Room> rooms_;

    public:

        Structure(int building_number, int number_of_rooms, const std::vector<Room>& rooms);
        double get_square() const;
        int get_number_of_rooms();
        nlohmann::json get_info() const;
};

#endif


