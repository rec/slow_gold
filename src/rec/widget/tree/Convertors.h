#ifndef __REC_WIDGET_TREE_CONVERTORS__
#define __REC_WIDGET_TREE_CONVERTORS__

#include <vector>

#include "rec/base/base.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {
namespace tree {

inline String getName(const File& f) { return f.getFileName(); }
inline string getName(const string& s) { return s; }

inline int getLength(const string& s) { return s.size(); }
inline int getLength(const String& s) { return s.length(); }

inline String toLowerCase(const String& s) { return s.toLowerCase(); }

inline string toLowerCase(const string& s) {
  string t = s;
  for (int i = 0; i < t.size(); ++i)
    t[i] = tolower(t[i]);
  return t;
}
  
  inline int foo() { return 1; }

inline void add(juce::Array<int>* list, int x) { list->add(x); }
inline void add(std::vector<int>* list, int x) { list->push_back(x); }

inline const String& get(const juce::Array<File>& files, int i) {
  return files[i].getFullPathName();
}

inline const string& get(const std::vector<string>& files, int i) {
  return files[i];
}


}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_CONVERTORS__
