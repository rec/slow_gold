// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/audio/source/Stretchy.pb.h"
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

const ::google::protobuf::Descriptor* StretchyProto_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  StretchyProto_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2faudio_2fsource_2fStretchy_2eproto() {
  protobuf_AddDesc_rec_2faudio_2fsource_2fStretchy_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/audio/source/Stretchy.proto");
  GOOGLE_CHECK(file != NULL);
  StretchyProto_descriptor_ = file->message_type(0);
  static const int StretchyProto_offsets_[14] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StretchyProto, time_scale_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StretchyProto, time_percent_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StretchyProto, sample_rate_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StretchyProto, channels_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StretchyProto, pitch_scale_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StretchyProto, semitone_shift_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StretchyProto, detune_cents_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StretchyProto, bands_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StretchyProto, filter_overlap_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StretchyProto, chunk_size_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StretchyProto, prefill_size_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StretchyProto, next_buffer_fill_size_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StretchyProto, inactive_wait_time_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StretchyProto, thread_priority_),
  };
  StretchyProto_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      StretchyProto_descriptor_,
      StretchyProto::default_instance_,
      StretchyProto_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StretchyProto, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(StretchyProto, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(StretchyProto));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2faudio_2fsource_2fStretchy_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    StretchyProto_descriptor_, &StretchyProto::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2faudio_2fsource_2fStretchy_2eproto() {
  delete StretchyProto::default_instance_;
  delete StretchyProto_reflection_;
}

void protobuf_AddDesc_rec_2faudio_2fsource_2fStretchy_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::rec::util::file::protobuf_AddDesc_rec_2futil_2ffile_2fVolumeFile_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\037rec/audio/source/Stretchy.proto\022\020rec.a"
    "udio.source\032\036rec/util/file/VolumeFile.pr"
    "oto\"\206\003\n\rStretchyProto\022\025\n\ntime_scale\030\001 \001("
    "\001:\0011\022\031\n\014time_percent\030\016 \001(\001:\003100\022\032\n\013sampl"
    "e_rate\030\002 \001(\001:\00544100\022\023\n\010channels\030\003 \001(\r:\0012"
    "\022\026\n\013pitch_scale\030\004 \001(\001:\0011\022\031\n\016semitone_shi"
    "ft\030\005 \001(\001:\0010\022\027\n\014detune_cents\030\006 \001(\001:\0010\022\023\n\005"
    "bands\030\007 \001(\r:\0042048\022\031\n\016filter_overlap\030\010 \001("
    "\r:\0011\022\027\n\nchunk_size\030\t \001(\r:\003512\022\033\n\014prefill"
    "_size\030\n \001(\r:\00515000\022$\n\025next_buffer_fill_s"
    "ize\030\013 \001(\r:\00515000\022\036\n\022inactive_wait_time\030\014"
    " \001(\005:\002-1\022\032\n\017thread_priority\030\r \001(\r:\0014", 476);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/audio/source/Stretchy.proto", &protobuf_RegisterTypes);
  StretchyProto::default_instance_ = new StretchyProto();
  StretchyProto::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2faudio_2fsource_2fStretchy_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2faudio_2fsource_2fStretchy_2eproto {
  StaticDescriptorInitializer_rec_2faudio_2fsource_2fStretchy_2eproto() {
    protobuf_AddDesc_rec_2faudio_2fsource_2fStretchy_2eproto();
  }
} static_descriptor_initializer_rec_2faudio_2fsource_2fStretchy_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int StretchyProto::kTimeScaleFieldNumber;
const int StretchyProto::kTimePercentFieldNumber;
const int StretchyProto::kSampleRateFieldNumber;
const int StretchyProto::kChannelsFieldNumber;
const int StretchyProto::kPitchScaleFieldNumber;
const int StretchyProto::kSemitoneShiftFieldNumber;
const int StretchyProto::kDetuneCentsFieldNumber;
const int StretchyProto::kBandsFieldNumber;
const int StretchyProto::kFilterOverlapFieldNumber;
const int StretchyProto::kChunkSizeFieldNumber;
const int StretchyProto::kPrefillSizeFieldNumber;
const int StretchyProto::kNextBufferFillSizeFieldNumber;
const int StretchyProto::kInactiveWaitTimeFieldNumber;
const int StretchyProto::kThreadPriorityFieldNumber;
#endif  // !_MSC_VER

