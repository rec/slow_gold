#include <stdlib.h>

#include <set>

#include "rec/util/RandomSelfInverseFunction.h"

namespace rec {
namespace util {

static const int STATE_SIZE = 16;

typedef std::vector<byte> ByteVector;

static int randomItemIndex(int size) {
  return static_cast<unsigned long>(random()) % size;
}

static void checkByte(int b) {
  DCHECK_GE(b, 0);
  DCHECK_LT(b, ByteFunction::COUNT);
}

template <typename T>
static void swap(T& b1, T& b2) {
  T t = b1; b1 = b2; b2 = t;
}

ByteFunction randomSelfInverseFunction(unsigned seed) {
  char state[STATE_SIZE];
  initstate(seed, state, STATE_SIZE);

  static const int COUNT = ByteFunction::COUNT;

  ByteFunction func;

  ByteVector bytes(COUNT);
  for (int i = 0; i < COUNT; ++i)
    bytes[i] = i;

  while (int size = bytes.size()) {
    int x = randomItemIndex(size);
    int y = randomItemIndex(size);
    int bx = bytes[x];
    int by = bytes[y];
    checkByte(x);
    checkByte(y);
    checkByte(bx);
    checkByte(by);
    func.function[bx] = by;
    func.function[by] = bx;

    if (x < y)
      swap(x, y);
    swap(bytes[x], bytes[size - 1]);
    if (x == y) {
      bytes.resize(size - 1);
    } else {
      swap(bytes[y], bytes[size - 2]);
      bytes.resize(size - 2);
    }
  }

  return func;
}

}  // namespace rec
}  // namespace util
