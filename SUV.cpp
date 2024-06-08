#include "suv.h"

SUV::SUV(int id, const std::string& make, const std::string& model, int groundClearance, double cargoCapacity, bool fourWheelDrive, double towingCapacity)
    : Car(id, make, model), groundClearance(groundClearance), cargoCapacity(cargoCapacity), fourWheelDrive(fourWheelDrive), towingCapacity(towingCapacity) {}

void SUV::display() const {
    Car::display();
    std::cout << "Ground Clearance: " << groundClearance << " inches" << std::endl;
    std::cout << "Cargo Capacity: " << cargoCapacity << " cubic feet" << std::endl;
    std::cout << "Four Wheel Drive: " << (fourWheelDrive ? "Yes" : "No") << std::endl;
    std::cout << "Towing Capacity: " << towingCapacity << " pounds" << std::endl;
}

void SUV::readFromBinary(std::ifstream& in) {
    Car::readFromBinary(in);
    in.read(reinterpret_cast<char*>(&groundClearance), sizeof(groundClearance));
    in.read(reinterpret_cast<char*>(&cargoCapacity), sizeof(cargoCapacity));
    in.read(reinterpret_cast<char*>(&fourWheelDrive), sizeof(fourWheelDrive));
    in.read(reinterpret_cast<char*>(&towingCapacity), sizeof(towingCapacity));
}

void SUV::writeToBinary(std::ofstream& out) const {
    Car::writeToBinary(out);
    out.write(reinterpret_cast<const char*>(&groundClearance), sizeof(groundClearance));
    out.write(reinterpret_cast<const char*>(&cargoCapacity), sizeof(cargoCapacity));
    out.write(reinterpret_cast<const char*>(&fourWheelDrive), sizeof(fourWheelDrive));
    out.write(reinterpret_cast<const char*>(&towingCapacity), sizeof(towingCapacity));
}

int SUV::getGroundClearance() const {
    return groundClearance;
}

double SUV::getCargoCapacity() const {
    return cargoCapacity;
}

bool SUV::getFourWheelDrive() const {
    return fourWheelDrive;
}

double SUV::getTowingCapacity() const {
    return towingCapacity;
}

void SUV::setGroundClearance(int groundClearance) {
    this->groundClearance = groundClearance;
}

void SUV::setCargoCapacity(double cargoCapacity) {
    this->cargoCapacity = cargoCapacity;
}

void SUV::setFourWheelDrive(bool fourWheelDrive) {
    this->fourWheelDrive = fourWheelDrive;
}

void SUV::setTowingCapacity(double towingCapacity) {
    this->towingCapacity = towingCapacity;
}

void SUV::validate() const {
    if (groundClearance < 0 || cargoCapacity < 0 || towingCapacity < 0) {
        throw InvalidValueException("Invalid value in SUV");
    }
}

std::ostream& operator<<(std::ostream& os, const SUV& suv) {
    suv.display();
    return os;
}

std::istream& operator>>(std::istream& is, SUV& suv) {
    is >> static_cast<Car<int>&>(suv);
    std::cout << "Enter Ground Clearance (inches): ";
    is >> suv.groundClearance;
    std::cout << "Enter Cargo Capacity (cubic feet): ";
    is >> suv.cargoCapacity;
    std::cout << "Enter Four Wheel Drive (0 for No, 1 for Yes): ";
    is >> suv.fourWheelDrive;
    std::cout << "Enter Towing Capacity (pounds): ";
    is >> suv.towingCapacity;
    return is;
}
