// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/slow/commands/Command.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/slow/commands/Command.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace rec {
namespace slow {

namespace {

const ::google::protobuf::Descriptor* Command_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Command_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* Command_Id_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2fslow_2fcommands_2fCommand_2eproto() {
  protobuf_AddDesc_rec_2fslow_2fcommands_2fCommand_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/slow/commands/Command.proto");
  GOOGLE_CHECK(file != NULL);
  Command_descriptor_ = file->message_type(0);
  static const int Command_offsets_[1] = {
  };
  Command_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Command_descriptor_,
      Command::default_instance_,
      Command_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Command));
  Command_Id_descriptor_ = Command_descriptor_->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2fslow_2fcommands_2fCommand_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Command_descriptor_, &Command::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2fslow_2fcommands_2fCommand_2eproto() {
  delete Command::default_instance_;
  delete Command_reflection_;
}

void protobuf_AddDesc_rec_2fslow_2fcommands_2fCommand_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::rec::command::protobuf_AddDesc_rec_2fcommand_2fCommand_2eproto();
  ::rec::command::protobuf_AddDesc_rec_2fcommand_2fmap_2fCommandMap_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\037rec/slow/commands/Command.proto\022\010rec.s"
    "low\032\031rec/command/Command.proto\032 rec/comm"
    "and/map/CommandMap.proto\"\366\022\n\007Command\"\352\022\n"
    "\002Id\022\010\n\004NONE\020\000\022\026\n\022ABOUT_THIS_PROGRAM\020:\022\022\n"
    "\016ADD_LOOP_POINT\020\001\022\025\n\021AUDIO_PREFERENCES\020\002"
    "\022\025\n\021CHECK_FOR_UPDATES\020D\022\033\n\027CLEAR_KEYBOAR"
    "D_MAPPINGS\020[\022\027\n\023CLEAR_MIDI_MAPPINGS\020\\\022\017\n"
    "\013CLEAR_LOOPS\020\004\022\023\n\017CLEAR_NAVIGATOR\020\003\022\026\n\022C"
    "LEAR_ALL_SETTINGS\020O\022!\n\035CLEAR_SETTINGS_FO"
    "R_THIS_TRACK\020P\022\031\n\025CLEAR_SAVED_FILE_DATA\020"
    "\005\022\016\n\nCLOSE_FILE\020\006\022\030\n\024COPY_ALL_LOOP_POINT"
    "S\020_\022\r\n\tCOPY_FILE\020g\022\017\n\013DEAUTHORIZE\020f\022\025\n\021D"
    "IM_VOLUME_TOGGLE\020\007\022\r\n\tEJECT_CDS\020\010\022\034\n\030EXP"
    "ORT_KEYBOARD_MAPPINGS\020R\022\030\n\024EXPORT_MIDI_M"
    "APPINGS\020S\022\023\n\017EXPORT_SETTINGS\020K\022\034\n\030FIND_M"
    "ISSING_LOOP_POINTS\020i\022\034\n\030IMPORT_KEYBOARD_"
    "MAPPINGS\020T\022\030\n\024IMPORT_MIDI_MAPPINGS\020U\022\023\n\017"
    "IMPORT_SETTINGS\020L\022\031\n\025INVERT_LOOP_SELECTI"
    "ON\020\t\022\n\n\004JUMP\020\240\215\006\022\023\n\rJUMP_SELECTED\020\260\333\006\022\025\n"
    "\021KEYBOARD_MAPPINGS\020\014\022\025\n\021LOOP_NEXT_SEGMEN"
    "T\020^\022\021\n\rMIDI_MAPPINGS\020\r\022\027\n\023MODE_ADD_LOOP_"
    "POINT\020\?\022\r\n\tMODE_DRAG\020<\022\021\n\rMODE_SET_TIME\020"
    "=\022\020\n\014MODE_ZOOM_IN\020>\022\r\n\tMOVE_FILE\020h\022\026\n\022MU"
    "TE_VOLUME_TOGGLE\020\016\022\022\n\016NUDGE_BACKWARD\020Y\022\021"
    "\n\rNUDGE_FORWARD\020Z\022\024\n\020NUDGE_BEGIN_LEFT\020\017\022"
    "\025\n\021NUDGE_BEGIN_RIGHT\020\020\022\022\n\016NUDGE_END_LEFT"
    "\020\021\022\023\n\017NUDGE_END_RIGHT\020\022\022\024\n\020NUDGE_PITCH_D"
    "OWN\020j\022\022\n\016NUDGE_PITCH_UP\020k\022\024\n\020NUDGE_SPEED"
    "_DOWN\020V\022\022\n\016NUDGE_SPEED_UP\020W\022\025\n\021NUDGE_VOL"
    "UME_DOWN\020\023\022\023\n\017NUDGE_VOLUME_UP\020\024\022\010\n\004OPEN\020"
    "\025\022\017\n\013OPEN_MANUAL\020A\022\026\n\022OPEN_PREVIOUS_FILE"
    "\020N\022\033\n\027OPEN_SLOWGOLD_DIRECTORY\020J\022\032\n\026PASTE"
    "_OVER_LOOP_POINTS\020`\022\022\n\014RECENT_FILES\020\340\266\r\022"
    "\010\n\004REDO\020\027\022\023\n\017REQUEST_SUPPORT\020B\022\027\n\023RESET_"
    "GAIN_TO_UNITY\020\030\022\017\n\013EXPORT_FILE\020E\022\031\n\025EXPO"
    "RT_FILE_SELECTION\020F\022\014\n\006SELECT\020\220\241\017\022\021\n\013SEL"
    "ECT_ONLY\020\240\357\017\022\022\n\014SET_LANGUAGE\020\320\3418\022\027\n\021SET_"
    "EXPORT_FORMAT\020\360\252+\022\031\n\025TOGGLE_ADVANCED_MEN"
    "US\020;\022\034\n\030TOGGLE_AUTOMATIC_UPDATES\020C\022\023\n\017TO"
    "GGLE_AUTOPLAY\020e\022\030\n\024TOGGLE_FOLLOW_CURSOR\020"
    "+\022\027\n\023TOGGLE_GRID_DISPLAY\020\033\022\036\n\032TOGGLE_COM"
    "MAND_BAR_AT_LEFT\0206\022\035\n\031TOGGLE_COMMAND_BAR"
    "_AT_TOP\0207\022!\n\035TOGGLE_FILE_OPEN_TREE_DISPL"
    "AY\020H\022\030\n\024TOGGLE_MODES_AT_LEFT\0208\022\027\n\023TOGGLE"
    "_MODES_AT_TOP\0209\022\035\n\031TOGGLE_PARALLEL_WAVEF"
    "ORMS\020*\022\032\n\026TOGGLE_PREFADER_LEVELS\020.\022\026\n\020TO"
    "GGLE_SELECTION\020\220\203\031\022\'\n#TOGGLE_SHOW_ABOUT_"
    "WINDOW_AT_STARTUP\020Q\022\035\n\031TOGGLE_SHOW_CURSO"
    "R_LABELS\0203\022\031\n\025TOGGLE_SHOW_HELP_PANE\0201\022\035\n"
    "\031TOGGLE_SHOW_LABELS_AT_TOP\0204\022\033\n\027TOGGLE_S"
    "HOW_MASTER_TUNE\020M\022!\n\035TOGGLE_SHOW_SELECTI"
    "ON_BUTTONS\0202\022\034\n\030TOGGLE_SHOW_TIMES_AT_TOP"
    "\0205\022\030\n\024TOGGLE_SHOW_TOOLTIPS\0200\022\025\n\021TOGGLE_S"
    "TART_STOP\020\034\022\031\n\025TOGGLE_STRETCH_ENABLE\020\035\022\033"
    "\n\027TOGGLE_TRANSFORM_ENABLE\020X\022\032\n\026TOGGLE_WH"
    "OLE_SONG_LOOP\020\036\022\016\n\nTREE_CLOSE\020\037\022\r\n\tTREE_"
    "DOWN\020 \022\r\n\tTREE_LEFT\020!\022\r\n\tTREE_OPEN\020\"\022\016\n\n"
    "TREE_RIGHT\020#\022\013\n\007TREE_UP\020$\022\010\n\004UNDO\020%\022\016\n\010U"
    "NSELECT\020\340\230\027\022\022\n\016WHATS_NEW_PAGE\020I\022\013\n\007ZOOM_"
    "IN\020\'\022\014\n\010ZOOM_OUT\020(\022\021\n\rZOOM_OUT_FULL\020@\022\025\n"
    "\021ZOOM_TO_SELECTION\020-\022\021\n\rFIRST_FREE_ID\020l\022"
    "\t\n\004QUIT\020\201 \022\010\n\003DEL\020\202 \022\010\n\003CUT\020\203 \022\t\n\004COPY\020\204"
    " \022\n\n\005PASTE\020\205 \022\017\n\nSELECT_ALL\020\206 \022\021\n\014DESELE"
    "CT_ALL\020\207 ", 2529);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/slow/commands/Command.proto", &protobuf_RegisterTypes);
  Command::default_instance_ = new Command();
  Command::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2fslow_2fcommands_2fCommand_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2fslow_2fcommands_2fCommand_2eproto {
  StaticDescriptorInitializer_rec_2fslow_2fcommands_2fCommand_2eproto() {
    protobuf_AddDesc_rec_2fslow_2fcommands_2fCommand_2eproto();
  }
} static_descriptor_initializer_rec_2fslow_2fcommands_2fCommand_2eproto_;

