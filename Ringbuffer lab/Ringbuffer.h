#pragma once
#include <mutex>
#include <thread>

#include "../../std_lib_facilities.h"
#include "chrono"
using namespace std::chrono_literals;

template <typename T>
class Ringbuffer {
 public:
  
  Ringbuffer<T>(int capacity);
  ~Ringbuffer<T>();

  void put(T c);
  T get();

  bool is_empty();
  bool if_full();
  int nextIndex(int i);
  bool full = 0;

 private:
  T* buffer;
  int bufferSize;
  int head = 0;
  int tail = 0;

  mutex readMutex;
  mutex writeMuted;
  mutex mutex_lock;

  // condition_variable writeCvar;
  // condition_variable readCvar;
};



template <typename T>
inline Ringbuffer<T>::Ringbuffer(int capacity) {
  buffer = new T[capacity];
  bufferSize = capacity;
}

template <typename T>
inline Ringbuffer<T>::~Ringbuffer() {
  if (buffer != nullptr) {
    delete[] buffer;
  }
}

template <typename T>
inline void Ringbuffer<T>::put(T c) {
  std::unique_lock<std::mutex> lock(mutex_lock);
  if (!if_full()) {
    buffer[head] = c;
    head = (head + 1) % bufferSize;
  }
  //buffer[head] = c;
  //if (if_full()) {
  //  tail = (tail + 1) % bufferSize;
  //}
  while (if_full()) {
  }

}

template <typename T>
inline T Ringbuffer<T>::get() {
  std::unique_lock<std::mutex> lock(readMutex);
  while (is_empty()) {
  }
  //full = false;
  tail = (tail + 1) % bufferSize;
  return buffer[tail];
}

template <typename T>
inline bool Ringbuffer<T>::is_empty() {
  return (head == tail);
}

template <typename T>
inline bool Ringbuffer<T>::if_full() {
  return nextIndex(head) == tail;
}

template <typename T>
inline int Ringbuffer<T>::nextIndex(int i) {
  return (i + 1) % bufferSize;
}
template <typename T>
void keyboard_input(Ringbuffer<T>* buff) {
  T input;
  while (cin >> input) {
    buff->put(input);
  }
}
template <typename T>
void random_input(Ringbuffer<T>* buff) {
  srand(time(NULL));
  while (true) {
    this_thread::sleep_for(200ms);
    int a = rand() % 10 + 48;
    buff->put(a);
  }
}

template <typename T>
T console_out(Ringbuffer<T>* buff) {
  while (true) {
    this_thread::sleep_for(500ms);
    cout << buff->get();
  }
}
