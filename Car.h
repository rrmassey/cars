#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

template<typename T>
class Car {
protected:
    int id;
    std::string make;
    std::string model;

public:
    Car(int id = 0, const std::string& make = "", const std::string& model = "") 
        : id(id), make(make), model(model) {}

    int getId() const { return id; }
    std::string getMake() const { return make; }
    std::string getModel() const { return model; }

    void setId(int id) { this->id = id; }
    void setMake(const std::string& make) { this->make = make; }
    void setModel(const std::string& model) { this->model = model; }

    virtual void display() const {
        std::cout << "ID: " << id << "\nMake: " << make << "\nModel: " << model << std::endl;
    }

    virtual void readFromBinary(std::ifstream& in) {
        in.read(reinterpret_cast<char*>(&id), sizeof(id));
        std::getline(in, make, '\0');
        std::getline(in, model, '\0');
    }

    virtual void writeToBinary(std::ofstream& out) const {
        out.write(reinterpret_cast<const char*>(&id), sizeof(id));
        out.write(make.c_str(), make.size() + 1);
        out.write(model.c_str(), model.size() + 1);
    }

    virtual void read(std::istream& is) {
        std::cout << "Enter ID: ";
        is >> id;
        is.ignore();
        std::cout << "Enter Make: ";
        std::getline(is, make);
        std::cout << "Enter Model: ";
        std::getline(is, model);
    }

    virtual void validate() const = 0;
};

#endif // CAR_H
