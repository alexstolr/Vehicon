/**
 * @brief Represents a Vehicle and holds its identifiers
 * eg license plate, certifiate, Public and Private key(for now this is not done correctly)
 * @author Alex Stoliar (alexstolr@gmail.com)
 * @date 08/01/2017
 */

#ifndef VEHICON_VEHICLE_H
#define VEHICON_VEHICLE_H

#include <stdint.h>


class Vehicle {

public:
    Vehicle();
    virtual ~Vehicle();

    const uint8_t *getCert() const;
    const uint8_t *getPubKey() const;
    const uint8_t *getPlateNum() const;

private:
    uint8_t cert[8] =       {0xFF, 0xFE, 00, 00, 00, 00, 00, 0xA1};
    uint8_t pubKey[8] =     {0xFF, 0xFE, 00, 00, 00, 00, 00, 0xA2};
    uint8_t prvKey[8] =     {0xFF, 0xFE, 00, 00, 00, 00, 00, 0xA3};
    uint8_t plateNum[8] =    {4,6,7,3,5,5,2,0};
    uint8_t brand[6] =     {'t','o','y','o','t','a'};
    uint8_t model[6] =     {'c','o','r','o','l','a'};
};


#endif //VEHICON_VEHICLE_H
