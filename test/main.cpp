#include <iostream>
#include <algorithm>
#include <unistd.h>
#include "matrix.h"

#define NUM_CASCADED 4

int main()
{
  std::cout << "--- LED DOT MATRIX ---" << std::endl;

  // Create matrix of 4 cascaded devices on spidev0.0
  LDM::Matrix mat("/dev/spidev0.0", NUM_CASCADED);
  sleep(2);

  // Set single led and flush to display
  std::cout << "  Single led test" << std::endl;
  mat.setLed(10, 4, true);
  mat.flush();
  sleep(2);

  // Flush without clearing buffer
  std::cout << "  Flush without clearing test" << std::endl;
  for (int i=0; i < 8*NUM_CASCADED; i++) {
    for (int j=0; j < 8; j++) {
      mat.setLed(i, j, true);
    }
    mat.flush(false);
    sleep(0.5);
  }
  sleep(2);

  // Access raw grid pointer
  std::cout << "  Raw Grid access test" << std::endl;
  bool* grid = mat.getGrid();
  for (int i=0; i < NUM_CASCADED; i+=2) {
    std::fill(grid + (64 * i), grid + (64 * (i + 1)), 0);
  }
  mat.flush(false);
  sleep(2);

  // Toggling LEDs
  std::cout << "  Toggle LED test" << std::endl;
  for (int i=0; i < 8*NUM_CASCADED; i++) {
    for (int j=0; j < 8; j++) {
      mat.toggleLed(i, j);
    }
  }
  mat.flush();
  sleep(2);

  // Clear matrix
  std::cout << "  Clearing matrix test" << std::endl;
  mat.clear();
}
