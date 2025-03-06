#include <gtest/gtest.h>
#include "include/Address.hpp"
#include "include/Flat.hpp"
#include "include/MyClass.hpp"
#include "include/Housing.hpp"
#include "include/Cottage.hpp"
#include "include/Structure.hpp"
#include "include/Apartment.hpp"


TEST(HouseTest, MnogoTest) {

    Address address1 = {"Mira", 10, 12};
    Room room1(Rooms::Kitchen, 12, "new kitchen");
    Room room2(Rooms::Bathroom, 9, "for me");
    Room room3(Rooms::Hallway, 20, "for guests");
    Room room4(Rooms::Bathroom, 8, "for guests");

    Address address2 = {"Truda", 5, 33};
    Room room5(Rooms::Kitchen, 12, "old");
    Room room6(Rooms::Bathroom, 9, "no comment");
    Room room7(Rooms::Hallway, 20, "big and large");
    Room room8(Rooms::Bathroom, 8, "for guests");

    std::vector<Room> rooms1 = {room1, room2, room3, room4};

    std::vector<Room> rooms2 = {room5, room6, room7, room8};

    Structure structure1(1, 4, rooms1); //выкидывать ошибку если не совпадает
    Structure structure2(2, 4, rooms2);

    std::cout << structure1.get_info().dump(4) << std::endl;

    std::vector<Structure> structures1 = {structure1, structure2};
    std::vector<Structure> structures2 = {structure1, structure2};

    Cottage* cottage1 = new Cottage(State::unoccupied, address1, 16, structures1, 2);
    Cottage* cottage2 = new Cottage(State::unoccupied, address2, 17, structures2, 2);

    Room room9(Rooms::Bathroom, 12, "new");
    Room room10(Rooms::Bathroom, 12, "new");
    Room room11(Rooms::Bathroom, 12, "new");
    Room room12(Rooms::Bathroom, 12, "new");

    std::array<Room, 4> rooms = {room9, room10, room11, room12};
    Flat* flat = new Flat(State::occupied, 12, address1, rooms);

    Housing app;
    app.register_new(cottage1);
    app.register_new(cottage2);
    app.register_new(flat);
    
    std::vector<House*> jjj = app.find_low_cost();
}

TEST(HouseTest, AddressTest) {

    Address address1 = {"Mira", 10, 12};
    Address address2 = {"Rigskaya", 10, 12};
    Address address3 = {"Mira", 10, 12};
    bool value = address1 == address2;
    bool value2 = address1 == address3;
    EXPECT_EQ(address1.house_number, 10);
    EXPECT_EQ(address1.number_of_flat, 12);
    EXPECT_EQ(value, 0);
    EXPECT_EQ(value2, 1);
}

TEST(HouseTest, FlatTest) {
    Address address1 = {"Mira", 10, 12};

    Room room1(Rooms::Bathroom, 12, "new");
    Room room2(Rooms::Bathroom, 12, "new");
    Room room3(Rooms::Bathroom, 12, "new");
    Room room4(Rooms::Bathroom, 12, "new");

    std::array<Room, 4> rooms = {room1, room2, room3, room4};
    Flat *flat = new Flat(State::occupied, 12, address1, rooms);

    bool value = address1 == flat->get_address();

    EXPECT_EQ(value, 1);

    EXPECT_EQ(flat->Flat::get_state(), State::occupied);
    EXPECT_EQ(flat->Flat::get_value(), 12);

    EXPECT_EQ(room1.get_comment(), "new");
    EXPECT_EQ(room2.get_square(), 12);
    EXPECT_EQ(room3.get_name(), Rooms::Bathroom);

    std::cout << address1.to_json().dump(4) << std::endl;

    delete flat;
}


TEST(HouseTest, HousingTest) {

    Address address1 = {"Mira", 10, 12};

    Room room1(Rooms::Bathroom, 12, "new");
    Room room2(Rooms::Bathroom, 12, "new");
    Room room3(Rooms::Bathroom, 12, "new");
    Room room4(Rooms::Bathroom, 12, "new");

    std::array<Room, 4> rooms = {room1, room2, room3, room4};
    Flat* flat = new Flat(State::unoccupied, 12, address1, rooms);

    Housing app;
    app.register_new(flat);

    EXPECT_THROW(app.register_new(flat), std::logic_error);

    Address address12 = flat->get_address();

    app.register_old(address12);
    EXPECT_EQ(flat->get_state(), State::unoccupied);

    std::vector<House*> houses = app.get_info();

    for (int i = 0; i < houses.size(); i++) {
        // std::cout << houses[i]->get_info().dump(4) <<std::endl;
    }
}


