#include "nes/nes.h"

int main(int argc, char **argv) {
  nes::Nes nes{};
  nes.Run();

  return EXIT_SUCCESS;
}