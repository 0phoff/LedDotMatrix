#include <algorithm>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#include "matrix.h"

namespace LDM
{
  Matrix::Matrix(std::string device, int num_cascaded, int speed)
    : m_device(device), m_num_cascaded(num_cascaded), m_speed(speed)
  {
    m_grid = std::make_unique<bool[]>(8 * m_num_cascaded);

    // Setup SPI device on Linux side
    m_fd = open(m_device.c_str(), O_RDWR);
    ioctl(m_fd, SPI_IOC_WR_MODE, 0);
    ioctl(m_fd, SPI_IOC_WR_BITS_PER_WORD, 8);
    ioctl(m_fd, SPI_IOC_WR_MAX_SPEED_HZ, &m_speed);
    ioctl(m_fd, SPI_IOC_WR_LSB_FIRST, 0);

    // Disable MAX7219 Shutdown mode
    unsigned char* data = new unsigned char[m_num_cascaded * 2];
    for (int i=0; i < m_num_cascaded; i++) {
      data[i * 2] = 0x0C;
      data[i * 2 + 1] = 0x01;
    }
    write(m_fd, data, 2 * m_num_cascaded);

    // Setup MAX7219 scan limit to all LEDs
    for (int i=0; i < m_num_cascaded; i++) {
      data[i * 2] = 0x0B;
      data[i * 2 + 1] = 0x07;
    }
    write(m_fd, data, 2 * m_num_cascaded);
    delete[] data;

    // Clear screen
    clear();
  }

  void Matrix::clear()
  {
    std::fill(m_grid.get(), m_grid.get()+(8*m_num_cascaded), 0);
    
    unsigned char* data = new unsigned char[m_num_cascaded * 2];
    for (unsigned int row=0; row < 9; row++) {
      for (int i=0; i < m_num_cascaded; i++) {
        data[i * 2] = row;
        data[i * 2 + 1] = 0x00;
      }
      write(m_fd, data, 2 * m_num_cascaded);
    }
    delete[] data;
  }
}
