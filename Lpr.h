/**
 * @brief This class provides License plate recognition.
 * @author Alex Stoliar (alexstolr@gmail.com)
 * @date 08/01/2017
 */

#ifndef VEHICON_LPR_H
#define VEHICON_LPR_H


#include <thread>

class Lpr {

public:
    Lpr();
    virtual ~Lpr();

    void findPlates();

private:
    bool foundPLate;
public:
    void setFoundPLate(bool foundPLate);

public:
    bool isFoundPLate() const;

};


#endif //VEHICON_LPR_H
