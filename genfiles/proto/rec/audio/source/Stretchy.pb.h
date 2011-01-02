// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/audio/source/Stretchy.proto

#ifndef PROTOBUF_rec_2faudio_2fsource_2fStretchy_2eproto__INCLUDED
#define PROTOBUF_rec_2faudio_2fsource_2fStretchy_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2003000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
#include "rec/util/file/VolumeFile.pb.h"
// @@protoc_insertion_point(includes)

namespace rec {
namespace audio {
namespace source {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2faudio_2fsource_2fStretchy_2eproto();
void protobuf_AssignDesc_rec_2faudio_2fsource_2fStretchy_2eproto();
void protobuf_ShutdownFile_rec_2faudio_2fsource_2fStretchy_2eproto();

class StretchyProto;

// ===================================================================

class StretchyProto : public ::google::protobuf::Message {
 public:
  StretchyProto();
  virtual ~StretchyProto();
  
  StretchyProto(const StretchyProto& from);
  
  inline StretchyProto& operator=(const StretchyProto& from) {
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
  static const StretchyProto& default_instance();
  
  void Swap(StretchyProto* other);
  
  // implements Message ----------------------------------------------
  
  StretchyProto* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const StretchyProto& from);
  void MergeFrom(const StretchyProto& from);
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
  
  // accessors -------------------------------------------------------
  
  // optional double time_scale = 1 [default = 1];
  inline bool has_time_scale() const;
  inline void clear_time_scale();
  static const int kTimeScaleFieldNumber = 1;
  inline double time_scale() const;
  inline void set_time_scale(double value);
  
  // optional double time_percent = 14 [default = 100];
  inline bool has_time_percent() const;
  inline void clear_time_percent();
  static const int kTimePercentFieldNumber = 14;
  inline double time_percent() const;
  inline void set_time_percent(double value);
  
  // optional double sample_rate = 2 [default = 44100];
  inline bool has_sample_rate() const;
  inline void clear_sample_rate();
  static const int kSampleRateFieldNumber = 2;
  inline double sample_rate() const;
  inline void set_sample_rate(double value);
  
  // optional uint32 channels = 3 [default = 2];
  inline bool has_channels() const;
  inline void clear_channels();
  static const int kChannelsFieldNumber = 3;
  inline ::google::protobuf::uint32 channels() const;
  inline void set_channels(::google::protobuf::uint32 value);
  
  // optional double pitch_scale = 4 [default = 1];
  inline bool has_pitch_scale() const;
  inline void clear_pitch_scale();
  static const int kPitchScaleFieldNumber = 4;
  inline double pitch_scale() const;
  inline void set_pitch_scale(double value);
  
  // optional double semitone_shift = 5 [default = 0];
  inline bool has_semitone_shift() const;
  inline void clear_semitone_shift();
  static const int kSemitoneShiftFieldNumber = 5;
  inline double semitone_shift() const;
  inline void set_semitone_shift(double value);
  
  // optional double detune_cents = 6 [default = 0];
  inline bool has_detune_cents() const;
  inline void clear_detune_cents();
  static const int kDetuneCentsFieldNumber = 6;
  inline double detune_cents() const;
  inline void set_detune_cents(double value);
  
  // optional uint32 bands = 7 [default = 2048];
  inline bool has_bands() const;
  inline void clear_bands();
  static const int kBandsFieldNumber = 7;
  inline ::google::protobuf::uint32 bands() const;
  inline void set_bands(::google::protobuf::uint32 value);
  
  // optional uint32 filter_overlap = 8 [default = 1];
  inline bool has_filter_overlap() const;
  inline void clear_filter_overlap();
  static const int kFilterOverlapFieldNumber = 8;
  inline ::google::protobuf::uint32 filter_overlap() const;
  inline void set_filter_overlap(::google::protobuf::uint32 value);
  
  // optional uint32 chunk_size = 9 [default = 512];
  inline bool has_chunk_size() const;
  inline void clear_chunk_size();
  static const int kChunkSizeFieldNumber = 9;
  inline ::google::protobuf::uint32 chunk_size() const;
  inline void set_chunk_size(::google::protobuf::uint32 value);
  
  // optional uint32 prefill_size = 10 [default = 15000];
  inline bool has_prefill_size() const;
  inline void clear_prefill_size();
  static const int kPrefillSizeFieldNumber = 10;
  inline ::google::protobuf::uint32 prefill_size() const;
  inline void set_prefill_size(::google::protobuf::uint32 value);
  
