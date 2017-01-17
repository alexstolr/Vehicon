/**
 * @brief ALV (Autonomous Land Vehicle) Authentication Protocol
 *
 * Protocol definition:
 * B0 = FE (msg start)
 * B1 = sequence number (each side has different sequence number)
 * B2 = length
 * B3 = opcode
 * B4 - Bn-4 = Data
 * Bn-3 - Bn = CRC
 *
 * @authors Alex Stoliar (alexstolr@gmail.com)
 * @date 23/09/16
 */

#include "Protocol.h"

Protocol::Protocol() {}

Protocol::~Protocol() {

}
