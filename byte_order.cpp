#include "byte_order.h"

void bufferAppendInt32(std::uint8_t *buffer, std::int32_t number,
                       std::size_t &index) {
  buffer[index++] = number >> 24;
  buffer[index++] = number >> 16;
  buffer[index++] = number >> 8;
  buffer[index++] = number;
}
void bufferAppendInt16(std::uint8_t *buffer, std::int16_t number,
                       std::size_t &index) {
  buffer[index++] = number >> 8;
  buffer[index++] = number;
}
