#ifndef SUV_H
#define SUV_H

#include "car.h"

class SUV : public Car<int> {
private:
    int groundClearance;  //in inches
    double cargoCapacity;  //in cubic feet
    bool fourWheelDrive;
    double towingCapacity;  //in pounds

public:
    SUV(int id = 0, const std::string& make = "", const std::string& model = "", int groundClearance = 0, double cargoCapacity = 0.0, bool fourWheelDrive = false, double towingCapacity = 0.0);

    void display() const override;
    void readFromBinary(std::ifstream& in) override;
    void writeToBinary(std::ofstream& out) const override;

    int getGroundClearance() const;
    double getCargoCapacity() const;
    bool getFourWheelDrive() const;
    double getTowingCapacity() const;

    void setGroundClearance(int groundClearance);
    void setCargoCapacity(double cargoCapacity);
    void setFourWheelDrive(bool fourWheelDrive);
    void setTowingCapacity(double towingCapacity);

    void validate() const override;

    friend std::ostream& operator<<(std::ostream& os, const SUV& suv);
    friend std::istream& operator>>(std::istream& is, SUV& suv);
};

#endif // SUV_H
