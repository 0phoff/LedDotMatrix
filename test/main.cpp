#include <iostream>
#include <algorithm>
#include <unistd.h>
#include "matrix.h"
#include "font.h"

#define NUM_CASCADED 4


void ledTest(LDM::Matrix& mat)
/*
 * This function performs a series of tests with the Matrix class to turn on/off individual LEDs.
 */
{
  // Set single led and flush to display
  std::cout << "    Single led test" << std::endl;
  mat.setLed(10, 4, true);
  mat.flush();
  sleep(2);

  // Flush without clearing buffer
  std::cout << "    Flush without clearing test" << std::endl;
  for (int i=0; i < 8*NUM_CASCADED; i++) {
    for (int j=0; j < 8; j++) {
      mat.setLed(i, j, true);
    }
    mat.flush(false);
    sleep(0.5);
  }
  sleep(2);

  // Access raw grid pointer
  std::cout << "    Raw Grid access test" << std::endl;
  bool* grid = mat.getGrid();
  for (int i=0; i < NUM_CASCADED; i+=2) {
    std::fill(grid + (64 * i), grid + (64 * (i + 1)), 0);
  }
  mat.flush(false);
  sleep(2);

  // Toggling LEDs
  std::cout << "    Toggle LED test" << std::endl;
  for (int i=0; i < 8*NUM_CASCADED; i++) {
    for (int j=0; j < 8; j++) {
      mat.toggleLed(i, j);
    }
  }
  mat.flush();
  sleep(2);
}


void fontTest(LDM::Matrix& mat)
/*
 * This function performs a series of tests with fonts on the Matrix class.
 */
{
  // Write with small font
  std::cout << "    Small font test" << std::endl;
  mat.setFont(&LDM::small_font, 0);
  mat.setPointer(3, 6);
  mat.print("01234");
  mat.flush();
  sleep(2);

  // Write with big font
  std::cout << "    Big font test" << std::endl;
  mat.setFont(&LDM::big_font);
  mat.setPointer(7, 7);
  mat.print("LDM");
  mat.flush();
  sleep(2);
}


int main()
{
  std::cout << "--- LED DOT MATRIX ---" << std::endl;

  // Create matrix of 4 cascaded devices on spidev0.0
  LDM::Matrix mat("/dev/spidev0.0", NUM_CASCADED);
  sleep(1);

  // Single led test
  std::cout << "  LED TEST" << std::endl;
  ledTest(mat);

  // Font test
  std::cout << "  FONT TEST" << std::endl;
  fontTest(mat);

  // Clear matrix
  std::cout << "  CLEAR MATRIX TEST" << std::endl;
  mat.clear();
}