TEST(HouseTest, MyClassTest) {
    ViewableTable<Address, House*> table;

    Address address1 = {"Mira", 10, 12};
    Room room1(Rooms::Bathroom, 12, "new");
    Room room2(Rooms::Bathroom, 12, "new");
    Room room3(Rooms::Bathroom, 12, "new");
    Room room4(Rooms::Bathroom, 12, "new");
    std::array<Room, 4> rooms = {room1, room2, room3, room4};
    Flat* flat = new Flat(State::unoccupied, 12, address1, rooms);

    House *flatting = flat;

    table.add(address1, flatting);
    EXPECT_EQ(table.get_size(), 1);
    auto& find = table.get(address1);
    EXPECT_EQ(find->get_type(), "Flat");

    for (auto it = table.begin(); it != table.end(); ++it) {
        auto entry = *it;
        std::cout << "Key: " << entry.key.to_json().dump(4) << ", Value: " << entry.value->get_info().dump(4) << std::endl;
    }

    delete flat;
} 

TEST(HouseTest, CottageTest) {
    Room room1(Rooms::Kitchen, 12, "new kitchen");
    Room room2(Rooms::LivingRoom, 20, "for guests");
    std::vector<Room> rooms1 = {room1, room2};

    Structure structure1(1, 2, rooms1);

    EXPECT_EQ(structure1.get_number_of_rooms(), 2);
    EXPECT_EQ(structure1.get_square(), 32);

    Room room3(Rooms::Kitchen, 12, "new kitchen");
    Room room4(Rooms::LivingRoom, 20, "for guests");

    std::vector<Room> rooms2 = {room3, room4};

    Structure structure2(2, 2, rooms2);

    std::vector<Structure> structures = {structure1, structure2};

    Address address = {"Mira", 10, 0};

    Cottage *cottage = new Cottage(State::unoccupied, address, 15, structures, 2);

    Housing app;
    app.register_new(cottage);

    EXPECT_THROW(app.register_new(cottage), std::logic_error);

    std::cout << cottage->get_info().dump(4) << std::endl;
}


TEST(HouseTest, SomeHouses) {
    Address address1 = {"Mira", 10, 12};
    Room room1(Rooms::Kitchen, 12, "new kitchen");
    Room room2(Rooms::Bathroom, 9, "for me");
    Room room3(Rooms::Hallway, 20, "for guests");
    Room room4(Rooms::Bathroom, 8, "for guests");

    Address address2 = {"Truda", 5, 33};
    Room room5(Rooms::Kitchen, 12, "old");
    Room room6(Rooms::Bathroom, 9, "no comment");
    Room room7(Rooms::Hallway, 20, "big and large");
    Room room8(Rooms::Bathroom, 8, "for guests");

    std::vector<Room> rooms1 = {room1, room2, room3, room4};

    std::vector<Room> rooms2 = {room5, room6, room7, room8};

    Structure structure1(1, 4, rooms1); //выкидывать ошибку если не совпадает
    Structure structure2(2, 4, rooms2);

    std::cout << structure1.get_info().dump(4) << std::endl;

    std::vector<Structure> structures1 = {structure1, structure2};
    std::vector<Structure> structures2 = {structure1, structure2};

    Cottage* cottage1 = new Cottage(State::unoccupied, address1, 16, structures1, 2);
    Cottage* cottage2 = new Cottage(State::unoccupied, address2, 17, structures2, 2);

    Room room9(Rooms::Bathroom, 12, "new");
    Room room10(Rooms::Bathroom, 12, "new");
    Room room11(Rooms::Bathroom, 12, "new");
    Room room12(Rooms::Bathroom, 12, "new");

    std::array<Room, 4> rooms = {room9, room10, room11, room12};
    Flat* flat = new Flat(State::occupied, 12, address1, rooms);

    bool value = address1 == flat->get_address();
    EXPECT_EQ(value, 1);
    EXPECT_EQ(flat->Flat::get_state(), State::occupied);
    EXPECT_EQ(flat->Flat::get_value(), 12);

    Housing app;
    app.register_new(cottage1);
    app.register_new(cottage2);
    app.register_new(flat);

    std::cout << cottage2->get_info().dump(4) << std:: endl;

    Address address12 = cottage1->get_address();
    Address address13 = cottage2->get_address();
    Address address14 = flat->get_address();

    app.register_old(address12);
    app.register_old(address13);
    app.register_old(address14);
    
    std::vector<House*> housing = app.get_info();
    for (int i = 0; i < housing.size(); i++) {
        std::cout << housing[i]->get_type() << std::endl;
    }
}

