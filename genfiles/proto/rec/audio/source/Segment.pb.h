// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/audio/source/Segment.proto

#ifndef PROTOBUF_rec_2faudio_2fsource_2fSegment_2eproto__INCLUDED
#define PROTOBUF_rec_2faudio_2fsource_2fSegment_2eproto__INCLUDED

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
void  protobuf_AddDesc_rec_2faudio_2fsource_2fSegment_2eproto();
void protobuf_AssignDesc_rec_2faudio_2fsource_2fSegment_2eproto();
void protobuf_ShutdownFile_rec_2faudio_2fsource_2fSegment_2eproto();

class Segment;
class SegmentList;

// ===================================================================

class Segment : public ::google::protobuf::Message {
 public:
  Segment();
  virtual ~Segment();
  
  Segment(const Segment& from);
  
  inline Segment& operator=(const Segment& from) {
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
  static const Segment& default_instance();
  
  void Swap(Segment* other);
  
  // implements Message ----------------------------------------------
  
  Segment* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Segment& from);
  void MergeFrom(const Segment& from);
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
  
  // optional double begin = 1;
  inline bool has_begin() const;
  inline void clear_begin();
  static const int kBeginFieldNumber = 1;
  inline double begin() const;
  inline void set_begin(double value);
  
  // optional double end = 2;
  inline bool has_end() const;
  inline void clear_end();
  static const int kEndFieldNumber = 2;
  inline double end() const;
  inline void set_end(double value);
  
  // optional string name = 3;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 3;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  
  // optional string notes = 4;
  inline bool has_notes() const;
  inline void clear_notes();
  static const int kNotesFieldNumber = 4;
  inline const ::std::string& notes() const;
  inline void set_notes(const ::std::string& value);
  inline void set_notes(const char* value);
  inline void set_notes(const char* value, size_t size);
  inline ::std::string* mutable_notes();
  
  // @@protoc_insertion_point(class_scope:rec.audio.source.Segment)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  double begin_;
  double end_;
  ::std::string* name_;
  static const ::std::string _default_name_;
  ::std::string* notes_;
  static const ::std::string _default_notes_;
  friend void  protobuf_AddDesc_rec_2faudio_2fsource_2fSegment_2eproto();
  friend void protobuf_AssignDesc_rec_2faudio_2fsource_2fSegment_2eproto();
  friend void protobuf_ShutdownFile_rec_2faudio_2fsource_2fSegment_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];
  
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
  static Segment* default_instance_;
};
// -------------------------------------------------------------------

class SegmentList : public ::google::protobuf::Message {
 public:
  SegmentList();
  virtual ~SegmentList();
  
  SegmentList(const SegmentList& from);
  
  inline SegmentList& operator=(const SegmentList& from) {
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
  static const SegmentList& default_instance();
  
  void Swap(SegmentList* other);
  
  // implements Message ----------------------------------------------
  
  SegmentList* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SegmentList& from);
  void MergeFrom(const SegmentList& from);
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
  
  // repeated .rec.audio.source.Segment segment = 1;
  inline int segment_size() const;
  inline void clear_segment();
  static const int kSegmentFieldNumber = 1;
  inline const ::rec::audio::source::Segment& segment(int index) const;
  inline ::rec::audio::source::Segment* mutable_segment(int index);
  inline ::rec::audio::source::Segment* add_segment();
  inline const ::google::protobuf::RepeatedPtrField< ::rec::audio::source::Segment >&
      segment() const;
  inline ::google::protobuf::RepeatedPtrField< ::rec::audio::source::Segment >*
      mutable_segment();
  
  // @@protoc_insertion_point(class_scope:rec.audio.source.SegmentList)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::google::protobuf::RepeatedPtrField< ::rec::audio::source::Segment > segment_;
  friend void  protobuf_AddDesc_rec_2faudio_2fsource_2fSegment_2eproto();
  friend void protobuf_AssignDesc_rec_2faudio_2fsource_2fSegment_2eproto();
  friend void protobuf_ShutdownFile_rec_2faudio_2fsource_2fSegment_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
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
  static SegmentList* default_instance_;
};
// ===================================================================


// ===================================================================

// Segment

// optional double begin = 1;
inline bool Segment::has_begin() const {
  return _has_bit(0);
}
inline void Segment::clear_begin() {
  begin_ = 0;
  _clear_bit(0);
}
inline double Segment::begin() const {
  return begin_;
}
inline void Segment::set_begin(double value) {
  _set_bit(0);
  begin_ = value;
}

// optional double end = 2;
inline bool Segment::has_end() const {
  return _has_bit(1);
}
inline void Segment::clear_end() {
  end_ = 0;
  _clear_bit(1);
}
inline double Segment::end() const {
  return end_;
}
inline void Segment::set_end(double value) {
  _set_bit(1);
  end_ = value;
}

// optional string name = 3;
inline bool Segment::has_name() const {
  return _has_bit(2);
}
inline void Segment::clear_name() {
  if (name_ != &_default_name_) {
    name_->clear();
  }
  _clear_bit(2);
}
inline const ::std::string& Segment::name() const {
  return *name_;
}
inline void Segment::set_name(const ::std::string& value) {
  _set_bit(2);
  if (name_ == &_default_name_) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Segment::set_name(const char* value) {
  _set_bit(2);
  if (name_ == &_default_name_) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Segment::set_name(const char* value, size_t size) {
  _set_bit(2);
  if (name_ == &_default_name_) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Segment::mutable_name() {
  _set_bit(2);
  if (name_ == &_default_name_) {
    name_ = new ::std::string;
  }
  return name_;
}

// optional string notes = 4;
inline bool Segment::has_notes() const {
  return _has_bit(3);
}
inline void Segment::clear_notes() {
  if (notes_ != &_default_notes_) {
    notes_->clear();
  }
  _clear_bit(3);
}
inline const ::std::string& Segment::notes() const {
  return *notes_;
}
inline void Segment::set_notes(const ::std::string& value) {
  _set_bit(3);
  if (notes_ == &_default_notes_) {
    notes_ = new ::std::string;
  }
  notes_->assign(value);
}
inline void Segment::set_notes(const char* value) {
  _set_bit(3);
  if (notes_ == &_default_notes_) {
    notes_ = new ::std::string;
  }
  notes_->assign(value);
}
inline void Segment::set_notes(const char* value, size_t size) {
  _set_bit(3);
  if (notes_ == &_default_notes_) {
    notes_ = new ::std::string;
  }
  notes_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Segment::mutable_notes() {
  _set_bit(3);
  if (notes_ == &_default_notes_) {
    notes_ = new ::std::string;
  }
  return notes_;
}

// -------------------------------------------------------------------

// SegmentList

// repeated .rec.audio.source.Segment segment = 1;
inline int SegmentList::segment_size() const {
  return segment_.size();
}
inline void SegmentList::clear_segment() {
  segment_.Clear();
}
inline const ::rec::audio::source::Segment& SegmentList::segment(int index) const {
  return segment_.Get(index);
}
inline ::rec::audio::source::Segment* SegmentList::mutable_segment(int index) {
  return segment_.Mutable(index);
}
inline ::rec::audio::source::Segment* SegmentList::add_segment() {
  return segment_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::rec::audio::source::Segment >&
SegmentList::segment() const {
  return segment_;
}
inline ::google::protobuf::RepeatedPtrField< ::rec::audio::source::Segment >*
SegmentList::mutable_segment() {
  return &segment_;
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

#endif  // PROTOBUF_rec_2faudio_2fsource_2fSegment_2eproto__INCLUDED