StretchyProto::StretchyProto()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void StretchyProto::InitAsDefaultInstance() {
}

StretchyProto::StretchyProto(const StretchyProto& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void StretchyProto::SharedCtor() {
  _cached_size_ = 0;
  time_scale_ = 1;
  time_percent_ = 100;
  sample_rate_ = 44100;
  channels_ = 2u;
  pitch_scale_ = 1;
  semitone_shift_ = 0;
  detune_cents_ = 0;
  bands_ = 2048u;
  filter_overlap_ = 1u;
  chunk_size_ = 512u;
  prefill_size_ = 15000u;
  next_buffer_fill_size_ = 15000u;
  inactive_wait_time_ = -1;
  thread_priority_ = 4u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

StretchyProto::~StretchyProto() {
  SharedDtor();
}

void StretchyProto::SharedDtor() {
  if (this != default_instance_) {
  }
}

void StretchyProto::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* StretchyProto::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return StretchyProto_descriptor_;
}

const StretchyProto& StretchyProto::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2faudio_2fsource_2fStretchy_2eproto();  return *default_instance_;
}

StretchyProto* StretchyProto::default_instance_ = NULL;

StretchyProto* StretchyProto::New() const {
  return new StretchyProto;
}

void StretchyProto::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    time_scale_ = 1;
    time_percent_ = 100;
    sample_rate_ = 44100;
    channels_ = 2u;
    pitch_scale_ = 1;
    semitone_shift_ = 0;
    detune_cents_ = 0;
    bands_ = 2048u;
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    filter_overlap_ = 1u;
    chunk_size_ = 512u;
    prefill_size_ = 15000u;
    next_buffer_fill_size_ = 15000u;
    inactive_wait_time_ = -1;
    thread_priority_ = 4u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool StretchyProto::MergePartialFromCodedStream(
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
          _set_bit(2);
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
          _set_bit(3);
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
          _set_bit(4);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(41)) goto parse_semitone_shift;
        break;
      }
      
      // optional double semitone_shift = 5 [default = 0];
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_semitone_shift:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &semitone_shift_)));
          _set_bit(5);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(49)) goto parse_detune_cents;
        break;
      }
      
      // optional double detune_cents = 6 [default = 0];
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_detune_cents:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &detune_cents_)));
          _set_bit(6);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(56)) goto parse_bands;
        break;
      }
      
      // optional uint32 bands = 7 [default = 2048];
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_bands:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &bands_)));
          _set_bit(7);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(64)) goto parse_filter_overlap;
        break;
      }
      
      // optional uint32 filter_overlap = 8 [default = 1];
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_filter_overlap:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &filter_overlap_)));
          _set_bit(8);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(72)) goto parse_chunk_size;
        break;
      }
      
      // optional uint32 chunk_size = 9 [default = 512];
      case 9: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_chunk_size:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &chunk_size_)));
          _set_bit(9);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(80)) goto parse_prefill_size;
        break;
      }
      
      // optional uint32 prefill_size = 10 [default = 15000];
      case 10: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_prefill_size:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &prefill_size_)));
          _set_bit(10);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(88)) goto parse_next_buffer_fill_size;
        break;
      }
      
      // optional uint32 next_buffer_fill_size = 11 [default = 15000];
      case 11: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_next_buffer_fill_size:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &next_buffer_fill_size_)));
          _set_bit(11);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(96)) goto parse_inactive_wait_time;
        break;
      }
      
      // optional int32 inactive_wait_time = 12 [default = -1];
      case 12: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_inactive_wait_time:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &inactive_wait_time_)));
          _set_bit(12);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(104)) goto parse_thread_priority;
        break;
      }
      
      // optional uint32 thread_priority = 13 [default = 4];
      case 13: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_thread_priority:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &thread_priority_)));
          _set_bit(13);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(113)) goto parse_time_percent;
        break;
      }
      
      // optional double time_percent = 14 [default = 100];
      case 14: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_time_percent:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &time_percent_)));
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

