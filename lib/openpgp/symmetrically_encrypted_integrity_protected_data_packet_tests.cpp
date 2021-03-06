#include <memory>
#include <sstream>

#include "gtest/gtest.h"

#include <neopg/symmetrically_encrypted_integrity_protected_data_packet.h>

using namespace NeoPG;

TEST(NeoPGTest,
     openpg_symmetrically_encrypted_integrity_protected_data_packet_test) {
  {
    std::stringstream out;
    SymmetricallyEncryptedIntegrityProtectedDataPacket packet;
    packet.m_data =
        std::vector<uint8_t>{0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    packet.write(out);
    ASSERT_EQ(out.str(), std::string("\xD2\x09"
                                     "\x01"
                                     "\x01\x02\x03\x04\x05\x06\x07\x08",
                                     11));
  }
}
