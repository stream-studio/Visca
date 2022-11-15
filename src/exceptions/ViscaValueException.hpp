#ifndef __VISCA_VALUE_EXCEPTION_HPP__
#define __VISCA_VALUE_EXCEPTION_HPP__

#include <iostream>
#include <string>
using namespace std;

class ViscaValueException : public std::exception {
    private:
        std::string message;
    public:
        ViscaValueException(std::string message);

        const char *what () const noexcept override{
            return message.c_str();
        }
};

#endif