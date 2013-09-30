// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/gui/proto/Button.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/gui/proto/Button.pb.h"

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
namespace gui {

namespace {

const ::google::protobuf::Descriptor* ButtonProto_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ButtonProto_reflection_ = NULL;
const ::google::protobuf::Descriptor* ButtonProto_State_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ButtonProto_State_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* ButtonProto_Behavior_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* ButtonProto_Style_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2fgui_2fproto_2fButton_2eproto() {
  protobuf_AddDesc_rec_2fgui_2fproto_2fButton_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/gui/proto/Button.proto");
  GOOGLE_CHECK(file != NULL);
  ButtonProto_descriptor_ = file->message_type(0);
  static const int ButtonProto_offsets_[7] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ButtonProto, behavior_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ButtonProto, style_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ButtonProto, state_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ButtonProto, state_on_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ButtonProto, command_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ButtonProto, command_index_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ButtonProto, mode_index_),
  };
  ButtonProto_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ButtonProto_descriptor_,
      ButtonProto::default_instance_,
      ButtonProto_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ButtonProto, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ButtonProto, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ButtonProto));
  ButtonProto_State_descriptor_ = ButtonProto_descriptor_->nested_type(0);
  static const int ButtonProto_State_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ButtonProto_State, normal_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ButtonProto_State, over_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ButtonProto_State, pressed_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ButtonProto_State, disabled_),
  };
  ButtonProto_State_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ButtonProto_State_descriptor_,
      ButtonProto_State::default_instance_,
      ButtonProto_State_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ButtonProto_State, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ButtonProto_State, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ButtonProto_State));
  ButtonProto_Behavior_descriptor_ = ButtonProto_descriptor_->enum_type(0);
  ButtonProto_Style_descriptor_ = ButtonProto_descriptor_->enum_type(1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2fgui_2fproto_2fButton_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ButtonProto_descriptor_, &ButtonProto::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ButtonProto_State_descriptor_, &ButtonProto_State::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2fgui_2fproto_2fButton_2eproto() {
  delete ButtonProto::default_instance_;
  delete ButtonProto_reflection_;
  delete ButtonProto_State::default_instance_;
  delete ButtonProto_State_reflection_;
}

void protobuf_AddDesc_rec_2fgui_2fproto_2fButton_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\032rec/gui/proto/Button.proto\022\007rec.gui\"\347\003"
    "\n\013ButtonProto\022/\n\010behavior\030\001 \001(\0162\035.rec.gu"
    "i.ButtonProto.Behavior\022)\n\005style\030\002 \001(\0162\032."
    "rec.gui.ButtonProto.Style\022)\n\005state\030\003 \001(\013"
    "2\032.rec.gui.ButtonProto.State\022,\n\010state_on"
    "\030\004 \001(\0132\032.rec.gui.ButtonProto.State\022\017\n\007co"
    "mmand\030\005 \001(\t\022\025\n\rcommand_index\030\006 \001(\r\022\022\n\nmo"
    "de_index\030\007 \001(\r\032H\n\005State\022\016\n\006normal\030\001 \001(\010\022"
    "\014\n\004over\030\002 \001(\010\022\017\n\007pressed\030\003 \001(\010\022\020\n\010disabl"
    "ed\030\004 \001(\010\"+\n\010Behavior\022\t\n\005CLICK\020\000\022\n\n\006TOGGL"
    "E\020\001\022\010\n\004MODE\020\002\"p\n\005Style\022\017\n\013ImageFitted\020\000\022"
    "\014\n\010ImageRaw\020\001\022\027\n\023ImageAboveTextLabel\020\002\022\033"
    "\n\027ImageOnButtonBackground\020\003\022\022\n\016ImageStre"
    "tched\020\004", 527);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/gui/proto/Button.proto", &protobuf_RegisterTypes);
  ButtonProto::default_instance_ = new ButtonProto();
  ButtonProto_State::default_instance_ = new ButtonProto_State();
  ButtonProto::default_instance_->InitAsDefaultInstance();
  ButtonProto_State::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2fgui_2fproto_2fButton_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2fgui_2fproto_2fButton_2eproto {
  StaticDescriptorInitializer_rec_2fgui_2fproto_2fButton_2eproto() {
    protobuf_AddDesc_rec_2fgui_2fproto_2fButton_2eproto();
  }
} static_descriptor_initializer_rec_2fgui_2fproto_2fButton_2eproto_;

