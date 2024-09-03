#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

//Exception class
class InvalidValueException : public std::exception{
private:
    std::string message;
public:
    InvalidValueException(const std::string& message) : message(message) {}
    const char* what() const noexcept override {return message.c_str();}
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

    int getId() const {return id;}
    std::string getMake() const {return make;}
    std::string getModel() const {return model;}

    void setId(int id) {this->id = id;}
    void setMake(const std::string& make) {this->make = make;}
    void setModel(const std::string& model) {this->model = model;}

    virtual void display() const{
        std::cout << "ID: " << id << std::endl;
        std::cout << "Make: " << make << std::endl;
        std::cout << "Model: " << model << std::endl;
    }

    virtual void readFromBinary(std::ifstream& in){
        in.read(reinterpret_cast<char*>(&id), sizeof(id));
        size_t size;
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        make.resize(size);
        in.read(&make[0], size);
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        model.resize(size);
        in.read(&model[0], size);
    }

    virtual void writeToBinary(std::ofstream& out) const{
        out.write(reinterpret_cast<const char*>(&id), sizeof(id));
        size_t size = make.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        out.write(make.c_str(), size);
        size = model.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        out.write(model.c_str(), size);
    }

    virtual void read(std::istream& is){
        std::cout << "Enter ID: ";
        is >> id;
        is.ignore();
        std::cout << "Enter Make: ";
        std::getline(is, make);
        std::cout << "Enter Model: ";
        std::getline(is, model);
    }

    friend std::ostream& operator<<(std::ostream& os, const Car& car){
        car.display();
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Car& car){
        car.read(is);
        return is;
    }
    virtual void validate() const = 0;
};

//Child class 1: Sedan
class Sedan : public Car<int> {
private:
    int year;
    double price;           //in dollars
    int trunkSize;          //in cubic feet
    double fuelEfficiency;  //in miles per gallon

public:
    Sedan(int id = 0, const std::string& make = "", const std::string& model = "", int year = 0, double price = 0.0, int trunkSize = 0, double fuelEfficiency = 0.0)
        : Car(id, make, model), year(year), price(price), trunkSize(trunkSize), fuelEfficiency(fuelEfficiency) {}

    void display() const override{
        Car::display();
        std::cout << "Year: " << year << std::endl;
        std::cout << "Price : $" << price << std::endl;
        std::cout << "Trunk Size: " << trunkSize << " cubic feet" << std::endl;
        std::cout << "Fuel Efficiency: " << fuelEfficiency << " mpg" << std::endl;
    }

    void readFromBinary(std::ifstream& in) override{
        Car::readFromBinary(in);
        in.read(reinterpret_cast<char*>(&year), sizeof(year));
        in.read(reinterpret_cast<char*>(&price), sizeof(price));
        in.read(reinterpret_cast<char*>(&trunkSize), sizeof(trunkSize));
        in.read(reinterpret_cast<char*>(&fuelEfficiency), sizeof(fuelEfficiency));
    }

    void writeToBinary(std::ofstream& out) const override{
        Car::writeToBinary(out);
        out.write(reinterpret_cast<const char*>(&year), sizeof(year));
        out.write(reinterpret_cast<const char*>(&price), sizeof(price));
        out.write(reinterpret_cast<const char*>(&trunkSize), sizeof(trunkSize));
        out.write(reinterpret_cast<const char*>(&fuelEfficiency), sizeof(fuelEfficiency));
    }

    int getYear() const {return year;}
    double getPrice() const {return price;}
    int getTrunkSize() const {return trunkSize;}
    double getFuelEfficiency() const {return fuelEfficiency;}

    void setYear(int year) {this->year = year;}
    void setPrice(double price) {this->price = price;}
    void setTrunkSize(int trunkSize) {this->trunkSize = trunkSize;}
    void setFuelEfficiency(double fuelEfficiency) {this->fuelEfficiency = fuelEfficiency;}

