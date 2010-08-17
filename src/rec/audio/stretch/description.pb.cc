// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "description.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace rec {
namespace audio {
namespace timescaler {

namespace {

const ::google::protobuf::Descriptor* Description_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Description_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_description_2eproto() {
  protobuf_AddDesc_description_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "description.proto");
  GOOGLE_CHECK(file != NULL);
  Description_descriptor_ = file->message_type(0);
  static const int Description_offsets_[10] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Description, time_scale_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Description, sample_rate_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Description, channels_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Description, pitch_scale_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Description, bands_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Description, filter_overlap_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Description, chunk_size_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Description, prefill_size_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Description, inactive_wait_time_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Description, thread_priority_),
  };
  Description_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Description_descriptor_,
      Description::default_instance_,
      Description_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Description, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Description, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Description));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_description_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Description_descriptor_, &Description::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_description_2eproto() {
  delete Description::default_instance_;
  delete Description_reflection_;
}

void protobuf_AddDesc_description_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\021description.proto\022\024rec.audio.timescale"
    "r\"\216\002\n\013Description\022\025\n\ntime_scale\030\001 \001(\001:\0011"
    "\022\032\n\013sample_rate\030\002 \001(\001:\00544100\022\023\n\010channels"
    "\030\003 \001(\r:\0012\022\026\n\013pitch_scale\030\004 \001(\001:\0011\022\023\n\005ban"
    "ds\030\005 \001(\r:\0042048\022\031\n\016filter_overlap\030\006 \001(\r:\001"
    "1\022\027\n\nchunk_size\030\007 \001(\r:\003512\022\032\n\014prefill_si"
    "ze\030\010 \001(\r:\0044096\022\036\n\022inactive_wait_time\030\t \001"
    "(\005:\002-1\022\032\n\017thread_priority\030\n \001(\r:\0014", 314);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "description.proto", &protobuf_RegisterTypes);
  Description::default_instance_ = new Description();
  Description::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_description_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_description_2eproto {
  StaticDescriptorInitializer_description_2eproto() {
    protobuf_AddDesc_description_2eproto();
  }
} static_descriptor_initializer_description_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int Description::kTimeScaleFieldNumber;
const int Description::kSampleRateFieldNumber;
const int Description::kChannelsFieldNumber;
const int Description::kPitchScaleFieldNumber;
const int Description::kBandsFieldNumber;
const int Description::kFilterOverlapFieldNumber;
const int Description::kChunkSizeFieldNumber;
const int Description::kPrefillSizeFieldNumber;
const int Description::kInactiveWaitTimeFieldNumber;
const int Description::kThreadPriorityFieldNumber;
#endif  // !_MSC_VER

Description::Description()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Description::InitAsDefaultInstance() {
}

Description::Description(const Description& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Description::SharedCtor() {
  _cached_size_ = 0;
  time_scale_ = 1;
  sample_rate_ = 44100;
  channels_ = 2u;
  pitch_scale_ = 1;
  bands_ = 2048u;
  filter_overlap_ = 1u;
  chunk_size_ = 512u;
  prefill_size_ = 4096u;
  inactive_wait_time_ = -1;
  thread_priority_ = 4u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Description::~Description() {
  SharedDtor();
}

void Description::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Description::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Description::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Description_descriptor_;
}

const Description& Description::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_description_2eproto();  return *default_instance_;
}

Description* Description::default_instance_ = NULL;

Description* Description::New() const {
  return new Description;
}

void Description::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    time_scale_ = 1;
    sample_rate_ = 44100;
    channels_ = 2u;
    pitch_scale_ = 1;
    bands_ = 2048u;
    filter_overlap_ = 1u;
    chunk_size_ = 512u;
    prefill_size_ = 4096u;
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    inactive_wait_time_ = -1;
    thread_priority_ = 4u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Description::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional double time_scale = 1 [default = 1];
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &time_scale_)));
          _set_bit(0);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(17)) goto parse_sample_rate;
        break;
      }
      
      // optional double sample_rate = 2 [default = 44100];
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_sample_rate:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &sample_rate_)));
          _set_bit(1);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_channels;
        break;
      }
      
      // optional uint32 channels = 3 [default = 2];
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_channels:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &channels_)));
          _set_bit(2);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(33)) goto parse_pitch_scale;
        break;
      }
      
      // optional double pitch_scale = 4 [default = 1];
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_pitch_scale:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &pitch_scale_)));
          _set_bit(3);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_bands;
        break;
      }
      
      // optional uint32 bands = 5 [default = 2048];
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_bands:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &bands_)));
          _set_bit(4);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(48)) goto parse_filter_overlap;
        break;
      }
      
      // optional uint32 filter_overlap = 6 [default = 1];
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_filter_overlap:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &filter_overlap_)));
          _set_bit(5);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(56)) goto parse_chunk_size;
        break;
      }
      
      // optional uint32 chunk_size = 7 [default = 512];
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_chunk_size:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &chunk_size_)));
          _set_bit(6);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(64)) goto parse_prefill_size;
        break;
      }
      
      // optional uint32 prefill_size = 8 [default = 4096];
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_prefill_size:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &prefill_size_)));
          _set_bit(7);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(72)) goto parse_inactive_wait_time;
        break;
      }
      
      // optional int32 inactive_wait_time = 9 [default = -1];
      case 9: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_inactive_wait_time:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &inactive_wait_time_)));
          _set_bit(8);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(80)) goto parse_thread_priority;
        break;
      }
      
      // optional uint32 thread_priority = 10 [default = 4];
      case 10: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_thread_priority:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &thread_priority_)));
          _set_bit(9);
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

