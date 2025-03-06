#include "Flat.hpp"


Flat::Flat(State state, double price_per_sq_meter, Address& address, std::array<Room, 4> rooms) {
    state_ = state;
    price_per_sq_meter_ = price_per_sq_meter;
    address_ = address;
    rooms_ = rooms;
}

std::string Flat::get_type() const {
    return "Flat";
}

State Flat::get_state() {
    return state_;
}

int Flat::get_value() {
    return price_per_sq_meter_;
}

Address Flat::get_address() const {
    return address_;
}

double Flat::get_square() const {
    int final_square = 0;
    for (auto& room : rooms_) {
        final_square += room.get_square();
    }
    return final_square;
}

nlohmann::json Flat::get_info() const {
    nlohmann::json j;
    j["type"] = "Flat";
    j["address"] = address_.to_json();
    j["state"] = state_ == State::occupied ? "occupied" : "unoccupied";
    j["square_meters"] = get_square();
    j["price_per_sq_meter"] = price_per_sq_meter_;
    return j;
}

void Flat::set_state(State state) {
    state_ = state;
}

