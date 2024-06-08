#include "sedan.h"

Sedan::Sedan(int id, const std::string& make, const std::string& model, int year, double price, int trunkSize, double fuelEfficiency)
    : Car(id, make, model), year(year), price(price), trunkSize(trunkSize), fuelEfficiency(fuelEfficiency) {}

void Sedan::display() const {
    Car::display();
    std::cout << "Year: " << year << std::endl;
    std::cout << "Price : $" << price << std::endl;
    std::cout << "Trunk Size: " << trunkSize << " cubic feet" << std::endl;
    std::cout << "Fuel Efficiency: " << fuelEfficiency << " mpg" << std::endl;
}

void Sedan::readFromBinary(std::ifstream& in) {
    Car::readFromBinary(in);
    in.read(reinterpret_cast<char*>(&year), sizeof(year));
    in.read(reinterpret_cast<char*>(&price), sizeof(price));
    in.read(reinterpret_cast<char*>(&trunkSize), sizeof(trunkSize));
    in.read(reinterpret_cast<char*>(&fuelEfficiency), sizeof(fuelEfficiency));
}

void Sedan::writeToBinary(std::ofstream& out) const {
    Car::writeToBinary(out);
    out.write(reinterpret_cast<const char*>(&year), sizeof(year));
    out.write(reinterpret_cast<const char*>(&price), sizeof(price));
    out.write(reinterpret_cast<const char*>(&trunkSize), sizeof(trunkSize));
    out.write(reinterpret_cast<const char*>(&fuelEfficiency), sizeof(fuelEfficiency));
}

int Sedan::getYear() const {
    return year;
}

double Sedan::getPrice() const {
    return price;
}

int Sedan::getTrunkSize() const {
    return trunkSize;
}

double Sedan::getFuelEfficiency() const {
    return fuelEfficiency;
}

void Sedan::setYear(int year) {
    this->year = year;
}

void Sedan::setPrice(double price) {
    this->price = price;
}

void Sedan::setTrunkSize(int trunkSize) {
    this->trunkSize = trunkSize;
}

void Sedan::setFuelEfficiency(double fuelEfficiency) {
    this->fuelEfficiency = fuelEfficiency;
}

void Sedan::validate() const {
    if (year < 1886 || price < 0 || trunkSize < 0 || fuelEfficiency < 0) {
        throw InvalidValueException("Invalid value in Sedan");
    }
}

std::ostream& operator<<(std::ostream& os, const Sedan& sedan) {
    sedan.display();
    return os;
}

std::istream& operator>>(std::istream& is, Sedan& sedan) {
    is >> static_cast<Car<int>&>(sedan);
    std::cout << "Enter Year: ";
    is >> sedan.year;
    std::cout << "Enter Price: ";
    is >> sedan.price;
    std::cout << "Enter Trunk Size (cubic feet): ";
    is >> sedan.trunkSize;
    std::cout << "Enter Fuel Efficiency (mpg): ";
    is >> sedan.fuelEfficiency;
return is;
}
