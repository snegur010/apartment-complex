#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <iostream>
#include "json.hpp"
#include "Address.hpp"

enum class Rooms {
    Kitchen,
    LivingRoom,
    Bathroom,
    Hallway
};

class Room {

    private:
        Rooms name_;
        double square_;
        std::string comment_;

    public:

        Room() = default;
        Room(Rooms name, double square, const std::string& comment);
        double get_square() const;
        nlohmann::json get_info() const;
        std::string get_comment() const;
        Rooms get_name() const;
        ~Room() = default;
};

#endif
