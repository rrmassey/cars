#include "Engine.h"

Engine::Engine(int horsepower, double displacement) 
    : horsepower(horsepower), displacement(displacement) {}

void Engine::display() const {
    std::cout << "Horsepower: " << horsepower << std::endl;
    std::cout << "Displacement: " << displacement << " liters" << std::endl;
    std::cout << "Number of Cylinders: " << numCylinders << std::endl;
    std::cout << "Torque: " << torque << " Nm" << std::endl;
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
