// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/audio/stretch/Stretch.proto

#ifndef PROTOBUF_rec_2faudio_2fstretch_2fStretch_2eproto__INCLUDED
#define PROTOBUF_rec_2faudio_2fstretch_2fStretch_2eproto__INCLUDED

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
#include "rec/audio/source/Stereo.pb.h"
// @@protoc_insertion_point(includes)

namespace rec {
namespace audio {
namespace stretch {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2faudio_2fstretch_2fStretch_2eproto();
void protobuf_AssignDesc_rec_2faudio_2fstretch_2fStretch_2eproto();
void protobuf_ShutdownFile_rec_2faudio_2fstretch_2fStretch_2eproto();

class Stretch;

enum Stretch_Strategy {
  Stretch_Strategy_AUDIO_MAGIC = 0,
  Stretch_Strategy_SOUNDTOUCH = 1
};
bool Stretch_Strategy_IsValid(int value);
const Stretch_Strategy Stretch_Strategy_Strategy_MIN = Stretch_Strategy_AUDIO_MAGIC;
const Stretch_Strategy Stretch_Strategy_Strategy_MAX = Stretch_Strategy_SOUNDTOUCH;
const int Stretch_Strategy_Strategy_ARRAYSIZE = Stretch_Strategy_Strategy_MAX + 1;

const ::google::protobuf::EnumDescriptor* Stretch_Strategy_descriptor();
inline const ::std::string& Stretch_Strategy_Name(Stretch_Strategy value) {
  return ::google::protobuf::internal::NameOfEnum(
    Stretch_Strategy_descriptor(), value);
}
inline bool Stretch_Strategy_Parse(
    const ::std::string& name, Stretch_Strategy* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Stretch_Strategy>(
    Stretch_Strategy_descriptor(), name, value);
}
// ===================================================================

class Stretch : public ::google::protobuf::Message {
 public:
  Stretch();
  virtual ~Stretch();
  
  Stretch(const Stretch& from);
  
  inline Stretch& operator=(const Stretch& from) {
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
  static const Stretch& default_instance();
  
  void Swap(Stretch* other);
  
  // implements Message ----------------------------------------------
  
  Stretch* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Stretch& from);
  void MergeFrom(const Stretch& from);
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
  