// ===================================================================

const ::google::protobuf::EnumDescriptor* ButtonProto_Behavior_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ButtonProto_Behavior_descriptor_;
}
bool ButtonProto_Behavior_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const ButtonProto_Behavior ButtonProto::CLICK;
const ButtonProto_Behavior ButtonProto::TOGGLE;
const ButtonProto_Behavior ButtonProto::MODE;
const ButtonProto_Behavior ButtonProto::Behavior_MIN;
const ButtonProto_Behavior ButtonProto::Behavior_MAX;
const int ButtonProto::Behavior_ARRAYSIZE;
#endif  // _MSC_VER
const ::google::protobuf::EnumDescriptor* ButtonProto_Style_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ButtonProto_Style_descriptor_;
}
bool ButtonProto_Style_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const ButtonProto_Style ButtonProto::ImageFitted;
const ButtonProto_Style ButtonProto::ImageRaw;
const ButtonProto_Style ButtonProto::ImageAboveTextLabel;
const ButtonProto_Style ButtonProto::ImageOnButtonBackground;
const ButtonProto_Style ButtonProto::ImageStretched;
const ButtonProto_Style ButtonProto::Style_MIN;
const ButtonProto_Style ButtonProto::Style_MAX;
const int ButtonProto::Style_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int ButtonProto_State::kNormalFieldNumber;
const int ButtonProto_State::kOverFieldNumber;
const int ButtonProto_State::kPressedFieldNumber;
const int ButtonProto_State::kDisabledFieldNumber;
#endif  // !_MSC_VER

ButtonProto_State::ButtonProto_State()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void ButtonProto_State::InitAsDefaultInstance() {
}

ButtonProto_State::ButtonProto_State(const ButtonProto_State& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void ButtonProto_State::SharedCtor() {
  _cached_size_ = 0;
  normal_ = false;
  over_ = false;
  pressed_ = false;
  disabled_ = false;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ButtonProto_State::~ButtonProto_State() {
  SharedDtor();
}

void ButtonProto_State::SharedDtor() {
  if (this != default_instance_) {
  }
}

void ButtonProto_State::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ButtonProto_State::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ButtonProto_State_descriptor_;
}

const ButtonProto_State& ButtonProto_State::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fgui_2fproto_2fButton_2eproto();
  return *default_instance_;
}

ButtonProto_State* ButtonProto_State::default_instance_ = NULL;

ButtonProto_State* ButtonProto_State::New() const {
  return new ButtonProto_State;
}

void ButtonProto_State::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    normal_ = false;
    over_ = false;
    pressed_ = false;
    disabled_ = false;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ButtonProto_State::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional bool normal = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &normal_)));
          set_has_normal();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_over;
        break;
      }

      // optional bool over = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_over:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &over_)));
          set_has_over();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_pressed;
        break;
      }

      // optional bool pressed = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_pressed:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &pressed_)));
          set_has_pressed();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_disabled;
        break;
      }

      // optional bool disabled = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_disabled:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &disabled_)));
          set_has_disabled();
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

