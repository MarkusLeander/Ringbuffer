#include "Ringbuffer.h"

int main() {

  Ringbuffer<char> buu(5);
  std::thread a1(keyboard_input<char>, &buu);
  std::thread a2(random_input<char>, &buu);
  std::thread a3(console_out<char>, &buu);
 
  a1.join();
  a2.join();
  a3.join();
}
