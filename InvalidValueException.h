#ifndef INVALIDVALUEEXCEPTION_H
#define INVALIDVALUEEXCEPTION_H

#include <string>
#include <exception>

class InvalidValueException : public std::exception {
private:
    std::string message;
public:
    InvalidValueException(const std::string& message);
    const char* what() const noexcept override;
};

#endif // INVALIDVALUEEXCEPTION_H