void ButtonProto_State::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional bool normal = 1;
  if (has_normal()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(1, this->normal(), output);
  }

  // optional bool over = 2;
  if (has_over()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(2, this->over(), output);
  }

  // optional bool pressed = 3;
  if (has_pressed()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(3, this->pressed(), output);
  }

  // optional bool disabled = 4;
  if (has_disabled()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(4, this->disabled(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* ButtonProto_State::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional bool normal = 1;
  if (has_normal()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(1, this->normal(), target);
  }

  // optional bool over = 2;
  if (has_over()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(2, this->over(), target);
  }

  // optional bool pressed = 3;
  if (has_pressed()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(3, this->pressed(), target);
  }

  // optional bool disabled = 4;
  if (has_disabled()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(4, this->disabled(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int ButtonProto_State::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional bool normal = 1;
    if (has_normal()) {
      total_size += 1 + 1;
    }

    // optional bool over = 2;
    if (has_over()) {
      total_size += 1 + 1;
    }

    // optional bool pressed = 3;
    if (has_pressed()) {
      total_size += 1 + 1;
    }

    // optional bool disabled = 4;
    if (has_disabled()) {
      total_size += 1 + 1;
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

void ButtonProto_State::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ButtonProto_State* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ButtonProto_State*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ButtonProto_State::MergeFrom(const ButtonProto_State& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_normal()) {
      set_normal(from.normal());
    }
    if (from.has_over()) {
      set_over(from.over());
    }
    if (from.has_pressed()) {
      set_pressed(from.pressed());
    }
    if (from.has_disabled()) {
      set_disabled(from.disabled());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ButtonProto_State::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ButtonProto_State::CopyFrom(const ButtonProto_State& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ButtonProto_State::IsInitialized() const {

  return true;
}

void ButtonProto_State::Swap(ButtonProto_State* other) {
  if (other != this) {
    std::swap(normal_, other->normal_);
    std::swap(over_, other->over_);
    std::swap(pressed_, other->pressed_);
    std::swap(disabled_, other->disabled_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ButtonProto_State::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ButtonProto_State_descriptor_;
  metadata.reflection = ButtonProto_State_reflection_;
  return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int ButtonProto::kBehaviorFieldNumber;
const int ButtonProto::kStyleFieldNumber;
const int ButtonProto::kStateFieldNumber;
const int ButtonProto::kStateOnFieldNumber;
const int ButtonProto::kCommandFieldNumber;
const int ButtonProto::kCommandIndexFieldNumber;
const int ButtonProto::kModeIndexFieldNumber;
#endif  // !_MSC_VER

ButtonProto::ButtonProto()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void ButtonProto::InitAsDefaultInstance() {
  state_ = const_cast< ::rec::gui::ButtonProto_State*>(&::rec::gui::ButtonProto_State::default_instance());
  state_on_ = const_cast< ::rec::gui::ButtonProto_State*>(&::rec::gui::ButtonProto_State::default_instance());
}

ButtonProto::ButtonProto(const ButtonProto& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void ButtonProto::SharedCtor() {
  _cached_size_ = 0;
  behavior_ = 0;
  style_ = 0;
  state_ = NULL;
  state_on_ = NULL;
  command_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  command_index_ = 0u;
  mode_index_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ButtonProto::~ButtonProto() {
  SharedDtor();
}

void ButtonProto::SharedDtor() {
  if (command_ != &::google::protobuf::internal::kEmptyString) {
    delete command_;
  }
  if (this != default_instance_) {
    delete state_;
    delete state_on_;
  }
}

void ButtonProto::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ButtonProto::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ButtonProto_descriptor_;
}

const ButtonProto& ButtonProto::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fgui_2fproto_2fButton_2eproto();
  return *default_instance_;
}

ButtonProto* ButtonProto::default_instance_ = NULL;

ButtonProto* ButtonProto::New() const {
  return new ButtonProto;
}

void ButtonProto::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    behavior_ = 0;
    style_ = 0;
    if (has_state()) {
      if (state_ != NULL) state_->::rec::gui::ButtonProto_State::Clear();
    }
    if (has_state_on()) {
      if (state_on_ != NULL) state_on_->::rec::gui::ButtonProto_State::Clear();
    }
    if (has_command()) {
      if (command_ != &::google::protobuf::internal::kEmptyString) {
        command_->clear();
      }
    }
    command_index_ = 0u;
    mode_index_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ButtonProto::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .rec.gui.ButtonProto.Behavior behavior = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::rec::gui::ButtonProto_Behavior_IsValid(value)) {
            set_behavior(static_cast< ::rec::gui::ButtonProto_Behavior >(value));
          } else {
            mutable_unknown_fields()->AddVarint(1, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_style;
        break;
      }

      // optional .rec.gui.ButtonProto.Style style = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_style:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::rec::gui::ButtonProto_Style_IsValid(value)) {
            set_style(static_cast< ::rec::gui::ButtonProto_Style >(value));
          } else {
            mutable_unknown_fields()->AddVarint(2, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_state;
        break;
      }

      // optional .rec.gui.ButtonProto.State state = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_state:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_state()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_state_on;
        break;
      }

      // optional .rec.gui.ButtonProto.State state_on = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_state_on:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_state_on()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(42)) goto parse_command;
        break;
      }

      // optional string command = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_command:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_command()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->command().data(), this->command().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(48)) goto parse_command_index;
        break;
      }

      // optional uint32 command_index = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_command_index:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &command_index_)));
          set_has_command_index();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(56)) goto parse_mode_index;
        break;
      }

      // optional uint32 mode_index = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_mode_index:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &mode_index_)));
          set_has_mode_index();
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

void ButtonProto::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .rec.gui.ButtonProto.Behavior behavior = 1;
  if (has_behavior()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->behavior(), output);
  }

  // optional .rec.gui.ButtonProto.Style style = 2;
  if (has_style()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      2, this->style(), output);
  }

  // optional .rec.gui.ButtonProto.State state = 3;
  if (has_state()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->state(), output);
  }

  // optional .rec.gui.ButtonProto.State state_on = 4;
  if (has_state_on()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4, this->state_on(), output);
  }

  // optional string command = 5;
  if (has_command()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->command().data(), this->command().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      5, this->command(), output);
  }

  // optional uint32 command_index = 6;
  if (has_command_index()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(6, this->command_index(), output);
  }

  // optional uint32 mode_index = 7;
  if (has_mode_index()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(7, this->mode_index(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* ButtonProto::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .rec.gui.ButtonProto.Behavior behavior = 1;
  if (has_behavior()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->behavior(), target);
  }

  // optional .rec.gui.ButtonProto.Style style = 2;
  if (has_style()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      2, this->style(), target);
  }

  // optional .rec.gui.ButtonProto.State state = 3;
  if (has_state()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->state(), target);
  }

  // optional .rec.gui.ButtonProto.State state_on = 4;
  if (has_state_on()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        4, this->state_on(), target);
  }

  // optional string command = 5;
  if (has_command()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->command().data(), this->command().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        5, this->command(), target);
  }

  // optional uint32 command_index = 6;
  if (has_command_index()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(6, this->command_index(), target);
  }

  // optional uint32 mode_index = 7;
  if (has_mode_index()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(7, this->mode_index(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int ButtonProto::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .rec.gui.ButtonProto.Behavior behavior = 1;
    if (has_behavior()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->behavior());
    }

    // optional .rec.gui.ButtonProto.Style style = 2;
    if (has_style()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->style());
    }

    // optional .rec.gui.ButtonProto.State state = 3;
    if (has_state()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->state());
    }

    // optional .rec.gui.ButtonProto.State state_on = 4;
    if (has_state_on()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->state_on());
    }

    // optional string command = 5;
    if (has_command()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->command());
    }

    // optional uint32 command_index = 6;
    if (has_command_index()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->command_index());
    }

    // optional uint32 mode_index = 7;
    if (has_mode_index()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->mode_index());
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

