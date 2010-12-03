// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/audio/source/TimeStretch.proto

#ifndef PROTOBUF_rec_2faudio_2fsource_2fTimeStretch_2eproto__INCLUDED
#define PROTOBUF_rec_2faudio_2fsource_2fTimeStretch_2eproto__INCLUDED

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
#include "rec/widget/tree/VolumeFile.pb.h"
// @@protoc_insertion_point(includes)

namespace rec {
namespace audio {
namespace source {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2faudio_2fsource_2fTimeStretch_2eproto();
void protobuf_AssignDesc_rec_2faudio_2fsource_2fTimeStretch_2eproto();
void protobuf_ShutdownFile_rec_2faudio_2fsource_2fTimeStretch_2eproto();

class TimeStretch;
class StretchedFile;

// ===================================================================

class TimeStretch : public ::google::protobuf::Message {
 public:
  TimeStretch();
  virtual ~TimeStretch();
  
  TimeStretch(const TimeStretch& from);
  
  inline TimeStretch& operator=(const TimeStretch& from) {
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
  static const TimeStretch& default_instance();
  
  void Swap(TimeStretch* other);
  
  // implements Message ----------------------------------------------
  
  TimeStretch* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TimeStretch& from);
  void MergeFrom(const TimeStretch& from);
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
  
  // optional uint32 bands = 5 [default = 2048];
  inline bool has_bands() const;
  inline void clear_bands();
  static const int kBandsFieldNumber = 5;
  inline ::google::protobuf::uint32 bands() const;
  inline void set_bands(::google::protobuf::uint32 value);
  
  // optional uint32 filter_overlap = 6 [default = 1];
  inline bool has_filter_overlap() const;
  inline void clear_filter_overlap();
  static const int kFilterOverlapFieldNumber = 6;
  inline ::google::protobuf::uint32 filter_overlap() const;
  inline void set_filter_overlap(::google::protobuf::uint32 value);
  
  // optional uint32 chunk_size = 7 [default = 512];
  inline bool has_chunk_size() const;
  inline void clear_chunk_size();
  static const int kChunkSizeFieldNumber = 7;
  inline ::google::protobuf::uint32 chunk_size() const;
  inline void set_chunk_size(::google::protobuf::uint32 value);
  
  // optional uint32 prefill_size = 8 [default = 15000];
  inline bool has_prefill_size() const;
  inline void clear_prefill_size();
  static const int kPrefillSizeFieldNumber = 8;
  inline ::google::protobuf::uint32 prefill_size() const;
  inline void set_prefill_size(::google::protobuf::uint32 value);
  
  // optional uint32 next_buffer_fill_size = 9 [default = 15000];
  inline bool has_next_buffer_fill_size() const;
  inline void clear_next_buffer_fill_size();
  static const int kNextBufferFillSizeFieldNumber = 9;
  inline ::google::protobuf::uint32 next_buffer_fill_size() const;
  inline void set_next_buffer_fill_size(::google::protobuf::uint32 value);
  
  // optional int32 inactive_wait_time = 10 [default = -1];
  inline bool has_inactive_wait_time() const;
  inline void clear_inactive_wait_time();
  static const int kInactiveWaitTimeFieldNumber = 10;
  inline ::google::protobuf::int32 inactive_wait_time() const;
  inline void set_inactive_wait_time(::google::protobuf::int32 value);
  
  // optional uint32 thread_priority = 11 [default = 4];
  inline bool has_thread_priority() const;
  inline void clear_thread_priority();
  static const int kThreadPriorityFieldNumber = 11;
  inline ::google::protobuf::uint32 thread_priority() const;
  inline void set_thread_priority(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:rec.audio.source.TimeStretch)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  double time_scale_;
  double sample_rate_;
  ::google::protobuf::uint32 channels_;
  double pitch_scale_;
  ::google::protobuf::uint32 bands_;
  ::google::protobuf::uint32 filter_overlap_;
  ::google::protobuf::uint32 chunk_size_;
  ::google::protobuf::uint32 prefill_size_;
  ::google::protobuf::uint32 next_buffer_fill_size_;
  ::google::protobuf::int32 inactive_wait_time_;
  ::google::protobuf::uint32 thread_priority_;
  friend void  protobuf_AddDesc_rec_2faudio_2fsource_2fTimeStretch_2eproto();
  friend void protobuf_AssignDesc_rec_2faudio_2fsource_2fTimeStretch_2eproto();
  friend void protobuf_ShutdownFile_rec_2faudio_2fsource_2fTimeStretch_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(11 + 31) / 32];
  
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
  static TimeStretch* default_instance_;
};
// -------------------------------------------------------------------

class StretchedFile : public ::google::protobuf::Message {
 public:
  StretchedFile();
  virtual ~StretchedFile();
  
