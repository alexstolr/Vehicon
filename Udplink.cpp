//
// Created by alex on 08/01/17.
//

#include "Udplink.h"

#include <iostream>
#include <thread>

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
    unsigned slen=sizeof(sockaddr);
    std::cout << __FUNCTION__ << ": waiting for datagram" << std::endl;
    int bytesRead = recvfrom(udpSoc, dataGram, sizeof(dataGram)-1, 0, (sockaddr *)&dstAddr, &slen);
    printf("message received: %s\n", dataGram);
    return bytesRead;
}

int Udplink::writeDatagram(char * datagram)
{
    std::cout << "Trying to receive datagram..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    return sendto(udpSoc, datagram, sizeof(datagram)-1, 0, (struct sockaddr*)&locAddr, sizeof(struct sockaddr_in));
}