void ButtonProto::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ButtonProto* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ButtonProto*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ButtonProto::MergeFrom(const ButtonProto& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_behavior()) {
      set_behavior(from.behavior());
    }
    if (from.has_style()) {
      set_style(from.style());
    }
    if (from.has_state()) {
      mutable_state()->::rec::gui::ButtonProto_State::MergeFrom(from.state());
    }
    if (from.has_state_on()) {
      mutable_state_on()->::rec::gui::ButtonProto_State::MergeFrom(from.state_on());
    }
    if (from.has_command()) {
      set_command(from.command());
    }
    if (from.has_command_index()) {
      set_command_index(from.command_index());
    }
    if (from.has_mode_index()) {
      set_mode_index(from.mode_index());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ButtonProto::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ButtonProto::CopyFrom(const ButtonProto& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ButtonProto::IsInitialized() const {

  return true;
}

void ButtonProto::Swap(ButtonProto* other) {
  if (other != this) {
    std::swap(behavior_, other->behavior_);
    std::swap(style_, other->style_);
    std::swap(state_, other->state_);
    std::swap(state_on_, other->state_on_);
    std::swap(command_, other->command_);
    std::swap(command_index_, other->command_index_);
    std::swap(mode_index_, other->mode_index_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ButtonProto::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ButtonProto_descriptor_;
  metadata.reflection = ButtonProto_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace gui
}  // namespace rec

// @@protoc_insertion_point(global_scope)
