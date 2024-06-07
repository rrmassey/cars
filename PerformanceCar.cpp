#include "PerformanceCar.h"
#include "InvalidValueException.h"

Engine PerformanceCar::getEngine() const {
    return engine;
}

double PerformanceCar::getTopSpeed() const {
    return topSpeed;
}

double PerformanceCar::getZeroToSixty() const {
    return zeroToSixty;
}

double PerformanceCar::getQuarterMile() const {
    return quarterMile;
}

void PerformanceCar::setEngine(const Engine& engine) {
    this->engine = engine;
}

void PerformanceCar::setTopSpeed(double topSpeed) {
    this->topSpeed = topSpeed;
}

void PerformanceCar::setZeroToSixty(double zeroToSixty) {
    this->zeroToSixty = zeroToSixty;
}

void PerformanceCar::setQuarterMile(double quarterMile) {
    this->quarterMile = quarterMile;
}

void PerformanceCar::display() const {
    Car::display();
    engine.display();
    std::cout << "Top Speed: " << topSpeed << " mph"
              << "\n0-60 mph: " << zeroToSixty << " seconds"
              << "\nQuarter Mile: " << quarterMile << " seconds" << std::endl;
}

void PerformanceCar::readFromBinary(std::ifstream& in) {
    Car::readFromBinary(in);
    engine.readFromBinary(in);
    in.read(reinterpret_cast<char*>(&topSpeed), sizeof(topSpeed));
    in.read(reinterpret_cast<char*>(&zeroToSixty), sizeof(zeroToSixty));
    in.read(reinterpret_cast<char*>(&quarterMile), sizeof(quarterMile));
}

void PerformanceCar::writeToBinary(std::ofstream& out) const {
    Car::writeToBinary(out);
    engine.writeToBinary(out);
    out.write(reinterpret_cast<const char*>(&topSpeed), sizeof(topSpeed));
    out.write(reinterpret_cast<const char*>(&zeroToSixty), sizeof(zeroToSixty));
    out.write(reinterpret_cast<const char*>(&quarterMile), sizeof(quarterMile));
}

void PerformanceCar::validate() const {
    if (topSpeed < 0 || zeroToSixty < 0 || quarterMile < 0) {
        throw InvalidValueException("Invalid value in PerformanceCar");
    }
    engine.validate();
}
