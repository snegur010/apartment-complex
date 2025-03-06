#include "Housing.hpp"
#include "MyClass.hpp"
#include "House.hpp"

#include <vector>
#include <stdexcept>
#include <iostream>
#include <thread>
#include <future>


void Housing::register_new(House* house) {
    try {
        auto& existing_house = table_.get(house->get_address());
        if (existing_house != nullptr) {
            throw std::logic_error("House is already occupied");
        }
    } catch (...) {
        table_.add(house->get_address(), house);
        house->set_state(State::occupied);
    }
}


void Housing::register_old(Address& address) {
    try {
        auto& existing_house = table_.get(address);
        if (existing_house->get_state() == State::occupied) {
            existing_house->set_state(State::unoccupied);
        } else {
            throw std::logic_error("House is not currently occupied");
        }
    } catch (const std::out_of_range&) {
        throw std::logic_error("House not found in the registry");
    }
}


std::vector<House*> Housing::get_info() {
    std::vector<House*> unoccupied_houses;
    for (auto& entry : table_) {
        if (entry.value->get_state() == State::unoccupied) {
            unoccupied_houses.push_back(entry.value);
        } 
    }
    return unoccupied_houses;
}

//вспомогательная функция для нахождения самого дешевого жилья в категории
House* Housing::find_min_for_category(const std::string& category) {

    House* min_house = nullptr;
    int min_price = std::numeric_limits<int>::max();

    for (auto& house : table_) {
        if (house.value->get_type() == category && house.value->get_value() < min_price) { //находим нужную категорию и сравниваем цену
            min_house = house.value;
            min_price = house.value->get_value();
        }
    }

    return min_house;
}


// основная многопоточная функция 
std::vector<House*> Housing::find_low_cost() {

    std::vector<std::thread> threads; //создаем вектор потоков
    std::mutex result_mutex;
    std::vector<House*> low_cost(3, nullptr);
    std::vector<std::string> categories = {"Flat", "Cottage", "Apartment"};

    auto start_time = std::chrono::high_resolution_clock::now(); // общее время начала

    for (size_t i = 0; i < categories.size(); ++i) { //для каждой категории вызываем функцию нахождения (выше)
        threads.emplace_back([&, i]() {
            auto thread_start = std::chrono::high_resolution_clock::now(); // старт времени для потока
            House* min_house = find_min_for_category(categories[i]);

            auto thread_end = std::chrono::high_resolution_clock::now();

            std::lock_guard<std::mutex> lock(result_mutex);
            low_cost[i] = min_house; //закрываем доступ на запись другим потокам и записываем

            std::cout << "Thread " << i << " finished in "
                      << std::chrono::duration_cast<std::chrono::nanoseconds>(thread_end - thread_start).count()
                      << " ns\n";

        });
    }

    for (auto& th : threads) { //синхронизируем
        if (th.joinable()) {
            th.join();
        }
    }

    return low_cost;
}
