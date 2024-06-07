#include "SUV.h"

SUV::SUV(int id, const std::string& make, const std::string& model, int year, double price, int seatingCapacity, double fuelEfficiency)
    : Car(id, make, model), year(year), price(price), seatingCapacity(seatingCapacity), fuelEfficiency(fuelEfficiency) {}

void SUV::display() const {
    Car::display();
    std::cout << "Year: " << year << std::endl;
    std::cout << "Price: $" << price << std::endl;
    std::cout << "Seating Capacity: " << seatingCapacity << std::endl;
    std::cout << "Fuel Efficiency: " << fuelEfficiency << " mpg" << std::endl;
}

void SUV::readFromBinary(std::ifstream& in) {
    Car::readFromBinary(in);
    in.read(reinterpret_cast<char*>(&year), sizeof(year));
    in.read(reinterpret_cast<char*>(&price), sizeof(price));
    in.read(reinterpret_cast<char*>(&seatingCapacity), sizeof(seatingCapacity));
    in.read(reinterpret_cast<char*>(&fuelEfficiency), sizeof(fuelEfficiency));
}

void SUV::writeToBinary(std::ofstream& out) const {
    Car::writeToBinary(out);
    out.write(reinterpret_cast<const char*>(&year), sizeof(year));
    out.write(reinterpret_cast<const char*>(&price), sizeof(price));
    out.write(reinterpret_cast<const char*>(&seatingCapacity), sizeof(seatingCapacity));
    out.write(reinterpret_cast<const char*>(&fuelEfficiency), sizeof(fuelEfficiency));
}

int SUV::getYear() const {
    return year;
}

double SUV::getPrice() const {
    return price;
}

int SUV::getSeatingCapacity() const {
    return seatingCapacity;
}

double SUV::getFuelEfficiency() const {
    return fuelEfficiency;
}

void SUV::setYear(int year) {
    this->year = year;
}

void SUV::setPrice(double price) {
    this->price = price;
}

void SUV::setSeatingCapacity(int seatingCapacity) {
    this->seatingCapacity = seatingCapacity;
}

void SUV::setFuelEfficiency(double fuelEfficiency) {
    this->fuelEfficiency = fuelEfficiency;
}

void SUV::validate() const {
    if (year < 1886 || price < 0 || seatingCapacity < 0 || fuelEfficiency < 0) {
        throw InvalidValueException("Invalid value in SUV");
    }
}

std::ostream& operator<<(std::ostream& os, const SUV& suv) {
    suv.display();
    return os;
}

std::istream& operator>>(std::istream& is, SUV& suv) {
    is >> static_cast<Car<int>&>(suv);
    std::cout << "Enter Year: ";
    is >> suv.year;
    std::cout << "Enter Price: ";
    is >> suv.price;
    std::cout << "Enter Seating Capacity: ";
    is >> suv.seatingCapacity;
    std::cout << "Enter Fuel Efficiency (mpg): ";
    is >> suv.fuelEfficiency;
    return is;
}