    void validate() const override{
        if (year < 1886 || price < 0 || trunkSize < 0 || fuelEfficiency < 0){
            throw InvalidValueException("Invalid value in Sedan");
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Sedan& sedan){
        sedan.display();
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Sedan& sedan){
        is >> static_cast<Car<int>&>(sedan);
        std::cout << "Enter Year: ";
        is >> sedan.year;
        std::cout << "Enter Price: ";
        is >> sedan.price;
        std::cout << "Enter Trunk Size (cubic feet): ";
        is >> sedan.trunkSize;
        std::cout << "Enter Fuel Efficiency (mpg): ";
        is >> sedan.fuelEfficiency;
        return is;
    }
};

//Composite class: Engine
class Engine {
private:
    int horsepower;
    double displacement;  //in liters
    int numCylinders;
    int torque;

public:
    Engine(int horsepower = 0, double displacement = 0.0)
        : horsepower(horsepower), displacement(displacement) {}

    void display() const{
        std::cout << "Horsepower: " << horsepower << std::endl;
        std::cout << "Displacement: " << displacement << " liters" << std::endl;
        std::cout << "Number of Cylinders: " << numCylinders << std::endl;
        std::cout << "Torque: " << torque << " Nm" << std::endl;
    }

    void readFromBinary(std::ifstream& in){
        in.read(reinterpret_cast<char*>(&horsepower), sizeof(horsepower));
        in.read(reinterpret_cast<char*>(&displacement), sizeof(displacement));
        in.read(reinterpret_cast<char*>(&numCylinders), sizeof(numCylinders));
        in.read(reinterpret_cast<char*>(&torque), sizeof(torque));
    }

    void writeToBinary(std::ofstream& out) const{
        out.write(reinterpret_cast<const char*>(&horsepower), sizeof(horsepower));
        out.write(reinterpret_cast<const char*>(&displacement), sizeof(displacement));
        out.write(reinterpret_cast<const char*>(&numCylinders), sizeof(numCylinders));
        out.write(reinterpret_cast<const char*>(&torque), sizeof(torque));
    }

    int getHorsepower() const {return horsepower;}
    double getDisplacement() const {return displacement;}
    int getNumCylinders() const {return numCylinders;}
    int getTorque() const {return torque;}

    void setHorsepower(int horsepower) {this->horsepower = horsepower;}
    void setDisplacement(double displacement) {this->displacement = displacement;}
    void setNumCylinders(int numCylinders) {this->numCylinders = numCylinders;}
    void setTorque(int torque) {this->torque = torque;}

    friend std::ostream& operator<<(std::ostream& os, const Engine& engine){
        os << "Horsepower: " << engine.horsepower << ", Displacement: " << engine.displacement << " liters";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Engine& engine){
        std::cout << "Enter Horsepower: ";
        is >> engine.horsepower;
        std::cout << "Enter Displacement (liters): ";
        is >> engine.displacement;
        std::cout << "Enter Number of Cylinders: ";
        is >> engine.numCylinders;
        std::cout << "Enter Torque : ";
        is >> engine.torque;
        return is;
    }
};

// Child class 2: SUV
class SUV : public Car<int> {
private:
    int groundClearance;  //in inches
    double cargoCapacity;  //in cubic feet
    bool fourWheelDrive;
    double towingCapacity;  //in pounds

public:
    SUV(int id = 0, const std::string& make = "", const std::string& model = "", int groundClearance = 0, double cargoCapacity = 0.0, bool fourWheelDrive = false, double towingCapacity = 0.0)
        : Car(id, make, model), groundClearance(groundClearance), cargoCapacity(cargoCapacity), fourWheelDrive(fourWheelDrive), towingCapacity(towingCapacity) {}

    void display() const override{
        Car::display();
        std::cout << "Ground Clearance: " << groundClearance << " inches" << std::endl;
        std::cout << "Cargo Capacity: " << cargoCapacity << " cubic feet" << std::endl;
        std::cout << "Four Wheel Drive: " << (fourWheelDrive ? "Yes" : "No") << std::endl;
        std::cout << "Towing Capacity: " << towingCapacity << " pounds" << std::endl;
    }