void StretchyProto::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional double time_scale = 1 [default = 1];
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(1, this->time_scale(), output);
  }
  
  // optional double sample_rate = 2 [default = 44100];
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(2, this->sample_rate(), output);
  }
  
  // optional uint32 channels = 3 [default = 2];
  if (_has_bit(3)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->channels(), output);
  }
  
  // optional double pitch_scale = 4 [default = 1];
  if (_has_bit(4)) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(4, this->pitch_scale(), output);
  }
  
  // optional double semitone_shift = 5 [default = 0];
  if (_has_bit(5)) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(5, this->semitone_shift(), output);
  }
  
  // optional double detune_cents = 6 [default = 0];
  if (_has_bit(6)) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(6, this->detune_cents(), output);
  }
  
  // optional uint32 bands = 7 [default = 2048];
  if (_has_bit(7)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(7, this->bands(), output);
  }
  
  // optional uint32 filter_overlap = 8 [default = 1];
  if (_has_bit(8)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(8, this->filter_overlap(), output);
  }
  
  // optional uint32 chunk_size = 9 [default = 512];
  if (_has_bit(9)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(9, this->chunk_size(), output);
  }
  
  // optional uint32 prefill_size = 10 [default = 15000];
  if (_has_bit(10)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(10, this->prefill_size(), output);
  }
  
  // optional uint32 next_buffer_fill_size = 11 [default = 15000];
  if (_has_bit(11)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(11, this->next_buffer_fill_size(), output);
  }
  
  // optional int32 inactive_wait_time = 12 [default = -1];
  if (_has_bit(12)) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(12, this->inactive_wait_time(), output);
  }
  
  // optional uint32 thread_priority = 13 [default = 4];
  if (_has_bit(13)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(13, this->thread_priority(), output);
  }
  
  // optional double time_percent = 14 [default = 100];
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(14, this->time_percent(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* StretchyProto::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional double time_scale = 1 [default = 1];
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(1, this->time_scale(), target);
  }
  
  // optional double sample_rate = 2 [default = 44100];
  if (_has_bit(2)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(2, this->sample_rate(), target);
  }
  
  // optional uint32 channels = 3 [default = 2];
  if (_has_bit(3)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->channels(), target);
  }
  
  // optional double pitch_scale = 4 [default = 1];
  if (_has_bit(4)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(4, this->pitch_scale(), target);
  }
  
  // optional double semitone_shift = 5 [default = 0];
  if (_has_bit(5)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(5, this->semitone_shift(), target);
  }
  
  // optional double detune_cents = 6 [default = 0];
  if (_has_bit(6)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(6, this->detune_cents(), target);
  }
  
  // optional uint32 bands = 7 [default = 2048];
  if (_has_bit(7)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(7, this->bands(), target);
  }
  
  // optional uint32 filter_overlap = 8 [default = 1];
  if (_has_bit(8)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(8, this->filter_overlap(), target);
  }
  
  // optional uint32 chunk_size = 9 [default = 512];
  if (_has_bit(9)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(9, this->chunk_size(), target);
  }
  
  // optional uint32 prefill_size = 10 [default = 15000];
  if (_has_bit(10)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(10, this->prefill_size(), target);
  }
  
  // optional uint32 next_buffer_fill_size = 11 [default = 15000];
  if (_has_bit(11)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(11, this->next_buffer_fill_size(), target);
  }
  
  // optional int32 inactive_wait_time = 12 [default = -1];
  if (_has_bit(12)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(12, this->inactive_wait_time(), target);
  }
  
  // optional uint32 thread_priority = 13 [default = 4];
  if (_has_bit(13)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(13, this->thread_priority(), target);
  }
  
  // optional double time_percent = 14 [default = 100];
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(14, this->time_percent(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int StretchyProto::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional double time_scale = 1 [default = 1];
    if (has_time_scale()) {
      total_size += 1 + 8;
    }
    
    // optional double time_percent = 14 [default = 100];
    if (has_time_percent()) {
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
    
    // optional double semitone_shift = 5 [default = 0];
    if (has_semitone_shift()) {
      total_size += 1 + 8;
    }
    
    // optional double detune_cents = 6 [default = 0];
    if (has_detune_cents()) {
      total_size += 1 + 8;
    }
    
    // optional uint32 bands = 7 [default = 2048];
    if (has_bands()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->bands());
    }
    
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // optional uint32 filter_overlap = 8 [default = 1];
    if (has_filter_overlap()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->filter_overlap());
    }
    
    // optional uint32 chunk_size = 9 [default = 512];
    if (has_chunk_size()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->chunk_size());
    }
    
    // optional uint32 prefill_size = 10 [default = 15000];
    if (has_prefill_size()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->prefill_size());
    }
    
    // optional uint32 next_buffer_fill_size = 11 [default = 15000];
    if (has_next_buffer_fill_size()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->next_buffer_fill_size());
    }
    
    // optional int32 inactive_wait_time = 12 [default = -1];
    if (has_inactive_wait_time()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->inactive_wait_time());
    }
    
    // optional uint32 thread_priority = 13 [default = 4];
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

