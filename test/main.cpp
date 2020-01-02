#include <iostream>
#include <unistd.h>
#include "matrix.h"

#define NUM_CASCADED 4

int main()
{
  std::cout << "--- LED DOT MATRIX ---" << std::endl;

  // Create matrix of 4 cascaded devices on spidev0.0
  LDM::Matrix mat("/dev/spidev0.0", NUM_CASCADED);
  sleep(1);

  // Set single led and flush to display
  std::cout << "  Single led test" << std::endl;
  mat.setLed(10, 4, true);
  mat.flush();
  sleep(1);

  // Flush without clearing buffer
  std::cout << "  Flush without clearing test" << std::endl;
  for (int i=0; i < 8*NUM_CASCADED; i++) {
    for (int j=0; j < 8; j++) {
      mat.setLed(i, j, true);
    }
    mat.flush(false);
    sleep(0.5);
  }
  sleep(1);

  // Clear matrix
  std::cout << "  Clearing matrix test" << std::endl;
  mat.clear();
}
