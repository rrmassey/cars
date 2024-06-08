#include "luxurysedan.h"

LuxurySedan::LuxurySedan(int id, const std::string& make, const std::string& model, int year, double price, int trunkSize, double fuelEfficiency, const std::string& interiorMaterial, bool hasMassageSeats, const std::string& infotainmentSystem, const std::string& paintColor)
    : Sedan(id, make, model, year, price, trunkSize, fuelEfficiency), interiorMaterial(interiorMaterial), hasMassageSeats(hasMassageSeats), infotainmentSystem(infotainmentSystem), paintColor(paintColor) {}

void LuxurySedan::display() const {
    Sedan::display();
    std::cout << "Interior Material: " << interiorMaterial << std::endl;
    std::cout << "Massage Seats: " << (hasMassageSeats ? "Yes" : "No") << std::endl;
    std::cout << "Infotainment System: " << infotainmentSystem << std::endl;
    std::cout << "Paint Color: " << paintColor << std::endl;
}

void LuxurySedan::readFromBinary(std::ifstream& in) {
    Sedan::readFromBinary(in);
    size_t size;
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    interiorMaterial.resize(size);
    in.read(&interiorMaterial[0], size);
    in.read(reinterpret_cast<char*>(&hasMassageSeats), sizeof(hasMassageSeats));
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    infotainmentSystem.resize(size);
    in.read(&infotainmentSystem[0], size);
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    paintColor.resize(size);
    in.read(&paintColor[0], size);
}

void LuxurySedan::writeToBinary(std::ofstream& out) const {
    Sedan::writeToBinary(out);
    size_t size = interiorMaterial.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(interiorMaterial.c_str(), size);
    out.write(reinterpret_cast<const char*>(&hasMassageSeats), sizeof(hasMassageSeats));
    size = infotainmentSystem.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(infotainmentSystem.c_str(), size);
    size = paintColor.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(paintColor.c_str(), size);
}

std::string LuxurySedan::getInteriorMaterial() const {
    return interiorMaterial;
}

bool LuxurySedan::getHasMassageSeats() const {
    return hasMassageSeats;
}

std::string LuxurySedan::getInfotainmentSystem() const {
    return infotainmentSystem;
}

std::string LuxurySedan::getPaintColor() const {
    return paintColor;
}

void LuxurySedan::setInteriorMaterial(const std::string& interiorMaterial) {
    this->interiorMaterial = interiorMaterial;
}

void LuxurySedan::setHasMassageSeats(bool hasMassageSeats) {
    this->hasMassageSeats = hasMassageSeats;
}

void LuxurySedan::setInfotainmentSystem(const std::string& infotainmentSystem) {
    this->infotainmentSystem = infotainmentSystem;
}

void LuxurySedan::setPaintColor(const std::string& paintColor) {
    this->paintColor = paintColor;
}

void LuxurySedan::validate() const {
    Sedan::validate();
    if (interiorMaterial.empty() || infotainmentSystem.empty()) {
        throw InvalidValueException("Invalid value in LuxurySedan");
    }
}

std::ostream& operator<<(std::ostream& os, const LuxurySedan& car) {
    car.display();
    return os;
}

std::istream& operator>>(std::istream& is, LuxurySedan& car) {
    is
