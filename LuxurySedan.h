#ifndef LUXURYSEDAN_H
#define LUXURYSEDAN_H

#include "Car.h"

class LuxurySedan : public Car<int> {
private:
    std::string interiorMaterial;
    bool hasMassageSeats;
    std::string infotainmentSystem;
    std::string paintColor;

public:
    LuxurySedan(int id = 0, const std::string& make = "", const std::string& model = "", 
                const std::string& interiorMaterial = "", bool hasMassageSeats = false, 
                const std::string& infotainmentSystem = "", const std::string& paintColor = "")
        : Car(id, make, model), interiorMaterial(interiorMaterial), hasMassageSeats(hasMassageSeats), 
          infotainmentSystem(infotainmentSystem), paintColor(paintColor) {}

    std::string getInteriorMaterial() const { return interiorMaterial; }
    bool getHasMassageSeats() const { return hasMassageSeats; }
    std::string getInfotainmentSystem() const { return infotainmentSystem; }
    std::string getPaintColor() const { return paintColor; }

    void setInteriorMaterial(const std::string& interiorMaterial) { this->interiorMaterial = interiorMaterial; }
    void setHasMassageSeats(bool hasMassageSeats) { this->hasMassageSeats = hasMassageSeats; }
    void setInfotainmentSystem(const std::string& infotainmentSystem) { this->infotainmentSystem = infotainmentSystem; }
    void setPaintColor(const std::string& paintColor) { this->paintColor = paintColor; }

    void display() const override {
        Car::display();
        std::cout << "Interior Material: " << interiorMaterial 
                  << "\nHas Massage Seats: " << (hasMassageSeats ? "Yes" : "No")
                  << "\nInfotainment System: " << infotainmentSystem 
                  << "\nPaint Color: " << paintColor << std::endl;
    }

    void readFromBinary(std::ifstream& in) override {
        Car::readFromBinary(in);
        std::getline(in, interiorMaterial, '\0');
        in.read(reinterpret_cast<char*>(&hasMassageSeats), sizeof(hasMassageSeats));
        std::getline(in, infotainmentSystem, '\0');
        std::getline(in, paintColor, '\0');
    }

    void writeToBinary(std::ofstream& out) const override {
        Car::writeToBinary(out);
        out.write(interiorMaterial.c_str(), interiorMaterial.size() + 1);
        out.write(reinterpret_cast<const char*>(&hasMassageSeats), sizeof(hasMassageSeats));
        out.write(infotainmentSystem.c_str(), infotainmentSystem.size() + 1);
        out.write(paintColor.c_str(), paintColor.size() + 1);
    }

    void validate() const override {
        // You can add more validations as required
    }

    friend std::ostream& operator<<(std::ostream& os, const LuxurySedan& car) {
        car.display();
        return os;
    }

    friend std::istream& operator>>(std::istream& is, LuxurySedan& car) {
        car.read(is);
        std::cout << "Enter Interior Material: ";
        std::getline(is, car.interiorMaterial);
        std::cout << "Has Massage Seats (1 for Yes, 0 for No): ";
        is >> car.hasMassageSeats;
        is.ignore();
        std::cout << "Enter Infotainment System: ";
        std::getline(is, car.infotainmentSystem);
        std::cout << "Enter Paint Color: ";
        std::getline(is, car.paintColor);
        return is;
    }
};

#endif // LUXURYSEDAN_H
