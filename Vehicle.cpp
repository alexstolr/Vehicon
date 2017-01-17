/**
 * @brief Repsents a Vehicle and holds its identifiers
 * eg license plate, certifiate, Public and Private key(for now this is not done correctly)
 * @author Alex Stoliar (alexstolr@gmail.com)
 * @date 08/01/2017
 */

#include "Vehicle.h"

Vehicle::Vehicle() {}

Vehicle::~Vehicle() {

}

const uint8_t *Vehicle::getCert() const {
    return cert;
}

const uint8_t *Vehicle::getPubKey() const {
    return pubKey;
}

const uint8_t *Vehicle::getPlateNum() const {
    return plateNum;
}
