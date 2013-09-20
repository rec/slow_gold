// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/slow/commands/Command.proto

#ifndef PROTOBUF_rec_2fslow_2fcommands_2fCommand_2eproto__INCLUDED
#define PROTOBUF_rec_2fslow_2fcommands_2fCommand_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
#include "rec/command/Command.pb.h"
#include "rec/command/map/CommandMap.pb.h"
// @@protoc_insertion_point(includes)

namespace rec {
namespace slow {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fslow_2fcommands_2fCommand_2eproto();
void protobuf_AssignDesc_rec_2fslow_2fcommands_2fCommand_2eproto();
void protobuf_ShutdownFile_rec_2fslow_2fcommands_2fCommand_2eproto();

class Command;

enum Command_Id {
  Command_Id_NONE = 0,
  Command_Id_ABOUT_THIS_PROGRAM = 58,
  Command_Id_ADD_LOOP_POINT = 1,
  Command_Id_AUDIO_PREFERENCES = 2,
  Command_Id_CHECK_FOR_UPDATES = 68,
  Command_Id_CLEAR_KEYBOARD_MAPPINGS = 91,
  Command_Id_CLEAR_MIDI_MAPPINGS = 92,
  Command_Id_CLEAR_LOOPS = 4,
  Command_Id_CLEAR_NAVIGATOR = 3,
  Command_Id_CLEAR_ALL_SETTINGS = 79,
  Command_Id_CLEAR_SETTINGS_FOR_THIS_TRACK = 80,
  Command_Id_CLEAR_SAVED_FILE_DATA = 5,
  Command_Id_CLOSE_FILE = 6,
  Command_Id_COPY_ALL_LOOP_POINTS = 95,
  Command_Id_DIM_VOLUME_TOGGLE = 7,
  Command_Id_EJECT_CDS = 8,
  Command_Id_EXPORT_KEYBOARD_MAPPINGS = 82,
  Command_Id_EXPORT_MIDI_MAPPINGS = 83,
  Command_Id_EXPORT_SETTINGS = 75,
  Command_Id_IMPORT_KEYBOARD_MAPPINGS = 84,
  Command_Id_IMPORT_MIDI_MAPPINGS = 85,
  Command_Id_IMPORT_SETTINGS = 76,
  Command_Id_INVERT_LOOP_SELECTION = 9,
  Command_Id_JUMP = 100000,
  Command_Id_JUMP_SELECTED = 110000,
  Command_Id_KEYBOARD_MAPPINGS = 12,
  Command_Id_LOOP_NEXT_SEGMENT = 94,
  Command_Id_MIDI_MAPPINGS = 13,
  Command_Id_MODE_ADD_LOOP_POINT = 63,
  Command_Id_MODE_DRAG = 60,
  Command_Id_MODE_SET_TIME = 61,
  Command_Id_MODE_ZOOM_IN = 62,
  Command_Id_MUTE_VOLUME_TOGGLE = 14,
  Command_Id_NUDGE_BACKWARD = 89,
  Command_Id_NUDGE_FORWARD = 90,
  Command_Id_NUDGE_BEGIN_LEFT = 15,
  Command_Id_NUDGE_BEGIN_RIGHT = 16,
  Command_Id_NUDGE_END_LEFT = 17,
  Command_Id_NUDGE_END_RIGHT = 18,
  Command_Id_NUDGE_SPEED_DOWN = 86,
  Command_Id_NUDGE_SPEED_UP = 87,
  Command_Id_NUDGE_VOLUME_DOWN = 19,
  Command_Id_NUDGE_VOLUME_UP = 20,
  Command_Id_OPEN = 21,
  Command_Id_OPEN_MANUAL = 65,
  Command_Id_OPEN_PREVIOUS_FILE = 78,
  Command_Id_OPEN_SLOWGOLD_DIRECTORY = 74,
  Command_Id_PASTE_OVER_LOOP_POINTS = 96,
  Command_Id_RECENT_FILES = 220000,
  Command_Id_REDO = 23,
  Command_Id_REQUEST_SUPPORT = 66,
  Command_Id_RESET_GAIN_TO_UNITY = 24,
  Command_Id_SAVE_FILE = 69,
  Command_Id_SAVE_FILE_SELECTION = 70,
  Command_Id_SELECT = 250000,
  Command_Id_SELECT_ONLY = 260000,
  Command_Id_SET_LANGUAGE = 930000,
  Command_Id_SET_SAVE_FORMAT = 710000,
  Command_Id_SET_SAVE_AS_AIFF = 97,
  Command_Id_SET_SAVE_AS_FLAC = 98,
  Command_Id_SET_SAVE_AS_OGG = 99,
  Command_Id_SET_SAVE_AS_WAV = 100,
  Command_Id_TOGGLE_ADVANCED_MENUS = 59,
  Command_Id_TOGGLE_AUTOMATIC_UPDATES = 67,
  Command_Id_TOGGLE_FOLLOW_CURSOR = 43,
  Command_Id_TOGGLE_GRID_DISPLAY = 27,
  Command_Id_TOGGLE_COMMAND_BAR_AT_LEFT = 54,
  Command_Id_TOGGLE_COMMAND_BAR_AT_TOP = 55,
  Command_Id_TOGGLE_FILE_OPEN_TREE_DISPLAY = 72,
  Command_Id_TOGGLE_MODES_AT_LEFT = 56,
  Command_Id_TOGGLE_MODES_AT_TOP = 57,
  Command_Id_TOGGLE_PARALLEL_WAVEFORMS = 42,
  Command_Id_TOGGLE_PREFADER_LEVELS = 46,
  Command_Id_TOGGLE_SELECTION = 410000,
  Command_Id_TOGGLE_SHOW_ABOUT_WINDOW_AT_STARTUP = 81,
  Command_Id_TOGGLE_SHOW_CURSOR_LABELS = 51,
  Command_Id_TOGGLE_SHOW_HELP_PANE = 49,
  Command_Id_TOGGLE_SHOW_LABELS_AT_TOP = 52,
  Command_Id_TOGGLE_SHOW_MASTER_TUNE = 77,
  Command_Id_TOGGLE_SHOW_SELECTION_BUTTONS = 50,
  Command_Id_TOGGLE_SHOW_TIMES_AT_TOP = 53,
  Command_Id_TOGGLE_SHOW_TOOLTIPS = 48,
  Command_Id_TOGGLE_START_STOP = 28,
  Command_Id_TOGGLE_STRETCH_ENABLE = 29,
  Command_Id_TOGGLE_TRANSFORM_ENABLE = 88,
  Command_Id_TOGGLE_WHOLE_SONG_LOOP = 30,
  Command_Id_TREE_CLOSE = 31,
  Command_Id_TREE_DOWN = 32,
  Command_Id_TREE_LEFT = 33,
  Command_Id_TREE_OPEN = 34,
  Command_Id_TREE_RIGHT = 35,
  Command_Id_TREE_UP = 36,
  Command_Id_UNDO = 37,
  Command_Id_UNSELECT = 380000,
  Command_Id_WHATS_NEW_PAGE = 73,
  Command_Id_ZOOM_IN = 39,
  Command_Id_ZOOM_OUT = 40,
  Command_Id_ZOOM_OUT_FULL = 64,
  Command_Id_ZOOM_TO_SELECTION = 45,
  Command_Id_FIRST_FREE_TYPE = 101,
  Command_Id_QUIT = 4097,
  Command_Id_DEL = 4098,
  Command_Id_CUT = 4099,
  Command_Id_COPY = 4100,
  Command_Id_PASTE = 4101,
  Command_Id_SELECT_ALL = 4102,
  Command_Id_DESELECT_ALL = 4103
};
bool Command_Id_IsValid(int value);
const Command_Id Command_Id_Id_MIN = Command_Id_NONE;
const Command_Id Command_Id_Id_MAX = Command_Id_SET_LANGUAGE;
const int Command_Id_Id_ARRAYSIZE = Command_Id_Id_MAX + 1;

const ::google::protobuf::EnumDescriptor* Command_Id_descriptor();
inline const ::std::string& Command_Id_Name(Command_Id value) {
  return ::google::protobuf::internal::NameOfEnum(
    Command_Id_descriptor(), value);
}
inline bool Command_Id_Parse(
    const ::std::string& name, Command_Id* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Command_Id>(
    Command_Id_descriptor(), name, value);
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

  typedef Command_Id Id;
  static const Id NONE = Command_Id_NONE;
  static const Id ABOUT_THIS_PROGRAM = Command_Id_ABOUT_THIS_PROGRAM;
  static const Id ADD_LOOP_POINT = Command_Id_ADD_LOOP_POINT;
  static const Id AUDIO_PREFERENCES = Command_Id_AUDIO_PREFERENCES;
  static const Id CHECK_FOR_UPDATES = Command_Id_CHECK_FOR_UPDATES;
  static const Id CLEAR_KEYBOARD_MAPPINGS = Command_Id_CLEAR_KEYBOARD_MAPPINGS;
  static const Id CLEAR_MIDI_MAPPINGS = Command_Id_CLEAR_MIDI_MAPPINGS;
  static const Id CLEAR_LOOPS = Command_Id_CLEAR_LOOPS;
  static const Id CLEAR_NAVIGATOR = Command_Id_CLEAR_NAVIGATOR;
  static const Id CLEAR_ALL_SETTINGS = Command_Id_CLEAR_ALL_SETTINGS;
  static const Id CLEAR_SETTINGS_FOR_THIS_TRACK = Command_Id_CLEAR_SETTINGS_FOR_THIS_TRACK;
  static const Id CLEAR_SAVED_FILE_DATA = Command_Id_CLEAR_SAVED_FILE_DATA;
  static const Id CLOSE_FILE = Command_Id_CLOSE_FILE;
  static const Id COPY_ALL_LOOP_POINTS = Command_Id_COPY_ALL_LOOP_POINTS;
  static const Id DIM_VOLUME_TOGGLE = Command_Id_DIM_VOLUME_TOGGLE;
  static const Id EJECT_CDS = Command_Id_EJECT_CDS;
  static const Id EXPORT_KEYBOARD_MAPPINGS = Command_Id_EXPORT_KEYBOARD_MAPPINGS;
  static const Id EXPORT_MIDI_MAPPINGS = Command_Id_EXPORT_MIDI_MAPPINGS;
  static const Id EXPORT_SETTINGS = Command_Id_EXPORT_SETTINGS;
  static const Id IMPORT_KEYBOARD_MAPPINGS = Command_Id_IMPORT_KEYBOARD_MAPPINGS;
  static const Id IMPORT_MIDI_MAPPINGS = Command_Id_IMPORT_MIDI_MAPPINGS;
  static const Id IMPORT_SETTINGS = Command_Id_IMPORT_SETTINGS;
  static const Id INVERT_LOOP_SELECTION = Command_Id_INVERT_LOOP_SELECTION;
  static const Id JUMP = Command_Id_JUMP;
  static const Id JUMP_SELECTED = Command_Id_JUMP_SELECTED;
  static const Id KEYBOARD_MAPPINGS = Command_Id_KEYBOARD_MAPPINGS;
  static const Id LOOP_NEXT_SEGMENT = Command_Id_LOOP_NEXT_SEGMENT;
  static const Id MIDI_MAPPINGS = Command_Id_MIDI_MAPPINGS;
  static const Id MODE_ADD_LOOP_POINT = Command_Id_MODE_ADD_LOOP_POINT;
  static const Id MODE_DRAG = Command_Id_MODE_DRAG;
  static const Id MODE_SET_TIME = Command_Id_MODE_SET_TIME;
  static const Id MODE_ZOOM_IN = Command_Id_MODE_ZOOM_IN;
  static const Id MUTE_VOLUME_TOGGLE = Command_Id_MUTE_VOLUME_TOGGLE;
  static const Id NUDGE_BACKWARD = Command_Id_NUDGE_BACKWARD;
  static const Id NUDGE_FORWARD = Command_Id_NUDGE_FORWARD;
  static const Id NUDGE_BEGIN_LEFT = Command_Id_NUDGE_BEGIN_LEFT;
  static const Id NUDGE_BEGIN_RIGHT = Command_Id_NUDGE_BEGIN_RIGHT;
  static const Id NUDGE_END_LEFT = Command_Id_NUDGE_END_LEFT;
  static const Id NUDGE_END_RIGHT = Command_Id_NUDGE_END_RIGHT;
  static const Id NUDGE_SPEED_DOWN = Command_Id_NUDGE_SPEED_DOWN;
  static const Id NUDGE_SPEED_UP = Command_Id_NUDGE_SPEED_UP;
  static const Id NUDGE_VOLUME_DOWN = Command_Id_NUDGE_VOLUME_DOWN;
  static const Id NUDGE_VOLUME_UP = Command_Id_NUDGE_VOLUME_UP;
  static const Id OPEN = Command_Id_OPEN;
  static const Id OPEN_MANUAL = Command_Id_OPEN_MANUAL;
  static const Id OPEN_PREVIOUS_FILE = Command_Id_OPEN_PREVIOUS_FILE;
  static const Id OPEN_SLOWGOLD_DIRECTORY = Command_Id_OPEN_SLOWGOLD_DIRECTORY;
  static const Id PASTE_OVER_LOOP_POINTS = Command_Id_PASTE_OVER_LOOP_POINTS;
  static const Id RECENT_FILES = Command_Id_RECENT_FILES;
  static const Id REDO = Command_Id_REDO;
  static const Id REQUEST_SUPPORT = Command_Id_REQUEST_SUPPORT;
  static const Id RESET_GAIN_TO_UNITY = Command_Id_RESET_GAIN_TO_UNITY;
  static const Id SAVE_FILE = Command_Id_SAVE_FILE;
  static const Id SAVE_FILE_SELECTION = Command_Id_SAVE_FILE_SELECTION;
  static const Id SELECT = Command_Id_SELECT;
  static const Id SELECT_ONLY = Command_Id_SELECT_ONLY;
  static const Id SET_LANGUAGE = Command_Id_SET_LANGUAGE;
  static const Id SET_SAVE_FORMAT = Command_Id_SET_SAVE_FORMAT;
  static const Id SET_SAVE_AS_AIFF = Command_Id_SET_SAVE_AS_AIFF;
  static const Id SET_SAVE_AS_FLAC = Command_Id_SET_SAVE_AS_FLAC;
  static const Id SET_SAVE_AS_OGG = Command_Id_SET_SAVE_AS_OGG;
  static const Id SET_SAVE_AS_WAV = Command_Id_SET_SAVE_AS_WAV;
  static const Id TOGGLE_ADVANCED_MENUS = Command_Id_TOGGLE_ADVANCED_MENUS;
  static const Id TOGGLE_AUTOMATIC_UPDATES = Command_Id_TOGGLE_AUTOMATIC_UPDATES;
  static const Id TOGGLE_FOLLOW_CURSOR = Command_Id_TOGGLE_FOLLOW_CURSOR;
  static const Id TOGGLE_GRID_DISPLAY = Command_Id_TOGGLE_GRID_DISPLAY;
  static const Id TOGGLE_COMMAND_BAR_AT_LEFT = Command_Id_TOGGLE_COMMAND_BAR_AT_LEFT;
  static const Id TOGGLE_COMMAND_BAR_AT_TOP = Command_Id_TOGGLE_COMMAND_BAR_AT_TOP;
  static const Id TOGGLE_FILE_OPEN_TREE_DISPLAY = Command_Id_TOGGLE_FILE_OPEN_TREE_DISPLAY;
  static const Id TOGGLE_MODES_AT_LEFT = Command_Id_TOGGLE_MODES_AT_LEFT;
  static const Id TOGGLE_MODES_AT_TOP = Command_Id_TOGGLE_MODES_AT_TOP;
  static const Id TOGGLE_PARALLEL_WAVEFORMS = Command_Id_TOGGLE_PARALLEL_WAVEFORMS;
  static const Id TOGGLE_PREFADER_LEVELS = Command_Id_TOGGLE_PREFADER_LEVELS;
  static const Id TOGGLE_SELECTION = Command_Id_TOGGLE_SELECTION;
  static const Id TOGGLE_SHOW_ABOUT_WINDOW_AT_STARTUP = Command_Id_TOGGLE_SHOW_ABOUT_WINDOW_AT_STARTUP;
  static const Id TOGGLE_SHOW_CURSOR_LABELS = Command_Id_TOGGLE_SHOW_CURSOR_LABELS;
  static const Id TOGGLE_SHOW_HELP_PANE = Command_Id_TOGGLE_SHOW_HELP_PANE;
  static const Id TOGGLE_SHOW_LABELS_AT_TOP = Command_Id_TOGGLE_SHOW_LABELS_AT_TOP;
  static const Id TOGGLE_SHOW_MASTER_TUNE = Command_Id_TOGGLE_SHOW_MASTER_TUNE;
  static const Id TOGGLE_SHOW_SELECTION_BUTTONS = Command_Id_TOGGLE_SHOW_SELECTION_BUTTONS;
  static const Id TOGGLE_SHOW_TIMES_AT_TOP = Command_Id_TOGGLE_SHOW_TIMES_AT_TOP;
  static const Id TOGGLE_SHOW_TOOLTIPS = Command_Id_TOGGLE_SHOW_TOOLTIPS;
  static const Id TOGGLE_START_STOP = Command_Id_TOGGLE_START_STOP;
  static const Id TOGGLE_STRETCH_ENABLE = Command_Id_TOGGLE_STRETCH_ENABLE;
  static const Id TOGGLE_TRANSFORM_ENABLE = Command_Id_TOGGLE_TRANSFORM_ENABLE;
  static const Id TOGGLE_WHOLE_SONG_LOOP = Command_Id_TOGGLE_WHOLE_SONG_LOOP;
  static const Id TREE_CLOSE = Command_Id_TREE_CLOSE;
  static const Id TREE_DOWN = Command_Id_TREE_DOWN;
  static const Id TREE_LEFT = Command_Id_TREE_LEFT;
  static const Id TREE_OPEN = Command_Id_TREE_OPEN;
  static const Id TREE_RIGHT = Command_Id_TREE_RIGHT;
  static const Id TREE_UP = Command_Id_TREE_UP;
  static const Id UNDO = Command_Id_UNDO;
  static const Id UNSELECT = Command_Id_UNSELECT;
  static const Id WHATS_NEW_PAGE = Command_Id_WHATS_NEW_PAGE;
  static const Id ZOOM_IN = Command_Id_ZOOM_IN;
  static const Id ZOOM_OUT = Command_Id_ZOOM_OUT;
  static const Id ZOOM_OUT_FULL = Command_Id_ZOOM_OUT_FULL;
  static const Id ZOOM_TO_SELECTION = Command_Id_ZOOM_TO_SELECTION;
  static const Id FIRST_FREE_TYPE = Command_Id_FIRST_FREE_TYPE;
  static const Id QUIT = Command_Id_QUIT;
  static const Id DEL = Command_Id_DEL;
  static const Id CUT = Command_Id_CUT;
  static const Id COPY = Command_Id_COPY;
  static const Id PASTE = Command_Id_PASTE;
  static const Id SELECT_ALL = Command_Id_SELECT_ALL;
  static const Id DESELECT_ALL = Command_Id_DESELECT_ALL;
  static inline bool Id_IsValid(int value) {
    return Command_Id_IsValid(value);
  }
  static const Id Id_MIN =
    Command_Id_Id_MIN;
  static const Id Id_MAX =
    Command_Id_Id_MAX;
  static const int Id_ARRAYSIZE =
    Command_Id_Id_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Id_descriptor() {
    return Command_Id_descriptor();
  }
  static inline const ::std::string& Id_Name(Id value) {
    return Command_Id_Name(value);
  }
  static inline bool Id_Parse(const ::std::string& name,
      Id* value) {
    return Command_Id_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:rec.slow.Command)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;


  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[1];

  friend void  protobuf_AddDesc_rec_2fslow_2fcommands_2fCommand_2eproto();
  friend void protobuf_AssignDesc_rec_2fslow_2fcommands_2fCommand_2eproto();
  friend void protobuf_ShutdownFile_rec_2fslow_2fcommands_2fCommand_2eproto();

  void InitAsDefaultInstance();
  static Command* default_instance_;
};
// ===================================================================


// ===================================================================

// Command


// @@protoc_insertion_point(namespace_scope)

}  // namespace slow
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::rec::slow::Command_Id>() {
  return ::rec::slow::Command_Id_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2fslow_2fcommands_2fCommand_2eproto__INCLUDED
