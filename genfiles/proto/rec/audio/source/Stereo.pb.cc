// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/audio/source/Stereo.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace rec {
namespace audio {
namespace source {

namespace {

const ::google::protobuf::Descriptor* StereoProto_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  StereoProto_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* StereoProto_Side_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* StereoProto_Type_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2faudio_2fsource_2fStereo_2eproto() {
  protobuf_AddDesc_rec_2faudio_2fsource_2fStereo_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/audio/source/Stereo.proto");
  GOOGLE_CHECK(file != NULL);
  StereoProto_descriptor_ = file->message_type(0);
  static const int StereoProto_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StereoProto, type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StereoProto, side_),
  };
  StereoProto_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      StereoProto_descriptor_,
      StereoProto::default_instance_,
      StereoProto_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StereoProto, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StereoProto, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(StereoProto));
  StereoProto_Side_descriptor_ = StereoProto_descriptor_->enum_type(0);
  StereoProto_Type_descriptor_ = StereoProto_descriptor_->enum_type(1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2faudio_2fsource_2fStereo_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    StereoProto_descriptor_, &StereoProto::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2faudio_2fsource_2fStereo_2eproto() {
  delete StereoProto::default_instance_;
  delete StereoProto_reflection_;
}

void protobuf_AddDesc_rec_2faudio_2fsource_2fStereo_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\035rec/audio/source/Stereo.proto\022\020rec.aud"
    "io.source\"\207\002\n\013StereoProto\0220\n\004type\030\001 \001(\0162"
    "\".rec.audio.source.StereoProto.Type\0220\n\004s"
    "ide\030\002 \001(\0162\".rec.audio.source.StereoProto"
    ".Side\"0\n\004Side\022\010\n\004LEFT\020\000\022\t\n\005RIGHT\020\001\022\023\n\017LE"
    "FT_PLUS_RIGHT\020\002\"b\n\004Type\022\017\n\013PASSTHROUGH\020\000"
    "\022\n\n\006SINGLE\020\001\022\010\n\004FLIP\020\002\022\026\n\022CENTER_ELIMINA"
    "TION\020\003\022\033\n\027CENTER_ELIMINATION_MONO\020\004", 315);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/audio/source/Stereo.proto", &protobuf_RegisterTypes);
  StereoProto::default_instance_ = new StereoProto();
  StereoProto::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2faudio_2fsource_2fStereo_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2faudio_2fsource_2fStereo_2eproto {
  StaticDescriptorInitializer_rec_2faudio_2fsource_2fStereo_2eproto() {
    protobuf_AddDesc_rec_2faudio_2fsource_2fStereo_2eproto();
  }
} static_descriptor_initializer_rec_2faudio_2fsource_2fStereo_2eproto_;


// ===================================================================

const ::google::protobuf::EnumDescriptor* StereoProto_Side_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return StereoProto_Side_descriptor_;
}
bool StereoProto_Side_IsValid(int value) {
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
const StereoProto_Side StereoProto::LEFT;
const StereoProto_Side StereoProto::RIGHT;
const StereoProto_Side StereoProto::LEFT_PLUS_RIGHT;
const StereoProto_Side StereoProto::Side_MIN;
const StereoProto_Side StereoProto::Side_MAX;
const int StereoProto::Side_ARRAYSIZE;
#endif  // _MSC_VER
const ::google::protobuf::EnumDescriptor* StereoProto_Type_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return StereoProto_Type_descriptor_;
}
bool StereoProto_Type_IsValid(int value) {
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
const StereoProto_Type StereoProto::PASSTHROUGH;
const StereoProto_Type StereoProto::SINGLE;
const StereoProto_Type StereoProto::FLIP;
const StereoProto_Type StereoProto::CENTER_ELIMINATION;
const StereoProto_Type StereoProto::CENTER_ELIMINATION_MONO;
const StereoProto_Type StereoProto::Type_MIN;
const StereoProto_Type StereoProto::Type_MAX;
const int StereoProto::Type_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int StereoProto::kTypeFieldNumber;
const int StereoProto::kSideFieldNumber;
#endif  // !_MSC_VER

StereoProto::StereoProto()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void StereoProto::InitAsDefaultInstance() {
}

StereoProto::StereoProto(const StereoProto& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void StereoProto::SharedCtor() {
  _cached_size_ = 0;
  type_ = 0;
  side_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

StereoProto::~StereoProto() {
  SharedDtor();
}

void StereoProto::SharedDtor() {
  if (this != default_instance_) {
  }
}

void StereoProto::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* StereoProto::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return StereoProto_descriptor_;
}

const StereoProto& StereoProto::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2faudio_2fsource_2fStereo_2eproto();  return *default_instance_;
}

StereoProto* StereoProto::default_instance_ = NULL;

StereoProto* StereoProto::New() const {
  return new StereoProto;
}

void StereoProto::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    type_ = 0;
    side_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool StereoProto::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .rec.audio.source.StereoProto.Type type = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::rec::audio::source::StereoProto_Type_IsValid(value)) {
            set_type(static_cast< ::rec::audio::source::StereoProto_Type >(value));
          } else {
            mutable_unknown_fields()->AddVarint(1, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_side;
        break;
      }
      
      // optional .rec.audio.source.StereoProto.Side side = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_side:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::rec::audio::source::StereoProto_Side_IsValid(value)) {
            set_side(static_cast< ::rec::audio::source::StereoProto_Side >(value));
          } else {
            mutable_unknown_fields()->AddVarint(2, value);
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

void StereoProto::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .rec.audio.source.StereoProto.Type type = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->type(), output);
  }
  
  // optional .rec.audio.source.StereoProto.Side side = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      2, this->side(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* StereoProto::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .rec.audio.source.StereoProto.Type type = 1;
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->type(), target);
  }
  
  // optional .rec.audio.source.StereoProto.Side side = 2;
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      2, this->side(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int StereoProto::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .rec.audio.source.StereoProto.Type type = 1;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->type());
    }
    
    // optional .rec.audio.source.StereoProto.Side side = 2;
    if (has_side()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->side());
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

void StereoProto::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const StereoProto* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const StereoProto*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void StereoProto::MergeFrom(const StereoProto& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_type(from.type());
    }
    if (from._has_bit(1)) {
      set_side(from.side());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void StereoProto::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void StereoProto::CopyFrom(const StereoProto& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool StereoProto::IsInitialized() const {
  
  return true;
}

void StereoProto::Swap(StereoProto* other) {
  if (other != this) {
    std::swap(type_, other->type_);
    std::swap(side_, other->side_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata StereoProto::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = StereoProto_descriptor_;
  metadata.reflection = StereoProto_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace source
}  // namespace audio
}  // namespace rec

// @@protoc_insertion_point(global_scope)
