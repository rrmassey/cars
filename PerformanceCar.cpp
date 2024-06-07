#ifndef PERFORMANCECAR_H
#define PERFORMANCECAR_H

#include "Car.h"
#include "Engine.h"

class PerformanceCar : public Car<int> {
private:
    Engine engine;
    double topSpeed;
    double zeroToSixty;
    double quarterMile;

public:
    PerformanceCar(int id = 0, const std::string& make = "", const std::string& model = "", 
                   const Engine& engine = Engine(), double topSpeed = 0.0, double zeroToSixty = 0.0, double quarterMile = 0.0)
        : Car(id, make, model), engine(engine), topSpeed(topSpeed), zeroToSixty(zeroToSixty), quarterMile(quarterMile) {}

    Engine getEngine() const { return engine; }
    double getTopSpeed() const { return topSpeed; }
    double getZeroToSixty() const { return zeroToSixty; }
    double getQuarterMile() const { return quarterMile; }

    void setEngine(const Engine& engine) { this->engine = engine; }
    void setTopSpeed(double topSpeed) { this->topSpeed = topSpeed; }
    void setZeroToSixty(double zeroToSixty) { this->zeroToSixty = zeroToSixty; }
    void setQuarterMile(double quarterMile) { this->quarterMile = quarterMile; }

    void display() const override {
        Car::display();
        engine.display();
        std::cout << "Top Speed: " << topSpeed << " mph"
                  << "\n0-60 mph: " << zeroToSixty << " seconds"
                  << "\nQuarter Mile: " << quarterMile << " seconds" << std::endl;
    }

    void readFromBinary(std::ifstream& in) override {
        Car::readFromBinary(in);
        engine.readFromBinary(in);
        in.read(reinterpret_cast<char*>(&topSpeed), sizeof(topSpeed));
        in.read(reinterpret_cast<char*>(&zeroToSixty), sizeof(zeroToSixty));
        in.read(reinterpret_cast<char*>(&quarterMile), sizeof(quarterMile));
    }

    void writeToBinary(std::ofstream& out) const override {
        Car::writeToBinary(out);
        engine.writeToBinary(out);
        out.write(reinterpret_cast<const char*>(&topSpeed), sizeof(topSpeed));
        out.write(reinterpret_cast<const char*>(&zeroToSixty), sizeof(zeroToSixty));
        out.write(reinterpret_cast<const char*>(&quarterMile), sizeof(quarterMile));
    }

    void validate() const override {
        if (topSpeed < 0 || zeroToSixty < 0 || quarterMile < 0) {
            throw InvalidValueException("Invalid value in PerformanceCar");
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const PerformanceCar& car) {
        car.display();
        return os;
    }

    friend std::istream& operator>>(std::istream& is, PerformanceCar& car) {
        car.read(is);
        car.engine.read(is);
        std::cout << "Enter Top Speed (mph): ";
        is >> car.topSpeed;
        std::cout << "Enter 0-60 mph time (seconds): ";
        is >> car.zeroToSixty;
        std::cout << "Enter Quarter Mile time (seconds): ";
        is >> car.quarterMile;
        return is;
    }
};

#endif // PERFORMANCECAR_H
