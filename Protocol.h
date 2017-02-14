/**
 * @brief ALV (Autonomous Land Vehicle) Authentication Protocol
 *
 * Protocol definition:
 * B0 = FE (msg start)
 * B1 = sequence number (each side has different sequence number)
 * B2 = length
 * B3 = opcode
 * B4 - Bn-4 = Data
 * Bn-3 - Bn = CRC
 *
 * @authors Alex Stoliar (alexstolr@gmail.com)
 * @date 23/09/16
 */

#ifndef VEHICON_PROTOCOL_H
#define VEHICON_PROTOCOL_H


#include "Crc32.h"
#include "Udplink.h"
#include "Vehicle.h"

class Protocol {

public:
    Protocol(Udplink * udplink);
    virtual ~Protocol();

    void startCommunication(char * plateNUmber);

private:
    Udplink * udplink;
    Vehicle * vehicleSelf;
    Crc32 * crc;
    char * cert;
    char * pubKey;

    uint16_t sequence;

    enum Opcodes
    {
        INIT_VERIFICATION = (uint8_t) 0x01,
        CONT_VERIFICATION = (uint8_t) 0x02
    };

    void init();


    void msgPack(int opCode, char * plateNUm);
    void initVerify(char * buf, char * plateNum);
    void contVerify();
    void msgUnpack(char * msg);
};


#endif //VEHICON_PROTOCOL_H
