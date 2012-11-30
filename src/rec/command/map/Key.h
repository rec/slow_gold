#ifndef __REC_COMMAND_MAP_KEY__
#define __REC_COMMAND_MAP_KEY__

#include "rec/command/map/MidiName.h"

namespace rec {
namespace command {

#if 1
typedef string KeyBase;

template <typename Type> string toString(const Type&);

template <>
inline string toString(const MidiMessage& msg) {
  string r = str(msg);
  if (msg.isNoteOn())
    r[2] = 127;

  if (msg.isController())
    r[2] = (r[2] < 64) ? 0 : 127;

  return r;
}

template <>
inline string toString(const KeyPress& kp) {
  return str(kp.getTextDescription());
}

template <typename Type> void fromString(const string&, Type*);


inline MidiMessage midiFromString(const string& s) {
  return MidiMessage(s.data(), s.size());
}

inline KeyPress keyPressFromString(const string& s) {
  return KeyPress::createFromDescription(str(s));
}


template <>
inline void fromString(const string& s, KeyPress* kp) {
  (*kp) = keyPressFromString(s);
}

template <>
inline void fromString(const string& s, MidiMessage* mm) {
  (*mm) = midiFromString(s);
}

#else

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

#endif
}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_MAP_KEY__
