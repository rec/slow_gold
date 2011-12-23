// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/gui/WindowPosition.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace rec {
namespace gui {

namespace {

const ::google::protobuf::Descriptor* WindowPosition_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  WindowPosition_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2fgui_2fWindowPosition_2eproto() {
  protobuf_AddDesc_rec_2fgui_2fWindowPosition_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/gui/WindowPosition.proto");
  GOOGLE_CHECK(file != NULL);
  WindowPosition_descriptor_ = file->message_type(0);
  static const int WindowPosition_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WindowPosition, juce_position_),
  };
  WindowPosition_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      WindowPosition_descriptor_,
      WindowPosition::default_instance_,
      WindowPosition_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WindowPosition, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WindowPosition, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(WindowPosition));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2fgui_2fWindowPosition_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    WindowPosition_descriptor_, &WindowPosition::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2fgui_2fWindowPosition_2eproto() {
  delete WindowPosition::default_instance_;
  delete WindowPosition_reflection_;
}

void protobuf_AddDesc_rec_2fgui_2fWindowPosition_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::rec::gui::protobuf_AddDesc_rec_2fgui_2fGeometry_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\034rec/gui/WindowPosition.proto\022\007rec.gui\032"
    "\026rec/gui/Geometry.proto\"\'\n\016WindowPositio"
    "n\022\025\n\rjuce_position\030\001 \001(\t", 104);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/gui/WindowPosition.proto", &protobuf_RegisterTypes);
  WindowPosition::default_instance_ = new WindowPosition();
  WindowPosition::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2fgui_2fWindowPosition_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2fgui_2fWindowPosition_2eproto {
  StaticDescriptorInitializer_rec_2fgui_2fWindowPosition_2eproto() {
    protobuf_AddDesc_rec_2fgui_2fWindowPosition_2eproto();
  }
} static_descriptor_initializer_rec_2fgui_2fWindowPosition_2eproto_;


// ===================================================================

const ::std::string WindowPosition::_default_juce_position_;
#ifndef _MSC_VER
const int WindowPosition::kJucePositionFieldNumber;
#endif  // !_MSC_VER

WindowPosition::WindowPosition()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void WindowPosition::InitAsDefaultInstance() {
}

WindowPosition::WindowPosition(const WindowPosition& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void WindowPosition::SharedCtor() {
  _cached_size_ = 0;
  juce_position_ = const_cast< ::std::string*>(&_default_juce_position_);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

WindowPosition::~WindowPosition() {
  SharedDtor();
}

void WindowPosition::SharedDtor() {
  if (juce_position_ != &_default_juce_position_) {
    delete juce_position_;
  }
  if (this != default_instance_) {
  }
}

void WindowPosition::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* WindowPosition::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return WindowPosition_descriptor_;
}

const WindowPosition& WindowPosition::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fgui_2fWindowPosition_2eproto();  return *default_instance_;
}

WindowPosition* WindowPosition::default_instance_ = NULL;

WindowPosition* WindowPosition::New() const {
  return new WindowPosition;
}

void WindowPosition::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (_has_bit(0)) {
      if (juce_position_ != &_default_juce_position_) {
        juce_position_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool WindowPosition::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string juce_position = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_juce_position()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->juce_position().data(), this->juce_position().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
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

void WindowPosition::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional string juce_position = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->juce_position().data(), this->juce_position().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->juce_position(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* WindowPosition::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional string juce_position = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->juce_position().data(), this->juce_position().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->juce_position(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int WindowPosition::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string juce_position = 1;
    if (has_juce_position()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->juce_position());
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

void WindowPosition::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const WindowPosition* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const WindowPosition*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void WindowPosition::MergeFrom(const WindowPosition& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_juce_position(from.juce_position());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void WindowPosition::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void WindowPosition::CopyFrom(const WindowPosition& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool WindowPosition::IsInitialized() const {
  
  return true;
}

void WindowPosition::Swap(WindowPosition* other) {
  if (other != this) {
    std::swap(juce_position_, other->juce_position_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata WindowPosition::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = WindowPosition_descriptor_;
  metadata.reflection = WindowPosition_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace gui
}  // namespace rec

// @@protoc_insertion_point(global_scope)
