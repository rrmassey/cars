#include "SUV.h"
#include "InvalidValueException.h"

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

void SUV::display() const {
    Car::display();
    std::cout << "Ground Clearance: " << groundClearance << " inches" 
              << "\nCargo Capacity: " << cargoCapacity << " cu ft" 
              << "\nFour-Wheel Drive: " << (fourWheelDrive ? "Yes" : "No")
              << "\nTowing Capacity: " << towingCapacity << " lbs" << std::endl;
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

void SUV::validate() const {
    if (groundClearance < 0 || cargoCapacity < 0 || towingCapacity < 0) {
        throw InvalidValueException("Invalid value in SUV");
    }
}
