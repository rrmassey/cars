#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <fstream>

class Engine {
private:
    int horsepower;
    double displacement;
    int numCylinders;
    int torque;

public:
    Engine(int horsepower = 0, double displacement = 0.0, int numCylinders = 0, int torque = 0)
        : horsepower(horsepower), displacement(displacement), numCylinders(numCylinders), torque(torque) {}

    int getHorsepower() const { return horsepower; }
    double getDisplacement() const { return displacement; }
    int getNumCylinders() const { return numCylinders; }
    int getTorque() const { return torque; }

    void setHorsepower(int horsepower) { this->horsepower = horsepower; }
    void setDisplacement(double displacement) { this->displacement = displacement; }
    void setNumCylinders(int numCylinders) { this->numCylinders = numCylinders; }
    void setTorque(int torque) { this->torque = torque; }

    void display() const {
        std::cout << "Horsepower: " << horsepower 
                  << "\nDisplacement: " << displacement << " L"
                  << "\nNumber of Cylinders: " << numCylinders 
                  << "\nTorque: " << torque << " lb-ft" << std::endl;
    }

    void readFromBinary(std::ifstream& in) {
        in.read(reinterpret_cast<char*>(&horsepower), sizeof(horsepower));
        in.read(reinterpret_cast<char*>(&displacement), sizeof(displacement));
        in.read(reinterpret_cast<char*>(&numCylinders), sizeof(numCylinders));
        in.read(reinterpret_cast<char*>(&torque), sizeof(torque));
    }

    void writeToBinary(std::ofstream& out) const {
        out.write(reinterpret_cast<const char*>(&horsepower), sizeof(horsepower));
        out.write(reinterpret_cast<const char*>(&displacement), sizeof(displacement));
        out.write(reinterpret_cast<const char*>(&numCylinders), sizeof(numCylinders));
        out.write(reinterpret_cast<const char*>(&torque), sizeof(torque));
    }

    void validate() const {
        if (horsepower < 0 || displacement < 0 || numCylinders < 0 || torque < 0) {
            throw InvalidValueException("Invalid value in Engine");
        }
    }
};

#endif // ENGINE_H
