// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: description.proto

#ifndef PROTOBUF_description_2eproto__INCLUDED
#define PROTOBUF_description_2eproto__INCLUDED

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
// @@protoc_insertion_point(includes)

namespace rec {
namespace audio {
namespace timescaler {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_description_2eproto();
void protobuf_AssignDesc_description_2eproto();
void protobuf_ShutdownFile_description_2eproto();

class Description;

// ===================================================================

class Description : public ::google::protobuf::Message {
 public:
  Description();
  virtual ~Description();
  
  Description(const Description& from);
  
  inline Description& operator=(const Description& from) {
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
  static const Description& default_instance();
  
  void Swap(Description* other);
  
  // implements Message ----------------------------------------------
  
  Description* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Description& from);
  void MergeFrom(const Description& from);
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
  
  // @@protoc_insertion_point(class_scope:rec.audio.timescaler.Description)
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
  friend void  protobuf_AddDesc_description_2eproto();
  friend void protobuf_AssignDesc_description_2eproto();
  friend void protobuf_ShutdownFile_description_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(7 + 31) / 32];
  
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
  static Description* default_instance_;
};
// ===================================================================


// ===================================================================

// Description

// optional double time_scale = 1 [default = 1];
inline bool Description::has_time_scale() const {
  return _has_bit(0);
}
inline void Description::clear_time_scale() {
  time_scale_ = 1;
  _clear_bit(0);
}
inline double Description::time_scale() const {
  return time_scale_;
}
inline void Description::set_time_scale(double value) {
  _set_bit(0);
  time_scale_ = value;
}

// optional double sample_rate = 2 [default = 44100];
inline bool Description::has_sample_rate() const {
  return _has_bit(1);
}
inline void Description::clear_sample_rate() {
  sample_rate_ = 44100;
  _clear_bit(1);
}
inline double Description::sample_rate() const {
  return sample_rate_;
}
inline void Description::set_sample_rate(double value) {
  _set_bit(1);
  sample_rate_ = value;
}

// optional uint32 channels = 3 [default = 2];
inline bool Description::has_channels() const {
  return _has_bit(2);
}
inline void Description::clear_channels() {
  channels_ = 2u;
  _clear_bit(2);
}
inline ::google::protobuf::uint32 Description::channels() const {
  return channels_;
}
inline void Description::set_channels(::google::protobuf::uint32 value) {
  _set_bit(2);
  channels_ = value;
}

// optional double pitch_scale = 4 [default = 1];
inline bool Description::has_pitch_scale() const {
  return _has_bit(3);
}
inline void Description::clear_pitch_scale() {
  pitch_scale_ = 1;
  _clear_bit(3);
}
inline double Description::pitch_scale() const {
  return pitch_scale_;
}
inline void Description::set_pitch_scale(double value) {
  _set_bit(3);
  pitch_scale_ = value;
}

// optional uint32 bands = 5 [default = 2048];
inline bool Description::has_bands() const {
  return _has_bit(4);
}
inline void Description::clear_bands() {
  bands_ = 2048u;
  _clear_bit(4);
}
inline ::google::protobuf::uint32 Description::bands() const {
  return bands_;
}
inline void Description::set_bands(::google::protobuf::uint32 value) {
  _set_bit(4);
  bands_ = value;
}

// optional uint32 filter_overlap = 6 [default = 1];
inline bool Description::has_filter_overlap() const {
  return _has_bit(5);
}
inline void Description::clear_filter_overlap() {
  filter_overlap_ = 1u;
  _clear_bit(5);
}
inline ::google::protobuf::uint32 Description::filter_overlap() const {
  return filter_overlap_;
}
inline void Description::set_filter_overlap(::google::protobuf::uint32 value) {
  _set_bit(5);
  filter_overlap_ = value;
}

// optional uint32 chunk_size = 7 [default = 512];
inline bool Description::has_chunk_size() const {
  return _has_bit(6);
}
inline void Description::clear_chunk_size() {
  chunk_size_ = 512u;
  _clear_bit(6);
}
inline ::google::protobuf::uint32 Description::chunk_size() const {
  return chunk_size_;
}
inline void Description::set_chunk_size(::google::protobuf::uint32 value) {
  _set_bit(6);
  chunk_size_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace timescaler
}  // namespace audio
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_description_2eproto__INCLUDED