  // optional uint32 next_buffer_fill_size = 11 [default = 15000];
  inline bool has_next_buffer_fill_size() const;
  inline void clear_next_buffer_fill_size();
  static const int kNextBufferFillSizeFieldNumber = 11;
  inline ::google::protobuf::uint32 next_buffer_fill_size() const;
  inline void set_next_buffer_fill_size(::google::protobuf::uint32 value);
  
  // optional int32 inactive_wait_time = 12 [default = -1];
  inline bool has_inactive_wait_time() const;
  inline void clear_inactive_wait_time();
  static const int kInactiveWaitTimeFieldNumber = 12;
  inline ::google::protobuf::int32 inactive_wait_time() const;
  inline void set_inactive_wait_time(::google::protobuf::int32 value);
  
  // optional uint32 thread_priority = 13 [default = 4];
  inline bool has_thread_priority() const;
  inline void clear_thread_priority();
  static const int kThreadPriorityFieldNumber = 13;
  inline ::google::protobuf::uint32 thread_priority() const;
  inline void set_thread_priority(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:rec.audio.source.StretchyProto)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  double time_scale_;
  double time_percent_;
  double sample_rate_;
  ::google::protobuf::uint32 channels_;
  double pitch_scale_;
  double semitone_shift_;
  double detune_cents_;
  ::google::protobuf::uint32 bands_;
  ::google::protobuf::uint32 filter_overlap_;
  ::google::protobuf::uint32 chunk_size_;
  ::google::protobuf::uint32 prefill_size_;
  ::google::protobuf::uint32 next_buffer_fill_size_;
  ::google::protobuf::int32 inactive_wait_time_;
  ::google::protobuf::uint32 thread_priority_;
  friend void  protobuf_AddDesc_rec_2faudio_2fsource_2fStretchy_2eproto();
  friend void protobuf_AssignDesc_rec_2faudio_2fsource_2fStretchy_2eproto();
  friend void protobuf_ShutdownFile_rec_2faudio_2fsource_2fStretchy_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(14 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static StretchyProto* default_instance_;
};
// ===================================================================


// ===================================================================

// StretchyProto

// optional double time_scale = 1 [default = 1];
inline bool StretchyProto::has_time_scale() const {
  return _has_bit(0);
}
inline void StretchyProto::clear_time_scale() {
  time_scale_ = 1;
  _clear_bit(0);
}
inline double StretchyProto::time_scale() const {
  return time_scale_;
}
inline void StretchyProto::set_time_scale(double value) {
  _set_bit(0);
  time_scale_ = value;
}

// optional double time_percent = 14 [default = 100];
inline bool StretchyProto::has_time_percent() const {
  return _has_bit(1);
}
inline void StretchyProto::clear_time_percent() {
  time_percent_ = 100;
  _clear_bit(1);
}
inline double StretchyProto::time_percent() const {
  return time_percent_;
}
inline void StretchyProto::set_time_percent(double value) {
  _set_bit(1);
  time_percent_ = value;
}

// optional double sample_rate = 2 [default = 44100];
inline bool StretchyProto::has_sample_rate() const {
  return _has_bit(2);
}
inline void StretchyProto::clear_sample_rate() {
  sample_rate_ = 44100;
  _clear_bit(2);
}
inline double StretchyProto::sample_rate() const {
  return sample_rate_;
}
inline void StretchyProto::set_sample_rate(double value) {
  _set_bit(2);
  sample_rate_ = value;
}

// optional uint32 channels = 3 [default = 2];
inline bool StretchyProto::has_channels() const {
  return _has_bit(3);
}
inline void StretchyProto::clear_channels() {
  channels_ = 2u;
  _clear_bit(3);
}
inline ::google::protobuf::uint32 StretchyProto::channels() const {
  return channels_;
}
inline void StretchyProto::set_channels(::google::protobuf::uint32 value) {
  _set_bit(3);
  channels_ = value;
}

// optional double pitch_scale = 4 [default = 1];
inline bool StretchyProto::has_pitch_scale() const {
  return _has_bit(4);
}
inline void StretchyProto::clear_pitch_scale() {
  pitch_scale_ = 1;
  _clear_bit(4);
}
inline double StretchyProto::pitch_scale() const {
  return pitch_scale_;
}
inline void StretchyProto::set_pitch_scale(double value) {
  _set_bit(4);
  pitch_scale_ = value;
}

// optional double semitone_shift = 5 [default = 0];
inline bool StretchyProto::has_semitone_shift() const {
  return _has_bit(5);
}
inline void StretchyProto::clear_semitone_shift() {
  semitone_shift_ = 0;
  _clear_bit(5);
}
inline double StretchyProto::semitone_shift() const {
  return semitone_shift_;
}
inline void StretchyProto::set_semitone_shift(double value) {
  _set_bit(5);
  semitone_shift_ = value;
}

// optional double detune_cents = 6 [default = 0];
inline bool StretchyProto::has_detune_cents() const {
  return _has_bit(6);
}
inline void StretchyProto::clear_detune_cents() {
  detune_cents_ = 0;
  _clear_bit(6);
}
inline double StretchyProto::detune_cents() const {
  return detune_cents_;
}
inline void StretchyProto::set_detune_cents(double value) {
  _set_bit(6);
  detune_cents_ = value;
}

// optional uint32 bands = 7 [default = 2048];
inline bool StretchyProto::has_bands() const {
  return _has_bit(7);
}
inline void StretchyProto::clear_bands() {
  bands_ = 2048u;
  _clear_bit(7);
}
inline ::google::protobuf::uint32 StretchyProto::bands() const {
  return bands_;
}
inline void StretchyProto::set_bands(::google::protobuf::uint32 value) {
  _set_bit(7);
  bands_ = value;
}

// optional uint32 filter_overlap = 8 [default = 1];
inline bool StretchyProto::has_filter_overlap() const {
  return _has_bit(8);
}
inline void StretchyProto::clear_filter_overlap() {
  filter_overlap_ = 1u;
  _clear_bit(8);
}
inline ::google::protobuf::uint32 StretchyProto::filter_overlap() const {
  return filter_overlap_;
}
inline void StretchyProto::set_filter_overlap(::google::protobuf::uint32 value) {
  _set_bit(8);
  filter_overlap_ = value;
}

// optional uint32 chunk_size = 9 [default = 512];
inline bool StretchyProto::has_chunk_size() const {
  return _has_bit(9);
}
inline void StretchyProto::clear_chunk_size() {
  chunk_size_ = 512u;
  _clear_bit(9);
}
inline ::google::protobuf::uint32 StretchyProto::chunk_size() const {
  return chunk_size_;
}
inline void StretchyProto::set_chunk_size(::google::protobuf::uint32 value) {
  _set_bit(9);
  chunk_size_ = value;
}

// optional uint32 prefill_size = 10 [default = 15000];
inline bool StretchyProto::has_prefill_size() const {
  return _has_bit(10);
}
inline void StretchyProto::clear_prefill_size() {
  prefill_size_ = 15000u;
  _clear_bit(10);
}
inline ::google::protobuf::uint32 StretchyProto::prefill_size() const {
  return prefill_size_;
}
inline void StretchyProto::set_prefill_size(::google::protobuf::uint32 value) {
  _set_bit(10);
  prefill_size_ = value;
}

// optional uint32 next_buffer_fill_size = 11 [default = 15000];
inline bool StretchyProto::has_next_buffer_fill_size() const {
  return _has_bit(11);
}
inline void StretchyProto::clear_next_buffer_fill_size() {
  next_buffer_fill_size_ = 15000u;
  _clear_bit(11);
}
inline ::google::protobuf::uint32 StretchyProto::next_buffer_fill_size() const {
  return next_buffer_fill_size_;
}
inline void StretchyProto::set_next_buffer_fill_size(::google::protobuf::uint32 value) {
  _set_bit(11);
  next_buffer_fill_size_ = value;
}

// optional int32 inactive_wait_time = 12 [default = -1];
inline bool StretchyProto::has_inactive_wait_time() const {
  return _has_bit(12);
}
inline void StretchyProto::clear_inactive_wait_time() {
  inactive_wait_time_ = -1;
  _clear_bit(12);
}
inline ::google::protobuf::int32 StretchyProto::inactive_wait_time() const {
  return inactive_wait_time_;
}
inline void StretchyProto::set_inactive_wait_time(::google::protobuf::int32 value) {
  _set_bit(12);
  inactive_wait_time_ = value;
}

// optional uint32 thread_priority = 13 [default = 4];
inline bool StretchyProto::has_thread_priority() const {
  return _has_bit(13);
}
inline void StretchyProto::clear_thread_priority() {
  thread_priority_ = 4u;
  _clear_bit(13);
}
inline ::google::protobuf::uint32 StretchyProto::thread_priority() const {
  return thread_priority_;
}
inline void StretchyProto::set_thread_priority(::google::protobuf::uint32 value) {
  _set_bit(13);
  thread_priority_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace source
}  // namespace audio
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2faudio_2fsource_2fStretchy_2eproto__INCLUDED
