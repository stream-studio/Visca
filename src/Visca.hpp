#ifndef __VISCA_HPP__
#define __VISCA_HPP__

#include <stdint.h>
#include <string>
#include <netinet/in.h>

class Visca{
    private:
        int mSocketFD;
        sockaddr_in mCameraAddress;
        uint32_t mSequenceNumber;

        void sendCommand(const char* command, const bool isQuery, const uint16_t size);

    public:
        Visca(std::string address, const uint32_t port);
        void goHome();
        void zoom(const int8_t speed);
        void panTilt(const int8_t panSpeed, const int8_t tiltSpeed);
        void presetSet(const uint8_t preset);
        void presetCall(const uint8_t preset);
};

#endif