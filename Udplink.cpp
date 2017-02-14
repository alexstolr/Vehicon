/**
 * @brief Handles incoming datagrams and writing data to peers.
 * @author Alex Stoliar (alexstolr@gmail.com)
 * @date 08/01/2017
 * @details: http://www.linuxhowtos.org/C_C++/socket.htm
 *           http://www.binarytides.com/programming-udp-sockets-c-linux/
 */

#include "Udplink.h"

#include <iostream>
#include <thread>
#define DEBUG_UDPLINK

Udplink::Udplink()
{
    std::cout<<__FUNCTION__ << ": initiated Udplink"  << std::endl;
    if((udpSoc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) //was PF
    {
        perror("cannot create socket");
    }

    memset(&locAddr, 0, sizeof(locAddr));
    locAddr.sin_family = AF_INET;
    locAddr.sin_addr.s_addr = INADDR_ANY;
    locAddr.sin_port = htons(UDP_LOCAL_PORT);

    if (bind(udpSoc,(struct sockaddr *)&locAddr, sizeof(struct sockaddr)) == 0)
    {
        printf("binding local address succesful!\n");
        memset(&dstAddr, 0, sizeof(dstAddr));
        dstAddr.sin_family = AF_INET;
        dstAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //target ip
        dstAddr.sin_port = htons(UDP_DEST_PORT);
    }
    else
    {
        perror("error bind failed\n");
    }
}

Udplink::~Udplink() {

}

int Udplink::readDatagram() {
    char datagram[32] = {0};
    unsigned slen=sizeof(sockaddr);
    //int bytesRead = 0;
    int bytesRead = recvfrom(udpSoc, datagram, sizeof(datagram)-1, 0, (sockaddr *)&dstAddr, &slen);
    //int bytesRead = recv(udpSoc, datagram, 32, 0);
//    for (int j = 0; j < 25; ++j) {
//        bytesRead += recvfrom(udpSoc, &datagram[j], 1, 0, (sockaddr *)&dstAddr, &slen);
//
//    }
    std::cout << sizeof(datagram) << std::endl;
#ifdef DEBUG_UDPLINK
    printf("MSG received: ");
    for (int i = 0; i < 25; i++)
    {
        printf("%0X ",(uint8_t)datagram[i]);
    }
    printf("\n");
#endif
    return bytesRead;
}

int Udplink::writeDatagram(char * datagram)
{
    //std::cout << "Writing data: " << datagram << std::endl;
    //std::this_thread::sleep_for(std::chrono::milliseconds(5000));
#ifdef DEBUG_UDPLINK
    printf("MSG sent: ");
    for (int i = 0; i < 25; i++)
    {
        printf("%0X ",(uint8_t)datagram[i]);
    }
    printf("\n");
#endif
    return sendto(udpSoc, datagram, 25/*sizeof(datagram)-1*/, 0, (struct sockaddr*)&locAddr, sizeof(struct sockaddr_in));
}
