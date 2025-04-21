# Car Management Program in C++

This C++ program provides a system for managing different types of cars, including Sedans, SUVs, Performance Cars, and Luxury Sedans. It utilizes inheritance and polymorphism to create a flexible and extensible car management system. The program allows users to input car details and saves them to binary files, which can then be loaded and displayed.

## Features

* **Object-Oriented Design:** Leverages classes and inheritance (`Car` base class with derived `Sedan`, `SUV`, `PerformanceCar`, and `LuxurySedan` classes) to model different car types and their specific attributes.
* **Polymorphism:** Demonstrates polymorphic behavior through virtual functions (`display`, `readFromBinary`, `writeToBinary`, `validate`) allowing for consistent handling of different car types.
* **Data Persistence:** Implements binary file I/O (`std::ofstream` and `std::ifstream`) to save and load car data, ensuring data persistence between program executions.
* **Exception Handling:** Includes a custom exception class (`InvalidValueException`) to handle invalid input values for car attributes, promoting robust data integrity.
* **Input Validation:** Each car type has a `validate()` method (though the main input is not directly validated in `main`) that checks for logical inconsistencies in the data (e.g., negative values where they are not allowed).
* **Composite Class:** Utilizes a `Engine` class as a composite within the `PerformanceCar` class to represent the engine specifications.
* **User Interaction:** Provides a simple command-line interface to choose the type of car to enter and allows for entering multiple car records.
