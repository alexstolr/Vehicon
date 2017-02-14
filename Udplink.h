/**
 * @brief Handles incoming datagrams and writing data to peers.
 * @author Alex Stoliar (alexstolr@gmail.com)
 * @date 08/01/2017
 * @details: http://www.linuxhowtos.org/C_C++/socket.htm
 *           http://www.binarytides.com/programming-udp-sockets-c-linux/
 */

#ifndef VEHICON_UDPLINK_H
#define VEHICON_UDPLINK_H

#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h> //  sockaddr_in
#include <stdio.h>
#include  <assert.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define UDP_LOCAL_PORT 16007
#define UDP_DEST_PORT 16008
#define BUF_SIZE 256


class Udplink {
public:
    Udplink();
    virtual ~Udplink();

    int readDatagram();
    int writeDatagram(char * datagram);

private:
    int udpSoc; //  udp socket file descriptor
    //char dataGram[1024];
    int broadcast = 1;
    struct sockaddr_in locAddr, dstAddr;
    char buffer[BUF_SIZE] = {0};   //Stores received data. Initiated to 0's
};



#endif //VEHICON_UDPLINK_H
