#ifndef SEDAN_H
#define SEDAN_H

#include "Car.h"

class Sedan : public Car<int> {
private:
    int year;
    double price;
    int trunkSize;
    double fuelEfficiency;

public:
    Sedan(int id = 0, const std::string& make = "", const std::string& model = "", 
          int year = 0, double price = 0.0, int trunkSize = 0, double fuelEfficiency = 0.0)
        : Car(id, make, model), year(year), price(price), trunkSize(trunkSize), fuelEfficiency(fuelEfficiency) {}

    int getYear() const { return year; }
    double getPrice() const { return price; }
    int getTrunkSize() const { return trunkSize; }
    double getFuelEfficiency() const { return fuelEfficiency; }

    void setYear(int year) { this->year = year; }
    void setPrice(double price) { this->price = price; }
    void setTrunkSize(int trunkSize) { this->trunkSize = trunkSize; }
    void setFuelEfficiency(double fuelEfficiency) { this->fuelEfficiency = fuelEfficiency; }

    void display() const override {
        Car::display();
        std::cout << "Year: " << year << "\nPrice: $" << price 
                  << "\nTrunk Size: " << trunkSize << " cu ft" 
                  << "\nFuel Efficiency: " << fuelEfficiency << " mpg" << std::endl;
    }

    void readFromBinary(std::ifstream& in) override {
        Car::readFromBinary(in);
        in.read(reinterpret_cast<char*>(&year), sizeof(year));
        in.read(reinterpret_cast<char*>(&price), sizeof(price));
        in.read(reinterpret_cast<char*>(&trunkSize), sizeof(trunkSize));
        in.read(reinterpret_cast<char*>(&fuelEfficiency), sizeof(fuelEfficiency));
    }

    void writeToBinary(std::ofstream& out) const override {
        Car::writeToBinary(out);
        out.write(reinterpret_cast<const char*>(&year), sizeof(year));
        out.write(reinterpret_cast<const char*>(&price), sizeof(price));
        out.write(reinterpret_cast<const char*>(&trunkSize), sizeof(trunkSize));
        out.write(reinterpret_cast<const char*>(&fuelEfficiency), sizeof(fuelEfficiency));
    }

    void validate() const override {
        if (year < 1886 || price < 0 || trunkSize < 0 || fuelEfficiency < 0) {
            throw InvalidValueException("Invalid value in Sedan");
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Sedan& sedan) {
        sedan.display();
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Sedan& sedan) {
        sedan.read(is);
        std::cout << "Enter Year: ";
        is >> sedan.year;
        std::cout << "Enter Price: ";
        is >> sedan.price;
        std::cout << "Enter Trunk Size: ";
        is >> sedan.trunkSize;
        std::cout << "Enter Fuel Efficiency (mpg): ";
        is >> sedan.fuelEfficiency;
        return is;
    }
};

#endif // SEDAN_H
