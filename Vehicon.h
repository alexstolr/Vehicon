/**
 * @brief Vehicon identifies vehicles on the road, starts a spontenious connection
 * and tries to authenticate the identity of the other vehicle.
 * on the other hand, it awaits for incoming connection request.
 * once a request has arrived, it tries to authenticate the other vehicle identity.
 * Once authentication is achieved, a secure session is initiated.
 * @author Alex Stoliar (alexstolr@gmail.com)
 * @date 08/01/2017
 */

#ifndef VEHICON_VEHICON_H
#define VEHICON_VEHICON_H

#include <iostream>
#include <thread>
#include "Lpr.h"
#include "Udplink.h"
#include "Protocol.h"
#include "Vssl.h"

class Vehicon {

private:

    bool terminate;
    Vehicle * vehicle;
    Vssl * vssl;
    Lpr * lpr;
    Udplink * udplink;
    Protocol * protocol;


    //Functions
    void init();
    void handleIncomingConnections();
    void handleOutgoingConnections();


public:
    Vehicon();
    virtual ~Vehicon();

    bool isTerminate() const;
    void setTerminate(bool terminate);

    void runCameraStream();
};


#endif //VEHICON_VEHICON_H
