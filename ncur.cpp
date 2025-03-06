#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <ncurses.h>
#include "include/Address.hpp"
#include "include/Housing.hpp"
#include "include/Flat.hpp"
#include "include/Apartment.hpp"
#include "include/Cottage.hpp"
#include "include/Room.hpp"

Address address_input() {
    std::cout << "=== Введите адрес жилья ===" << std::endl;
    std::cout << "Улица: ";
    std::string street;
    std::cin >> street;

    std::cout << "Номер дома: ";
    int house_number;

    try {
        std::cin >> house_number; //cin != EOF
        while (house_number <= 0) {
            std::cout << "Введите корректное число" << std::endl;
            std::cout << "Номер дома: ";
            std::cin >> house_number;
        }
        
    } catch (...) {
        throw std::logic_error("EOF END OF FILE");
    }

    std::cout << "Номер квартиры (или 0, если нет, для коттеджа): ";
    int flat_number;
    std::cin >> flat_number;

    Address address(street, house_number, flat_number);

    return address;
}

std::array<Room, 4> room_input() {
    std::cout << "=== Введите комнаты ===" << std::endl;

    std::array<Room, 4> rooms;
    for (int i = 0; i < 4; ++i) {
        std::cout << "=== Комната " << (i + 1) << std::endl;

        std::cout << "Тип комнаты (0 - Кухня, 1 - Гостиная, 2 - Ванная, 3 - Коридор): ";
        int room_type_int;
        std::cin >> room_type_int;

        while (room_type_int > 3 || room_type_int < 0) {
            std::cout << "Введите корректное число" << std::endl;
            std::cout << "Тип комнаты (0 - Кухня, 1 - Гостиная, 2 - Ванная, 3 - Коридор): ";
            std::cin >> room_type_int;
        }

        Rooms room_type = static_cast<Rooms>(room_type_int);

        std::cout << "Площадь: ";
        double square;
        std::cin >> square;

        while (square <= 0) {
            std::cout << "Введите корректное число" << std::endl;
            std::cout << "Площадь: ";
            std::cin >> square;
        }

        std::cout << "Комментарий: ";
        std::string comment;
        std::cin.ignore();
        std::getline(std::cin, comment);

        Room room(room_type, square, comment);
        rooms[i] = std::move(room);
    }

    return rooms;
}

std::vector<Room> rooms_input() {

    std::cout << "=== Введите комнаты ===" << std::endl;
    std::cout << "Введите количество комнат: ";
    size_t num_rooms;
    std::cin >> num_rooms;

    while (num_rooms <= 0){
        std::cout << "Введите правильное число" << std::endl;
        std::cout << "Введите количество комнат: ";
        std::cin >> num_rooms;
    }

    std::vector<Room> rooms;

    for (int i = 0; i < num_rooms; ++i) {
        std::cout << "=== Комната " << (i + 1) << std::endl;

        std::cout << "Тип комнаты (0 - Кухня, 1 - Гостиная, 2 - Ванная, 3 - Коридор): ";
        size_t room_type_int;
        std::cin >> room_type_int;

        while (room_type_int < 0 || room_type_int > 3) {
            std::cout << "Введите корректное число" << std::endl;
            std::cout << "Тип комнаты (0 - Кухня, 1 - Гостиная, 2 - Ванная, 3 - Коридор): ";
            std::cin >> room_type_int;
        }

        Rooms room_type = static_cast<Rooms>(room_type_int);

        std::cout << "Площадь: ";
        double square;
        std::cin >> square;

        while (square <= 0) {
            std::cout << "Введите корректное число" << std::endl;
            std::cout << "Площадь: ";
            std::cin >> square;
        }

        std::cout << "Комментарий: ";
        std::string comment;
        std::cin.ignore();
        std::getline(std::cin, comment);

        Room room(room_type, square, comment);
        rooms.push_back(room);
    }

    return rooms;

}

std::vector<Structure> structures_input() {

    std::cout << "Вам предстоит внести информацию обо всех строениях" << std::endl;
    std::cout << "Введите количество строений: ";
    int str_rooms;
    std::cin >> str_rooms;

    while (str_rooms <= 0) {
        std::cout << "Введите коррекное число" << std::endl;
        std::cout << "Введите количество строений: ";
        std::cin >> str_rooms;
    }

    std::vector<Structure> structures;

    for (int i = 0; i < str_rooms; i++) {
        std::cout << "Введите номер строения: ";
        int building_number;
        std::cin >> building_number;

        while (building_number < 0) {
            std::cout << "Введите корректное число" << std::endl;
            std::cout << "Введите номер строения: ";
            std::cin >> building_number;
        }

        std::vector rooms = rooms_input();
        int number_of_rooms = rooms.size();
        Structure structure(building_number, number_of_rooms, rooms);
        structures.push_back(structure);
    }

    return structures;

}