TEST(HouseTest, MyClassTest2) {
    ViewableTable<int, std::string> table;
    std::string string1 = "hello";
    table.add(5, string1);
    auto& get = table.get(5);

    for (auto it = table.begin(); it != table.end(); ++it) {
        std::cout << it.operator*().key << std::endl;
        EXPECT_EQ(it.operator*().key, 5);
    } 

    ViewableTable<Address, Address> table2;
    Address address("Mira", 5, 10);
    Address address1("Mira", 20, 20);
    table2.add(address, address1);
    auto get2 = table2.get(address);

    EXPECT_EQ(get2.street, "Mira");
    EXPECT_EQ(get2.house_number, 20);
    EXPECT_EQ(get2.number_of_flat, 20);

    EXPECT_EQ(table2.get_size(), 1);
} 

TEST(ViewableTableTest, ExceptionHandling) {
    ViewableTable<int, std::string> table;

    EXPECT_THROW(table.get(10), std::out_of_range);

    std::string value = "test";
    table.add(1, value);
    EXPECT_THROW(table.add(1, value), std::logic_error);

    EXPECT_THROW(table[1], std::out_of_range);
}

TEST(ViewableTableTest, ResizeTest) {
    ViewableTable<int, std::string> table(2);
    std::string value1 = "value1";
    std::string value2 = "value2";
    std::string value3 = "value3";

    table.add(1, value1);
    table.add(2, value2);
    EXPECT_EQ(table.get_size(), 2);

    table.add(3, value3);
    EXPECT_EQ(table.get_size(), 3);

    std::string new_value = "value1";
    EXPECT_EQ(table.get(1), new_value);
}


TEST(ViewableTableTest, BasicScenario) {

    Housing app;

    Address address1 = {"Mira", 10, 12};
    Address address2 = {"Truda", 5, 33};
    Address address3 = {"Rigskaya", 6, 33};
    Address address4 = {"Truda", 7, 33};
    Address address5 = {"Truda", 8, 33};
    Address address6 = {"Truda", 10, 33};

    Room room1(Rooms::Kitchen, 12, "new kitchen");
    Room room2(Rooms::Bathroom, 9, "for me");
    Room room3(Rooms::Hallway, 20, "for guests");
    Room room4(Rooms::Bathroom, 8, "for guests");

    Room room5(Rooms::Kitchen, 12, "old");
    Room room6(Rooms::Bathroom, 9, "no comment");
    Room room7(Rooms::Hallway, 20, "big and large");
    Room room8(Rooms::Bathroom, 8, "for guests");

    std::vector<Room> rooms1 = {room1, room2, room3, room4};

    std::vector<Room> rooms2 = {room5, room6, room7, room8};

    std::array<Room, 4> rooms_flat = {room1, room2, room3, room4};

    Structure structure1(1, 4, rooms1); 
    Structure structure2(2, 4, rooms2);

    std::vector<Structure> structures1 = {structure1, structure2};
    std::vector<Structure> structures2 = {structure1, structure2};

    Cottage* cottage1 = new Cottage(State::unoccupied, address1, 20, structures1, 2);
    Cottage* cottage2 = new Cottage(State::unoccupied, address2, 15, structures1, 2); 
    Cottage* cottage3 = new Cottage(State::unoccupied, address3, 25, structures1, 2);

    Flat* flat1 = new Flat(State::occupied, 12, address1, rooms_flat);
    Flat* flat2 = new Flat(State::occupied, 10, address2, rooms_flat); 
    Flat* flat3 = new Flat(State::occupied, 11, address3, rooms_flat);

    Apartment* apartment1 = new Apartment(State::occupied, 5, address4, rooms1, 4);
    Apartment* apartment2 = new Apartment(State::occupied, 6, address5, rooms2, 4); 
    Apartment* apartment3 = new Apartment(State::occupied, 7, address6, rooms1, 4);

    app.register_new(cottage1);
    app.register_new(cottage2);
    app.register_new(cottage3);
    app.register_new(flat1);
    app.register_new(flat2);
    app.register_new(flat3);
    app.register_new(apartment1);
    app.register_new(apartment2);
    app.register_new(apartment3);

    auto result = app.find_low_cost();

    for (int i = 0; i < result.size(); i++) {
        std::cout << result[i]->get_type() << " " <<result[i]->get_square()*result[i]->get_value() << std::endl;
    }
}