    void readFromBinary(std::ifstream& in) override{
        Car::readFromBinary(in);
        in.read(reinterpret_cast<char*>(&groundClearance), sizeof(groundClearance));
        in.read(reinterpret_cast<char*>(&cargoCapacity), sizeof(cargoCapacity));
        in.read(reinterpret_cast<char*>(&fourWheelDrive), sizeof(fourWheelDrive));
        in.read(reinterpret_cast<char*>(&towingCapacity), sizeof(towingCapacity));
    }

    void writeToBinary(std::ofstream& out) const override{
        Car::writeToBinary(out);
        out.write(reinterpret_cast<const char*>(&groundClearance), sizeof(groundClearance));
        out.write(reinterpret_cast<const char*>(&cargoCapacity), sizeof(cargoCapacity));
        out.write(reinterpret_cast<const char*>(&fourWheelDrive), sizeof(fourWheelDrive));
        out.write(reinterpret_cast<const char*>(&towingCapacity), sizeof(towingCapacity));
    }

    int getGroundClearance() const {return groundClearance;}
    double getCargoCapacity() const {return cargoCapacity;}
    bool getFourWheelDrive() const {return fourWheelDrive;}
    double getTowingCapacity() const {return towingCapacity;}

    void setGroundClearance(int groundClearance) {this->groundClearance = groundClearance;}
    void setCargoCapacity(double cargoCapacity) {this->cargoCapacity = cargoCapacity;}
    void setFourWheelDrive(bool fourWheelDrive) {this->fourWheelDrive = fourWheelDrive;}
    void setTowingCapacity(double towingCapacity) {this->towingCapacity = towingCapacity;}

    void validate() const override{
        if (groundClearance < 0 || cargoCapacity < 0 || towingCapacity < 0) {
            throw InvalidValueException("Invalid value in SUV");
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const SUV& suv){
        suv.display();
        return os;
    }

    friend std::istream& operator>>(std::istream& is, SUV& suv){
        is >> static_cast<Car<int>&>(suv);
        std::cout << "Enter Ground Clearance (inches): ";
        is >> suv.groundClearance;
        std::cout << "Enter Cargo Capacity (cubic feet): ";
        is >> suv.cargoCapacity;
        std::cout << "Enter Four Wheel Drive (0 for No, 1 for Yes): ";
        is >> suv.fourWheelDrive;
        std::cout << "Enter Towing Capacity (pounds): ";
        is >> suv.towingCapacity;
        return is;
    }
};

// Child class 3: Performance Car
class PerformanceCar : public SUV {
private:
    Engine engine;
    double topSpeed;  // in mph
    double zeroToSixty;  // in seconds
    double quarterMile;    // in seconds

public:
    PerformanceCar(int id = 0, const std::string& make = "", const std::string& model = "", int groundClearance = 0, double cargoCapacity = 0.0, bool fourWheelDrive = false, double towingCapacity = 0.0, const Engine& engine = Engine(), double topSpeed = 0.0, double zeroToSixty = 0.0, double quarterMile = 0.0)
        : SUV(id, make, model, groundClearance, cargoCapacity, fourWheelDrive, towingCapacity), engine(engine), topSpeed(topSpeed), zeroToSixty(zeroToSixty), quarterMile(quarterMile) {}

    void display() const override{
        SUV::display();
        engine.display();
        std::cout << "Top Speed: " << topSpeed << " mph" << std::endl;
        std::cout << "0-60 mph: " << zeroToSixty << " seconds" << std::endl;
        std::cout << "Quarter mile time: " << quarterMile << " seconds" << std::endl;
    }

    void readFromBinary(std::ifstream& in) override{
        SUV::readFromBinary(in);
        engine.readFromBinary(in);
        in.read(reinterpret_cast<char*>(&topSpeed), sizeof(topSpeed));
        in.read(reinterpret_cast<char*>(&zeroToSixty), sizeof(zeroToSixty));
        in.read(reinterpret_cast<char*>(&quarterMile), sizeof(quarterMile));
    }