void add_house(Housing& housing) {

    std::cout << "\n=== Добавление нового жилья ===" << std::endl;
    std::cout << "Выберите тип жилья:" << std::endl;
    std::cout << "1. Квартира" << std::endl;
    std::cout << "2. Апартаменты" << std::endl;
    std::cout << "3. Коттедж" << std::endl;
    std::cout << "Ваш выбор: ";

    int choice;
    std::cin >> choice;

    while (choice < 1 || choice > 3) {
        std::cout << "Введите корректное число" << std::endl;
        std::cout << "Выберите тип жилья:" << std::endl;
        std::cout << "1. Квартира" << std::endl;
        std::cout << "2. Апартаменты" << std::endl;
        std::cout << "3. Коттедж" << std::endl;
        std::cout << "Ваш выбор: ";

        std::cin >> choice;
    }

    std::cout << "Введите состояние жилья (0 - Незаселенное, 1 - Заселенное): ";
    int state_int;
    std::cin >> state_int;

    while (state_int < 0 || state_int > 1) {
        std::cout << "Введите корректное число" << std::endl;
        std::cout << "Введите состояние жилья (0 - Незаселенное, 1 - Заселенное): ";
        std::cin >> state_int;
    }

    State state = static_cast<State>(state_int); //то же самое

    std::cout << "Введите цену за квадратный метр жилья: ";
    int cost_square;
    std::cin >> cost_square;

    while (cost_square <= 0) {
        std::cout << "Введите корректное число" << std::endl;
        std::cout << "Введите цену за квадратный метр жилья: ";
        std::cin >> cost_square;
    }


    if (choice == 1) {

        try {
            Address address = address_input();
            std::array<Room, 4> rooms = room_input();
            Flat* flat = new Flat(state, cost_square, address, rooms);
            try {
                housing.register_new(flat);
                std::cout << "Квартира успешно добавлена!" << std::endl;

            } catch (const std::exception& e) {
                delete flat;
                std::cout << "\nОшибка: " << e.what() << std::endl;
                return;
            }
        } catch(...) {
            throw std::logic_error("EOF");
        }
        

    } else if (choice == 2) {

        Address address = address_input();
        std::vector<Room> rooms = rooms_input();
        int size = rooms.size();
        Apartment *apartment = new Apartment(state, cost_square, address, rooms, size);
        try {
            housing.register_new(apartment);
            std::cout << "Апартаменты успешно добавлены!" << std::endl;
        } catch (const std::exception& e) {
            delete apartment;
            std::cout << "\nОшибка: " << e.what() << std::endl;
            return;
        }
        
    } else if (choice == 3) {

        Address address = address_input();
        std::vector<Structure> structures = structures_input();
        int number_of_structures = structures.size();
        Cottage* cottage = new Cottage(state, address, cost_square, structures, number_of_structures);
        try {
            housing.register_new(cottage);
            std::cout << "Коттедж успешно добавлен!" << std::endl;
        } catch (const std::exception& e) {
            delete cottage;
            std::cout << "\nОшибка: " << e.what() << std::endl;
            return;
        }
        
    } else {
        std::cout << "Неверный выбор! Попробуйте снова." << std::endl;
    }
}

void display_houses(Housing& housing) {
    std::cout << "Информация обо всем незаселенном жилье: " << std::endl;

    std::vector<House*> houses = housing.get_info();

    for (int i = 0; i < houses.size(); i++) {
        std::cout << houses[i]->get_info().dump(4) <<std::endl;
    }
}

void register_old(Housing &housing) {
    Address address = address_input();
    try {
        housing.register_old(address);
    } catch(...) {
        return;
    }
}

int main() {

    Housing housing;

    int choice;

    do {
        std::cout << "\n________________ГЛАВНОЕ МЕНЮ________________" << std::endl;
        std::cout << "1. Зарегистрировать заселение в жилье" << std::endl;
        std::cout << "2. Зарегистрировать освобождение жилья" << std::endl;
        std::cout << "3. Показать информацию обо всем предложении жилья (незаселенное жилье)" << std::endl;
        printf("0. Выйти\n");
        printf("Ваш выбор: ");

        std::cin >> choice;

        switch (choice) {

            case 1:
                try {
                    add_house(housing);
                } catch (...) {
                    return 1;
                }
                break;
            case 2:

                register_old(housing);
                
                break;
            case 3:
                display_houses(housing);
                break;

            case 0:
                std::cout << "Выход из программы..." << std::endl;
                break;

            default:

                std::cout << "Неверный выбор! Попробуйте снова." << std::endl;
                break;
        }

    } while (choice != 0);

    return 0;
}