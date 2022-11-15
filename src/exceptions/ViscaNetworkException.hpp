#ifndef __VISCA_NETWORK_EXCEPTION_HPP__
#define __VISCA_NETWORK_EXCEPTION_HPP__

#include <iostream>
#include <string>
using namespace std;

class ViscaNetworkException : public std::exception {
    private:
        std::string message;
    public:
        ViscaNetworkException(std::string message);

        const char *what() const noexcept override{
            return message.c_str();
        }
};

#endif