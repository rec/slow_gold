// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/command/Command.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace rec {
namespace command {

namespace {

const ::google::protobuf::Descriptor* Command_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Command_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* Command_Type_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2fcommand_2fCommand_2eproto() {
  protobuf_AddDesc_rec_2fcommand_2fCommand_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/command/Command.proto");
  GOOGLE_CHECK(file != NULL);
  Command_descriptor_ = file->message_type(0);
  static const int Command_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command, command_),
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
  Command_Type_descriptor_ = Command_descriptor_->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2fcommand_2fCommand_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Command_descriptor_, &Command::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2fcommand_2fCommand_2eproto() {
  delete Command::default_instance_;
  delete Command_reflection_;
}

void protobuf_AddDesc_rec_2fcommand_2fCommand_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\031rec/command/Command.proto\022\013rec.command"
    "\"\222\017\n\007Command\022*\n\007command\030\001 \001(\0162\031.rec.comm"
    "and.Command.Type\"\332\016\n\004Type\022\010\n\004NONE\020\000\022\t\n\004Q"
    "UIT\020\201 \022\010\n\003DEL\020\202 \022\010\n\003CUT\020\203 \022\t\n\004COPY\020\204 \022\n\n"
    "\005PASTE\020\205 \022\017\n\nSELECT_ALL\020\206 \022\021\n\014DESELECT_A"
    "LL\020\207 \022\022\n\016ADD_LOOP_POINT\020\001\022\025\n\021AUDIO_PREFE"
    "RENCES\020\002\022\023\n\017CLEAR_NAVIGATOR\020\003\022\017\n\013CLEAR_L"
    "OOPS\020\004\022\031\n\025CLEAR_SAVED_FILE_DATA\020\005\022\016\n\nCLO"
    "SE_FILE\020\006\022!\n\035CONTRACT_FROM_NEXT_LOOP_POI"
    "NT\020K\022%\n!CONTRACT_FROM_PREVIOUS_LOOP_POIN"
    "T\020L\022\025\n\021DIM_VOLUME_TOGGLE\020M\022\r\n\tEJECT_CDS\020"
    "\007\022\035\n\031EXTEND_TO_NEXT_LOOP_POINT\020I\022!\n\035EXTE"
    "ND_TO_PREVIOUS_LOOP_POINT\020J\022\031\n\025INVERT_LO"
    "OP_SELECTION\020\023\022&\n\"JUMP_TO_NEXT_LOOP_POIN"
    "T_AND_SELECT\020\010\022*\n&JUMP_TO_PREVIOUS_LOOP_"
    "POINT_AND_SELECT\020\t\022\034\n\030JUMP_TO_START_AND_"
    "SELECT\020\n\022\032\n\026JUMP_TO_END_AND_SELECT\020W\022(\n$"
    "JUMP_TO_NEXT_LOOP_POINT_IN_SELECTION\020P\022,"
    "\n(JUMP_TO_PREVIOUS_LOOP_POINT_IN_SELECTI"
    "ON\020Q\022\036\n\032JUMP_TO_START_OF_SELECTION\020R\022\025\n\021"
    "KEYBOARD_MAPPINGS\020\022\022\021\n\rMIDI_MAPPINGS\020\021\022\026"
    "\n\022MUTE_VOLUME_TOGGLE\020N\022\024\n\020NUDGE_BEGIN_LE"
    "FT\020\013\022\025\n\021NUDGE_BEGIN_RIGHT\020\014\022\022\n\016NUDGE_END"
    "_LEFT\020\r\022\023\n\017NUDGE_END_RIGHT\020\016\022\025\n\021NUDGE_VO"
    "LUME_DOWN\020;\022\023\n\017NUDGE_VOLUME_UP\020H\022\010\n\004OPEN"
    "\020\017\022\020\n\014RECENT_FILES\020\020\022\027\n\023RESET_GAIN_TO_UN"
    "ITY\020O\022\014\n\010SELECT_0\020\024\022\014\n\010SELECT_1\020\025\022\014\n\010SEL"
    "ECT_2\020\026\022\014\n\010SELECT_3\020\027\022\014\n\010SELECT_4\020\030\022\014\n\010S"
    "ELECT_5\020\031\022\014\n\010SELECT_6\020\032\022\014\n\010SELECT_7\020\033\022\014\n"
    "\010SELECT_8\020\034\022\014\n\010SELECT_9\020\035\022\021\n\rSELECT_ONLY"
    "_0\020\036\022\021\n\rSELECT_ONLY_1\020\037\022\021\n\rSELECT_ONLY_2"
    "\020 \022\021\n\rSELECT_ONLY_3\020!\022\021\n\rSELECT_ONLY_4\020\""
    "\022\021\n\rSELECT_ONLY_5\020#\022\021\n\rSELECT_ONLY_6\020$\022\021"
    "\n\rSELECT_ONLY_7\020%\022\021\n\rSELECT_ONLY_8\020&\022\021\n\r"
    "SELECT_ONLY_9\020\'\022\025\n\021SELECT_FIRST_ONLY\020S\022\024"
    "\n\020SELECT_LAST_ONLY\020T\022\024\n\020SELECT_NEXT_ONLY"
    "\020U\022\030\n\024SELECT_PREVIOUS_ONLY\020V\022\014\n\010TOGGLE_0"
    "\020(\022\014\n\010TOGGLE_1\020)\022\014\n\010TOGGLE_2\020*\022\014\n\010TOGGLE"
    "_3\020+\022\014\n\010TOGGLE_4\020,\022\014\n\010TOGGLE_5\020-\022\014\n\010TOGG"
    "LE_6\020.\022\014\n\010TOGGLE_7\020/\022\014\n\010TOGGLE_8\0200\022\014\n\010TO"
    "GGLE_9\0201\022\032\n\026TOGGLE_WHOLE_SONG_LOOP\020:\022\025\n\021"
    "TOGGLE_START_STOP\0202\022\031\n\025TOGGLE_STRETCH_EN"
    "ABLE\0203\022\016\n\nTREE_CLOSE\0204\022\r\n\tTREE_DOWN\0205\022\r\n"
    "\tTREE_LEFT\0206\022\r\n\tTREE_OPEN\0207\022\016\n\nTREE_RIGH"
    "T\0208\022\013\n\007TREE_UP\0209\022\016\n\nUNSELECT_0\020<\022\016\n\nUNSE"
    "LECT_1\020=\022\016\n\nUNSELECT_2\020>\022\016\n\nUNSELECT_3\020?"
    "\022\016\n\nUNSELECT_4\020@\022\016\n\nUNSELECT_5\020A\022\016\n\nUNSE"
    "LECT_6\020B\022\016\n\nUNSELECT_7\020C\022\016\n\nUNSELECT_8\020D"
    "\022\016\n\nUNSELECT_9\020E\022\013\n\007ZOOM_IN\020F\022\014\n\010ZOOM_OU"
    "T\020G\022\020\n\014LAST_COMMAND\020W", 1981);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/command/Command.proto", &protobuf_RegisterTypes);
  Command::default_instance_ = new Command();
  Command::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2fcommand_2fCommand_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2fcommand_2fCommand_2eproto {
  StaticDescriptorInitializer_rec_2fcommand_2fCommand_2eproto() {
    protobuf_AddDesc_rec_2fcommand_2fCommand_2eproto();
  }
} static_descriptor_initializer_rec_2fcommand_2fCommand_2eproto_;


// ===================================================================

const ::google::protobuf::EnumDescriptor* Command_Type_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Command_Type_descriptor_;
}
bool Command_Type_IsValid(int value) {
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
    case 10:
    case 11:
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
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
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
    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
    case 47:
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
    case 71:
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
    case 4097:
    case 4098:
    case 4099:
    case 4100:
    case 4101:
    case 4102:
    case 4103:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const Command_Type Command::NONE;
const Command_Type Command::QUIT;
const Command_Type Command::DEL;
const Command_Type Command::CUT;
const Command_Type Command::COPY;
const Command_Type Command::PASTE;
const Command_Type Command::SELECT_ALL;
const Command_Type Command::DESELECT_ALL;
const Command_Type Command::ADD_LOOP_POINT;
const Command_Type Command::AUDIO_PREFERENCES;
const Command_Type Command::CLEAR_NAVIGATOR;
const Command_Type Command::CLEAR_LOOPS;
const Command_Type Command::CLEAR_SAVED_FILE_DATA;
const Command_Type Command::CLOSE_FILE;
const Command_Type Command::CONTRACT_FROM_NEXT_LOOP_POINT;
const Command_Type Command::CONTRACT_FROM_PREVIOUS_LOOP_POINT;
const Command_Type Command::DIM_VOLUME_TOGGLE;
const Command_Type Command::EJECT_CDS;
const Command_Type Command::EXTEND_TO_NEXT_LOOP_POINT;
const Command_Type Command::EXTEND_TO_PREVIOUS_LOOP_POINT;
const Command_Type Command::INVERT_LOOP_SELECTION;
const Command_Type Command::JUMP_TO_NEXT_LOOP_POINT_AND_SELECT;
const Command_Type Command::JUMP_TO_PREVIOUS_LOOP_POINT_AND_SELECT;
const Command_Type Command::JUMP_TO_START_AND_SELECT;
const Command_Type Command::JUMP_TO_END_AND_SELECT;
const Command_Type Command::JUMP_TO_NEXT_LOOP_POINT_IN_SELECTION;
const Command_Type Command::JUMP_TO_PREVIOUS_LOOP_POINT_IN_SELECTION;
const Command_Type Command::JUMP_TO_START_OF_SELECTION;
const Command_Type Command::KEYBOARD_MAPPINGS;
const Command_Type Command::MIDI_MAPPINGS;
const Command_Type Command::MUTE_VOLUME_TOGGLE;
const Command_Type Command::NUDGE_BEGIN_LEFT;
const Command_Type Command::NUDGE_BEGIN_RIGHT;
const Command_Type Command::NUDGE_END_LEFT;
const Command_Type Command::NUDGE_END_RIGHT;
const Command_Type Command::NUDGE_VOLUME_DOWN;
const Command_Type Command::NUDGE_VOLUME_UP;
const Command_Type Command::OPEN;
const Command_Type Command::RECENT_FILES;
const Command_Type Command::RESET_GAIN_TO_UNITY;
const Command_Type Command::SELECT_0;
const Command_Type Command::SELECT_1;
const Command_Type Command::SELECT_2;
const Command_Type Command::SELECT_3;
const Command_Type Command::SELECT_4;
const Command_Type Command::SELECT_5;
const Command_Type Command::SELECT_6;
const Command_Type Command::SELECT_7;
const Command_Type Command::SELECT_8;
const Command_Type Command::SELECT_9;
const Command_Type Command::SELECT_ONLY_0;
const Command_Type Command::SELECT_ONLY_1;
const Command_Type Command::SELECT_ONLY_2;
const Command_Type Command::SELECT_ONLY_3;
const Command_Type Command::SELECT_ONLY_4;
const Command_Type Command::SELECT_ONLY_5;
const Command_Type Command::SELECT_ONLY_6;
const Command_Type Command::SELECT_ONLY_7;
const Command_Type Command::SELECT_ONLY_8;
const Command_Type Command::SELECT_ONLY_9;
const Command_Type Command::SELECT_FIRST_ONLY;
const Command_Type Command::SELECT_LAST_ONLY;
const Command_Type Command::SELECT_NEXT_ONLY;
const Command_Type Command::SELECT_PREVIOUS_ONLY;
const Command_Type Command::TOGGLE_0;
const Command_Type Command::TOGGLE_1;
const Command_Type Command::TOGGLE_2;
const Command_Type Command::TOGGLE_3;
const Command_Type Command::TOGGLE_4;
const Command_Type Command::TOGGLE_5;
const Command_Type Command::TOGGLE_6;
const Command_Type Command::TOGGLE_7;
const Command_Type Command::TOGGLE_8;
const Command_Type Command::TOGGLE_9;
const Command_Type Command::TOGGLE_WHOLE_SONG_LOOP;
const Command_Type Command::TOGGLE_START_STOP;
const Command_Type Command::TOGGLE_STRETCH_ENABLE;
const Command_Type Command::TREE_CLOSE;
const Command_Type Command::TREE_DOWN;
const Command_Type Command::TREE_LEFT;
const Command_Type Command::TREE_OPEN;
const Command_Type Command::TREE_RIGHT;
const Command_Type Command::TREE_UP;
const Command_Type Command::UNSELECT_0;
const Command_Type Command::UNSELECT_1;
const Command_Type Command::UNSELECT_2;
const Command_Type Command::UNSELECT_3;
const Command_Type Command::UNSELECT_4;
const Command_Type Command::UNSELECT_5;
const Command_Type Command::UNSELECT_6;
const Command_Type Command::UNSELECT_7;
const Command_Type Command::UNSELECT_8;
const Command_Type Command::UNSELECT_9;
const Command_Type Command::ZOOM_IN;
const Command_Type Command::ZOOM_OUT;
const Command_Type Command::LAST_COMMAND;
const Command_Type Command::Type_MIN;
const Command_Type Command::Type_MAX;
const int Command::Type_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int Command::kCommandFieldNumber;
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
  command_ = 0;
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
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fcommand_2fCommand_2eproto();  return *default_instance_;
}

Command* Command::default_instance_ = NULL;

Command* Command::New() const {
  return new Command;
}

void Command::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    command_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Command::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .rec.command.Command.Type command = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::rec::command::Command_Type_IsValid(value)) {
            set_command(static_cast< ::rec::command::Command_Type >(value));
          } else {
            mutable_unknown_fields()->AddVarint(1, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Command::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .rec.command.Command.Type command = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->command(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Command::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .rec.command.Command.Type command = 1;
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->command(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Command::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .rec.command.Command.Type command = 1;
    if (has_command()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->command());
    }
    
  }
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
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_command(from.command());
    }
  }
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
    std::swap(command_, other->command_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
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

}  // namespace command
}  // namespace rec

// @@protoc_insertion_point(global_scope)