void StretchyProto::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const StretchyProto* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const StretchyProto*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void StretchyProto::MergeFrom(const StretchyProto& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_time_scale(from.time_scale());
    }
    if (from._has_bit(1)) {
      set_time_percent(from.time_percent());
    }
    if (from._has_bit(2)) {
      set_sample_rate(from.sample_rate());
    }
    if (from._has_bit(3)) {
      set_channels(from.channels());
    }
    if (from._has_bit(4)) {
      set_pitch_scale(from.pitch_scale());
    }
    if (from._has_bit(5)) {
      set_semitone_shift(from.semitone_shift());
    }
    if (from._has_bit(6)) {
      set_detune_cents(from.detune_cents());
    }
    if (from._has_bit(7)) {
      set_bands(from.bands());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from._has_bit(8)) {
      set_filter_overlap(from.filter_overlap());
    }
    if (from._has_bit(9)) {
      set_chunk_size(from.chunk_size());
    }
    if (from._has_bit(10)) {
      set_prefill_size(from.prefill_size());
    }
    if (from._has_bit(11)) {
      set_next_buffer_fill_size(from.next_buffer_fill_size());
    }
    if (from._has_bit(12)) {
      set_inactive_wait_time(from.inactive_wait_time());
    }
    if (from._has_bit(13)) {
      set_thread_priority(from.thread_priority());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void StretchyProto::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void StretchyProto::CopyFrom(const StretchyProto& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool StretchyProto::IsInitialized() const {
  
  return true;
}

void StretchyProto::Swap(StretchyProto* other) {
  if (other != this) {
    std::swap(time_scale_, other->time_scale_);
    std::swap(time_percent_, other->time_percent_);
    std::swap(sample_rate_, other->sample_rate_);
    std::swap(channels_, other->channels_);
    std::swap(pitch_scale_, other->pitch_scale_);
    std::swap(semitone_shift_, other->semitone_shift_);
    std::swap(detune_cents_, other->detune_cents_);
    std::swap(bands_, other->bands_);
    std::swap(filter_overlap_, other->filter_overlap_);
    std::swap(chunk_size_, other->chunk_size_);
    std::swap(prefill_size_, other->prefill_size_);
    std::swap(next_buffer_fill_size_, other->next_buffer_fill_size_);
    std::swap(inactive_wait_time_, other->inactive_wait_time_);
    std::swap(thread_priority_, other->thread_priority_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata StretchyProto::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = StretchyProto_descriptor_;
  metadata.reflection = StretchyProto_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace source
}  // namespace audio
}  // namespace rec

// @@protoc_insertion_point(global_scope)
