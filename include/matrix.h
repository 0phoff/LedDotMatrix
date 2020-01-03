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
      bool* m_grid;
      unsigned char* m_data;
      int m_fd;
      unsigned int m_pointer_x, m_pointer_y;
      const Font* m_font;

    public:
      // CTOR
      Matrix(std::string device, int num_cascaded, int speed=100000);
      ~Matrix();

      // Getters
      inline const std::string& getDevice() const { return m_device; }
      inline int getSpeed() const { return m_speed; }
      inline int getNumCascaded() const { return m_num_cascaded; }
      inline const Font* getFont() const { return m_font; }
      inline unsigned int getPointerX() const { return m_pointer_x; }
      inline unsigned int getPointerY() const { return m_pointer_y; }
      inline std::pair<unsigned int, unsigned int> getPointer() const { return {m_pointer_x, m_pointer_y}; }
      inline bool* getGrid() { return m_grid; }
      inline bool getLed(unsigned int x, unsigned y) const
      {
        assert(x < 8 * m_num_cascaded);   // X should be inside grid
        assert(y < 8);                    // Y should be inside grid
        return m_grid[8 * x + y];
      }

      // Setters
      inline void setFont(const Font* font) { m_font = font; }
      inline void setPointerX(unsigned int x) { m_pointer_x = x; }
      inline void setPointerY(unsigned int y) { m_pointer_y = y; }
      inline void setPointer(unsigned int x, unsigned int y)
      {
        m_pointer_x = x;
        m_pointer_y = y;
      }
      inline void resetPointer()
      {
        m_pointer_x = 0;
        m_pointer_y = 7;
      }
      inline void setLed(unsigned int x, unsigned int y, bool value)
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
  };
}
