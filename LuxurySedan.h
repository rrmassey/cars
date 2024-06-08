#ifndef LUXURYSEDAN_H
#define LUXURYSEDAN_H

#include "sedan.h"

class LuxurySedan : public Sedan {
private:
    std::string interiorMaterial;
    bool hasMassageSeats;
    std::string infotainmentSystem;
    std::string paintColor;

public:
    LuxurySedan(int id = 0, const std::string& make = "", const std::string& model = "", int year = 0, double price = 0.0, int trunkSize = 0, double fuelEfficiency = 0.0, const std::string& interiorMaterial = "", bool hasMassageSeats = false, const std::string& infotainmentSystem = "", const std::string& paintColor = "");

    void display() const override;
    void readFromBinary(std::ifstream& in) override;
    void writeToBinary(std::ofstream& out) const override;

    std::string getInteriorMaterial() const;
    bool getHasMassageSeats() const;
    std::string getInfotainmentSystem() const;
    std::string getPaintColor() const;

    void setInteriorMaterial(const std::string& interiorMaterial);
    void setHasMassageSeats(bool hasMassageSeats);
    void setInfotainmentSystem(const std::string& infotainmentSystem);
    void setPaintColor(const std::string& paintColor);

    void validate() const override;

    friend std::ostream& operator<<(std::ostream& os, const LuxurySedan& car);
    friend std::istream& operator>>(std::istream& is, LuxurySedan& car);
};

#endif // LUXURYSEDAN_H
