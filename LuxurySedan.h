#ifndef LUXURYSEDAN_H
#define LUXURYSEDAN_H

#include "Car.h"

class LuxurySedan : public Car<int> {
private:
    int year;
    double price;
    std::string features;
public:
    LuxurySedan(int id = 0, const std::string& make = "", const std::string& model = "", int year = 0, double price = 0.0, const std::string& features = "");

    void display() const override;
    void readFromBinary(std::ifstream& in) override;
    void writeToBinary(std::ofstream& out) const override;

    int getYear() const;
    double getPrice() const;
    std::string getFeatures() const;

    void setYear(int year);
    void setPrice(double price);
    void setFeatures(const std::string& features);

    void validate() const override;

    friend std::ostream& operator<<(std::ostream& os, const LuxurySedan& car);
    friend std::istream& operator>>(std::istream& is, LuxurySedan& car);
};

#endif // LUXURYSEDAN_H
