#include "rec/widget/tree/Tree.h"

namespace rec {
namespace widget {
namespace tree {

bool isASCII(int c) { return c >= 0 && c <= 0xFF; }

bool isPunctuation(int c) {
  return isASCII(c) &&
    (c < '0' || (c > '9' && c < 'A') || (c > 'Z' && c < 'a') || c > 'z');
}

int compareChars(int c, int d) {
  bool pc = isPunctuation(c);
  bool pd = isPunctuation(d);

  return (pc == pd) ? (tolower(c) - tolower(d)) : (pc ? -1 : 1);
}

bool compareFiles(const File& f, const File& g) {
  return compareStrings(f.getFileName(), g.getFileName()) < 0;
}

void eraseVolumePrefix(string* name, bool diskToo) {
  static const int len = strlen("/Volumes/");
  if (name->find("/Volumes/") == 0) {
    int pos = diskToo ? name->find("/", len) : len;
    if (pos != -1)
      name->erase(0, pos);
  }
}


}  // namespace tree
}  // namespace widget
}  // namespace rec
