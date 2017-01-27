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

#include "Protocol.h"

//#define DEBUG_PROTOCOL

Protocol::Protocol(Udplink * udplink)
{
    crc = new Crc32();
    vehicleSelf = new Vehicle();
    this->udplink = udplink;
    sequence = 0;
}

Protocol::~Protocol()
{
    delete crc;
    delete vehicleSelf;
}

void Protocol::init()
{

}


void Protocol::msgPack(int opCode,char * plateNum)
{
    switch (opCode)
    {
        case INIT_VERIFICATION:
            initVerify();
            break;
        case CONT_VERIFICATION:
            break;
        default:
            break;
    }

}

/**
 * @brief Alv::initVerify is called when a peer vehicle is recognized on the road.
 * this function starts the process of verification of peer via ca and attributes
 * by sending the recognized peer an INIT_VERIFICATION MESSAGE which includes
 * local certificate & public key.
 */
void Protocol::initVerify()
{
    uint8_t buf[25] = {0};
    buf[0] = 0xFE;
    buf[1] = (sequence >> 8) & 0xFF;
    buf[2] = sequence & 0xFF;
    buf[3] = 0x11; // 17 = opcode + cert + public key
    buf[4] = INIT_VERIFICATION;
    for (int i = 0; i < 8; i++)
    {
        buf[i + 5] = cert[i];
        buf[i + 13] = pubKey[i];
    }
    uint32_t crcVal = crc->calcCrc((char *)buf,21);
    buf[21] = (crcVal >> 24) & 0xFF;
    buf[22] = (crcVal >> 16) & 0xFF;
    buf[23] = (crcVal >> 8) & 0xFF;
    buf[24] = crcVal & 0xFF;
    sequence++;
#ifdef DEBUG_PROTOCOL
    printf("MSG: ");
    for (int i = 0; i < 25; i++)
    {
        printf("%X ",buf[i]);
    }
    printf("\n");
#endif
}

/**
 * @brief Alv::contVerify is called after receiving a initVerify message from the peer
 * and sucessfuly verifying peer identity.
 * this function continues the process of verification of peer via ca and attributes
 * by sending the verified peer an CONT_VERIFICATION MESSAGE which includes
 * local certificate & public key.
 */
void Protocol::contVerify()
{
    sequence = 41378;
    uint8_t buf[25] = {0};
    buf[0] = 0xFE;
    buf[1] = (sequence >> 8) & 0xFF;
    buf[2] = sequence & 0xFF;
    buf[3] = 0x11; // 17 = opcode + cert + public key
    buf[4] = CONT_VERIFICATION;
    for (int i = 0; i < 8; i++)
    {
        buf[i + 5] = cert[i];
        buf[i + 13] = pubKey[i];
    }
    uint32_t crcVal = crc->calcCrc((char *)buf,21);
    buf[21] = (crcVal >> 24) & 0xFF;
    buf[22] = (crcVal >> 16) & 0xFF;
    buf[23] = (crcVal >> 8) & 0xFF;
    buf[24] = crcVal & 0xFF;
    sequence++;
#ifdef DEBUG_PROTOCOL
    printf("MSG: ");
    for (int i = 0; i < 25; i++)
    {
        printf("%X ",buf[i]);
    }
    printf("\n");
#endif
}

void Protocol::msgUnpack(char *msg)
{

}

void Protocol::startCommunication(char * plateNum)
{
    msgPack(INIT_VERIFICATION,plateNum);
}
