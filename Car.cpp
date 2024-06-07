#include "Car.h"
#include "InvalidValueException.h"

// Car class template implementations
template<typename T>
T Car<T>::getId() const {
    return id;
}

template<typename T>
std::string Car<T>::getMake() const {
    return make;
}

template<typename T>
std::string Car<T>::getModel() const {
    return model;
}

template<typename T>
void Car<T>::setId(T id) {
    this->id = id;
}

template<typename T>
void Car<T>::setMake(const std::string& make) {
    this->make = make;
}

template<typename T>
void Car<T>::setModel(const std::string& model) {
    this->model = model;
}

template<typename T>
void Car<T>::display() const {
    std::cout << "ID: " << id 
              << "\nMake: " << make 
              << "\nModel: " << model << std::endl;
}

template<typename T>
void Car<T>::readFromBinary(std::ifstream& in) {
    in.read(reinterpret_cast<char*>(&id), sizeof(id));
    std::getline(in, make, '\0');
    std::getline(in, model, '\0');
}

template<typename T>
void Car<T>::writeToBinary(std::ofstream& out) const {
    out.write(reinterpret_cast<const char*>(&id), sizeof(id));
    out.write(make.c_str(), make.size() + 1);
    out.write(model.c_str(), model.size() + 1);
}

template<typename T>
void Car<T>::read(std::istream& is) {
    std::cout << "Enter ID: ";
    is >> id;
    is.ignore();
    std::cout << "Enter Make: ";
    std::getline(is, make);
    std::cout << "Enter Model: ";
    std::getline(is, model);
}

// Explicit instantiation for the Car<int> template
template class Car<int>;
