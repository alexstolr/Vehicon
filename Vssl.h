/**
 * @brief Handles all regarding security, ssl, cert, authentication etc...
 * https://www.ibm.com/developerworks/library/l-openssl/
 * https://gist.github.com/nathan-osman/5041136
 * http://stackoverflow.com/questions/256405/programmatically-create-x509-certificate-using-openssl
 * @author Alex Stoliar (alexstolr@gmail.com)
 * @date 08/01/2017
 */

#ifndef VEHICON_VSSL_H
#define VEHICON_VSSL_H

#include <cstdio>
#include <iostream>
#include <openssl/pem.h>
#include <openssl/x509v3.h>
#include "Vehicle.h"

class Vssl {

public:
    Vssl(Vehicle * vehicle);
    virtual ~Vssl();

private:
    Vehicle * vehicle;

    EVP_PKEY * generate_key();
    X509 * generate_x509(EVP_PKEY * pkey);
    bool write_to_disk(EVP_PKEY * pkey, X509 * x509);
    bool init();

};


#endif //VEHICON_VSSL_H
