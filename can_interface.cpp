#include "can_interface.h"
#include "byte_order.h"
#include <array>
#include <cstdint>
#include <cstring>
#include <net/if.h>
#include <print>
#include <sys/ioctl.h>
#include <system_error>
#include <unistd.h>

Can::Can() {
  if ((sockFD = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
    throw std::system_error(errno, std::generic_category(),
                            "FAILED TO CREATE SOCKET");
  }

  ifreq ifr{};
  std::strncpy(ifr.ifr_name, "vcan0", sizeof(ifr.ifr_name) - 1);
  if (ioctl(sockFD, SIOCGIFINDEX, &ifr) < 0) {
    throw std::system_error(errno, std::generic_category(), "IOCTL FAILED");
  }

  sockaddr_can addr{};
  std::memset(&addr, 0, sizeof(addr));
  addr.can_family = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;

  if (bind(sockFD, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr)) <
      0) {
    throw std::system_error(errno, std::generic_category(),
                            "FAILED TO BIND CAN SOCKET");
  }
}

Can::~Can() {
  if (sockFD >= 0) {
    close(sockFD);
  }
}

void Can::comm_can_transmit_eid(std::uint32_t id, const std::uint8_t *data,
                                std::size_t len) {
  if (len > 8)
    len = 8; // set length to 8bytes if exceeds that
  can_frame frame{};
  frame.can_id = id | CAN_EFF_FLAG; //
  frame.can_dlc = len;
  std::print("\nCANID {:08x}:", frame.can_id);
  for (size_t i = 0; i < len; i++) {
    frame.data[i] = data[i];
    std::print("{:x} ", frame.data[i]);
  }

  if (write(sockFD, &frame, sizeof(can_frame)) != sizeof(can_frame)) {
    close(sockFD);
    throw std::system_error(errno, std::generic_category(),
                            "FAILED TO SEND DATA");
  }
}

void Can::encodeCAN(std::uint8_t motorID, float angle, std::int16_t speed,
                    std::uint16_t accel, CAN_PACKET_ID controlMode) {
  std::size_t sendIndex = 0;
  std::size_t sendIndex1 = 4;
  std::array<std::uint8_t, 8> buffer;
  bufferAppendInt32(buffer.data(), static_cast<std::int32_t>(angle * posScale),
                    sendIndex);
  bufferAppendInt16(buffer.data(), speed / speedNormDivisor, sendIndex1);
  bufferAppendInt16(buffer.data(), accel / speedNormDivisor, sendIndex1);
  comm_can_transmit_eid(motorID | static_cast<std::uint32_t>(controlMode << 8),
                        buffer.data(), sendIndex1);
}
