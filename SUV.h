#ifndef SUV_H
#define SUV_H

#include "Car.h"

class SUV : public Car<int> {
private:
    int year;
    double price;
    int seatingCapacity;
    double fuelEfficiency;
public:
    SUV(int id = 0, const std::string& make = "", const std::string& model = "", int year = 0, double price = 0.0, int seatingCapacity = 0, double fuelEfficiency = 0.0);

    void display() const override;
    void readFromBinary(std::ifstream& in) override;
    void writeToBinary(std::ofstream& out) const override;

    int getYear() const;
    double getPrice() const;
    int getSeatingCapacity() const;
    double getFuelEfficiency() const;

    void setYear(int year);
    void setPrice(double price);
    void setSeatingCapacity(int seatingCapacity);
    void setFuelEfficiency(double fuelEfficiency);

    void validate() const override;

    friend std::ostream& operator<<(std::ostream& os, const SUV& suv);
    friend std::istream& operator>>(std::istream& is, SUV& suv);
};

#endif // SUV_H