// ===================================================================

const ::google::protobuf::EnumDescriptor* Command_Id_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Command_Id_descriptor_;
}
bool Command_Id_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 23:
    case 24:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 39:
    case 40:
    case 42:
    case 43:
    case 45:
    case 46:
    case 48:
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 56:
    case 57:
    case 58:
    case 59:
    case 60:
    case 61:
    case 62:
    case 63:
    case 64:
    case 65:
    case 66:
    case 67:
    case 68:
    case 69:
    case 70:
    case 72:
    case 73:
    case 74:
    case 75:
    case 76:
    case 77:
    case 78:
    case 79:
    case 80:
    case 81:
    case 82:
    case 83:
    case 84:
    case 85:
    case 86:
    case 87:
    case 88:
    case 89:
    case 90:
    case 91:
    case 92:
    case 94:
    case 95:
    case 96:
    case 101:
    case 102:
    case 103:
    case 104:
    case 105:
    case 106:
    case 107:
    case 108:
    case 4097:
    case 4098:
    case 4099:
    case 4100:
    case 4101:
    case 4102:
    case 4103:
    case 100000:
    case 110000:
    case 220000:
    case 250000:
    case 260000:
    case 380000:
    case 410000:
    case 710000:
    case 930000:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const Command_Id Command::NONE;
