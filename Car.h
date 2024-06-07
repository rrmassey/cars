#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include "InvalidValueException.h"

template <typename T>
class Car {
private:
    int id;
    std::string make;
    std::string model;
public:
    Car(int id = 0, const std::string& make = "", const std::string& model = "");
    virtual ~Car();

    int getId() const;
    std::string getMake() const;
    std::string getModel() const;

    void setId(int id);
    void setMake(const std::string& make);
    void setModel(const std::string& model);

    virtual void display() const;
    virtual void readFromBinary(std::ifstream& in);
    virtual void writeToBinary(std::ofstream& out) const;
    virtual void read(std::istream& is);

    friend std::ostream& operator<<(std::ostream& os, const Car& car) {
        car.display();
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Car& car) {
        car.read(is);
        return is;
    }
    virtual void validate() const = 0;
};

#include "Car.cpp"

#endif // CAR_H
