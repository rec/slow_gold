// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/audio/util/BufferManager.proto

#ifndef PROTOBUF_rec_2faudio_2futil_2fBufferManager_2eproto__INCLUDED
#define PROTOBUF_rec_2faudio_2futil_2fBufferManager_2eproto__INCLUDED

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
void  protobuf_AddDesc_rec_2faudio_2futil_2fBufferManager_2eproto();
void protobuf_AssignDesc_rec_2faudio_2futil_2fBufferManager_2eproto();
void protobuf_ShutdownFile_rec_2faudio_2futil_2fBufferManager_2eproto();

class BufferManagerDesc;

// ===================================================================

class BufferManagerDesc : public ::google::protobuf::Message {
 public:
  BufferManagerDesc();
  virtual ~BufferManagerDesc();

  BufferManagerDesc(const BufferManagerDesc& from);

  inline BufferManagerDesc& operator=(const BufferManagerDesc& from) {
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
  static const BufferManagerDesc& default_instance();

  void Swap(BufferManagerDesc* other);

  // implements Message ----------------------------------------------

  BufferManagerDesc* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BufferManagerDesc& from);
  void MergeFrom(const BufferManagerDesc& from);
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

  // optional uint64 max_size = 1;
  inline bool has_max_size() const;
  inline void clear_max_size();
  static const int kMaxSizeFieldNumber = 1;
  inline ::google::protobuf::uint64 max_size() const;
  inline void set_max_size(::google::protobuf::uint64 value);

  // optional double reallocate_shrinkage = 2 [default = 0.9];
  inline bool has_reallocate_shrinkage() const;
  inline void clear_reallocate_shrinkage();
  static const int kReallocateShrinkageFieldNumber = 2;
  inline double reallocate_shrinkage() const;
  inline void set_reallocate_shrinkage(double value);

  // optional uint32 source_samples_per_thumbnail_sample = 3 [default = 512];
  inline bool has_source_samples_per_thumbnail_sample() const;
  inline void clear_source_samples_per_thumbnail_sample();
  static const int kSourceSamplesPerThumbnailSampleFieldNumber = 3;
  inline ::google::protobuf::uint32 source_samples_per_thumbnail_sample() const;
  inline void set_source_samples_per_thumbnail_sample(::google::protobuf::uint32 value);

  // optional uint32 chunk_size = 4 [default = 512];
  inline bool has_chunk_size() const;
  inline void clear_chunk_size();
  static const int kChunkSizeFieldNumber = 4;
  inline ::google::protobuf::uint32 chunk_size() const;
  inline void set_chunk_size(::google::protobuf::uint32 value);

  // optional uint32 min_preload_size = 5 [default = 1024];
  inline bool has_min_preload_size() const;
  inline void clear_min_preload_size();
  static const int kMinPreloadSizeFieldNumber = 5;
  inline ::google::protobuf::uint32 min_preload_size() const;
  inline void set_min_preload_size(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:rec.audio.BufferManagerDesc)
 private:
  inline void set_has_max_size();
  inline void clear_has_max_size();
  inline void set_has_reallocate_shrinkage();
  inline void clear_has_reallocate_shrinkage();
  inline void set_has_source_samples_per_thumbnail_sample();
  inline void clear_has_source_samples_per_thumbnail_sample();
  inline void set_has_chunk_size();
  inline void clear_has_chunk_size();
  inline void set_has_min_preload_size();
  inline void clear_has_min_preload_size();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint64 max_size_;
  double reallocate_shrinkage_;
  ::google::protobuf::uint32 source_samples_per_thumbnail_sample_;
  ::google::protobuf::uint32 chunk_size_;
  ::google::protobuf::uint32 min_preload_size_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];

  friend void  protobuf_AddDesc_rec_2faudio_2futil_2fBufferManager_2eproto();
  friend void protobuf_AssignDesc_rec_2faudio_2futil_2fBufferManager_2eproto();
  friend void protobuf_ShutdownFile_rec_2faudio_2futil_2fBufferManager_2eproto();

  void InitAsDefaultInstance();
  static BufferManagerDesc* default_instance_;
};
// ===================================================================


