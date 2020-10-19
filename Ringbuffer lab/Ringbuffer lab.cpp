#include "Ringbuffer.h"

int main() {

  Ringbuffer<char> buu(5);
  // std::thread a1(keyboard_input<char>, buu);
  // std::thread a2(console_out<char>, buu);
  // a1.join();
  // a2.join();
  // keyboard_input(buu);
  // console_out(buu);
  // random_input(buu);
  std::thread a1(keyboard_input<char>, &buu);
  std::thread a2(console_out<char>, &buu);
  std::thread a3(random_input<char>, &buu);

  a1.join();
  a2.join();
  a3.join();
}
