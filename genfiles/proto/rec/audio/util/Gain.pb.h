// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/audio/util/Gain.proto

#ifndef PROTOBUF_rec_2faudio_2futil_2fGain_2eproto__INCLUDED
#define PROTOBUF_rec_2faudio_2futil_2fGain_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace rec {
namespace audio {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2faudio_2futil_2fGain_2eproto();
void protobuf_AssignDesc_rec_2faudio_2futil_2fGain_2eproto();
void protobuf_ShutdownFile_rec_2faudio_2futil_2fGain_2eproto();

class Gain;

// ===================================================================

class Gain : public ::google::protobuf::Message {
 public:
  Gain();
  virtual ~Gain();

  Gain(const Gain& from);

  inline Gain& operator=(const Gain& from) {
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
  static const Gain& default_instance();

  void Swap(Gain* other);

  // implements Message ----------------------------------------------

  Gain* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Gain& from);
  void MergeFrom(const Gain& from);
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

  // optional double level = 1 [default = 1];
  inline bool has_level() const;
  inline void clear_level();
  static const int kLevelFieldNumber = 1;
  inline double level() const;
  inline void set_level(double value);

  // optional double gain = 5 [default = 0];
  inline bool has_gain() const;
  inline void clear_gain();
  static const int kGainFieldNumber = 5;
  inline double gain() const;
  inline void set_gain(double value);

  // optional bool mute = 2;
  inline bool has_mute() const;
  inline void clear_mute();
  static const int kMuteFieldNumber = 2;
  inline bool mute() const;
  inline void set_mute(bool value);

  // optional bool dim = 3;
  inline bool has_dim() const;
  inline void clear_dim();
  static const int kDimFieldNumber = 3;
  inline bool dim() const;
  inline void set_dim(bool value);

  // optional double dim_level = 4 [default = 0.2];
  inline bool has_dim_level() const;
  inline void clear_dim_level();
  static const int kDimLevelFieldNumber = 4;
  inline double dim_level() const;
  inline void set_dim_level(double value);

  // optional bool prefader_levels = 6;
  inline bool has_prefader_levels() const;
  inline void clear_prefader_levels();
  static const int kPrefaderLevelsFieldNumber = 6;
  inline bool prefader_levels() const;
  inline void set_prefader_levels(bool value);

  // @@protoc_insertion_point(class_scope:rec.audio.Gain)
 private:
  inline void set_has_level();
  inline void clear_has_level();
  inline void set_has_gain();
  inline void clear_has_gain();
  inline void set_has_mute();
  inline void clear_has_mute();
  inline void set_has_dim();
  inline void clear_has_dim();
  inline void set_has_dim_level();
  inline void clear_has_dim_level();
  inline void set_has_prefader_levels();
  inline void clear_has_prefader_levels();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  double level_;
  double gain_;
  double dim_level_;
  bool mute_;
  bool dim_;
  bool prefader_levels_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(6 + 31) / 32];

  friend void  protobuf_AddDesc_rec_2faudio_2futil_2fGain_2eproto();
  friend void protobuf_AssignDesc_rec_2faudio_2futil_2fGain_2eproto();
  friend void protobuf_ShutdownFile_rec_2faudio_2futil_2fGain_2eproto();

  void InitAsDefaultInstance();
  static Gain* default_instance_;
};
// ===================================================================


// ===================================================================

// Gain

// optional double level = 1 [default = 1];
inline bool Gain::has_level() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Gain::set_has_level() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Gain::clear_has_level() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Gain::clear_level() {
  level_ = 1;
  clear_has_level();
}
inline double Gain::level() const {
  return level_;
}
inline void Gain::set_level(double value) {
  set_has_level();
  level_ = value;
}

// optional double gain = 5 [default = 0];
inline bool Gain::has_gain() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Gain::set_has_gain() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Gain::clear_has_gain() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Gain::clear_gain() {
  gain_ = 0;
  clear_has_gain();
}
inline double Gain::gain() const {
  return gain_;
}
inline void Gain::set_gain(double value) {
  set_has_gain();
  gain_ = value;
}

// optional bool mute = 2;
inline bool Gain::has_mute() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Gain::set_has_mute() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Gain::clear_has_mute() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Gain::clear_mute() {
  mute_ = false;
  clear_has_mute();
}
inline bool Gain::mute() const {
  return mute_;
}
inline void Gain::set_mute(bool value) {
  set_has_mute();
  mute_ = value;
}

// optional bool dim = 3;
inline bool Gain::has_dim() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Gain::set_has_dim() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Gain::clear_has_dim() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Gain::clear_dim() {
  dim_ = false;
  clear_has_dim();
}
inline bool Gain::dim() const {
  return dim_;
}
inline void Gain::set_dim(bool value) {
  set_has_dim();
  dim_ = value;
}

// optional double dim_level = 4 [default = 0.2];
inline bool Gain::has_dim_level() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Gain::set_has_dim_level() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Gain::clear_has_dim_level() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Gain::clear_dim_level() {
  dim_level_ = 0.2;
  clear_has_dim_level();
}
inline double Gain::dim_level() const {
  return dim_level_;
}
inline void Gain::set_dim_level(double value) {
  set_has_dim_level();
  dim_level_ = value;
}

// optional bool prefader_levels = 6;
inline bool Gain::has_prefader_levels() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Gain::set_has_prefader_levels() {
  _has_bits_[0] |= 0x00000020u;
}
inline void Gain::clear_has_prefader_levels() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void Gain::clear_prefader_levels() {
  prefader_levels_ = false;
  clear_has_prefader_levels();
}
inline bool Gain::prefader_levels() const {
  return prefader_levels_;
}
inline void Gain::set_prefader_levels(bool value) {
  set_has_prefader_levels();
  prefader_levels_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace audio
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2faudio_2futil_2fGain_2eproto__INCLUDED
