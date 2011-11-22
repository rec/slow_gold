// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/slow/GuiSettings.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace rec {
namespace slow {

namespace {

const ::google::protobuf::Descriptor* GuiSettings_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  GuiSettings_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2fslow_2fGuiSettings_2eproto() {
  protobuf_AddDesc_rec_2fslow_2fGuiSettings_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/slow/GuiSettings.proto");
  GOOGLE_CHECK(file != NULL);
  GuiSettings_descriptor_ = file->message_type(0);
  static const int GuiSettings_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GuiSettings, show_grid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GuiSettings, drop_adds_to_browser_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GuiSettings, parallel_waveforms_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GuiSettings, show_names_in_waveform_),
  };
  GuiSettings_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      GuiSettings_descriptor_,
      GuiSettings::default_instance_,
      GuiSettings_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GuiSettings, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GuiSettings, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(GuiSettings));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2fslow_2fGuiSettings_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    GuiSettings_descriptor_, &GuiSettings::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2fslow_2fGuiSettings_2eproto() {
  delete GuiSettings::default_instance_;
  delete GuiSettings_reflection_;
}

void protobuf_AddDesc_rec_2fslow_2fGuiSettings_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\032rec/slow/GuiSettings.proto\022\010rec.slow\"\223"
    "\001\n\013GuiSettings\022\027\n\tshow_grid\030\001 \001(\010:\004true\022"
    "\"\n\024drop_adds_to_browser\030\002 \001(\010:\004true\022!\n\022p"
    "arallel_waveforms\030\003 \001(\010:\005false\022$\n\026show_n"
    "ames_in_waveform\030\004 \001(\010:\004true", 188);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/slow/GuiSettings.proto", &protobuf_RegisterTypes);
  GuiSettings::default_instance_ = new GuiSettings();
  GuiSettings::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2fslow_2fGuiSettings_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2fslow_2fGuiSettings_2eproto {
  StaticDescriptorInitializer_rec_2fslow_2fGuiSettings_2eproto() {
    protobuf_AddDesc_rec_2fslow_2fGuiSettings_2eproto();
  }
} static_descriptor_initializer_rec_2fslow_2fGuiSettings_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int GuiSettings::kShowGridFieldNumber;
const int GuiSettings::kDropAddsToBrowserFieldNumber;
const int GuiSettings::kParallelWaveformsFieldNumber;
const int GuiSettings::kShowNamesInWaveformFieldNumber;
#endif  // !_MSC_VER

GuiSettings::GuiSettings()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void GuiSettings::InitAsDefaultInstance() {
}

GuiSettings::GuiSettings(const GuiSettings& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void GuiSettings::SharedCtor() {
  _cached_size_ = 0;
  show_grid_ = true;
  drop_adds_to_browser_ = true;
  parallel_waveforms_ = false;
  show_names_in_waveform_ = true;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

GuiSettings::~GuiSettings() {
  SharedDtor();
}

void GuiSettings::SharedDtor() {
  if (this != default_instance_) {
  }
}

void GuiSettings::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* GuiSettings::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return GuiSettings_descriptor_;
}

const GuiSettings& GuiSettings::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fslow_2fGuiSettings_2eproto();  return *default_instance_;
}

GuiSettings* GuiSettings::default_instance_ = NULL;

GuiSettings* GuiSettings::New() const {
  return new GuiSettings;
}

void GuiSettings::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    show_grid_ = true;
    drop_adds_to_browser_ = true;
    parallel_waveforms_ = false;
    show_names_in_waveform_ = true;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool GuiSettings::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional bool show_grid = 1 [default = true];
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &show_grid_)));
          _set_bit(0);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_drop_adds_to_browser;
        break;
      }
      
      // optional bool drop_adds_to_browser = 2 [default = true];
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_drop_adds_to_browser:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &drop_adds_to_browser_)));
          _set_bit(1);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_parallel_waveforms;
        break;
      }
      
      // optional bool parallel_waveforms = 3 [default = false];
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_parallel_waveforms:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &parallel_waveforms_)));
          _set_bit(2);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_show_names_in_waveform;
        break;
      }
      
      // optional bool show_names_in_waveform = 4 [default = true];
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_show_names_in_waveform:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &show_names_in_waveform_)));
          _set_bit(3);
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

void GuiSettings::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional bool show_grid = 1 [default = true];
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(1, this->show_grid(), output);
  }
  
  // optional bool drop_adds_to_browser = 2 [default = true];
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(2, this->drop_adds_to_browser(), output);
  }
  
  // optional bool parallel_waveforms = 3 [default = false];
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(3, this->parallel_waveforms(), output);
  }
  
  // optional bool show_names_in_waveform = 4 [default = true];
  if (_has_bit(3)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(4, this->show_names_in_waveform(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* GuiSettings::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional bool show_grid = 1 [default = true];
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(1, this->show_grid(), target);
  }
  
  // optional bool drop_adds_to_browser = 2 [default = true];
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(2, this->drop_adds_to_browser(), target);
  }
  
  // optional bool parallel_waveforms = 3 [default = false];
  if (_has_bit(2)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(3, this->parallel_waveforms(), target);
  }
  
  // optional bool show_names_in_waveform = 4 [default = true];
  if (_has_bit(3)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(4, this->show_names_in_waveform(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int GuiSettings::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional bool show_grid = 1 [default = true];
    if (has_show_grid()) {
      total_size += 1 + 1;
    }
    
    // optional bool drop_adds_to_browser = 2 [default = true];
    if (has_drop_adds_to_browser()) {
      total_size += 1 + 1;
    }
    
    // optional bool parallel_waveforms = 3 [default = false];
    if (has_parallel_waveforms()) {
      total_size += 1 + 1;
    }
    
    // optional bool show_names_in_waveform = 4 [default = true];
    if (has_show_names_in_waveform()) {
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

void GuiSettings::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const GuiSettings* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const GuiSettings*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void GuiSettings::MergeFrom(const GuiSettings& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_show_grid(from.show_grid());
    }
    if (from._has_bit(1)) {
      set_drop_adds_to_browser(from.drop_adds_to_browser());
    }
    if (from._has_bit(2)) {
      set_parallel_waveforms(from.parallel_waveforms());
    }
    if (from._has_bit(3)) {
      set_show_names_in_waveform(from.show_names_in_waveform());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void GuiSettings::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void GuiSettings::CopyFrom(const GuiSettings& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GuiSettings::IsInitialized() const {
  
  return true;
}

void GuiSettings::Swap(GuiSettings* other) {
  if (other != this) {
    std::swap(show_grid_, other->show_grid_);
    std::swap(drop_adds_to_browser_, other->drop_adds_to_browser_);
    std::swap(parallel_waveforms_, other->parallel_waveforms_);
    std::swap(show_names_in_waveform_, other->show_names_in_waveform_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata GuiSettings::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = GuiSettings_descriptor_;
  metadata.reflection = GuiSettings_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace slow
}  // namespace rec

// @@protoc_insertion_point(global_scope)
