#pragma once

#include <array>
#include <cstdint>

class Can;

class MotorJoint {
public:
  void setAngles(Can &can, std::array<std::uint8_t, 6> motorID,
                 std::array<float, 6> jointAngles,
                 std::array<float, 6> jointVel,
                 std::array<float, 6> jointAccel);
};
