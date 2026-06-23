# CAN-bus control software for a 6-DOF robotic arm built on CubeMars AK10-9 actuators, written for a robotics project for Robotics@UH.

## What this actually is

This is a **Linux host-side application**, not microcontroller firmware. It
uses [SocketCAN](https://docs.kernel.org/networking/can.html) to open a CAN
socket on a Linux machine and send position/velocity/acceleration commands
to AK10-9 actuators over the bus. The actuators run their own onboard
position/velocity/current control loops -- this code is the layer that
talks *to* those loops, not the loops themselves.

## Status

- [x] CAN frame encoding (extended ID, position/velocity/acceleration
      packing into an 8-byte payload)
- [x] SocketCAN socket setup, bind, and teardown
- [x] Per-joint command dispatch for a 6-DOF arm (`MotorJoint::setAngles`)
- [ ] Real-hardware validation over a physical `can0` interface (currently
      defaults to the virtual `vcan0` interface for local testing)
- [ ] Telemetry / feedback reading back from the actuators
- [ ] Verifying the velocity/acceleration scale factors against CubeMars'
      official CAN protocol documentation (see note in `can_interface.h`)

## Build

```bash
cmake -G Ninja -B build
ninja -C build
```

Requires a Linux machine with `linux/can.h` 

To test without physical hardware, set up a virtual CAN interface first:

```bash
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0
```

## Usage

```cpp
Can can("vcan0");                  // or "can0" for real hardware
MotorJoint arm;

std::array<std::uint8_t, 6> motorIDs{1, 2, 3, 4, 5, 6};
std::array<float, 6> angles{...};
std::array<float, 6> velocities{...};
std::array<float, 6> accelerations{...};

arm.setAngles(can, motorIDs, angles, velocities, accelerations);
```

The `Can` connection is opened once and reused -- it is not recreated on
every command, since opening/binding a socket on every control-loop tick
would add unnecessary latency.

## Files

| File | Purpose |
|---|---|
| `can_interface.h/.cpp` | SocketCAN connection + CAN frame encoding for AK10-9 position/velocity commands |
| `byte_order.h/.cpp` | Little/big-endian-safe buffer packing helpers for building CAN payloads |
| `robotFunctions.h/.cpp` | Per-joint command dispatch across all 6 motors |
| `main.cpp` | Minimal smoke test |

## Known limitations

- No error recovery if a CAN write fails mid-sequence (one bad frame
  currently throws and unwinds the whole command).
- No unit tests yet.
- Velocity/acceleration scaling factors are carried over from an earlier
  version of this code and haven't been independently verified against
  CubeMars' AK-series CAN protocol spec.