    void writeToBinary(std::ofstream& out) const override{
        SUV::writeToBinary(out);
        engine.writeToBinary(out);
        out.write(reinterpret_cast<const char*>(&topSpeed), sizeof(topSpeed));
        out.write(reinterpret_cast<const char*>(&zeroToSixty), sizeof(zeroToSixty));
        out.write(reinterpret_cast<const char*>(&quarterMile), sizeof(quarterMile));
    }

    Engine getEngine() const {return engine;}
    double getTopSpeed() const {return topSpeed;}
    double getZeroToSixty() const {return zeroToSixty;}
    double getquarterMile() const {return quarterMile;}

    void setEngine(const Engine& engine) {this->engine = engine;}
    void setTopSpeed(double topSpeed) {this->topSpeed = topSpeed;}
    void setZeroToSixty(double zeroToSixty) {this->zeroToSixty = zeroToSixty;}
    void setquarterMile(double quarterMile) {this->quarterMile = quarterMile;}

    void validate() const override{
        SUV::validate();
        if (topSpeed < 0 || zeroToSixty < 0) {
            throw InvalidValueException("Invalid value in PerformanceCar");
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const PerformanceCar& car){
        car.display();
        return os;
    }

    friend std::istream& operator>>(std::istream& is, PerformanceCar& car){
        is >> static_cast<SUV&>(car);
        std::cout << "Enter Engine Details:\n";
        is >> car.engine;
        std::cout << "Enter Top Speed (mph): ";
        is >> car.topSpeed;
        std::cout << "Enter 0-60 mph Time (seconds): ";
        is >> car.zeroToSixty;
        std::cout << "Enter Quarter Mile Time (seconds): ";
        is >> car.quarterMile;
        return is;
    }
};

//Subclass: LuxurySedan
class LuxurySedan : public Sedan {
private:
    std::string interiorMaterial;
    bool hasMassageSeats;
    std::string infotainmentSystem;
    std::string paintColor;

public:
    LuxurySedan(int id = 0, const std::string& make = "", const std::string& model = "", int year = 0, double price = 0.0, int trunkSize = 0, double fuelEfficiency = 0.0, const std::string& interiorMaterial = "", bool hasMassageSeats = false, const std::string& infotainmentSystem = "", const std::string& paintColor = "")
        : Sedan(id, make, model, year, price, trunkSize, fuelEfficiency), interiorMaterial(interiorMaterial), hasMassageSeats(hasMassageSeats), infotainmentSystem(infotainmentSystem), paintColor(paintColor) {}

    void display() const override{
        Sedan::display();
        std::cout << "Interior Material: " << interiorMaterial << std::endl;
        std::cout << "Massage Seats: " << (hasMassageSeats ? "Yes" : "No") << std::endl;
        std::cout << "Infotainment System: " << infotainmentSystem << std::endl;
        std::cout << "Paint Color: " << paintColor << std::endl;
    }

    void readFromBinary(std::ifstream& in) override{
        Sedan::readFromBinary(in);
        size_t size;
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        interiorMaterial.resize(size);
        in.read(&interiorMaterial[0], size);
        in.read(reinterpret_cast<char*>(&hasMassageSeats), sizeof(hasMassageSeats));
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        infotainmentSystem.resize(size);
        in.read(&infotainmentSystem[0], size);
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        paintColor.resize(size);
        in.read(&paintColor[0], size);
    }

    void writeToBinary(std::ofstream& out) const override{
        Sedan::writeToBinary(out);
        size_t size = interiorMaterial.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        out.write(interiorMaterial.c_str(), size);
        out.write(reinterpret_cast<const char*>(&hasMassageSeats), sizeof(hasMassageSeats));
        size = infotainmentSystem.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        out.write(infotainmentSystem.c_str(), size);
        size = paintColor.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        out.write(paintColor.c_str(), size);
    }

    std::string getInteriorMaterial() const {return interiorMaterial;}
    bool getHasMassageSeats() const {return hasMassageSeats;}
    std::string getInfotainmentSystem() const {return infotainmentSystem;}
    std::string getPaintColor() const {return paintColor;}

