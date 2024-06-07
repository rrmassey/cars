#ifndef SUV_H
#define SUV_H

#include "Car.h"

class SUV : public Car<int> {
private:
    int groundClearance;
    double cargoCapacity;
    bool fourWheelDrive;
    double towingCapacity;

public:
    SUV(int id = 0, const std::string& make = "", const std::string& model = "", 
        int groundClearance = 0, double cargoCapacity = 0.0, bool fourWheelDrive = false, double towingCapacity = 0.0)
        : Car(id, make, model), groundClearance(groundClearance), cargoCapacity(cargoCapacity), 
          fourWheelDrive(fourWheelDrive), towingCapacity(towingCapacity) {}

    int getGroundClearance() const { return groundClearance; }
    double getCargoCapacity() const { return cargoCapacity; }
    bool getFourWheelDrive() const { return fourWheelDrive; }
    double getTowingCapacity() const { return towingCapacity; }

    void setGroundClearance(int groundClearance) { this->groundClearance = groundClearance; }
    void setCargoCapacity(double cargoCapacity) { this->cargoCapacity = cargoCapacity; }
    void setFourWheelDrive(bool fourWheelDrive) { this->fourWheelDrive = fourWheelDrive; }
    void setTowingCapacity(double towingCapacity) { this->towingCapacity = towingCapacity; }

    void display() const override {
        Car::display();
        std::cout << "Ground Clearance: " << groundClearance << " inches"
                  << "\nCargo Capacity: " << cargoCapacity << " cu ft"
                  << "\nFour-Wheel Drive: " << (fourWheelDrive ? "Yes" : "No")
                  << "\nTowing Capacity: " << towingCapacity << " lbs" << std::endl;
    }

    void readFromBinary(std::ifstream& in) override {
        Car::readFromBinary(in);
        in.read(reinterpret_cast<char*>(&groundClearance), sizeof(groundClearance));
        in.read(reinterpret_cast<char*>(&cargoCapacity), sizeof(cargoCapacity));
        in.read(reinterpret_cast<char*>(&fourWheelDrive), sizeof(fourWheelDrive));
        in.read(reinterpret_cast<char*>(&towingCapacity), sizeof(towingCapacity));
    }

    void writeToBinary(std::ofstream& out) const override {
        Car::writeToBinary(out);
        out.write(reinterpret_cast<const char*>(&groundClearance), sizeof(groundClearance));
        out.write(reinterpret_cast<const char*>(&cargoCapacity), sizeof(cargoCapacity));
        out.write(reinterpret_cast<const char*>(&fourWheelDrive), sizeof(fourWheelDrive));
        out.write(reinterpret_cast<const char*>(&towingCapacity), sizeof(towingCapacity));
    }

    void validate() const override {
        if (groundClearance < 0 || cargoCapacity < 0 || towingCapacity < 0) {
            throw InvalidValueException("Invalid value in SUV");
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const SUV& suv) {
        suv.display();
        return os;
    }

    friend std::istream& operator>>(std::istream& is, SUV& suv) {
        suv.read(is);
        std::cout << "Enter Ground Clearance (inches): ";
        is >> suv.groundClearance;
        std::cout << "Enter Cargo Capacity (cu ft): ";
        is >> suv.cargoCapacity;
        std::cout << "Four-Wheel Drive (1 for Yes, 0 for No): ";
        is >> suv.fourWheelDrive;
        std::cout << "Enter Towing Capacity (lbs): ";
        is >> suv.towingCapacity;
        return is;
    }
};

#endif // SUV_H
