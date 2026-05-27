#include <array>
#include <cstdint>

class MotorJoint {

public:
  void setAngles(std::array<std::uint8_t, 6> motorID,
                 std::array<float, 6> jointAngles,
                 std::array<float, 6> jointVel,
                 std::array<float, 6> jointAccel);
};
