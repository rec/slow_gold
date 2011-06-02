// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/audio/util/Gain.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace rec {
namespace audio {

namespace {

const ::google::protobuf::Descriptor* Gain_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Gain_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2faudio_2futil_2fGain_2eproto() {
  protobuf_AddDesc_rec_2faudio_2futil_2fGain_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/audio/util/Gain.proto");
  GOOGLE_CHECK(file != NULL);
  Gain_descriptor_ = file->message_type(0);
  static const int Gain_offsets_[5] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Gain, level_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Gain, gain_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Gain, mute_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Gain, dim_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Gain, dim_level_),
  };
  Gain_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Gain_descriptor_,
      Gain::default_instance_,
      Gain_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Gain, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Gain, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Gain));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2faudio_2futil_2fGain_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Gain_descriptor_, &Gain::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2faudio_2futil_2fGain_2eproto() {
  delete Gain::default_instance_;
  delete Gain_reflection_;
}

void protobuf_AddDesc_rec_2faudio_2futil_2fGain_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\031rec/audio/util/Gain.proto\022\trec.audio\"\\"
    "\n\004Gain\022\020\n\005level\030\001 \001(\002:\0011\022\017\n\004gain\030\005 \001(\002:\001"
    "0\022\014\n\004mute\030\002 \001(\010\022\013\n\003dim\030\003 \001(\010\022\026\n\tdim_leve"
    "l\030\004 \001(\002:\0030.3", 132);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/audio/util/Gain.proto", &protobuf_RegisterTypes);
  Gain::default_instance_ = new Gain();
  Gain::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2faudio_2futil_2fGain_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2faudio_2futil_2fGain_2eproto {
  StaticDescriptorInitializer_rec_2faudio_2futil_2fGain_2eproto() {
    protobuf_AddDesc_rec_2faudio_2futil_2fGain_2eproto();
  }
} static_descriptor_initializer_rec_2faudio_2futil_2fGain_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int Gain::kLevelFieldNumber;
const int Gain::kGainFieldNumber;
const int Gain::kMuteFieldNumber;
const int Gain::kDimFieldNumber;
const int Gain::kDimLevelFieldNumber;
#endif  // !_MSC_VER

Gain::Gain()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Gain::InitAsDefaultInstance() {
}

Gain::Gain(const Gain& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Gain::SharedCtor() {
  _cached_size_ = 0;
  level_ = 1;
  gain_ = 0;
  mute_ = false;
  dim_ = false;
  dim_level_ = 0.3f;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Gain::~Gain() {
  SharedDtor();
}

void Gain::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Gain::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Gain::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Gain_descriptor_;
}

const Gain& Gain::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2faudio_2futil_2fGain_2eproto();  return *default_instance_;
}

Gain* Gain::default_instance_ = NULL;

Gain* Gain::New() const {
  return new Gain;
}

void Gain::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    level_ = 1;
    gain_ = 0;
    mute_ = false;
    dim_ = false;
    dim_level_ = 0.3f;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Gain::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional float level = 1 [default = 1];
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &level_)));
          _set_bit(0);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_mute;
        break;
      }
      
      // optional bool mute = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_mute:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &mute_)));
          _set_bit(2);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_dim;
        break;
      }
      
      // optional bool dim = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_dim:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &dim_)));
          _set_bit(3);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(37)) goto parse_dim_level;
        break;
      }
      
      // optional float dim_level = 4 [default = 0.3];
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_dim_level:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &dim_level_)));
          _set_bit(4);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(45)) goto parse_gain;
        break;
      }
      
      // optional float gain = 5 [default = 0];
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_gain:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &gain_)));
          _set_bit(1);
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

void Gain::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional float level = 1 [default = 1];
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(1, this->level(), output);
  }
  
  // optional bool mute = 2;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(2, this->mute(), output);
  }
  
  // optional bool dim = 3;
  if (_has_bit(3)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(3, this->dim(), output);
  }
  
  // optional float dim_level = 4 [default = 0.3];
  if (_has_bit(4)) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(4, this->dim_level(), output);
  }
  
  // optional float gain = 5 [default = 0];
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(5, this->gain(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Gain::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional float level = 1 [default = 1];
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(1, this->level(), target);
  }
  
  // optional bool mute = 2;
  if (_has_bit(2)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(2, this->mute(), target);
  }
  
  // optional bool dim = 3;
  if (_has_bit(3)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(3, this->dim(), target);
  }
  
  // optional float dim_level = 4 [default = 0.3];
  if (_has_bit(4)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(4, this->dim_level(), target);
  }
  
  // optional float gain = 5 [default = 0];
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(5, this->gain(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Gain::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional float level = 1 [default = 1];
    if (has_level()) {
      total_size += 1 + 4;
    }
    
    // optional float gain = 5 [default = 0];
    if (has_gain()) {
      total_size += 1 + 4;
    }
    
    // optional bool mute = 2;
    if (has_mute()) {
      total_size += 1 + 1;
    }
    
    // optional bool dim = 3;
    if (has_dim()) {
      total_size += 1 + 1;
    }
    
    // optional float dim_level = 4 [default = 0.3];
    if (has_dim_level()) {
      total_size += 1 + 4;
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

void Gain::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Gain* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Gain*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Gain::MergeFrom(const Gain& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_level(from.level());
    }
    if (from._has_bit(1)) {
      set_gain(from.gain());
    }
    if (from._has_bit(2)) {
      set_mute(from.mute());
    }
    if (from._has_bit(3)) {
      set_dim(from.dim());
    }
    if (from._has_bit(4)) {
      set_dim_level(from.dim_level());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Gain::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Gain::CopyFrom(const Gain& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Gain::IsInitialized() const {
  
  return true;
}

void Gain::Swap(Gain* other) {
  if (other != this) {
    std::swap(level_, other->level_);
    std::swap(gain_, other->gain_);
    std::swap(mute_, other->mute_);
    std::swap(dim_, other->dim_);
    std::swap(dim_level_, other->dim_level_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Gain::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Gain_descriptor_;
  metadata.reflection = Gain_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace audio
}  // namespace rec

// @@protoc_insertion_point(global_scope)