/**
 * @brief Vehicon identifies vehicles on the road, starts a spontenious connection
 * and tries to authenticate the identity of the other vehicle.
 * on the other hand, it awaits for incoming connection request.
 * once a request has arrived, it tries to authenticate the other vehicle identity.
 * Once authentication is achieved, a secure session is initiated.
 * @author Alex Stoliar (alexstolr@gmail.com)
 * @date 08/01/2017
 */


#include "Vehicon.h"
#include "Lpr.h"

Vehicon::Vehicon() : terminate(false)
{
    std::cout<<"Initiated Vehicon!" << std::endl;
    lpr = new Lpr();
    udplink = new Udplink();
    init();
}

Vehicon::~Vehicon()
{
    delete lpr;
}

void Vehicon::init()
{
    std::thread t1(&Vehicon::handleIncomingConnections, this);
    //std::thread lprThread (&this->handleOutgoingConnections);
    //std::thread udpListenThread (&this->handleIncomingConnections);
    //lprThread.join();
    //udpListenThread.join();

}

bool Vehicon::isTerminate() const
{
    return terminate;
}

void Vehicon::setTerminate(bool terminate)
{
    Vehicon::terminate = terminate;
}

void Vehicon::handleOutgoingConnections()
{
    while(!lpr->isFoundPLate())
    {
        lpr->findPlates();
    }
}

void Vehicon::handleIncomingConnections()
{
    while(!udplink->readDatagram())
    {

    }
}

