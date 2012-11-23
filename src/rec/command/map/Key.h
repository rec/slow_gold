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
  virtual KeyBase& operator=(const KeyBase&) = 0;

 private:
  JUCE_LEAK_DETECTOR(KeyBase);
};

template <typename Type>
class Key : public KeyBase {
 public:
  Key() {}
  virtual ~Key() {}

  Key(const KeyBase& ck) { (*this) = ck; }
  Key(const Type& t) { (*this) = t; }

  virtual String name() const;

  KeyBase& operator=(const Type& t) {
    key_ = t;
    return *this;
  }

  virtual KeyBase& operator=(const KeyBase& other) {
    if (const Key<Type>* that = dynamic_cast<const Key<Type>*>(&other))
      key_ = that->key_;
    else
      LOG(DFATAL) << "Tried to assign wrong type to key";

    return *this;
  }

 private:
  Type key_;

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
