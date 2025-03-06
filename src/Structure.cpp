#include "Structure.hpp"


Structure::Structure(int building_number, int number_of_rooms, const std::vector<Room>& rooms) {
    building_number_ = building_number;
    number_of_rooms_ = number_of_rooms;
    rooms_ = rooms;
}

double Structure::get_square() const {
    int final_square = 0;
    for (const auto& room : rooms_) {
        final_square += room.get_square();
    }
    return final_square;
}

int Structure::get_number_of_rooms() {
    return number_of_rooms_;
}

nlohmann::json Structure::get_info() const {
    nlohmann::json j;
    j["building_number"] = building_number_;
    j["number_of_rooms"] = number_of_rooms_;
    j["rooms"] = nlohmann::json::array();
    for (const auto& room : rooms_) {
        j["rooms"].push_back(room.get_info());
    }
    return j;
}