void Description::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional double time_scale = 1 [default = 1];
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(1, this->time_scale(), output);
  }
  
  // optional double sample_rate = 2 [default = 44100];
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(2, this->sample_rate(), output);
  }
  
  // optional uint32 channels = 3 [default = 2];
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->channels(), output);
  }
  
  // optional double pitch_scale = 4 [default = 1];
  if (_has_bit(3)) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(4, this->pitch_scale(), output);
  }
  
  // optional uint32 bands = 5 [default = 2048];
  if (_has_bit(4)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(5, this->bands(), output);
  }
  
  // optional uint32 filter_overlap = 6 [default = 1];
  if (_has_bit(5)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(6, this->filter_overlap(), output);
  }
  
  // optional uint32 chunk_size = 7 [default = 512];
  if (_has_bit(6)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(7, this->chunk_size(), output);
  }
  
  // optional uint32 prefill_size = 8 [default = 4096];
  if (_has_bit(7)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(8, this->prefill_size(), output);
  }
  
  // optional int32 inactive_wait_time = 9 [default = -1];
  if (_has_bit(8)) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(9, this->inactive_wait_time(), output);
  }
  
  // optional uint32 thread_priority = 10 [default = 4];
  if (_has_bit(9)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(10, this->thread_priority(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Description::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional double time_scale = 1 [default = 1];
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(1, this->time_scale(), target);
  }
  
  // optional double sample_rate = 2 [default = 44100];
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(2, this->sample_rate(), target);
  }
  
  // optional uint32 channels = 3 [default = 2];
  if (_has_bit(2)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->channels(), target);
  }
  
  // optional double pitch_scale = 4 [default = 1];
  if (_has_bit(3)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(4, this->pitch_scale(), target);
  }
  
  // optional uint32 bands = 5 [default = 2048];
  if (_has_bit(4)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(5, this->bands(), target);
  }
  
  // optional uint32 filter_overlap = 6 [default = 1];
  if (_has_bit(5)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(6, this->filter_overlap(), target);
  }
  
  // optional uint32 chunk_size = 7 [default = 512];
  if (_has_bit(6)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(7, this->chunk_size(), target);
  }
  
  // optional uint32 prefill_size = 8 [default = 4096];
  if (_has_bit(7)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(8, this->prefill_size(), target);
  }
  
  // optional int32 inactive_wait_time = 9 [default = -1];
  if (_has_bit(8)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(9, this->inactive_wait_time(), target);
  }
  
  // optional uint32 thread_priority = 10 [default = 4];
  if (_has_bit(9)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(10, this->thread_priority(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Description::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional double time_scale = 1 [default = 1];
    if (has_time_scale()) {
      total_size += 1 + 8;
    }
    
    // optional double sample_rate = 2 [default = 44100];
    if (has_sample_rate()) {
      total_size += 1 + 8;
    }
    
    // optional uint32 channels = 3 [default = 2];
    if (has_channels()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->channels());
    }
    
    // optional double pitch_scale = 4 [default = 1];
    if (has_pitch_scale()) {
      total_size += 1 + 8;
    }
    
    // optional uint32 bands = 5 [default = 2048];
    if (has_bands()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->bands());
    }
    
    // optional uint32 filter_overlap = 6 [default = 1];
    if (has_filter_overlap()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->filter_overlap());
    }
    
    // optional uint32 chunk_size = 7 [default = 512];
    if (has_chunk_size()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->chunk_size());
    }
    
    // optional uint32 prefill_size = 8 [default = 4096];
    if (has_prefill_size()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->prefill_size());
    }
    
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // optional int32 inactive_wait_time = 9 [default = -1];
    if (has_inactive_wait_time()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->inactive_wait_time());
    }
    
    // optional uint32 thread_priority = 10 [default = 4];
    if (has_thread_priority()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->thread_priority());
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

void Description::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Description* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Description*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Description::MergeFrom(const Description& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_time_scale(from.time_scale());
    }
    if (from._has_bit(1)) {
      set_sample_rate(from.sample_rate());
    }
    if (from._has_bit(2)) {
      set_channels(from.channels());
    }
    if (from._has_bit(3)) {
      set_pitch_scale(from.pitch_scale());
    }
    if (from._has_bit(4)) {
      set_bands(from.bands());
    }
    if (from._has_bit(5)) {
      set_filter_overlap(from.filter_overlap());
    }
    if (from._has_bit(6)) {
      set_chunk_size(from.chunk_size());
    }
    if (from._has_bit(7)) {
      set_prefill_size(from.prefill_size());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from._has_bit(8)) {
      set_inactive_wait_time(from.inactive_wait_time());
    }
    if (from._has_bit(9)) {
      set_thread_priority(from.thread_priority());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Description::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Description::CopyFrom(const Description& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Description::IsInitialized() const {
  
  return true;
}

void Description::Swap(Description* other) {
  if (other != this) {
    std::swap(time_scale_, other->time_scale_);
    std::swap(sample_rate_, other->sample_rate_);
    std::swap(channels_, other->channels_);
    std::swap(pitch_scale_, other->pitch_scale_);
    std::swap(bands_, other->bands_);
    std::swap(filter_overlap_, other->filter_overlap_);
    std::swap(chunk_size_, other->chunk_size_);
    std::swap(prefill_size_, other->prefill_size_);
    std::swap(inactive_wait_time_, other->inactive_wait_time_);
    std::swap(thread_priority_, other->thread_priority_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Description::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Description_descriptor_;
  metadata.reflection = Description_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace timescaler
}  // namespace audio
}  // namespace rec

// @@protoc_insertion_point(global_scope)
