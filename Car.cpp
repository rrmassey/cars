#include "car.h"

template <typename T>
Car<T>::Car(int id, const std::string& make, const std::string& model)
    : id(id), make(make), model(model) {}

template <typename T>
int Car<T>::getId() const {
    return id;
}

template <typename T>
std::string Car<T>::getMake() const {
    return make;
}

template <typename T>
std::string Car<T>::getModel() const {
    return model;
}

template <typename T>
void Car<T>::setId(int id) {
    this->id = id;
}

template <typename T>
void Car<T>::setMake(const std::string& make) {
    this->make = make;
}

template <typename T>
void Car<T>::setModel(const std::string& model) {
    this->model = model;
}

template <typename T>
void Car<T>::display() const {
    std::cout << "ID: " << id << std::endl;
    std::cout << "Make: " << make << std::endl;
    std::cout << "Model: " << model << std::endl;
}

template <typename T>
void Car<T>::readFromBinary(std::ifstream& in) {
    in.read(reinterpret_cast<char*>(&id), sizeof(id));
    size_t size;
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    make.resize(size);
    in.read(&make[0], size);
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    model.resize(size);
    in.read(&model[0], size);
}

template <typename T>
void Car<T>::writeToBinary(std::ofstream& out) const {
    out.write(reinterpret_cast<const char*>(&id), sizeof(id));
    size_t size = make.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(make.c_str(), size);
    size = model.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(model.c_str(), size);
}

template <typename T>
void Car<T>::read(std::istream& is) {
    std::cout << "Enter ID: ";
    is >> id;
    is.ignore();
    std::cout << "Enter Make: ";
    std::getline(is, make);
    std::cout << "Enter Model: ";
    std::getline(is, model);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Car<T>& car) {
    car.display();
    return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, Car<T>& car) {
    car.read(is);
    return is;
}
