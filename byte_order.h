#pragma once

#include <cstdint>

void bufferAppendInt32(std::uint8_t *buffer, std::int32_t number,
                       std::size_t &index);

void bufferAppendInt16(std::uint8_t *buffer, std::int16_t number,
                       std::size_t &index);
