#include "LuxurySedan.h"
#include "InvalidValueException.h"

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

void LuxurySedan::display() const {
    Car::display();
    std::cout << "Interior Material: " << interiorMaterial 
              << "\nMassage Seats: " << (hasMassageSeats ? "Yes" : "No")
              << "\nInfotainment System: " << infotainmentSystem 
              << "\nPaint Color: " << paintColor << std::endl;
}

void LuxurySedan::readFromBinary(std::ifstream& in) {
    Car::readFromBinary(in);
    std::getline(in, interiorMaterial, '\0');
    in.read(reinterpret_cast<char*>(&hasMassageSeats), sizeof(hasMassageSeats));
    std::getline(in, infotainmentSystem, '\0');
    std::getline(in, paintColor, '\0');
}

void LuxurySedan::writeToBinary(std::ofstream& out) const {
    Car::writeToBinary(out);
    out.write(interiorMaterial.c_str(), interiorMaterial.size() + 1);
    out.write(reinterpret_cast<const char*>(&hasMassageSeats), sizeof(hasMassageSeats));
    out.write(infotainmentSystem.c_str(), infotainmentSystem.size() + 1);
    out.write(paintColor.c_str(), paintColor.size() + 1);
}

void LuxurySedan::validate() const {
    if (interiorMaterial.empty() || infotainmentSystem.empty() || paintColor.empty()) {
        throw InvalidValueException("Invalid value in LuxurySedan");
    }
}