// ===================================================================

// BufferManagerDesc

// optional uint64 max_size = 1;
inline bool BufferManagerDesc::has_max_size() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void BufferManagerDesc::set_has_max_size() {
  _has_bits_[0] |= 0x00000001u;
}
inline void BufferManagerDesc::clear_has_max_size() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void BufferManagerDesc::clear_max_size() {
  max_size_ = GOOGLE_ULONGLONG(0);
  clear_has_max_size();
}
inline ::google::protobuf::uint64 BufferManagerDesc::max_size() const {
  return max_size_;
}
inline void BufferManagerDesc::set_max_size(::google::protobuf::uint64 value) {
  set_has_max_size();
  max_size_ = value;
}

// optional double reallocate_shrinkage = 2 [default = 0.9];
inline bool BufferManagerDesc::has_reallocate_shrinkage() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void BufferManagerDesc::set_has_reallocate_shrinkage() {
  _has_bits_[0] |= 0x00000002u;
}
inline void BufferManagerDesc::clear_has_reallocate_shrinkage() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void BufferManagerDesc::clear_reallocate_shrinkage() {
  reallocate_shrinkage_ = 0.9;
  clear_has_reallocate_shrinkage();
}
inline double BufferManagerDesc::reallocate_shrinkage() const {
  return reallocate_shrinkage_;
}
inline void BufferManagerDesc::set_reallocate_shrinkage(double value) {
  set_has_reallocate_shrinkage();
  reallocate_shrinkage_ = value;
}

// optional uint32 source_samples_per_thumbnail_sample = 3 [default = 512];
inline bool BufferManagerDesc::has_source_samples_per_thumbnail_sample() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void BufferManagerDesc::set_has_source_samples_per_thumbnail_sample() {
  _has_bits_[0] |= 0x00000004u;
}
inline void BufferManagerDesc::clear_has_source_samples_per_thumbnail_sample() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void BufferManagerDesc::clear_source_samples_per_thumbnail_sample() {
  source_samples_per_thumbnail_sample_ = 512u;
  clear_has_source_samples_per_thumbnail_sample();
}
inline ::google::protobuf::uint32 BufferManagerDesc::source_samples_per_thumbnail_sample() const {
  return source_samples_per_thumbnail_sample_;
}
inline void BufferManagerDesc::set_source_samples_per_thumbnail_sample(::google::protobuf::uint32 value) {
  set_has_source_samples_per_thumbnail_sample();
  source_samples_per_thumbnail_sample_ = value;
}

// optional uint32 chunk_size = 4 [default = 512];
inline bool BufferManagerDesc::has_chunk_size() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void BufferManagerDesc::set_has_chunk_size() {
  _has_bits_[0] |= 0x00000008u;
}
inline void BufferManagerDesc::clear_has_chunk_size() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void BufferManagerDesc::clear_chunk_size() {
  chunk_size_ = 512u;
  clear_has_chunk_size();
}
inline ::google::protobuf::uint32 BufferManagerDesc::chunk_size() const {
  return chunk_size_;
}
inline void BufferManagerDesc::set_chunk_size(::google::protobuf::uint32 value) {
  set_has_chunk_size();
  chunk_size_ = value;
}

// optional uint32 min_preload_size = 5 [default = 1024];
inline bool BufferManagerDesc::has_min_preload_size() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void BufferManagerDesc::set_has_min_preload_size() {
  _has_bits_[0] |= 0x00000010u;
}
inline void BufferManagerDesc::clear_has_min_preload_size() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void BufferManagerDesc::clear_min_preload_size() {
  min_preload_size_ = 1024u;
  clear_has_min_preload_size();
}
inline ::google::protobuf::uint32 BufferManagerDesc::min_preload_size() const {
  return min_preload_size_;
}
inline void BufferManagerDesc::set_min_preload_size(::google::protobuf::uint32 value) {
  set_has_min_preload_size();
  min_preload_size_ = value;
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

#endif  // PROTOBUF_rec_2faudio_2futil_2fBufferManager_2eproto__INCLUDED