TEST(HousingTest, NoApartments) {
    Housing app;

    Address address1 = {"Mira", 10, 12};
    Address address2 = {"Truda", 5, 33};
    Address address3 = {"Rigskaya", 6, 33};
    Address address4 = {"Truda", 7, 33};
    Address address5 = {"Truda", 8, 33};
    Address address6 = {"Truda", 10, 33};

    Room room1(Rooms::Kitchen, 12, "new kitchen");
    Room room2(Rooms::Bathroom, 9, "for me");
    Room room3(Rooms::Hallway, 20, "for guests");
    Room room4(Rooms::Bathroom, 8, "for guests");

    Room room5(Rooms::Kitchen, 12, "old");
    Room room6(Rooms::Bathroom, 9, "no comment");
    Room room7(Rooms::Hallway, 20, "big and large");
    Room room8(Rooms::Bathroom, 8, "for guests");

    std::vector<Room> rooms1 = {room1, room2, room3, room4};

    std::vector<Room> rooms2 = {room5, room6, room7, room8};

    std::array<Room, 4> rooms_flat = {room1, room2, room3, room4};

    Structure structure1(1, 4, rooms1); 
    Structure structure2(2, 4, rooms2);

    std::vector<Structure> structures1 = {structure1, structure2};
    std::vector<Structure> structures2 = {structure1, structure2};

    Cottage* cottage1 = new Cottage(State::unoccupied, address1, 20, structures1, 2);
    Cottage* cottage2 = new Cottage(State::unoccupied, address2, 15, structures1, 2); 
    Cottage* cottage3 = new Cottage(State::unoccupied, address3, 25, structures1, 2);

    Flat* flat1 = new Flat(State::occupied, 12, address1, rooms_flat);
    Flat* flat2 = new Flat(State::occupied, 10, address2, rooms_flat); 
    Flat* flat3 = new Flat(State::occupied, 11, address3, rooms_flat);

    Apartment* apartment1 = new Apartment(State::occupied, 5, address4, rooms1, 4);
    Apartment* apartment2 = new Apartment(State::occupied, 6, address5, rooms2, 4); 
    Apartment* apartment3 = new Apartment(State::occupied, 7, address6, rooms1, 4);

    app.register_new(cottage1);
    app.register_new(cottage2);
    app.register_new(cottage3);
    app.register_new(flat1);
    app.register_new(flat2);
    app.register_new(flat3);

    auto result = app.find_low_cost();

    for (int i = 0; i < result.size(); i++) {
        if (result[i] != nullptr) {
            std::cout << result[i]->get_type() << " " <<result[i]->get_square()*result[i]->get_value() << std::endl;
        }
        
    }

    EXPECT_EQ(result[0]->get_value(), 10);
}

TEST(ViewableTableTest, SameCost) {

    Housing app;

    Address address1 = {"Mira", 10, 12};
    Address address2 = {"Truda", 5, 33};
    Address address3 = {"Rigskaya", 6, 33};
    Address address4 = {"Truda", 7, 33};
    Address address5 = {"Truda", 8, 33};
    Address address6 = {"Truda", 10, 33};

    Room room1(Rooms::Kitchen, 12, "new kitchen");
    Room room2(Rooms::Bathroom, 9, "for me");
    Room room3(Rooms::Hallway, 20, "for guests");
    Room room4(Rooms::Bathroom, 8, "for guests");

    Room room5(Rooms::Kitchen, 12, "old");
    Room room6(Rooms::Bathroom, 9, "no comment");
    Room room7(Rooms::Hallway, 20, "big and large");
    Room room8(Rooms::Bathroom, 8, "for guests");

    std::vector<Room> rooms1 = {room1, room2, room3, room4};

    std::vector<Room> rooms2 = {room5, room6, room7, room8};

    std::array<Room, 4> rooms_flat = {room1, room2, room3, room4};

    Structure structure1(1, 4, rooms1); 
    Structure structure2(2, 4, rooms2);

    std::vector<Structure> structures1 = {structure1, structure2};
    std::vector<Structure> structures2 = {structure1, structure2};

    Cottage* cottage1 = new Cottage(State::unoccupied, address1, 20, structures1, 2);
    Cottage* cottage2 = new Cottage(State::unoccupied, address2, 15, structures1, 2); 
    Cottage* cottage3 = new Cottage(State::unoccupied, address3, 25, structures1, 2);

    Flat* flat1 = new Flat(State::occupied, 12, address1, rooms_flat);
    Flat* flat2 = new Flat(State::occupied, 12, address2, rooms_flat); 
    Flat* flat3 = new Flat(State::occupied, 12, address3, rooms_flat);

    Apartment* apartment1 = new Apartment(State::occupied, 5, address4, rooms1, 4);
    Apartment* apartment2 = new Apartment(State::occupied, 6, address5, rooms2, 4); 
    Apartment* apartment3 = new Apartment(State::occupied, 7, address6, rooms1, 4);

    app.register_new(cottage1);
    app.register_new(cottage2);
    app.register_new(cottage3);
    app.register_new(flat1);
    app.register_new(flat2);
    app.register_new(flat3);
    app.register_new(apartment1);
    app.register_new(apartment2);
    app.register_new(apartment3);

    auto result = app.find_low_cost();

    for (int i = 0; i < result.size(); i++) {
        std::cout << result[i]->get_info().dump(4) << std::endl << result[i]->get_square()*result[i]->get_value() << std::endl;
    }
}