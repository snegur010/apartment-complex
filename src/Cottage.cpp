#include "Cottage.hpp"


Cottage::Cottage(State state, Address address, int cost, std::vector<Structure> structures, int number_of_structures) {
    state_ = state;
    address_ = address;
    address_.number_of_flat = 0;
    price_per_sq_meter_ = cost;
    number_of_structures_ = number_of_structures;
    structures_ = std::move(structures);
}

std::string Cottage::get_type() const {
    return "Cottage";
}

nlohmann::json Cottage::get_info() const {
    nlohmann::json j;
    j["type"] = get_type();
    j["address"] = address_.to_json();
    j["state"] = (state_ == State::occupied) ? "occupied" : "unoccupied";
    j["structures"] = nlohmann::json::array();
    for (const auto& structure : structures_) {
        j["structures"].push_back(structure.get_info());
    }
    j["total_square"] = get_square();
    return j;
}

State Cottage::get_state() {
    return state_;
}

void Cottage::set_state(State state) {
    state_ = state;
}

int Cottage::get_value() {
    return price_per_sq_meter_;
}

Address Cottage::get_address() const {
    return address_;
}

double Cottage::get_square() const {

    int final_square = 0;
    for (auto& structures : structures_) {
        final_square += structures.get_square();
    }
    return final_square;
}