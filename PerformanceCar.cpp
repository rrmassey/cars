#include "performancecar.h"

PerformanceCar::PerformanceCar(int id, const std::string& make, const std::string& model, int groundClearance, double cargoCapacity, bool fourWheelDrive, double towingCapacity, const Engine& engine, double topSpeed, double zeroToSixty, double quarterMile)
    : SUV(id, make, model, groundClearance, cargoCapacity, fourWheelDrive, towingCapacity), engine(engine), topSpeed(topSpeed), zeroToSixty(zeroToSixty), quarterMile(quarterMile) {}
void PerformanceCar::display() const {
SUV::display();
engine.display();
std::cout << "Top Speed: " << topSpeed << " mph" << std::endl;
std::cout << "0-60 mph: " << zeroToSixty << " seconds" << std::endl;
std::cout << "Quarter mile time: " << quarterMile << " seconds" << std::endl;
}
void PerformanceCar::readFromBinary(std::ifstream& in) {
SUV::readFromBinary(in);
engine.readFromBinary(in);
in.read(reinterpret_cast<char*>(&topSpeed), sizeof(topSpeed));
in.read(reinterpret_cast<char*>(&zeroToSixty), sizeof(zeroToSixty));
in.read(reinterpret_cast<char*>(&quarterMile), sizeof(quarterMile));
}
void PerformanceCar::writeToBinary(std::ofstream& out) const {
SUV::writeToBinary(out);
engine.writeToBinary(out);
out.write(reinterpret_cast<const char*>(&topSpeed), sizeof(topSpeed));
out.write(reinterpret_cast<const char*>(&zeroToSixty), sizeof(zeroToSixty));
out.write(reinterpret_cast<const char*>(&quarterMile), sizeof(quarterMile));
}
Engine PerformanceCar::getEngine() const {
return engine;
}
double PerformanceCar::getTopSpeed() const {
return topSpeed;
}
double PerformanceCar::getZeroToSixty() const {
return zeroToSixty;
}
double PerformanceCar::getquarterMile() const {
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
void PerformanceCar::setquarterMile(double quarterMile) {
this->quarterMile = quarterMile;
}
void PerformanceCar::validate() const {
SUV::validate();
if (topSpeed < 0 || zeroToSixty < 0) {
throw InvalidValueException("Invalid value in PerformanceCar");
}
}
std::ostream& operator<<(std::ostream& os, const PerformanceCar& car) {
car.display();
return os;
}
std::istream& operator>>(std::istream& is, PerformanceCar& car) {
is >> static_cast<SUV&>(car);
std::cout << "Enter Engine Details:\n";
is >> car.engine;
std::cout << "Enter Top Speed (mph): ";
is >> car.topSpeed;
std::cout << "Enter 0-60 mph Time (seconds): ";
is >> car.zeroToSixty;
std::cout << "Enter Quarter Mile Time (seconds): ";
is >> car.quarterMile;
return is;
}
