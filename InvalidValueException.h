#ifndef INVALIDVALUEEXCEPTION_H
#define INVALIDVALUEEXCEPTION_H

#include <stdexcept>

class InvalidValueException : public std::runtime_error {
public:
    InvalidValueException(const std::string& message) : std::runtime_error(message) {}
};

#endif // INVALIDVALUEEXCEPTION_H
