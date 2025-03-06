#include "Apartment.hpp"

Apartment::Apartment(State state, double price_per_sq_meter, Address& address, std::vector<Room> &rooms, int number_of_rooms) {
    state_ = state;
    price_per_sq_meter_ = price_per_sq_meter;
    address_ = std::move(address);
    number_of_rooms_ = number_of_rooms;
    rooms_ = std::move(rooms);
}

std::string Apartment::get_type() const {
    return "Apartment";
}

void Apartment::set_state(State state) {
    state_ = state;
}

State Apartment::get_state() {
    return state_;
}

int Apartment::get_value() {
    return price_per_sq_meter_;
}

Address Apartment::get_address() const {
    return address_;
}

double Apartment::get_square() const {
    int final_square = 0;

    for (auto& room : rooms_) {
        final_square += room.get_square();
    }

    return final_square;
}

nlohmann::json Apartment::get_info() const {
    nlohmann::json j;
    j["type"] = "Apartment";
    j["address"] = address_.to_json();
    j["state"] = state_ == State::occupied ? "occupied" : "unoccupied";
    j["rooms"] = nlohmann::json::array();
    for (const auto& room : rooms_) {
        j["rooms"].push_back(room.get_info());
    }
    j["square_meters"] = get_square();
    j["price_per_sq_meter"] = price_per_sq_meter_;
    return j;
}
