#ifndef ENGINE_H
#define ENGINE_H

#include <string>

class Engine {
private:
    int horsepower;
    int cylinderCount;
    std::string fuelType; //e.g., "Gasoline", "Diesel", "Electric"

public:
    Engine(int horsepower = 0, int cylinderCount = 0, const std::string& fuelType = "")
        : horsepower(horsepower), cylinderCount(cylinderCount), fuelType(fuelType) {}

    int getHorsepower() const { return horsepower; }
    int getCylinderCount() const { return cylinderCount; }
    std::string getFuelType() const { return fuelType; }

    void setHorsepower(int horsepower) { this->horsepower = horsepower; }
    void setCylinderCount(int cylinderCount) { this->cylinderCount = cylinderCount; }
    void setFuelType(const std::string& fuelType) { this->fuelType = fuelType; }

    void display() const {
        std::cout << "Horsepower: " << horsepower << std::endl;
        std::cout << "Cylinder Count: " << cylinderCount << std::endl;
        std::cout << "Fuel Type: " << fuelType << std::endl;
    }

    void readFromBinary(std::ifstream& in) {
        in.read(reinterpret_cast<char*>(&horsepower), sizeof(horsepower));
        in.read(reinterpret_cast<char*>(&cylinderCount), sizeof(cylinderCount));
        size_t size;
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        fuelType.resize(size);
        in.read(&fuelType[0], size);
    }

    void writeToBinary(std::ofstream& out) const {
        out.write(reinterpret_cast<const char*>(&horsepower), sizeof(horsepower));
        out.write(reinterpret_cast<const char*>(&cylinderCount), sizeof(cylinderCount));
        size_t size = fuelType.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        out.write(fuelType.c_str(), size);
    }

    void read(std::istream& is) {
        std::cout << "Enter Horsepower: ";
        is >> horsepower;
        std::cout << "Enter Cylinder Count: ";
        is >> cylinderCount;
        is.ignore();
        std::cout << "Enter Fuel Type: ";
        std::getline(is, fuelType);
    }

    friend std::ostream& operator<<(std::ostream& os, const Engine& engine) {
        engine.display();
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Engine& engine) {
        engine.read(is);
        return is;
    }
};

#endif // ENGINE_H
