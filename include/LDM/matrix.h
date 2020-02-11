#pragma once
#include <memory>
#include <string>
#include <cassert>
#include <utility>
#include "font.h"

namespace LDM
{
  class Matrix
  {
    private:
      const std::string m_device;
      const unsigned int m_num_cascaded, m_speed;
      unsigned char m_intensity;
      bool* m_grid;
      unsigned char* m_data;
      int m_fd;
      unsigned int m_pointer_x, m_pointer_y;
      const Font* m_font;
      int m_font_space;

    public:
      // CTOR
      Matrix(std::string device, unsigned int num_cascaded, unsigned int speed=100000, unsigned char intensity=0);
      ~Matrix();

      // Getters
      const std::string& getDevice() const { return m_device; }
      unsigned int getSpeed() const { return m_speed; }
      unsigned int getNumCascaded() const { return m_num_cascaded; }
      unsigned int getIntensity() const { return m_intensity; }
      const Font* getFont() const { return m_font; }
      int getFontSpace() const {return m_font_space; }
      unsigned int getPointerX() const { return m_pointer_x; }
      unsigned int getPointerY() const { return m_pointer_y; }
      std::pair<unsigned int, unsigned int> getPointer() const { return {m_pointer_x, m_pointer_y}; }
      bool* getGrid() { return m_grid; }
      bool getLed(unsigned int x, unsigned y) const
      {
        assert(x < 8 * m_num_cascaded);   // X should be inside grid
        assert(y < 8);                    // Y should be inside grid
        return m_grid[8 * x + y];
      }

      // Setters
      void setIntensity(unsigned char value);
      void setFont(const Font* font, int space=1) { m_font = font; m_font_space = space; }
      void setFontSpace(int space) { m_font_space = space; }
      void setPointerX(unsigned int x) { m_pointer_x = x; }
      void setPointerY(unsigned int y) { m_pointer_y = y; }
      void setPointer(unsigned int x, unsigned int y)
      {
        m_pointer_x = x;
        m_pointer_y = y;
      }
      void resetPointer()
      {
        m_pointer_x = 0;
        m_pointer_y = 7;
      }
      void setLed(unsigned int x, unsigned int y, bool value)
      {
        assert(x < 8 * m_num_cascaded);   // X should be inside grid
        assert(y < 8);                    // Y should be inside grid
        m_grid[8 * x + y] = value;
      }

      // Functionality
      void clear();
      void flush(bool clear_grid=true);
      bool toggleLed(unsigned int x, unsigned int y);
      void print(const std::string& string, bool overwrite=true);
      void print(char value, bool overwrite=true);
  };
}
