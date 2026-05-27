#include "can_interface.h"
#include <ctype.h>

int main() {
  Can can;
  can.encodeCAN(0x68, 1000, 10000, 10000, CAN_PACKET_SET_POS_SPD);
}
