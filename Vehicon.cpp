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
    std::cout<<__FUNCTION__ << ": initiated Vehicon \n"  << std::endl;
    lpr = new Lpr();
    udplink = new Udplink();
    protocol = new Protocol(udplink);
    init();
}

Vehicon::~Vehicon()
{
    delete lpr;
    delete protocol;
    delete udplink;

}

/**
 * Runs two threads -
 * 1. Thread for trying to recognize license plate from camera and try start a connection.
 * 2. Try get a datagram from other Vehicle that tries to start a connection with us.
 */
void Vehicon::init()
{
    std::thread lprThread (&Vehicon::handleOutgoingConnections,this);
    std::thread udpListenThread (&Vehicon::handleIncomingConnections,this);
    lprThread.join();
    udpListenThread.join();

}

bool Vehicon::isTerminate() const
{
    return terminate;
}

void Vehicon::setTerminate(bool terminate)
{
    this->terminate = terminate;
}

void Vehicon::handleOutgoingConnections()
{
    std::string tmpPlate = "";
    while(!lpr->isFoundPLate())
    {
        if((tmpPlate = lpr->findPlates()) != "")
        {
            std::cout << "Plate number: " << tmpPlate << std::endl;
            char * tmpPlateChar = new char[tmpPlate.length() + 1];
            strcpy(tmpPlateChar, tmpPlate.c_str());
            protocol->startCommunication(tmpPlateChar);
            delete [] tmpPlateChar;
        }
    }
}

void Vehicon::handleIncomingConnections()
{
    while(!udplink->readDatagram())
    {
//        if(udplink->readDatagram())
//        {
//            std::cout << "Waiting for data over udp" << std::endl;
//        }
//        else
//        {
//            std::cout << "didnt get dataover udp" << std::endl;
//        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
}

