#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <fstream>

class Engine {
private:
    int horsepower;
    double displacement;  //in liters
    int numCylinders;
    int torque;

public:
    Engine(int horsepower = 0, double displacement = 0.0);

    void display() const;
    void readFromBinary(std::ifstream& in);
    void writeToBinary(std::ofstream& out) const;

    int getHorsepower() const;
    double getDisplacement() const;
    int getNumCylinders() const;
    int getTorque() const;

    void setHorsepower(int horsepower);
    void setDisplacement(double displacement);
    void setNumCylinders(int numCylinders);
    void setTorque(int torque);

    friend std::ostream& operator<<(std::ostream& os, const Engine& engine);
    friend std::istream& operator>>(std::istream& is, Engine& engine);
};

#endif // ENGINE_H
