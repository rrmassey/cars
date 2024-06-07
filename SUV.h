#ifndef SUV_H
#define SUV_H

#include "Car.h"

class SUV : public Car<int> {
private:
    int groundClearance;  //in inches
    bool fourWheelDrive;
    int seatingCapacity;

public:
    SUV(int id = 0, const std::string& make = "", const std::string& model = "", int groundClearance = 0, bool fourWheelDrive = false, int seatingCapacity = 0)
        : Car(id, make, model), groundClearance(groundClearance), fourWheelDrive(fourWheelDrive), seatingCapacity(seatingCapacity) {}

    void display() const override {
        Car::display();
        std::cout << "Ground Clearance: " << groundClearance << " inches" << std::endl;
        std::cout << "Four-Wheel Drive: " << (fourWheelDrive ? "Yes" : "No") << std::endl;
        std::cout << "Seating Capacity: " << seatingCapacity << std::endl;
    }

    void readFromBinary(std::ifstream& in) override {
        Car::readFromBinary(in);
        in.read(reinterpret_cast<char*>(&groundClearance), sizeof(groundClearance));
        in.read(reinterpret_cast<char*>(&fourWheelDrive), sizeof(fourWheelDrive));
        in.read(reinterpret_cast<char*>(&seatingCapacity), sizeof(seatingCapacity));
    }

    void writeToBinary(std::ofstream& out) const override {
        Car::writeToBinary(out);
        out.write(reinterpret_cast<const char*>(&groundClearance), sizeof(groundClearance));
        out.write(reinterpret_cast<const char*>(&fourWheelDrive), sizeof(fourWheelDrive));
        out.write(reinterpret_cast<const char*>(&seatingCapacity), sizeof(seatingCapacity));
    }

    int getGroundClearance() const { return groundClearance; }
    bool getFourWheelDrive() const { return fourWheelDrive; }
    int getSeatingCapacity() const { return seatingCapacity; }

    void setGroundClearance(int groundClearance) { this->groundClearance = groundClearance; }
    void setFourWheelDrive(bool fourWheelDrive) { this->fourWheelDrive = fourWheelDrive; }
    void setSeatingCapacity(int seatingCapacity) { this->seatingCapacity = seatingCapacity; }

    void validate() const override {
        if (groundClearance < 0 || seatingCapacity < 0) {
            throw InvalidValueException("Invalid value in SUV");
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const SUV& suv) {
        suv.display();
        return os;
    }

    friend std::istream& operator>>(std::istream& is, SUV& suv) {
        is >> static_cast<Car<int>&>(suv);
        std::cout << "Enter Ground Clearance (inches): ";
        is >> suv.groundClearance;
        std::cout << "Enter Four-Wheel Drive (1 for Yes, 0 for No): ";
        is >> suv.fourWheelDrive;
        std::cout << "Enter Seating Capacity: ";
        is >> suv.seatingCapacity;
        return is;
    }
};

#endif // SUV_H
