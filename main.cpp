#include "can_interface.h"
#include "robotFunctions.h"

int main() {
  Can can("vcan0");

  MotorJoint arm;
  std::array<std::uint8_t, 6> motorIDs{1, 2, 3, 4, 5, 6};
  std::array<float, 6> jointAngles{0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
  std::array<float, 6> jointVel{0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
  std::array<float, 6> jointAccel{0.f, 0.f, 0.f, 0.f, 0.f, 0.f};

  arm.setAngles(can, motorIDs, jointAngles, jointVel, jointAccel);

  return 0;
}
