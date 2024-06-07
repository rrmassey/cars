#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

//Exception class
class InvalidValueException : public std::exception {
private:
    std::string message;
public:
    InvalidValueException(const std::string& message) : message(message) {}
    const char* what() const noexcept override { return message.c_str(); }
};

//Base class (template)
template <typename T>
class Car {
private:
    int id;
    std::string make;
    std::string model;
public:
    Car(int id = 0, const std::string& make = "", const std::string& model = "") 
        : id(id), make(make), model(model) {}

    virtual ~Car() {}

    int getId() const { return id; }
    std::string getMake() const { return make; }
    std::string getModel() const { return model; }

    void setId(int id) { this->id = id; }
    void setMake(const std::string& make) { this->make = make; }
    void setModel(const std::string& model) { this->model = model; }

    virtual void display() const {
        std::cout << "ID: " << id << std::endl;
        std::cout << "Make: " << make << std::endl;
        std::cout << "Model: " << model << std::endl;
    }

    virtual void readFromBinary(std::ifstream& in) {
        in.read(reinterpret_cast<char*>(&id), sizeof(id));
        size_t size;
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        make.resize(size);
        in.read(&make[0], size);
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        model.resize(size);
        in.read(&model[0], size);
    }

    virtual void writeToBinary(std::ofstream& out) const {
        out.write(reinterpret_cast<const char*>(&id), sizeof(id));
        size_t size = make.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        out.write(make.c_str(), size);
        size = model.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        out.write(model.c_str(), size);
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

#endif // CAR_H
