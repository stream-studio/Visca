#include <iostream>
#include <Visca.hpp>

int main(){
    std::cout << "Visca IP demo" << std::endl;
    Visca v("192.168.1.45", 45678);
    v.panTilt(10, 10);
}