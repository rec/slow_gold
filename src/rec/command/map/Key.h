#ifndef __REC_COMMAND_MAP_KEY__
#define __REC_COMMAND_MAP_KEY__

#include "rec/command/map/MidiName.h"

namespace rec {
namespace command {

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
  Key(const Key<Type>& that) : key_(that.key_) {}
  Key(const Type& key) : key_(key) {}
  virtual ~Key() {}
  const Type& key() const { return key_; }

  virtual String name() const;

 private:
  const Type key_;

  JUCE_LEAK_DETECTOR(Key);
};

template <>
inline String Key<MidiMessage>::name() const {
  return midiName(key_);
}

template <>
inline String Key<juce::KeyPress>::name() const {
  return key_.getTextDescription();
}

template <typename Type>
KeyBase* makeKey(const Type& t) {
  return new Key<Type>(t);
}

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_MAP_KEY__
