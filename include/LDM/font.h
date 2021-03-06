#pragma once
#include <cassert>

namespace LDM
{
  class Font
  {
    private:
      const unsigned int m_width, m_height;
      const unsigned char m_min_val, m_max_val;
      const unsigned char* m_data;

    public:
      Font(
        unsigned int width, unsigned int height,
        unsigned char min_val, unsigned char max_val,
        const unsigned char* data
      );
      
      // Getters
      unsigned int getWidth() const { return m_width; }
      unsigned int getHeight() const { return m_height; }
      unsigned char getMinVal() const { return m_min_val; }
      unsigned char getMaxVal() const { return m_max_val; }
      const unsigned char* getChar(unsigned char value) const
      {
        assert(value >= m_min_val);   // Value should be bigger than representable min_value
        assert(value <= m_max_val);   // Value should be smaller than representable max_value
        return &m_data[(value - m_min_val) * m_width];
      }
  };

  extern const Font small_font;
  extern const Font big_font;
}
