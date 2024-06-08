#ifndef PERFORMANCECAR_H
#define PERFORMANCECAR_H

#include "suv.h"
#include "engine.h"

class PerformanceCar : public SUV {
private:
    Engine engine;
    double topSpeed;  // in mph
    double zeroToSixty;  // in seconds
    double quarterMile;    // in seconds

public:
    PerformanceCar(int id = 0, const std::string& make = "", const std::string& model = "", int groundClearance = 0, double cargoCapacity = 0.0, bool fourWheelDrive = false, double towingCapacity = 0.0, const Engine& engine = Engine(), double topSpeed = 0.0, double zeroToSixty = 0.0, double quarterMile = 0.0);

    void display() const override;
    void readFromBinary(std::ifstream& in) override;
    void writeToBinary(std::ofstream& out) const override;

    Engine getEngine() const;
    double getTopSpeed() const;
    double getZeroToSixty() const;
    double getquarterMile() const;

    void setEngine(const Engine& engine);
    void setTopSpeed(double topSpeed);
    void setZeroToSixty(double zeroToSixty);
    void setquarterMile(double quarterMile);

    void validate() const override;

    friend std::ostream& operator<<(std::ostream& os, const PerformanceCar& car);
    friend std::istream& operator>>(std::istream& is, PerformanceCar& car);
};

#endif // PERFORMANCECAR_H
