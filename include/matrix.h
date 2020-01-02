#pragma once
#include <memory>
#include <string>

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

      // Functionality
      void clear();
      void flush(bool clear_grid=true);
      void setLed(unsigned int x, unsigned int y, bool value);
  };

}
