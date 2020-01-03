#include <algorithm>
#include <cctype>
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
    m_grid = new bool[64 * m_num_cascaded];
    m_data = new unsigned char[2 * m_num_cascaded];
    m_font = nullptr;
    resetPointer();

    // Setup SPI device on Linux side
    m_fd = open(m_device.c_str(), O_RDWR);
    ioctl(m_fd, SPI_IOC_WR_MODE, 0);
    ioctl(m_fd, SPI_IOC_WR_BITS_PER_WORD, 8);
    ioctl(m_fd, SPI_IOC_WR_MAX_SPEED_HZ, &m_speed);
    ioctl(m_fd, SPI_IOC_WR_LSB_FIRST, 0);

    // Disable MAX7219 Shutdown mode
    for (int i=0; i < m_num_cascaded; i++) {
      m_data[i * 2] = 0x0C;
      m_data[i * 2 + 1] = 0x01;
    }
    write(m_fd, m_data, 2 * m_num_cascaded);

    // Setup MAX7219 scan limit to all LEDs
    for (int i=0; i < m_num_cascaded; i++) {
      m_data[i * 2] = 0x0B;
      m_data[i * 2 + 1] = 0x07;
    }
    write(m_fd, m_data, 2 * m_num_cascaded);

    // Clear screen
    clear();
  }

  Matrix::~Matrix()
  {
    delete[] m_data;
    delete[] m_grid;
    close(m_fd);
  }

  void Matrix::clear()
  {
    std::fill(m_grid, m_grid + (64 * m_num_cascaded), 0);
    m_pointer_x = 0;
    m_pointer_y = 7;
    
    for (unsigned int row=0; row < 9; row++) {
      for (int i=0; i < m_num_cascaded; i++) {
        m_data[i * 2] = (unsigned char) row;
        m_data[i * 2 + 1] = 0x00;
      }
      write(m_fd, m_data, 2 * m_num_cascaded);
    }
  }

  void Matrix::flush(bool clear_grid)
  {
    for (unsigned int row=0; row < 8; row++) {
      for (int num=0; num < m_num_cascaded; num++) {
        m_data[num * 2] = (unsigned char) (row + 1);

        m_data[num * 2 + 1] = 0x00;
        for (int col=0; col < 8; col++) {
          if (m_grid[(64 * num) + (col * 8) + row])
            m_data[num * 2 + 1] |= 1 << 7 - col;
        }
      }
      write(m_fd, m_data, 2 * m_num_cascaded);
      
    }

    if (clear_grid) {
      std::fill(m_grid, m_grid + (64 * m_num_cascaded), 0);
      m_pointer_x = 0;
      m_pointer_y = 7;
    }
  }

  bool Matrix::toggleLed(unsigned int x, unsigned int y)
  {
    bool value = !getLed(x, y);
    setLed(x, y, value);
    return value;
  }

  void Matrix::print(const std::string& string, bool overwrite)
  {
    assert(m_font);   // Font cannot be null
    auto width = m_font->getWidth();
    auto height = m_font->getHeight();
    auto space = m_font->getSpace();

    for (auto val : string) {
      const unsigned char* bitmap = m_font->getChar(toupper(val));

      for (int i=0; i < width; i++) {
        if (m_pointer_x < 0) {
          m_pointer_x++;
          continue;
        }
        else if (m_pointer_x > 8 * m_num_cascaded)
          break;

        auto row = bitmap[i];
        for (int j=0; j < height; j++) {
          bool led_value = (row & (1<<j)) != 0;
          if (led_value || overwrite)
            setLed(m_pointer_x, m_pointer_y - j, led_value);
        }
        m_pointer_x++;
      }
      m_pointer_x += space;
    }
  }
}
