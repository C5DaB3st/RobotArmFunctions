#pragma once 

#include <cstdint>
#include <linux/can.h>
#include <sys/socket.h>

enum CAN_PACKET_ID {
  CAN_PACKET_SET_DUTY = 0,      // Duty Cycle Mode
  CAN_PACKET_SET_CURRENT,       // Current Loop Mode
  CAN_PACKET_SET_CURRENT_BRAKE, // Current Brake Mode
  CAN_PACKET_SET_RPM,           // Speed Mode
  CAN_PACKET_SET_POS,           // Position Mode
  CAN_PACKET_SET_ORIGIN_HERE,   // Set origin position mode (zero mode)
  CAN_PACKET_SET_POS_SPD,       // Position-Velocity Loop Mode
};

class Can {
public:
  explicit Can(const std::string &ifaceName = "vcan0");
  ~Can();

  Can(const Can &) = delete;
  Can &operator=(const Can &) = delete;
  
  void comm_can_transmit_eid(std::uint32_t id, const std::uint8_t *data,
                             std::size_t len);
  void encodeCAN(std::uint8_t motorID, float angle, float speed, float accel,
                 CAN_PACKET_ID controlMode);
 
};
