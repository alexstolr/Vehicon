cmake_minimum_required(VERSION 3.6)
project(Vehicon)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(SOURCE_FILES main.cpp Vehicon.cpp Vehicon.h Lpr.cpp Lpr.h Udplink.cpp Udplink.h Crc32.cpp Crc32.h Protocol.cpp Protocol.h Vehicle.cpp Vehicle.h Vssl.cpp Vssl.h)
add_executable(Vehicon ${SOURCE_FILES})

find_package(OpenCV REQUIRED) #OpenCV
find_package(OpenSSL REQUIRED)
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/lib) #OpenALPR
include_directories($(OpenCV_INCLUDE_DIRS) ${OPENSSL_INCLUDE_DIR}) #OpenCV

target_link_libraries(Vehicon -lpthread ${OpenCV_LIBS} ${OPENSSL_LIBRARIES} libopenalpr.so) #Threads