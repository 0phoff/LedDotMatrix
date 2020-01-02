#pragma once
#include <memory>
#include <string>

namespace LDM
{

  class Matrix
  {
    private:
      std::unique_ptr<bool[]> m_grid;
      const std::string m_device;
      const int m_speed, m_num_cascaded;
      int m_fd;

    public:
      // CTOR
      Matrix(std::string device, int num_cascaded, int speed=100000);

      // Getters
      const std::string& getDevice() const { return m_device; }
      int getSpeed() const { return m_speed; }
      int getNumCascaded() const { return m_num_cascaded; }

      // Functionality
      void clear();
  };

}
