#include "Sedan.h"
#include "InvalidValueException.h"

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

void Sedan::display() const {
    Car::display();
    std::cout << "Year: " << year 
              << "\nPrice: $" << price 
              << "\nTrunk Size: " << trunkSize << " cu ft" 
              << "\nFuel Efficiency: " << fuelEfficiency << " mpg" << std::endl;
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

void Sedan::validate() const {
    if (year < 0 || price < 0 || trunkSize < 0 || fuelEfficiency < 0) {
        throw InvalidValueException("Invalid value in Sedan");
    }
}
