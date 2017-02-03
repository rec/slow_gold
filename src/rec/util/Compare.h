#pragma once

#include "rec/base/base.h"

namespace rec {
namespace util {

bool isASCII(int c);
bool isPunctuation(int c);
int compareChars(int c, int d);

struct CompareChars {
    bool operator()(int c, int d) {
        return compareChars(c, d) < 0;
    }
};

struct LessThanEqualChar {
    LessThanEqualChar(int c) : c_(c) {}
    bool operator()(int c) const { return c < c_; }

    int c_;
};

template <typename Str>
int compareStrings(const Str& x, const Str& y);

template <typename Str>
int indexOfDifference(const Str& s, const Str& t);

template <typename Collection>
int indexOfDifference(const Collection& items, const int i);

bool compareFiles(const File& f, const File& g);

}  // namespace util
}  // namespace rec
