#include "Engine.h"
#include "InvalidValueException.h"

int Engine::getHorsepower() const {
    return horsepower;
}

double Engine::getDisplacement() const {
    return displacement;
}

int Engine::getNumCylinders() const {
    return numCylinders;
}

int Engine::getTorque() const {
    return torque;
}

void Engine::setHorsepower(int horsepower) {
    this->horsepower = horsepower;
}

void Engine::setDisplacement(double displacement) {
    this->displacement = displacement;
}

void Engine::setNumCylinders(int numCylinders) {
    this->numCylinders = numCylinders;
}

void Engine::setTorque(int torque) {
    this->torque = torque;
}

void Engine::display() const {
    std::cout << "Horsepower: " << horsepower 
              << "\nDisplacement: " << displacement << " L" 
              << "\nNumber of Cylinders: " << numCylinders 
              << "\nTorque: " << torque << " lb-ft" << std::endl;
}

void Engine::readFromBinary(std::ifstream& in) {
    in.read(reinterpret_cast<char*>(&horsepower), sizeof(horsepower));
    in.read(reinterpret_cast<char*>(&displacement), sizeof(displacement));
    in.read(reinterpret_cast<char*>(&numCylinders), sizeof(numCylinders));
    in.read(reinterpret_cast<char*>(&torque), sizeof(torque));
}

void Engine::writeToBinary(std::ofstream& out) const {
    out.write(reinterpret_cast<const char*>(&horsepower), sizeof(horsepower));
    out.write(reinterpret_cast<const char*>(&displacement), sizeof(displacement));
    out.write(reinterpret_cast<const char*>(&numCylinders), sizeof(numCylinders));
    out.write(reinterpret_cast<const char*>(&torque), sizeof(torque));
}

void Engine::validate() const {
    if (horsepower < 0 || displacement < 0 || numCylinders < 0 || torque < 0) {
        throw InvalidValueException("Invalid value in Engine");
    }
}