    void setInteriorMaterial(const std::string& interiorMaterial) {this->interiorMaterial = interiorMaterial;}
    void setHasMassageSeats(bool hasMassageSeats) {this->hasMassageSeats = hasMassageSeats;}
    void setInfotainmentSystem(const std::string& infotainmentSystem) {this->infotainmentSystem = infotainmentSystem;}
    void setPaintColor(const std::string& paintColor) {this->paintColor = paintColor;}

    void validate() const override{
        Sedan::validate();
        if (interiorMaterial.empty() || infotainmentSystem.empty()){
            throw InvalidValueException("Invalid value in LuxurySedan");
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const LuxurySedan& car){
        car.display();
        return os;
    }

    friend std::istream& operator>>(std::istream& is, LuxurySedan& car){
        is >> static_cast<Sedan&>(car);
        is.ignore();
        std::cout << "Enter Interior Material: ";
        std::getline(is, car.interiorMaterial);
        std::cout << "Has Massage Seats (0 for No, 1 for Yes): ";
        is >> car.hasMassageSeats;
        is.ignore();
        std::cout << "Enter Infotainment System: ";
        std::getline(is, car.infotainmentSystem);
        std::cout << "Enter Paint Color: ";
        std::getline(is, car.paintColor);
        return is;
    }
};

//Test driver program
int main() {
    try {
        char choice;
        do {
            std::cout << "Choose an option:" << std::endl;
            std::cout << "1. Enter Sedan" << std::endl;
            std::cout << "2. Enter SUV" << std::endl;
            std::cout << "3. Enter Performance Car" << std::endl;
            std::cout << "4. Enter Luxury Sedan" << std::endl;
            int option;
            std::cin >> option;

            if (option == 1){
                Sedan sedan;
                std::cin >> sedan;
                std::ofstream outFile("sedan.dat", std::ios::binary);
                sedan.writeToBinary(outFile);
                outFile.close();

                Sedan loadedSedan;
                std::ifstream inFile("sedan.dat", std::ios::binary);
                loadedSedan.readFromBinary(inFile);
                inFile.close();
                std::cout << "Loaded Sedan Data:\n" << loadedSedan;
            } 
            else if (option == 2){
                SUV suv;
                std::cin >> suv;
                std::ofstream outFile("suv.dat", std::ios::binary);
                suv.writeToBinary(outFile);
                outFile.close();

                SUV loadedSUV;
                std::ifstream inFile("suv.dat", std::ios::binary);
                loadedSUV.readFromBinary(inFile);
                inFile.close();
                std::cout << "Loaded SUV Data:\n" << loadedSUV;
            } 
            else if (option == 3){
                PerformanceCar car;
                std::cin >> car;
                std::ofstream outFile("performance_car.dat", std::ios::binary);
                car.writeToBinary(outFile);
                outFile.close();

                PerformanceCar loadedCar;
                std::ifstream inFile("performance_car.dat", std::ios::binary);
                loadedCar.readFromBinary(inFile);
                inFile.close();
                std::cout << "Loaded Performance Car Data:\n" << loadedCar;
            } 
            else if (option == 4){
                LuxurySedan car;
                std::cin >> car;
                std::ofstream outFile("luxury_sedan.dat", std::ios::binary);
                car.writeToBinary(outFile);
                outFile.close();

                LuxurySedan loadedCar;
                std::ifstream inFile("luxury_sedan.dat", std::ios::binary);
                loadedCar.readFromBinary(inFile);
                inFile.close();
                std::cout << "Loaded Luxury Sedan Data:\n" << loadedCar;
            } 
            else {
                std::cout << "Invalid option! Please try again." << std::endl;
            }
            std::cout << "Do you want to enter another car? (y/n): ";
            std::cin >> choice;
        } 
            while (choice == 'y');

    } 
    catch (const std::exception& e){
        std::cerr << "Error: " << e.what() << '\n';
    }
    std::cout << "Bye, Bye! Thank you for using our program!" << std::endl;
    return 0;
}