  StretchedFile(const StretchedFile& from);
  
  inline StretchedFile& operator=(const StretchedFile& from) {
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
  static const StretchedFile& default_instance();
  
  void Swap(StretchedFile* other);
  
  // implements Message ----------------------------------------------
  
  StretchedFile* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const StretchedFile& from);
  void MergeFrom(const StretchedFile& from);
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
  
  // optional .rec.audio.source.TimeStretch stretch = 1;
  inline bool has_stretch() const;
  inline void clear_stretch();
  static const int kStretchFieldNumber = 1;
  inline const ::rec::audio::source::TimeStretch& stretch() const;
  inline ::rec::audio::source::TimeStretch* mutable_stretch();
  
  // optional .rec.widget.tree.VolumeFile file = 2;
  inline bool has_file() const;
  inline void clear_file();
  static const int kFileFieldNumber = 2;
  inline const ::rec::widget::tree::VolumeFile& file() const;
  inline ::rec::widget::tree::VolumeFile* mutable_file();
  
  // @@protoc_insertion_point(class_scope:rec.audio.source.StretchedFile)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::rec::audio::source::TimeStretch* stretch_;
  ::rec::widget::tree::VolumeFile* file_;
  friend void  protobuf_AddDesc_rec_2faudio_2fsource_2fTimeStretch_2eproto();
  friend void protobuf_AssignDesc_rec_2faudio_2fsource_2fTimeStretch_2eproto();
  friend void protobuf_ShutdownFile_rec_2faudio_2fsource_2fTimeStretch_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
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
  static StretchedFile* default_instance_;
};
// ===================================================================


// ===================================================================

// TimeStretch

// optional double time_scale = 1 [default = 1];
inline bool TimeStretch::has_time_scale() const {
  return _has_bit(0);
}
inline void TimeStretch::clear_time_scale() {
  time_scale_ = 1;
  _clear_bit(0);
}
inline double TimeStretch::time_scale() const {
  return time_scale_;
}
inline void TimeStretch::set_time_scale(double value) {
  _set_bit(0);
  time_scale_ = value;
}

// optional double sample_rate = 2 [default = 44100];
inline bool TimeStretch::has_sample_rate() const {
  return _has_bit(1);
}
inline void TimeStretch::clear_sample_rate() {
  sample_rate_ = 44100;
  _clear_bit(1);
}
inline double TimeStretch::sample_rate() const {
  return sample_rate_;
}
inline void TimeStretch::set_sample_rate(double value) {
  _set_bit(1);
  sample_rate_ = value;
}

// optional uint32 channels = 3 [default = 2];
inline bool TimeStretch::has_channels() const {
  return _has_bit(2);
}
inline void TimeStretch::clear_channels() {
  channels_ = 2u;
  _clear_bit(2);
}
inline ::google::protobuf::uint32 TimeStretch::channels() const {
  return channels_;
}
inline void TimeStretch::set_channels(::google::protobuf::uint32 value) {
  _set_bit(2);
  channels_ = value;
}

// optional double pitch_scale = 4 [default = 1];
inline bool TimeStretch::has_pitch_scale() const {
  return _has_bit(3);
}
inline void TimeStretch::clear_pitch_scale() {
  pitch_scale_ = 1;
  _clear_bit(3);
}
inline double TimeStretch::pitch_scale() const {
  return pitch_scale_;
}
inline void TimeStretch::set_pitch_scale(double value) {
  _set_bit(3);
  pitch_scale_ = value;
}

// optional uint32 bands = 5 [default = 2048];
inline bool TimeStretch::has_bands() const {
  return _has_bit(4);
}
inline void TimeStretch::clear_bands() {
  bands_ = 2048u;
  _clear_bit(4);
}
inline ::google::protobuf::uint32 TimeStretch::bands() const {
  return bands_;
}
inline void TimeStretch::set_bands(::google::protobuf::uint32 value) {
  _set_bit(4);
  bands_ = value;
}

// optional uint32 filter_overlap = 6 [default = 1];
inline bool TimeStretch::has_filter_overlap() const {
  return _has_bit(5);
}
inline void TimeStretch::clear_filter_overlap() {
  filter_overlap_ = 1u;
  _clear_bit(5);
}
inline ::google::protobuf::uint32 TimeStretch::filter_overlap() const {
  return filter_overlap_;
}
inline void TimeStretch::set_filter_overlap(::google::protobuf::uint32 value) {
  _set_bit(5);
  filter_overlap_ = value;
}

// optional uint32 chunk_size = 7 [default = 512];
inline bool TimeStretch::has_chunk_size() const {
  return _has_bit(6);
}
inline void TimeStretch::clear_chunk_size() {
  chunk_size_ = 512u;
  _clear_bit(6);
}
inline ::google::protobuf::uint32 TimeStretch::chunk_size() const {
  return chunk_size_;
}
inline void TimeStretch::set_chunk_size(::google::protobuf::uint32 value) {
  _set_bit(6);
  chunk_size_ = value;
}

// optional uint32 prefill_size = 8 [default = 15000];
inline bool TimeStretch::has_prefill_size() const {
  return _has_bit(7);
}
inline void TimeStretch::clear_prefill_size() {
  prefill_size_ = 15000u;
  _clear_bit(7);
}
inline ::google::protobuf::uint32 TimeStretch::prefill_size() const {
  return prefill_size_;
}
inline void TimeStretch::set_prefill_size(::google::protobuf::uint32 value) {
  _set_bit(7);
  prefill_size_ = value;
}

// optional uint32 next_buffer_fill_size = 9 [default = 15000];
inline bool TimeStretch::has_next_buffer_fill_size() const {
  return _has_bit(8);
}
inline void TimeStretch::clear_next_buffer_fill_size() {
  next_buffer_fill_size_ = 15000u;
  _clear_bit(8);
}
inline ::google::protobuf::uint32 TimeStretch::next_buffer_fill_size() const {
  return next_buffer_fill_size_;
}
inline void TimeStretch::set_next_buffer_fill_size(::google::protobuf::uint32 value) {
  _set_bit(8);
  next_buffer_fill_size_ = value;
}

// optional int32 inactive_wait_time = 10 [default = -1];
inline bool TimeStretch::has_inactive_wait_time() const {
  return _has_bit(9);
}
inline void TimeStretch::clear_inactive_wait_time() {
  inactive_wait_time_ = -1;
  _clear_bit(9);
}
inline ::google::protobuf::int32 TimeStretch::inactive_wait_time() const {
  return inactive_wait_time_;
}
inline void TimeStretch::set_inactive_wait_time(::google::protobuf::int32 value) {
  _set_bit(9);
  inactive_wait_time_ = value;
}

// optional uint32 thread_priority = 11 [default = 4];
inline bool TimeStretch::has_thread_priority() const {
  return _has_bit(10);
}
inline void TimeStretch::clear_thread_priority() {
  thread_priority_ = 4u;
  _clear_bit(10);
}
inline ::google::protobuf::uint32 TimeStretch::thread_priority() const {
  return thread_priority_;
}
inline void TimeStretch::set_thread_priority(::google::protobuf::uint32 value) {
  _set_bit(10);
  thread_priority_ = value;
}

// -------------------------------------------------------------------

// StretchedFile

// optional .rec.audio.source.TimeStretch stretch = 1;
inline bool StretchedFile::has_stretch() const {
  return _has_bit(0);
}
inline void StretchedFile::clear_stretch() {
  if (stretch_ != NULL) stretch_->::rec::audio::source::TimeStretch::Clear();
  _clear_bit(0);
}
inline const ::rec::audio::source::TimeStretch& StretchedFile::stretch() const {
  return stretch_ != NULL ? *stretch_ : *default_instance_->stretch_;
}
inline ::rec::audio::source::TimeStretch* StretchedFile::mutable_stretch() {
  _set_bit(0);
  if (stretch_ == NULL) stretch_ = new ::rec::audio::source::TimeStretch;
  return stretch_;
}

// optional .rec.widget.tree.VolumeFile file = 2;
inline bool StretchedFile::has_file() const {
  return _has_bit(1);
}
inline void StretchedFile::clear_file() {
  if (file_ != NULL) file_->::rec::widget::tree::VolumeFile::Clear();
  _clear_bit(1);
}
inline const ::rec::widget::tree::VolumeFile& StretchedFile::file() const {
  return file_ != NULL ? *file_ : *default_instance_->file_;
}
inline ::rec::widget::tree::VolumeFile* StretchedFile::mutable_file() {
  _set_bit(1);
  if (file_ == NULL) file_ = new ::rec::widget::tree::VolumeFile;
  return file_;
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

#endif  // PROTOBUF_rec_2faudio_2fsource_2fTimeStretch_2eproto__INCLUDED
