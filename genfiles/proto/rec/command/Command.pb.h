// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/command/Command.proto

#ifndef PROTOBUF_rec_2fcommand_2fCommand_2eproto__INCLUDED
#define PROTOBUF_rec_2fcommand_2fCommand_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2003000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace rec {
namespace command {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fcommand_2fCommand_2eproto();
void protobuf_AssignDesc_rec_2fcommand_2fCommand_2eproto();
void protobuf_ShutdownFile_rec_2fcommand_2fCommand_2eproto();

class Command;

enum Command_Type {
  Command_Type_NONE = 0,
  Command_Type_QUIT = 4097,
  Command_Type_DEL = 4098,
  Command_Type_CUT = 4099,
  Command_Type_COPY = 4100,
  Command_Type_PASTE = 4101,
  Command_Type_SELECT_ALL = 4102,
  Command_Type_DESELECT_ALL = 4103,
  Command_Type_ADD_LOOP_POINT = 1,
  Command_Type_AUDIO_PREFERENCES = 2,
  Command_Type_CLEAR_NAVIGATOR = 3,
  Command_Type_CLEAR_LOOPS = 4,
  Command_Type_CLEAR_SAVED_FILE_DATA = 5,
  Command_Type_CLOSE_FILE = 6,
  Command_Type_CONTRACT_FROM_NEXT_LOOP_POINT = 75,
  Command_Type_CONTRACT_FROM_PREVIOUS_LOOP_POINT = 76,
  Command_Type_DIM_VOLUME_TOGGLE = 77,
  Command_Type_EJECT_CDS = 7,
  Command_Type_EXTEND_TO_NEXT_LOOP_POINT = 73,
  Command_Type_EXTEND_TO_PREVIOUS_LOOP_POINT = 74,
  Command_Type_INVERT_LOOP_SELECTION = 19,
  Command_Type_JUMP_TO_0 = 90,
  Command_Type_JUMP_TO_1 = 91,
  Command_Type_JUMP_TO_2 = 92,
  Command_Type_JUMP_TO_3 = 93,
  Command_Type_JUMP_TO_4 = 94,
  Command_Type_JUMP_TO_5 = 95,
  Command_Type_JUMP_TO_6 = 96,
  Command_Type_JUMP_TO_7 = 97,
  Command_Type_JUMP_TO_8 = 98,
  Command_Type_JUMP_TO_9 = 99,
  Command_Type_JUMP_TO_FIRST_SEGMENT = 87,
  Command_Type_JUMP_TO_PREVIOUS_SEGMENT = 8,
  Command_Type_JUMP_TO_NEXT_SEGMENT = 9,
  Command_Type_JUMP_TO_LAST_SEGMENT = 10,
  Command_Type_JUMP_TO_FIRST_SELECTED_SEGMENT = 82,
  Command_Type_JUMP_TO_PREVIOUS_SELECTED_SEGMENT = 81,
  Command_Type_JUMP_TO_NEXT_SELECTED_SEGMENT = 80,
  Command_Type_JUMP_TO_LAST_SELECTED_SEGMENT = 88,
  Command_Type_KEYBOARD_MAPPINGS = 18,
  Command_Type_MIDI_MAPPINGS = 17,
  Command_Type_MUTE_VOLUME_TOGGLE = 78,
  Command_Type_NUDGE_BEGIN_LEFT = 11,
  Command_Type_NUDGE_BEGIN_RIGHT = 12,
  Command_Type_NUDGE_END_LEFT = 13,
  Command_Type_NUDGE_END_RIGHT = 14,
  Command_Type_NUDGE_VOLUME_DOWN = 59,
  Command_Type_NUDGE_VOLUME_UP = 72,
  Command_Type_OPEN = 15,
  Command_Type_RECENT_FILES = 16,
  Command_Type_RESET_GAIN_TO_UNITY = 79,
  Command_Type_SELECT_0 = 20,
  Command_Type_SELECT_1 = 21,
  Command_Type_SELECT_2 = 22,
  Command_Type_SELECT_3 = 23,
  Command_Type_SELECT_4 = 24,
  Command_Type_SELECT_5 = 25,
  Command_Type_SELECT_6 = 26,
  Command_Type_SELECT_7 = 27,
  Command_Type_SELECT_8 = 28,
  Command_Type_SELECT_9 = 29,
  Command_Type_SELECT_ONLY_0 = 30,
  Command_Type_SELECT_ONLY_1 = 31,
  Command_Type_SELECT_ONLY_2 = 32,
  Command_Type_SELECT_ONLY_3 = 33,
  Command_Type_SELECT_ONLY_4 = 34,
  Command_Type_SELECT_ONLY_5 = 35,
  Command_Type_SELECT_ONLY_6 = 36,
  Command_Type_SELECT_ONLY_7 = 37,
  Command_Type_SELECT_ONLY_8 = 38,
  Command_Type_SELECT_ONLY_9 = 39,
  Command_Type_SELECT_FIRST_SEGMENT_ONLY = 83,
  Command_Type_SELECT_LAST_SEGMENT_ONLY = 84,
  Command_Type_SELECT_NEXT_SEGMENT_ONLY = 85,
  Command_Type_SELECT_PREVIOUS_SEGMENT_ONLY = 86,
  Command_Type_TOGGLE_0 = 40,
  Command_Type_TOGGLE_1 = 41,
  Command_Type_TOGGLE_2 = 42,
  Command_Type_TOGGLE_3 = 43,
  Command_Type_TOGGLE_4 = 44,
  Command_Type_TOGGLE_5 = 45,
  Command_Type_TOGGLE_6 = 46,
  Command_Type_TOGGLE_7 = 47,
  Command_Type_TOGGLE_8 = 48,
  Command_Type_TOGGLE_9 = 49,
  Command_Type_TOGGLE_WHOLE_SONG_LOOP = 58,
  Command_Type_TOGGLE_START_STOP = 50,
  Command_Type_TOGGLE_STRETCH_ENABLE = 51,
  Command_Type_TREE_CLOSE = 52,
  Command_Type_TREE_DOWN = 53,
  Command_Type_TREE_LEFT = 54,
  Command_Type_TREE_OPEN = 55,
  Command_Type_TREE_RIGHT = 56,
  Command_Type_TREE_UP = 57,
  Command_Type_UNSELECT_0 = 60,
  Command_Type_UNSELECT_1 = 61,
  Command_Type_UNSELECT_2 = 62,
  Command_Type_UNSELECT_3 = 63,
  Command_Type_UNSELECT_4 = 64,
  Command_Type_UNSELECT_5 = 65,
  Command_Type_UNSELECT_6 = 66,
  Command_Type_UNSELECT_7 = 67,
  Command_Type_UNSELECT_8 = 68,
  Command_Type_UNSELECT_9 = 69,
  Command_Type_ZOOM_IN = 70,
  Command_Type_ZOOM_OUT = 71,
  Command_Type_LAST_COMMAND = 99
};
bool Command_Type_IsValid(int value);
const Command_Type Command_Type_Type_MIN = Command_Type_NONE;
const Command_Type Command_Type_Type_MAX = Command_Type_DESELECT_ALL;
const int Command_Type_Type_ARRAYSIZE = Command_Type_Type_MAX + 1;

const ::google::protobuf::EnumDescriptor* Command_Type_descriptor();
inline const ::std::string& Command_Type_Name(Command_Type value) {
  return ::google::protobuf::internal::NameOfEnum(
    Command_Type_descriptor(), value);
}
inline bool Command_Type_Parse(
    const ::std::string& name, Command_Type* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Command_Type>(
    Command_Type_descriptor(), name, value);
}
// ===================================================================

class Command : public ::google::protobuf::Message {
 public:
  Command();
  virtual ~Command();
  
