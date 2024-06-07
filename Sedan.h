#ifndef SEDAN_H
#define SEDAN_H

#include "Car.h"

class Sedan : public Car<int> {
private:
    int year;
    double price;
    int trunkSize;
    double fuelEfficiency;
public:
    Sedan(int id = 0, const std::string& make = "", const std::string& model = "", int year = 0, double price = 0.0, int trunkSize = 0, double fuelEfficiency = 0.0);

    void display() const override;
    void readFromBinary(std::ifstream& in) override;
    void writeToBinary(std::ofstream& out) const override;

    int getYear() const;
    double getPrice() const;
    int getTrunkSize() const;
    double getFuelEfficiency() const;

    void setYear(int year);
    void setPrice(double price);
    void setTrunkSize(int trunkSize);
    void setFuelEfficiency(double fuelEfficiency);

    void validate() const override;

    friend std::ostream& operator<<(std::ostream& os, const Sedan& sedan);
    friend std::istream& operator>>(std::istream& is, Sedan& sedan);
};

#endif // SEDAN_H
