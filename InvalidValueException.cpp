#include "InvalidValueException.h"

InvalidValueException::InvalidValueException(const std::string& message) : message(message) {}

const char* InvalidValueException::what() const noexcept {
    return message.c_str();
}
