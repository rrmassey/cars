#ifndef PERFORMANCECAR_H
#define PERFORMANCECAR_H

#include "Car.h"

class PerformanceCar : public Car<int> {
private:
    int year;
    double price;
    int horsepower;
    double topSpeed;
public:
    PerformanceCar(int id = 0, const std::string& make = "", const std::string& model = "", int year = 0, double price = 0.0, int horsepower = 0, double topSpeed = 0.0);

    void display() const override;
    void readFromBinary(std::ifstream& in) override;
    void writeToBinary(std::ofstream& out) const override;

    int getYear() const;
    double getPrice() const;
    int getHorsepower() const;
    double getTopSpeed() const;

    void setYear(int year);
    void setPrice(double price);
    void setHorsepower(int horsepower);
    void setTopSpeed(double topSpeed);

    void validate() const override;

    friend std::ostream& operator<<(std::ostream& os, const PerformanceCar& car);
    friend std::istream& operator>>(std::istream& is, PerformanceCar& car);
};

#endif // PERFORMANCECAR_H
