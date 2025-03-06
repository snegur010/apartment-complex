#include "Room.hpp"

Room::Room(Rooms name, double square, const std::string& comment) {
    name_ = name;
    square_ = square;
    comment_ = comment;
}

double Room::get_square() const {
    return square_;
}

nlohmann::json Room::get_info() const {
    nlohmann::json j;
    j["name"] = get_name();
    j["square"] = get_square();
    j["comment"] = get_comment();
    return j;
}

std::string Room::get_comment() const {
    return comment_;
}

Rooms Room::get_name() const {
    return name_;
}
