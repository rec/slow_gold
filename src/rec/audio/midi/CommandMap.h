#ifndef __REC_AUDIO_MIDI_COMMANDMAP__
#define __REC_AUDIO_MIDI_COMMANDMAP__

#include <map>

#include "rec/audio/midi/CommandMap.pb.h"
#include "rec/base/base.h"

namespace rec {
namespace audio {
namespace midi {

class CommandMap {
 public:
  typedef command::Command::Type Command;
  typedef string Key;

  CommandMap() {}

  void initialize(const CommandMapProto&);
  const CommandMapProto getProto() const;

  Command getCommand(const Key&);
  string getKey(Command);

 private:
  typedef std::map<Key, Command> KeyToCommand;
  typedef std::map<Command, Key> CommandToKey;

  KeyToCommand toCommand_;
  CommandToKey toKey_;

  DISALLOW_COPY_AND_ASSIGN(CommandMap);
};

}  // namespace midi
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_MIDI_COMMANDMAP__