  Command(const Command& from);
  
  inline Command& operator=(const Command& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Command& default_instance();
  
  void Swap(Command* other);
  
  // implements Message ----------------------------------------------
  
  Command* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Command& from);
  void MergeFrom(const Command& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  typedef Command_Type Type;
  static const Type NONE = Command_Type_NONE;
  static const Type QUIT = Command_Type_QUIT;
  static const Type DEL = Command_Type_DEL;
  static const Type CUT = Command_Type_CUT;
  static const Type COPY = Command_Type_COPY;
  static const Type PASTE = Command_Type_PASTE;
  static const Type SELECT_ALL = Command_Type_SELECT_ALL;
  static const Type DESELECT_ALL = Command_Type_DESELECT_ALL;
  static const Type ADD_LOOP_POINT = Command_Type_ADD_LOOP_POINT;
  static const Type AUDIO_PREFERENCES = Command_Type_AUDIO_PREFERENCES;
  static const Type CLEAR_NAVIGATOR = Command_Type_CLEAR_NAVIGATOR;
  static const Type CLEAR_LOOPS = Command_Type_CLEAR_LOOPS;
  static const Type CLEAR_SAVED_FILE_DATA = Command_Type_CLEAR_SAVED_FILE_DATA;
  static const Type CLOSE_FILE = Command_Type_CLOSE_FILE;
  static const Type CONTRACT_FROM_NEXT_LOOP_POINT = Command_Type_CONTRACT_FROM_NEXT_LOOP_POINT;
  static const Type CONTRACT_FROM_PREVIOUS_LOOP_POINT = Command_Type_CONTRACT_FROM_PREVIOUS_LOOP_POINT;
  static const Type DIM_VOLUME_TOGGLE = Command_Type_DIM_VOLUME_TOGGLE;
  static const Type EJECT_CDS = Command_Type_EJECT_CDS;
  static const Type EXTEND_TO_NEXT_LOOP_POINT = Command_Type_EXTEND_TO_NEXT_LOOP_POINT;
  static const Type EXTEND_TO_PREVIOUS_LOOP_POINT = Command_Type_EXTEND_TO_PREVIOUS_LOOP_POINT;
  static const Type INVERT_LOOP_SELECTION = Command_Type_INVERT_LOOP_SELECTION;
  static const Type JUMP_TO_0 = Command_Type_JUMP_TO_0;
  static const Type JUMP_TO_1 = Command_Type_JUMP_TO_1;
  static const Type JUMP_TO_2 = Command_Type_JUMP_TO_2;
  static const Type JUMP_TO_3 = Command_Type_JUMP_TO_3;
  static const Type JUMP_TO_4 = Command_Type_JUMP_TO_4;
  static const Type JUMP_TO_5 = Command_Type_JUMP_TO_5;
  static const Type JUMP_TO_6 = Command_Type_JUMP_TO_6;
  static const Type JUMP_TO_7 = Command_Type_JUMP_TO_7;
  static const Type JUMP_TO_8 = Command_Type_JUMP_TO_8;
  static const Type JUMP_TO_9 = Command_Type_JUMP_TO_9;
  static const Type JUMP_TO_FIRST_SEGMENT = Command_Type_JUMP_TO_FIRST_SEGMENT;
  static const Type JUMP_TO_PREVIOUS_SEGMENT = Command_Type_JUMP_TO_PREVIOUS_SEGMENT;
  static const Type JUMP_TO_NEXT_SEGMENT = Command_Type_JUMP_TO_NEXT_SEGMENT;
  static const Type JUMP_TO_LAST_SEGMENT = Command_Type_JUMP_TO_LAST_SEGMENT;
  static const Type JUMP_TO_FIRST_SELECTED_SEGMENT = Command_Type_JUMP_TO_FIRST_SELECTED_SEGMENT;
  static const Type JUMP_TO_PREVIOUS_SELECTED_SEGMENT = Command_Type_JUMP_TO_PREVIOUS_SELECTED_SEGMENT;
  static const Type JUMP_TO_NEXT_SELECTED_SEGMENT = Command_Type_JUMP_TO_NEXT_SELECTED_SEGMENT;
  static const Type JUMP_TO_LAST_SELECTED_SEGMENT = Command_Type_JUMP_TO_LAST_SELECTED_SEGMENT;
  static const Type KEYBOARD_MAPPINGS = Command_Type_KEYBOARD_MAPPINGS;
  static const Type MIDI_MAPPINGS = Command_Type_MIDI_MAPPINGS;
  static const Type MUTE_VOLUME_TOGGLE = Command_Type_MUTE_VOLUME_TOGGLE;
  static const Type NUDGE_BEGIN_LEFT = Command_Type_NUDGE_BEGIN_LEFT;
  static const Type NUDGE_BEGIN_RIGHT = Command_Type_NUDGE_BEGIN_RIGHT;
  static const Type NUDGE_END_LEFT = Command_Type_NUDGE_END_LEFT;
  static const Type NUDGE_END_RIGHT = Command_Type_NUDGE_END_RIGHT;
  static const Type NUDGE_VOLUME_DOWN = Command_Type_NUDGE_VOLUME_DOWN;
  static const Type NUDGE_VOLUME_UP = Command_Type_NUDGE_VOLUME_UP;
  static const Type OPEN = Command_Type_OPEN;
  static const Type RECENT_FILES = Command_Type_RECENT_FILES;
  static const Type RESET_GAIN_TO_UNITY = Command_Type_RESET_GAIN_TO_UNITY;
  static const Type SELECT_0 = Command_Type_SELECT_0;
  static const Type SELECT_1 = Command_Type_SELECT_1;
  static const Type SELECT_2 = Command_Type_SELECT_2;
  static const Type SELECT_3 = Command_Type_SELECT_3;
  static const Type SELECT_4 = Command_Type_SELECT_4;
  static const Type SELECT_5 = Command_Type_SELECT_5;
  static const Type SELECT_6 = Command_Type_SELECT_6;
  static const Type SELECT_7 = Command_Type_SELECT_7;
  static const Type SELECT_8 = Command_Type_SELECT_8;
  static const Type SELECT_9 = Command_Type_SELECT_9;
  static const Type SELECT_ONLY_0 = Command_Type_SELECT_ONLY_0;
  static const Type SELECT_ONLY_1 = Command_Type_SELECT_ONLY_1;
  static const Type SELECT_ONLY_2 = Command_Type_SELECT_ONLY_2;
  static const Type SELECT_ONLY_3 = Command_Type_SELECT_ONLY_3;
  static const Type SELECT_ONLY_4 = Command_Type_SELECT_ONLY_4;
  static const Type SELECT_ONLY_5 = Command_Type_SELECT_ONLY_5;
  static const Type SELECT_ONLY_6 = Command_Type_SELECT_ONLY_6;
  static const Type SELECT_ONLY_7 = Command_Type_SELECT_ONLY_7;
  static const Type SELECT_ONLY_8 = Command_Type_SELECT_ONLY_8;
  static const Type SELECT_ONLY_9 = Command_Type_SELECT_ONLY_9;
  static const Type SELECT_FIRST_SEGMENT_ONLY = Command_Type_SELECT_FIRST_SEGMENT_ONLY;
  static const Type SELECT_LAST_SEGMENT_ONLY = Command_Type_SELECT_LAST_SEGMENT_ONLY;
  static const Type SELECT_NEXT_SEGMENT_ONLY = Command_Type_SELECT_NEXT_SEGMENT_ONLY;
  static const Type SELECT_PREVIOUS_SEGMENT_ONLY = Command_Type_SELECT_PREVIOUS_SEGMENT_ONLY;
  static const Type TOGGLE_0 = Command_Type_TOGGLE_0;
  static const Type TOGGLE_1 = Command_Type_TOGGLE_1;
  static const Type TOGGLE_2 = Command_Type_TOGGLE_2;
  static const Type TOGGLE_3 = Command_Type_TOGGLE_3;
  static const Type TOGGLE_4 = Command_Type_TOGGLE_4;
  static const Type TOGGLE_5 = Command_Type_TOGGLE_5;
  static const Type TOGGLE_6 = Command_Type_TOGGLE_6;
  static const Type TOGGLE_7 = Command_Type_TOGGLE_7;
  static const Type TOGGLE_8 = Command_Type_TOGGLE_8;
  static const Type TOGGLE_9 = Command_Type_TOGGLE_9;
  static const Type TOGGLE_WHOLE_SONG_LOOP = Command_Type_TOGGLE_WHOLE_SONG_LOOP;
  static const Type TOGGLE_START_STOP = Command_Type_TOGGLE_START_STOP;
  static const Type TOGGLE_STRETCH_ENABLE = Command_Type_TOGGLE_STRETCH_ENABLE;
  static const Type TREE_CLOSE = Command_Type_TREE_CLOSE;
  static const Type TREE_DOWN = Command_Type_TREE_DOWN;
  static const Type TREE_LEFT = Command_Type_TREE_LEFT;
  static const Type TREE_OPEN = Command_Type_TREE_OPEN;
  static const Type TREE_RIGHT = Command_Type_TREE_RIGHT;
  static const Type TREE_UP = Command_Type_TREE_UP;
  static const Type UNSELECT_0 = Command_Type_UNSELECT_0;
  static const Type UNSELECT_1 = Command_Type_UNSELECT_1;
  static const Type UNSELECT_2 = Command_Type_UNSELECT_2;
  static const Type UNSELECT_3 = Command_Type_UNSELECT_3;
  static const Type UNSELECT_4 = Command_Type_UNSELECT_4;
  static const Type UNSELECT_5 = Command_Type_UNSELECT_5;
  static const Type UNSELECT_6 = Command_Type_UNSELECT_6;
  static const Type UNSELECT_7 = Command_Type_UNSELECT_7;
  static const Type UNSELECT_8 = Command_Type_UNSELECT_8;
  static const Type UNSELECT_9 = Command_Type_UNSELECT_9;
  static const Type ZOOM_IN = Command_Type_ZOOM_IN;
  static const Type ZOOM_OUT = Command_Type_ZOOM_OUT;
  static const Type LAST_COMMAND = Command_Type_LAST_COMMAND;
  static inline bool Type_IsValid(int value) {
    return Command_Type_IsValid(value);
  }
  static const Type Type_MIN =
    Command_Type_Type_MIN;
  static const Type Type_MAX =
    Command_Type_Type_MAX;
  static const int Type_ARRAYSIZE =
    Command_Type_Type_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Type_descriptor() {
    return Command_Type_descriptor();
  }
  static inline const ::std::string& Type_Name(Type value) {
    return Command_Type_Name(value);
  }
  static inline bool Type_Parse(const ::std::string& name,
      Type* value) {
    return Command_Type_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // optional .rec.command.Command.Type command = 1;
  inline bool has_command() const;
  inline void clear_command();
  static const int kCommandFieldNumber = 1;
  inline ::rec::command::Command_Type command() const;
  inline void set_command(::rec::command::Command_Type value);
  
  // @@protoc_insertion_point(class_scope:rec.command.Command)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  int command_;
  friend void  protobuf_AddDesc_rec_2fcommand_2fCommand_2eproto();
  friend void protobuf_AssignDesc_rec_2fcommand_2fCommand_2eproto();
  friend void protobuf_ShutdownFile_rec_2fcommand_2fCommand_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static Command* default_instance_;
};
// ===================================================================


// ===================================================================

// Command

// optional .rec.command.Command.Type command = 1;
inline bool Command::has_command() const {
  return _has_bit(0);
}
inline void Command::clear_command() {
  command_ = 0;
  _clear_bit(0);
}
inline ::rec::command::Command_Type Command::command() const {
  return static_cast< ::rec::command::Command_Type >(command_);
}
inline void Command::set_command(::rec::command::Command_Type value) {
  GOOGLE_DCHECK(::rec::command::Command_Type_IsValid(value));
  _set_bit(0);
  command_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace command
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::rec::command::Command_Type>() {
  return ::rec::command::Command_Type_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2fcommand_2fCommand_2eproto__INCLUDED
