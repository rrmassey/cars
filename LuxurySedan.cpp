#include "LuxurySedan.h"

LuxurySedan::LuxurySedan(int id, const std::string& make, const std::string& model, int year, double price, const std::string& features)
    : Car(id, make, model), year(year), price(price), features(features) {}

void LuxurySedan::display() const {
    Car::display();
    std::cout << "Year: " << year << std::endl;
    std::cout << "Price: $" << price << std::endl;
    std::cout << "Features: " << features << std::endl;
}

void LuxurySedan::readFromBinary(std::ifstream& in) {
    Car::readFromBinary(in);
    in.read(reinterpret_cast<char*>(&year), sizeof(year));
    in.read(reinterpret_cast<char*>(&price), sizeof(price));
    std::getline(in, features, '\0');
}

void LuxurySedan::writeToBinary(std::ofstream& out) const {
    Car::writeToBinary(out);
    out.write(reinterpret_cast<const char*>(&year), sizeof(year));
    out.write(reinterpret_cast<const char*>(&price), sizeof(price));
    out.write(features.c_str(), features.size() + 1);
}

int LuxurySedan::getYear() const {
    return year;
}

double LuxurySedan::getPrice() const {
    return price;
}

std::string LuxurySedan::getFeatures() const {
    return features;
}

void LuxurySedan::setYear(int year) {
    this->year = year;
}

void LuxurySedan::setPrice(double price) {
    this->price = price;
}

void LuxurySedan::setFeatures(const std::string& features) {
    this->features = features;
}

void LuxurySedan::validate() const {
    if (year < 1886 || price < 0) {
        throw InvalidValueException("Invalid value in LuxurySedan");
    }
}

std::ostream& operator<<(std::ostream& os, const LuxurySedan& car) {
    car.display();
    return os;
}

std::istream& operator>>(std::istream& is, LuxurySedan& car) {
    is >> static_cast<Car<int>&>(car);
    std::cout << "Enter Year: ";
    is >> car.year;
    std::cout << "Enter Price: ";
    is >> car.price;
    std::cout << "Enter Features: ";
    is.ignore(); // to ignore any newline character left in the input buffer
    std::getline(is, car.features);
    return is;
}