  typedef Stretch_Strategy Strategy;
  static const Strategy AUDIO_MAGIC = Stretch_Strategy_AUDIO_MAGIC;
  static const Strategy SOUNDTOUCH = Stretch_Strategy_SOUNDTOUCH;
  static inline bool Strategy_IsValid(int value) {
    return Stretch_Strategy_IsValid(value);
  }
  static const Strategy Strategy_MIN =
    Stretch_Strategy_Strategy_MIN;
  static const Strategy Strategy_MAX =
    Stretch_Strategy_Strategy_MAX;
  static const int Strategy_ARRAYSIZE =
    Stretch_Strategy_Strategy_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Strategy_descriptor() {
    return Stretch_Strategy_descriptor();
  }
  static inline const ::std::string& Strategy_Name(Strategy value) {
    return Stretch_Strategy_Name(value);
  }
  static inline bool Strategy_Parse(const ::std::string& name,
      Strategy* value) {
    return Stretch_Strategy_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // optional .rec.audio.stretch.Stretch.Strategy strategy = 18 [default = AUDIO_MAGIC];
  inline bool has_strategy() const;
  inline void clear_strategy();
  static const int kStrategyFieldNumber = 18;
  inline ::rec::audio::stretch::Stretch_Strategy strategy() const;
  inline void set_strategy(::rec::audio::stretch::Stretch_Strategy value);
  
  // optional bool time_disabled = 1 [default = false];
  inline bool has_time_disabled() const;
  inline void clear_time_disabled();
  static const int kTimeDisabledFieldNumber = 1;
  inline bool time_disabled() const;
  inline void set_time_disabled(bool value);
  
  // optional bool pitch_disabled = 2 [default = false];
  inline bool has_pitch_disabled() const;
  inline void clear_pitch_disabled();
  static const int kPitchDisabledFieldNumber = 2;
  inline bool pitch_disabled() const;
  inline void set_pitch_disabled(bool value);
  
  // optional bool passthrough_when_disabled = 3 [default = true];
  inline bool has_passthrough_when_disabled() const;
  inline void clear_passthrough_when_disabled();
  static const int kPassthroughWhenDisabledFieldNumber = 3;
  inline bool passthrough_when_disabled() const;
  inline void set_passthrough_when_disabled(bool value);
  
  // optional double time_scale = 4 [default = 1];
  inline bool has_time_scale() const;
  inline void clear_time_scale();
  static const int kTimeScaleFieldNumber = 4;
  inline double time_scale() const;
  inline void set_time_scale(double value);
  
  // optional double time_percent = 5 [default = 100];
  inline bool has_time_percent() const;
  inline void clear_time_percent();
  static const int kTimePercentFieldNumber = 5;
  inline double time_percent() const;
  inline void set_time_percent(double value);
  
  // optional double sample_rate = 6 [default = 44100];
  inline bool has_sample_rate() const;
  inline void clear_sample_rate();
  static const int kSampleRateFieldNumber = 6;
  inline double sample_rate() const;
  inline void set_sample_rate(double value);
  
  // optional uint32 channels = 7 [default = 2];
  inline bool has_channels() const;
  inline void clear_channels();
  static const int kChannelsFieldNumber = 7;
  inline ::google::protobuf::uint32 channels() const;
  inline void set_channels(::google::protobuf::uint32 value);
  
  // optional double pitch_scale = 8 [default = 1];
  inline bool has_pitch_scale() const;
  inline void clear_pitch_scale();
  static const int kPitchScaleFieldNumber = 8;
  inline double pitch_scale() const;
  inline void set_pitch_scale(double value);
  
  // optional double semitone_shift = 9 [default = 0];
  inline bool has_semitone_shift() const;
  inline void clear_semitone_shift();
  static const int kSemitoneShiftFieldNumber = 9;
  inline double semitone_shift() const;
  inline void set_semitone_shift(double value);
  
  // optional double detune_cents = 10 [default = 0];
  inline bool has_detune_cents() const;
  inline void clear_detune_cents();
  static const int kDetuneCentsFieldNumber = 10;
  inline double detune_cents() const;
  inline void set_detune_cents(double value);
  
  // optional uint32 bands = 11 [default = 2048];
  inline bool has_bands() const;
  inline void clear_bands();
  static const int kBandsFieldNumber = 11;
  inline ::google::protobuf::uint32 bands() const;
  inline void set_bands(::google::protobuf::uint32 value);
  
  // optional uint32 filter_overlap = 12 [default = 1];
  inline bool has_filter_overlap() const;
  inline void clear_filter_overlap();
  static const int kFilterOverlapFieldNumber = 12;
  inline ::google::protobuf::uint32 filter_overlap() const;
  inline void set_filter_overlap(::google::protobuf::uint32 value);
  
  // optional uint32 chunk_size = 13 [default = 1024];
  inline bool has_chunk_size() const;
  inline void clear_chunk_size();
  static const int kChunkSizeFieldNumber = 13;
  inline ::google::protobuf::uint32 chunk_size() const;
  inline void set_chunk_size(::google::protobuf::uint32 value);
  
  // optional uint32 prefill_size = 14 [default = 15000];
  inline bool has_prefill_size() const;
  inline void clear_prefill_size();
  static const int kPrefillSizeFieldNumber = 14;
  inline ::google::protobuf::uint32 prefill_size() const;
  inline void set_prefill_size(::google::protobuf::uint32 value);
  
  // optional uint32 next_buffer_fill_size = 15 [default = 15000];
  inline bool has_next_buffer_fill_size() const;
  inline void clear_next_buffer_fill_size();
  static const int kNextBufferFillSizeFieldNumber = 15;
  inline ::google::protobuf::uint32 next_buffer_fill_size() const;
  inline void set_next_buffer_fill_size(::google::protobuf::uint32 value);
  
  // optional int32 inactive_wait_time = 16 [default = -1];
  inline bool has_inactive_wait_time() const;
  inline void clear_inactive_wait_time();
  static const int kInactiveWaitTimeFieldNumber = 16;
  inline ::google::protobuf::int32 inactive_wait_time() const;
  inline void set_inactive_wait_time(::google::protobuf::int32 value);
  
  // optional uint32 thread_priority = 17 [default = 4];
  inline bool has_thread_priority() const;
  inline void clear_thread_priority();
  static const int kThreadPriorityFieldNumber = 17;
  inline ::google::protobuf::uint32 thread_priority() const;
  inline void set_thread_priority(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:rec.audio.stretch.Stretch)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  int strategy_;
  bool time_disabled_;
  bool pitch_disabled_;
  bool passthrough_when_disabled_;
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
  friend void  protobuf_AddDesc_rec_2faudio_2fstretch_2fStretch_2eproto();
  friend void protobuf_AssignDesc_rec_2faudio_2fstretch_2fStretch_2eproto();
  friend void protobuf_ShutdownFile_rec_2faudio_2fstretch_2fStretch_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(18 + 31) / 32];
  
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
  static Stretch* default_instance_;
};
// ===================================================================


// ===================================================================

// Stretch

// optional .rec.audio.stretch.Stretch.Strategy strategy = 18 [default = AUDIO_MAGIC];
inline bool Stretch::has_strategy() const {
  return _has_bit(0);
}
inline void Stretch::clear_strategy() {
  strategy_ = 0;
  _clear_bit(0);
}
inline ::rec::audio::stretch::Stretch_Strategy Stretch::strategy() const {
  return static_cast< ::rec::audio::stretch::Stretch_Strategy >(strategy_);
}
inline void Stretch::set_strategy(::rec::audio::stretch::Stretch_Strategy value) {
  GOOGLE_DCHECK(::rec::audio::stretch::Stretch_Strategy_IsValid(value));
  _set_bit(0);
  strategy_ = value;
}

// optional bool time_disabled = 1 [default = false];
inline bool Stretch::has_time_disabled() const {
  return _has_bit(1);
}
inline void Stretch::clear_time_disabled() {
  time_disabled_ = false;
  _clear_bit(1);
}
inline bool Stretch::time_disabled() const {
  return time_disabled_;
}
inline void Stretch::set_time_disabled(bool value) {
  _set_bit(1);
  time_disabled_ = value;
}

// optional bool pitch_disabled = 2 [default = false];
inline bool Stretch::has_pitch_disabled() const {
  return _has_bit(2);
}
inline void Stretch::clear_pitch_disabled() {
  pitch_disabled_ = false;
  _clear_bit(2);
}
inline bool Stretch::pitch_disabled() const {
  return pitch_disabled_;
}
inline void Stretch::set_pitch_disabled(bool value) {
  _set_bit(2);
  pitch_disabled_ = value;
}

// optional bool passthrough_when_disabled = 3 [default = true];
inline bool Stretch::has_passthrough_when_disabled() const {
  return _has_bit(3);
}
inline void Stretch::clear_passthrough_when_disabled() {
  passthrough_when_disabled_ = true;
  _clear_bit(3);
}
inline bool Stretch::passthrough_when_disabled() const {
  return passthrough_when_disabled_;
}
inline void Stretch::set_passthrough_when_disabled(bool value) {
  _set_bit(3);
  passthrough_when_disabled_ = value;
}

// optional double time_scale = 4 [default = 1];
inline bool Stretch::has_time_scale() const {
  return _has_bit(4);
}
inline void Stretch::clear_time_scale() {
  time_scale_ = 1;
  _clear_bit(4);
}
inline double Stretch::time_scale() const {
  return time_scale_;
}
inline void Stretch::set_time_scale(double value) {
  _set_bit(4);
  time_scale_ = value;
}

// optional double time_percent = 5 [default = 100];
inline bool Stretch::has_time_percent() const {
  return _has_bit(5);
}
inline void Stretch::clear_time_percent() {
  time_percent_ = 100;
  _clear_bit(5);
}
inline double Stretch::time_percent() const {
  return time_percent_;
}
inline void Stretch::set_time_percent(double value) {
  _set_bit(5);
  time_percent_ = value;
}

// optional double sample_rate = 6 [default = 44100];
inline bool Stretch::has_sample_rate() const {
  return _has_bit(6);
}
inline void Stretch::clear_sample_rate() {
  sample_rate_ = 44100;
  _clear_bit(6);
}
inline double Stretch::sample_rate() const {
  return sample_rate_;
}
inline void Stretch::set_sample_rate(double value) {
  _set_bit(6);
  sample_rate_ = value;
}

// optional uint32 channels = 7 [default = 2];
inline bool Stretch::has_channels() const {
  return _has_bit(7);
}
inline void Stretch::clear_channels() {
  channels_ = 2u;
  _clear_bit(7);
}
inline ::google::protobuf::uint32 Stretch::channels() const {
  return channels_;
}
inline void Stretch::set_channels(::google::protobuf::uint32 value) {
  _set_bit(7);
  channels_ = value;
}

// optional double pitch_scale = 8 [default = 1];
inline bool Stretch::has_pitch_scale() const {
  return _has_bit(8);
}
inline void Stretch::clear_pitch_scale() {
  pitch_scale_ = 1;
  _clear_bit(8);
}
inline double Stretch::pitch_scale() const {
  return pitch_scale_;
}
inline void Stretch::set_pitch_scale(double value) {
  _set_bit(8);
  pitch_scale_ = value;
}

// optional double semitone_shift = 9 [default = 0];
inline bool Stretch::has_semitone_shift() const {
  return _has_bit(9);
}
inline void Stretch::clear_semitone_shift() {
  semitone_shift_ = 0;
  _clear_bit(9);
}
inline double Stretch::semitone_shift() const {
  return semitone_shift_;
}
inline void Stretch::set_semitone_shift(double value) {
  _set_bit(9);
  semitone_shift_ = value;
}

// optional double detune_cents = 10 [default = 0];
inline bool Stretch::has_detune_cents() const {
  return _has_bit(10);
}
inline void Stretch::clear_detune_cents() {
  detune_cents_ = 0;
  _clear_bit(10);
}
inline double Stretch::detune_cents() const {
  return detune_cents_;
}
inline void Stretch::set_detune_cents(double value) {
  _set_bit(10);
  detune_cents_ = value;
}

// optional uint32 bands = 11 [default = 2048];
inline bool Stretch::has_bands() const {
  return _has_bit(11);
}
inline void Stretch::clear_bands() {
  bands_ = 2048u;
  _clear_bit(11);
}
inline ::google::protobuf::uint32 Stretch::bands() const {
  return bands_;
}
inline void Stretch::set_bands(::google::protobuf::uint32 value) {
  _set_bit(11);
  bands_ = value;
}

// optional uint32 filter_overlap = 12 [default = 1];
inline bool Stretch::has_filter_overlap() const {
  return _has_bit(12);
}
inline void Stretch::clear_filter_overlap() {
  filter_overlap_ = 1u;
  _clear_bit(12);
}
inline ::google::protobuf::uint32 Stretch::filter_overlap() const {
  return filter_overlap_;
}
inline void Stretch::set_filter_overlap(::google::protobuf::uint32 value) {
  _set_bit(12);
  filter_overlap_ = value;
}

// optional uint32 chunk_size = 13 [default = 1024];
inline bool Stretch::has_chunk_size() const {
  return _has_bit(13);
}
inline void Stretch::clear_chunk_size() {
  chunk_size_ = 1024u;
  _clear_bit(13);
}
inline ::google::protobuf::uint32 Stretch::chunk_size() const {
  return chunk_size_;
}
inline void Stretch::set_chunk_size(::google::protobuf::uint32 value) {
  _set_bit(13);
  chunk_size_ = value;
}

// optional uint32 prefill_size = 14 [default = 15000];
inline bool Stretch::has_prefill_size() const {
  return _has_bit(14);
}
inline void Stretch::clear_prefill_size() {
  prefill_size_ = 15000u;
  _clear_bit(14);
}
inline ::google::protobuf::uint32 Stretch::prefill_size() const {
  return prefill_size_;
}
inline void Stretch::set_prefill_size(::google::protobuf::uint32 value) {
  _set_bit(14);
  prefill_size_ = value;
}

// optional uint32 next_buffer_fill_size = 15 [default = 15000];
inline bool Stretch::has_next_buffer_fill_size() const {
  return _has_bit(15);
}
inline void Stretch::clear_next_buffer_fill_size() {
  next_buffer_fill_size_ = 15000u;
  _clear_bit(15);
}
inline ::google::protobuf::uint32 Stretch::next_buffer_fill_size() const {
  return next_buffer_fill_size_;
}
inline void Stretch::set_next_buffer_fill_size(::google::protobuf::uint32 value) {
  _set_bit(15);
  next_buffer_fill_size_ = value;
}

// optional int32 inactive_wait_time = 16 [default = -1];
inline bool Stretch::has_inactive_wait_time() const {
  return _has_bit(16);
}
inline void Stretch::clear_inactive_wait_time() {
  inactive_wait_time_ = -1;
  _clear_bit(16);
}
inline ::google::protobuf::int32 Stretch::inactive_wait_time() const {
  return inactive_wait_time_;
}
inline void Stretch::set_inactive_wait_time(::google::protobuf::int32 value) {
  _set_bit(16);
  inactive_wait_time_ = value;
}

// optional uint32 thread_priority = 17 [default = 4];
inline bool Stretch::has_thread_priority() const {
  return _has_bit(17);
}
inline void Stretch::clear_thread_priority() {
  thread_priority_ = 4u;
  _clear_bit(17);
}
inline ::google::protobuf::uint32 Stretch::thread_priority() const {
  return thread_priority_;
}
inline void Stretch::set_thread_priority(::google::protobuf::uint32 value) {
  _set_bit(17);
  thread_priority_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::rec::audio::stretch::Stretch_Strategy>() {
  return ::rec::audio::stretch::Stretch_Strategy_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2faudio_2fstretch_2fStretch_2eproto__INCLUDED
