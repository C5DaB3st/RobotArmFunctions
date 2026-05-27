#include "robotFunctions.h"
#include "can_interface.h"

void MotorJoint::setAngles(std::array<std::uint8_t, 6> motorID,
                           std::array<float, 6> jointAngles,
                           std::array<float, 6> jointVel,
                           std::array<float, 6> jointAccel) {
  Can can;
  for (std::size_t i = 0; i < 6; i++) {
    can.encodeCAN(motorID.at(i), jointAngles.at(i), jointVel.at(i),
                  jointAccel.at(i), CAN_PACKET_ID::CAN_PACKET_SET_POS_SPD);
  }
}
