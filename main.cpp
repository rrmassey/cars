#include <iostream>
#include "sedan.h"
#include "suv.h"
#include "performancecar.h"
#include "luxurysedan.h"

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
