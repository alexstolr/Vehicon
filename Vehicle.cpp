/**
 * @brief Represents a Vehicle and holds its identifiers
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

X509 *Vehicle::getX509Cert() const {
    return x509Cert;
}

void Vehicle::setX509Cert(X509 *x509Cert) {
    Vehicle::x509Cert = x509Cert;
}

EVP_PKEY *Vehicle::getPkey() const {
    return pkey;
}

void Vehicle::setPkey(EVP_PKEY *pkey) {
    Vehicle::pkey = pkey;
}
