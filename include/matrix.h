#pragma once
#include <memory>
#include <string>
#include <cassert>

namespace LDM
{

  class Matrix
  {
    private:
      bool* m_grid;
      unsigned char* m_data;
      const std::string m_device;
      const unsigned int m_speed, m_num_cascaded;
      int m_fd;

    public:
      // CTOR
      Matrix(std::string device, int num_cascaded, int speed=100000);
      ~Matrix();

      // Getters
      const std::string& getDevice() const { return m_device; }
      int getSpeed() const { return m_speed; }
      int getNumCascaded() const { return m_num_cascaded; }

      // Setters
      inline void setLed(unsigned int x, unsigned int y, bool value)
      {
        assert(x < 8 * m_num_cascaded);   // X should be inside grid
        assert(y < 8);                    // Y should be inside grid
        m_grid[8 * x + y] = value;
      }

      // Functionality
      void clear();
      void flush(bool clear_grid=true);
  };

}
