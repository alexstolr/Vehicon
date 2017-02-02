/**
 * @brief This class provides License plate recognition.
 * OpenALPR: http://doc.openalpr.com/bindings.html
 * @author Alex Stoliar (alexstolr@gmail.com)
 * @date 08/01/2017
 */

#include "Lpr.h"

#define MAX_PLATE_NUMBER (50)
#define OPENALPRCONF "libs/openalpr/src/config/openalpr.conf"
#define CAMERA_MODE "VIDEO"//"STILL", "VIDEO", "TEST"
#define CAMERA_STREAM
#define CONFIDENCE_LEVEL 90
#define FRAME_TO_PIC_RATIO 17 // 30*17 ~= 500 --> save to file every half a second


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

/**
 * For now i am saving the frame as a local image and runnung alpr on the image
 * until i figure out how to run openalpr on frame in real time.
 * @return
 */
std::string Lpr::runOpenAlprOnStill()
{
    cv::VideoCapture cap(1); // open usb camera
    if(!cap.isOpened())  // check if we succeeded
    {
        std::cerr << "Error Opening Video Camera" << std::endl;
    }
    std::string tmpStr = "";
    cv::Mat edges;
    cv::namedWindow("edges",1);
    int frameToPicRatio = 0;
    while(!foundPLate)
    {
        frameToPicRatio++;
        frameToPicRatio = frameToPicRatio%FRAME_TO_PIC_RATIO;
        cv::Mat frame;
        cap >> frame; // get a new frame from camera
        //cvtColor(frame, edges, 0);
        //GaussianBlur(edges, edges, cv::Size(7,7), 1.5, 1.5);
        //Canny(edges, edges, 0, 30, 3);
        if(frameToPicRatio == 1)
        {
            cv::imwrite("/home/alex/Workspace/Vehicon/include/images/tmp.jpg", frame); //TODO figure out better path
        }
        tmpStr = runOPenAlprOnImgFile();
        if(tmpStr != "")
            break;
        std::cout << tmpStr << std::endl;
        cv::imshow("edges", frame);
        if(cv::waitKey(30) >= 0) break;
    }

}

std::string Lpr::runOpenAlprOnVideo()
{
    cv::VideoCapture cap(1); // open usb camera
    if(!cap.isOpened())  // check if we succeeded
    {
        std::cerr << "Error Opening Video Camera" << std::endl;
    }
    std::string tmpStr = "";
    int frameToPicRatio = 0;
    cv::Mat edges;
    cv::namedWindow("edges",1);
    while(!foundPLate)
    {
        frameToPicRatio++;
        frameToPicRatio = frameToPicRatio%FRAME_TO_PIC_RATIO;
        cv::Mat frame;
        cap >> frame; // get a new frame from camera
        if(frameToPicRatio == 1)
        {
            alpr::AlprResults results = openalpr.recognize(frame);
            if(results.plates.size() != 0)
            {
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
        }
        //cvtColor(frame, edges, 0);
        //GaussianBlur(edges, edges, cv::Size(7,7), 1.5, 1.5);
        //Canny(edges, edges, 0, 30, 3);
        cv::imshow("edges", frame);
        if(cv::waitKey(30) >= 0) break;
    }

}

std::string Lpr::runOPenAlprOnImgFile()
{
    alpr::AlprResults results = openalpr.recognize("/home/alex/Workspace/Vehicon/include/images/tmp.jpg"); //TODO figure out better path
    //Need only one plate for POC
    if(results.plates.size() != 0)
    {
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
    return "";

}

void Lpr::runCameraStream()
{
    cv::VideoCapture cap(1); // open usb camera
    if(!cap.isOpened())  // check if we succeeded
    {
        std::cerr << "Error Opening Video Camera" << std::endl;
    }

    cv::Mat edges;
    cv::namedWindow("edges",1);
    while(true)
    {
        cv::Mat frame;
        cap >> frame; // get a new frame from camera
        //cvtColor(frame, edges, 0);
        //GaussianBlur(edges, edges, cv::Size(7,7), 1.5, 1.5);
        //Canny(edges, edges, 0, 30, 3);
        cv::imshow("edges", frame);
        if(cv::waitKey(30) >= 0) break;
    }
}