const Command_Id Command::ABOUT_THIS_PROGRAM;
const Command_Id Command::ADD_LOOP_POINT;
const Command_Id Command::AUDIO_PREFERENCES;
const Command_Id Command::CHECK_FOR_UPDATES;
const Command_Id Command::CLEAR_KEYBOARD_MAPPINGS;
const Command_Id Command::CLEAR_MIDI_MAPPINGS;
const Command_Id Command::CLEAR_LOOPS;
const Command_Id Command::CLEAR_NAVIGATOR;
const Command_Id Command::CLEAR_ALL_SETTINGS;
const Command_Id Command::CLEAR_SETTINGS_FOR_THIS_TRACK;
const Command_Id Command::CLEAR_SAVED_FILE_DATA;
const Command_Id Command::CLOSE_FILE;
const Command_Id Command::COPY_ALL_LOOP_POINTS;
const Command_Id Command::COPY_FILE;
const Command_Id Command::DEAUTHORIZE;
const Command_Id Command::DIM_VOLUME_TOGGLE;
const Command_Id Command::EJECT_CDS;
const Command_Id Command::EXPORT_KEYBOARD_MAPPINGS;
const Command_Id Command::EXPORT_MIDI_MAPPINGS;
const Command_Id Command::EXPORT_SETTINGS;
const Command_Id Command::FIND_MISSING_LOOP_POINTS;
const Command_Id Command::IMPORT_KEYBOARD_MAPPINGS;
const Command_Id Command::IMPORT_MIDI_MAPPINGS;
const Command_Id Command::IMPORT_SETTINGS;
const Command_Id Command::INVERT_LOOP_SELECTION;
const Command_Id Command::JUMP;
const Command_Id Command::JUMP_SELECTED;
const Command_Id Command::KEYBOARD_MAPPINGS;
const Command_Id Command::LOOP_NEXT_SEGMENT;
const Command_Id Command::MIDI_MAPPINGS;
const Command_Id Command::MODE_ADD_LOOP_POINT;
const Command_Id Command::MODE_DRAG;
const Command_Id Command::MODE_SET_TIME;
const Command_Id Command::MODE_ZOOM_IN;
const Command_Id Command::MOVE_FILE;
const Command_Id Command::MUTE_VOLUME_TOGGLE;
const Command_Id Command::NUDGE_BACKWARD;
const Command_Id Command::NUDGE_FORWARD;
const Command_Id Command::NUDGE_BEGIN_LEFT;
const Command_Id Command::NUDGE_BEGIN_RIGHT;
const Command_Id Command::NUDGE_END_LEFT;
const Command_Id Command::NUDGE_END_RIGHT;
const Command_Id Command::NUDGE_PITCH_DOWN;
const Command_Id Command::NUDGE_PITCH_UP;
const Command_Id Command::NUDGE_SPEED_DOWN;
const Command_Id Command::NUDGE_SPEED_UP;
const Command_Id Command::NUDGE_VOLUME_DOWN;
const Command_Id Command::NUDGE_VOLUME_UP;
const Command_Id Command::OPEN;
const Command_Id Command::OPEN_MANUAL;
const Command_Id Command::OPEN_PREVIOUS_FILE;
const Command_Id Command::OPEN_SLOWGOLD_DIRECTORY;
const Command_Id Command::PASTE_OVER_LOOP_POINTS;
const Command_Id Command::RECENT_FILES;
const Command_Id Command::REDO;
const Command_Id Command::REQUEST_SUPPORT;
const Command_Id Command::RESET_GAIN_TO_UNITY;
const Command_Id Command::EXPORT_FILE;
const Command_Id Command::EXPORT_FILE_SELECTION;
const Command_Id Command::SELECT;
const Command_Id Command::SELECT_ONLY;
const Command_Id Command::SET_LANGUAGE;
const Command_Id Command::SET_EXPORT_FORMAT;
const Command_Id Command::TOGGLE_ADVANCED_MENUS;
const Command_Id Command::TOGGLE_AUTOMATIC_UPDATES;
const Command_Id Command::TOGGLE_AUTOPLAY;
const Command_Id Command::TOGGLE_FOLLOW_CURSOR;
const Command_Id Command::TOGGLE_GRID_DISPLAY;
const Command_Id Command::TOGGLE_COMMAND_BAR_AT_LEFT;
const Command_Id Command::TOGGLE_COMMAND_BAR_AT_TOP;
const Command_Id Command::TOGGLE_FILE_OPEN_TREE_DISPLAY;
const Command_Id Command::TOGGLE_MODES_AT_LEFT;
const Command_Id Command::TOGGLE_MODES_AT_TOP;
const Command_Id Command::TOGGLE_PARALLEL_WAVEFORMS;
const Command_Id Command::TOGGLE_PREFADER_LEVELS;
const Command_Id Command::TOGGLE_SELECTION;
const Command_Id Command::TOGGLE_SHOW_ABOUT_WINDOW_AT_STARTUP;
const Command_Id Command::TOGGLE_SHOW_CURSOR_LABELS;
const Command_Id Command::TOGGLE_SHOW_HELP_PANE;
const Command_Id Command::TOGGLE_SHOW_LABELS_AT_TOP;
const Command_Id Command::TOGGLE_SHOW_MASTER_TUNE;
const Command_Id Command::TOGGLE_SHOW_SELECTION_BUTTONS;
const Command_Id Command::TOGGLE_SHOW_TIMES_AT_TOP;
const Command_Id Command::TOGGLE_SHOW_TOOLTIPS;
const Command_Id Command::TOGGLE_START_STOP;
const Command_Id Command::TOGGLE_STRETCH_ENABLE;
const Command_Id Command::TOGGLE_TRANSFORM_ENABLE;
const Command_Id Command::TOGGLE_WHOLE_SONG_LOOP;
const Command_Id Command::TREE_CLOSE;
const Command_Id Command::TREE_DOWN;
const Command_Id Command::TREE_LEFT;
const Command_Id Command::TREE_OPEN;
const Command_Id Command::TREE_RIGHT;
const Command_Id Command::TREE_UP;
const Command_Id Command::UNDO;
const Command_Id Command::UNSELECT;
const Command_Id Command::WHATS_NEW_PAGE;
const Command_Id Command::ZOOM_IN;
const Command_Id Command::ZOOM_OUT;
const Command_Id Command::ZOOM_OUT_FULL;
const Command_Id Command::ZOOM_TO_SELECTION;
const Command_Id Command::FIRST_FREE_ID;
const Command_Id Command::QUIT;
const Command_Id Command::DEL;
const Command_Id Command::CUT;
const Command_Id Command::COPY;
const Command_Id Command::PASTE;
const Command_Id Command::SELECT_ALL;
const Command_Id Command::DESELECT_ALL;
const Command_Id Command::Id_MIN;
const Command_Id Command::Id_MAX;
const int Command::Id_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
#endif  // !_MSC_VER

Command::Command()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Command::InitAsDefaultInstance() {
}

Command::Command(const Command& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Command::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command::~Command() {
  SharedDtor();
}

void Command::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Command::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Command_descriptor_;
}

const Command& Command::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fslow_2fcommands_2fCommand_2eproto();
  return *default_instance_;
}

Command* Command::default_instance_ = NULL;

Command* Command::New() const {
  return new Command;
}

void Command::Clear() {
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Command::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
        ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
      return true;
    }
    DO_(::google::protobuf::internal::WireFormat::SkipField(
          input, tag, mutable_unknown_fields()));
  }
  return true;
#undef DO_
}

void Command::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Command::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Command::ByteSize() const {
  int total_size = 0;

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Command::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Command* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Command*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Command::MergeFrom(const Command& from) {
  GOOGLE_CHECK_NE(&from, this);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Command::CopyFrom(const Command& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Command::IsInitialized() const {

  return true;
}

void Command::Swap(Command* other) {
  if (other != this) {
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Command::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Command_descriptor_;
  metadata.reflection = Command_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace slow
}  // namespace rec

// @@protoc_insertion_point(global_scope)
