#include "rec/util/Crypt.h"
#include "rec/base/ArraySize.h"

namespace rec {
namespace util {

namespace {

unsigned char MASK[] = {
    0xf7, 0x19, 0xcd, 0xb8, 0x6a, 0x04, 0x5c, 0x78,
    0x36, 0xe2, 0xf3, 0x0e, 0x60, 0xab, 0xee, 0x30,
    0x27, 0xed, 0x58, 0xfe, 0x7e, 0x42, 0x5f, 0xca,
    0x21, 0x68, 0xfc, 0x6e, 0xcb, 0x5c, 0x6c, 0x28,
    0xc4, 0xaf, 0x06, 0x8a, 0x74, 0x05, 0xbc, 0xac,
    0x7d, 0xa2, 0xac, 0xf4, 0x66, 0xfa, 0x48, 0xf3,
    0x1e, 0x76, 0x32, 0x54, 0xd8, 0x61, 0xab, 0x67,
    0xeb, 0x31, 0xa9, 0x9a, 0xf5, 0x86, 0xd4, 0x9a
};

}  // namespace

void crypt(string* target) {
    for (auto i = 0; i < target->size(); ++i)
        target->at(i) ^= MASK[i % arraysize(MASK)];
}

string crypt(const string& str) {
    auto s = str;
    crypt(&s);
    return s;
}

}  // namespace util
}  // namespace rec