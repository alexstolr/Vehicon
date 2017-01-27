/**
 * @brief This class provides License plate recognition.
 * @author Alex Stoliar (alexstolr@gmail.com)
 * @date 08/01/2017
 */

#ifndef VEHICON_LPR_H
#define VEHICON_LPR_H

#include "alpr.h"                           /* http://doc.openalpr.com/index.html */
#include "opencv2/opencv.hpp"               /* http://docs.opencv.org/2.4/index.html */
#include <thread>

class Lpr {

public:
    Lpr();
    virtual ~Lpr();

    std::string findPlates();
    void setFoundPLate(bool foundPLate);
    bool isFoundPLate() const;

private:
    alpr::Alpr openalpr;
    bool foundPLate;

    std::string runOpenALPR();
    void initOpenALPR();

    std::string runOpenAlprOnStill();
    std::string runOpenAlprOnVideo();
    std::string runOPenAlprOnImgFile();
};


#endif //VEHICON_LPR_H
