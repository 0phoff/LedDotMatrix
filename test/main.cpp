#include <iostream>
#include <unistd.h>

#include "matrix.h"

int main()
{
  std::cout << "--- LED DOT MATRIX ---" << std::endl;

  // Create matrix of 4 cascaded devices on spidev0.0
  LDM::Matrix mat("/dev/spidev0.0", 4);
  sleep(2);

  mat.setLed(10, 4, true);
  mat.flush();
}
