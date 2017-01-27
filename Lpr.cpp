/**
 * @brief This class provides License plate recognition.
 * OpenALPR: http://doc.openalpr.com/bindings.html
 * @author Alex Stoliar (alexstolr@gmail.com)
 * @date 08/01/2017
 */

#include "Lpr.h"

#define MAX_PLATE_NUMBER (50)
#define OPENALPRCONF "libs/openalpr/src/config/openalpr.conf"
#define CAMERA_MODE "TEST"//"STILL", "VIDEO", "TEST"
#define CONFIDENCE_LEVEL 90


Lpr::Lpr() : foundPLate(false),openalpr(alpr::Alpr("eu", OPENALPRCONF))
{
    std::cout<<__FUNCTION__ << ": initiated Lpr"  << std::endl;
    std::cout<< "LPR working mode: " << (std::string)CAMERA_MODE << "\n" << std::endl;
}

Lpr::~Lpr()
{

}

std::string Lpr::findPlates()
{
    std::cout << "Looking for plates..." << std::endl;
    return runOpenALPR();
    //std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

bool Lpr::isFoundPLate() const
{
    return foundPLate;
}

void Lpr::setFoundPLate(bool foundPLate)
{
    Lpr::foundPLate = foundPLate;
}

void Lpr::initOpenALPR()
{
    // Initialize the library using EU style license plates.
    // You can use other countries/regions as well (for example: "eu", "au", or "kr")
    // ALEX: I did this in the constructor

    // Optionally specify the top N possible plates to return (with confidences).  Default is 10
    openalpr.setTopN(1);

    // Optionally, provide the library with a region for pattern matching.  This improves accuracy by
    // comparing the plate text with the regional pattern.
    openalpr.setDefaultRegion("md");

    // Make sure the library loaded before continuing.
    // For example, it could fail if the config/runtime_data is not found
    if (openalpr.isLoaded() == false)
    {
        std::cerr << "Error loading OpenALPR" << std::endl;
    }
}

std::string Lpr::runOpenALPR()
{
    if(CAMERA_MODE=="STILL")
    {
        return runOpenAlprOnStill();
    }
    else if(CAMERA_MODE=="VIDEO")
    {
        return runOpenAlprOnVideo();
    }
    else //test
    {
        return runOPenAlprOnImgFile();
    }
}

std::string Lpr::runOpenAlprOnStill()
{

}

std::string Lpr::runOpenAlprOnVideo()
{

}

std::string Lpr::runOPenAlprOnImgFile()
{
    alpr::AlprResults results = openalpr.recognize("/home/alex/Workspace/Vehicon/include/images/3.jpg");
    //Need only one plate for POC
    alpr::AlprPlateResult plate = results.plates[0];
    alpr::AlprPlate candidate = plate.topNPlates[0];
    if(candidate.overall_confidence >= CONFIDENCE_LEVEL)
    {
        std::string peerPlate = candidate.characters;
        std::cout << "License Plate: " << peerPlate << "\t confidence: " << candidate.overall_confidence;
        std::cout << "\t pattern_match: " << candidate.matches_template << std::endl;
        foundPLate = true;
        return peerPlate;
    }
    return "";
}




