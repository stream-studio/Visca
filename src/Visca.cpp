#include "Visca.hpp"
#include "exceptions/ViscaNetworkException.hpp"
#include "exceptions/ViscaValueException.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <arpa/inet.h>

Visca::Visca(std::string address, const uint32_t port){
  mSocketFD = socket(AF_INET,
                    SOCK_DGRAM,
                    IPPROTO_UDP);
  if (mSocketFD == 0) {
    throw new ViscaNetworkException("Couldn't create socket");
  }


  sockaddr_in addr;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);
  addr.sin_family = AF_INET;  
  
  bind(mSocketFD, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
  
  mCameraAddress.sin_family = AF_INET;
  mCameraAddress.sin_port = htons(port);

  if (inet_pton(AF_INET, address.c_str(), &mCameraAddress.sin_addr) <= 0){
    throw new ViscaNetworkException("Incorrect address format");
  }


  /*listenAddr = bind(socketFD, INADDR_ANY, );
  G_SOCKET_ADDRESS(g_inet_socket_address_new(g_inet_address_new_any(G_SOCKET_FAMILY_IPV4), port));
  cameraAddr = G_SOCKET_ADDRESS(g_inet_socket_address_new(g_inet_address_new_from_string(address.c_str()), port));

  if (g_socket_bind(socket, listenAddr, FALSE, &error) == FALSE) {
    throw new ViscaNetworkException("Couldn't bin udp socket");
  }*/
  

}

void Visca::sendCommand(const char* command, const bool isQuery, const uint16_t size){

  // Malloc size (header (2) + size (2) + sequence number (4) )

  mSequenceNumber++;
  uint16_t payloadSize = size + 2;
  const char header[10] = {'\x01','\x00', static_cast<char>((payloadSize & 0x0000ff00) >> 8), static_cast<char>(payloadSize & 0x000000ff), static_cast<char>((mSequenceNumber & 0xff000000) >> 24), static_cast<char>((mSequenceNumber & 0x00ff0000) >> 16), static_cast<char>((mSequenceNumber & 0x0000ff00) >> 8), static_cast<char>(mSequenceNumber & 0x000000ff), '\x81', '\x01'};
  const size_t messageSize = 8 + payloadSize + 1;
  char* message = (char*) malloc(messageSize);

  // message allocation HEADER + CONTENT + END MARK
  memcpy(message, header , 10);
  memcpy(message + 10, command, size);
  message[messageSize-1] = '\xFF';

  sendto(mSocketFD, message, messageSize, 0, reinterpret_cast<const sockaddr*>(&mCameraAddress), sizeof(mCameraAddress));
  free(message);

}

void Visca::goHome(){
  const char message[2] = {'\x06', '\x04'};
  sendCommand(message, false, 2);
}

void Visca::zoom(const int8_t speed){
  
  if ( abs(speed) > 7 ){
    throw new ViscaValueException("Speed must not exceed 7");
  }

  char direction;
  if ( speed == 0 ){
    direction = '\x00';
  }
  else if (speed > 0){
    direction = '\x02';
  }
  else {
    direction = '\x03';
  }

  const char message[3] = {'\x04', '\x07', static_cast<char>( ( static_cast<char>(abs(speed) - '0' ) << 4 ) | ( direction - '0' )) };
  sendCommand(message, false, 3);

}

void Visca::presetCall(uint8_t preset){
    if (preset > 15){
          throw new ViscaNetworkException("Preset must not exceed 15");
    }
    const char message[4] = {'\x04', '\x3F', '\x02', static_cast<char>( ('0' << 4) | ( preset - '0' ) )};
    sendCommand(message, false, 4);   
}

void Visca::presetSet(uint8_t preset){
    if (preset > 15){
      throw new ViscaNetworkException("Preset must not exceed 15");
    }
    const char message[4] = {'\x04', '\x3F', '\x01', static_cast<char>( ('0' << 4) | ( preset - '0' ) ) };
    sendCommand(message, false, 4);
}

static char getDirection(int8_t speed){
  if ( speed == 0 ){
    return '\x03';
  }
  else if (speed > 0){
    return '\x02';
  }
  else {
    return '\x01';
  }

}

void Visca::panTilt(const int8_t panSpeed, const int8_t tiltSpeed){
  
  const char message[6] = {'\x06', '\x01', static_cast<char>(abs(panSpeed)), static_cast<char>(abs(tiltSpeed)), getDirection(panSpeed), getDirection(tiltSpeed)};
  sendCommand(message, false, 6);

}

