#include "PerformanceCar.h"

PerformanceCar::PerformanceCar(int id, const std::string& make, const std::string& model, int year, double price, int horsepower, double topSpeed)
    : Car(id, make, model), year(year), price(price), horsepower(horsepower), topSpeed(topSpeed) {}

void PerformanceCar::display() const {
    Car::display();
    std::cout << "Year: " << year << std::endl;
    std::cout << "Price: $" << price << std::endl;
    std::cout << "Horsepower: " << horsepower << " hp" << std::endl;
    std::cout << "Top Speed: " << topSpeed << " mph" << std::endl;
}

void PerformanceCar::readFromBinary(std::ifstream& in) {
    Car::readFromBinary(in);
    in.read(reinterpret_cast<char*>(&year), sizeof(year));
    in.read(reinterpret_cast<char*>(&price), sizeof(price));
    in.read(reinterpret_cast<char*>(&horsepower), sizeof(horsepower));
    in.read(reinterpret_cast<char*>(&topSpeed), sizeof(topSpeed));
}

void PerformanceCar::writeToBinary(std::ofstream& out) const {
    Car::writeToBinary(out);
    out.write(reinterpret_cast<const char*>(&year), sizeof(year));
    out.write(reinterpret_cast<const char*>(&price), sizeof(price));
    out.write(reinterpret_cast<const char*>(&horsepower), sizeof(horsepower));
    out.write(reinterpret_cast<const char*>(&topSpeed), sizeof(topSpeed));
}

int PerformanceCar::getYear() const {
    return year;
}

double PerformanceCar::getPrice() const {
    return price;
}

int PerformanceCar::getHorsepower() const {
    return horsepower;
}

double PerformanceCar::getTopSpeed() const {
    return topSpeed;
}

void PerformanceCar::setYear(int year) {
    this->year = year;
}

void PerformanceCar::setPrice(double price) {
    this->price = price;
}

void PerformanceCar::setHorsepower(int horsepower) {
    this->horsepower = horsepower;
}

void PerformanceCar::setTopSpeed(double topSpeed) {
    this->topSpeed = topSpeed;
}

void PerformanceCar::validate() const {
    if (year < 1886 || price < 0 || horsepower < 0 || topSpeed < 0) {
        throw InvalidValueException("Invalid value in PerformanceCar");
    }
}

std::ostream& operator<<(std::ostream& os, const PerformanceCar& car) {
    car.display();
    return os;
}

std::istream& operator>>(std::istream& is, PerformanceCar& car) {
    is >> static_cast<Car<int>&>(car);
    std::cout << "Enter Year: ";
    is >> car.year;
    std::cout << "Enter Price: ";
    is >> car.price;
    std::cout << "Enter Horsepower: ";
    is >> car.horsepower;
    std::cout << "Enter Top Speed (mph): ";
    is >> car.topSpeed;
    return is;
}
