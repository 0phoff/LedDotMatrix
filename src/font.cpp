#include <cassert>
#include "font.h"

namespace LDM
{
  Font::Font(
    unsigned int width, unsigned int height,
    unsigned char min_val, unsigned char max_val,
    const unsigned char* data
  )
    : m_width(width), m_height(height), m_min_val(min_val), m_max_val(max_val), m_data(data)
  {}

  const unsigned char small_data[] = {
    0x0E, 0x11, 0x11, 0x11, 0x0E,   // 0
    0x00, 0x00, 0x10, 0x1F, 0x00,   // 1
    0x00, 0x09, 0x13, 0x15, 0x09,   // 2
    0x00, 0x11, 0x15, 0x15, 0x1F,   // 3
    0x00, 0x1C, 0x04, 0x04, 0x1F,   // 4
    0x00, 0x0D, 0x15, 0x15, 0x17,   // 5
    0x00, 0x1F, 0x15, 0x15, 0x17,   // 6
    0x00, 0x11, 0x12, 0x14, 0x18,   // 7
    0x00, 0x1B, 0x15, 0x15, 0x1B,   // 8
    0x00, 0x1D, 0x15, 0x15, 0x1F,   // 9
    0x00, 0x00, 0x00, 0x00, 0x00,   // :
    0x00, 0x00, 0x00, 0x00, 0x00,   // ;
    0x00, 0x00, 0x00, 0x00, 0x00,   // <
    0x00, 0x00, 0x00, 0x00, 0x00,   // =
    0x00, 0x00, 0x00, 0x00, 0x00,   // >
    0x00, 0x00, 0x00, 0x00, 0x00,   // ?
    0x00, 0x00, 0x00, 0x00, 0x00,   // @
    0x1F, 0x14, 0x14, 0x14, 0x1F,   // A
    0x1F, 0x15, 0x15, 0x15, 0x0E,   // B
    0x1F, 0x11, 0x11, 0x11, 0x11,   // C
    0x1F, 0x11, 0x11, 0x11, 0x0E,   // D
    0x1F, 0x15, 0x15, 0x15, 0x11,   // E
    0x1F, 0x14, 0x14, 0x14, 0x10,   // F
    0x1F, 0x11, 0x15, 0x15, 0x17,   // G
    0x1F, 0x04, 0x04, 0x04, 0x1F,   // H
    0x11, 0x11, 0x1F, 0x11, 0x11,   // I
    0x00, 0x13, 0x11, 0x1F, 0x10,   // J
    0x00, 0x1F, 0x04, 0x0A, 0x11,   // K
    0x00, 0x1F, 0x01, 0x01, 0x01,   // L
    0x1F, 0x08, 0x04, 0x08, 0x1F,   // M
    0x1F, 0x08, 0x04, 0x02, 0x1F,   // N
    0x1F, 0x11, 0x11, 0x11, 0x1F,   // O
    0x1F, 0x14, 0x14, 0x14, 0x1C,   // P
    0x1F, 0x11, 0x11, 0x13, 0x1F,   // Q
    0x1F, 0x14, 0x14, 0x16, 0x1D,   // R
    0x1D, 0x15, 0x15, 0x15, 0x17,   // S
    0x10, 0x10, 0x1F, 0x10, 0x10,   // T
    0x1F, 0x01, 0x01, 0x01, 0x1F,   // U
    0x18, 0x06, 0x01, 0x06, 0x18,   // V
    0x1F, 0x01, 0x02, 0x01, 0x1F,   // W
    0x11, 0x0A, 0x04, 0x0A, 0x11,   // X
    0x10, 0x08, 0x07, 0x08, 0x10,   // Y
    0x11, 0x13, 0x15, 0x19, 0x11,   // Z
  };
  const Font small_font(5, 5, 48, 90, small_data);

  const unsigned char big_data[] = {
    0x3E, 0x45, 0x49, 0x51, 0x3E,   // 0
    0x11, 0x21, 0x7F, 0x01, 0x01,   // 1
    0x27, 0x49, 0x49, 0x49, 0x31,   // 2
    0x22, 0x41, 0x49, 0x49, 0x36,   // 3
    0x0C, 0x14, 0x24, 0x44, 0x7F,   // 4
    0x79, 0x49, 0x49, 0x49, 0x46,   // 5
    0x3E, 0x49, 0x49, 0x49, 0x06,   // 6
    0x60, 0x40, 0x47, 0x48, 0x70,   // 7
    0x36, 0x49, 0x49, 0x49, 0x36,   // 8
    0x30, 0x49, 0x49, 0x49, 0x3E,   // 9
    0x00, 0x00, 0x00, 0x00, 0x00,   // :
    0x00, 0x00, 0x00, 0x00, 0x00,   // ;
    0x00, 0x00, 0x00, 0x00, 0x00,   // <
    0x00, 0x00, 0x00, 0x00, 0x00,   // =
    0x00, 0x00, 0x00, 0x00, 0x00,   // >
    0x00, 0x00, 0x00, 0x00, 0x00,   // ?
    0x00, 0x00, 0x00, 0x00, 0x00,   // @
    0x3F, 0x48, 0x48, 0x48, 0x3F,   // A
    0x7F, 0x49, 0x49, 0x49, 0x36,   // B
    0x3E, 0x41, 0x41, 0x41, 0x22,   // C
    0x7F, 0x41, 0x41, 0x41, 0x3E,   // D
    0x7F, 0x49, 0x49, 0x49, 0x41,   // E
    0x7F, 0x48, 0x48, 0x48, 0x40,   // F
    0x3E, 0x41, 0x45, 0x45, 0x26,   // G
    0x7F, 0x08, 0x08, 0x08, 0x7F,   // H
    0x41, 0x41, 0x7F, 0x41, 0x41,   // I
    0x46, 0x41, 0x41, 0x41, 0x7E,   // J
    0x7F, 0x08, 0x14, 0x22, 0x41,   // K
    0x7F, 0x01, 0x01, 0x01, 0x01,   // L
    0x7F, 0x10, 0x0C, 0x10, 0x7F,   // M
    0x7F, 0x10, 0x08, 0x04, 0x7F,   // N
    0x3E, 0x41, 0x41, 0x41, 0x3E,   // O
    0x7F, 0x48, 0x48, 0x48, 0x30,   // P
    0x3E, 0x41, 0x41, 0x43, 0x3F,   // Q
    0x7F, 0x48, 0x4C, 0x4A, 0x31,   // R
    0x32, 0x49, 0x49, 0x49, 0x26,   // S
    0x40, 0x40, 0x7F, 0x40, 0x40,   // T
    0x7E, 0x01, 0x01, 0x01, 0x7E,   // U
    0x7C, 0x02, 0x01, 0x02, 0x7C,   // V
    0x7E, 0x01, 0x06, 0x01, 0x7E,   // W
    0x41, 0x22, 0x1C, 0x22, 0x41,   // X
    0x40, 0x20, 0x1F, 0x20, 0x40,   // Y
    0x43, 0x45, 0x49, 0x51, 0x61,   // Z
  };
  const Font big_font(5, 7, 48, 90, big_data);
}
