#ifndef __REC_COMMAND_MAP_KEY__
#define __REC_COMMAND_MAP_KEY__

#include "rec/command/map/MidiName.h"

namespace rec {
namespace command {
namespace map {

class KeyBase {
 public:
  KeyBase() {}
  virtual ~KeyBase() {}
  virtual String name() const = 0;

 private:
  JUCE_LEAK_DETECTOR(KeyBase);
};

typedef juce::OwnedArray<KeyBase> KeyArray;

template <typename Type>
class Key : public KeyBase {
 public:
  Key(const Type& key) : key_(key) {}
  virtual ~Key() {}
  virtual String name() const;

 private:
  const Type key_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Key);
};

template <>
inline String Key<MidiMessage>::name() const {
  return midiName(key_);
}

template <>
inline String Key<KeyPress>::name() const {
  return key_.getTextDescription();
}

template <typename Type>
KeyBase* makeKey(const Type& t) {
  return new Key<Type>(t);
}

}  // namespace map
}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_MAP_KEY__
