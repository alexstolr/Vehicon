/**
 * @brief This class provides License plate recognition.
 * @author Alex Stoliar (alexstolr@gmail.com)
 * @date 08/01/2017
 */

#include "Lpr.h"

#include <iostream>


Lpr::Lpr() : foundPLate(false)
{
    std::cout<<__FUNCTION__ << ": initiated Lpr"  << std::endl;
}

Lpr::~Lpr()
{

}

void Lpr::findPlates()
{
    std::cout << "Looking for plates..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

bool Lpr::isFoundPLate() const
{
    return foundPLate;
}

void Lpr::setFoundPLate(bool foundPLate)
{
    Lpr::foundPLate = foundPLate;
}
