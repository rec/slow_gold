// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/slow/Parameters.proto

#ifndef PROTOBUF_rec_2fslow_2fParameters_2eproto__INCLUDED
#define PROTOBUF_rec_2fslow_2fParameters_2eproto__INCLUDED

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
#include "rec/util/file/VirtualFile.pb.h"
#include "rec/audio/stretch/Stretch.pb.h"
// @@protoc_insertion_point(includes)

namespace rec {
namespace slow {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fslow_2fParameters_2eproto();
void protobuf_AssignDesc_rec_2fslow_2fParameters_2eproto();
void protobuf_ShutdownFile_rec_2fslow_2fParameters_2eproto();

class Parameters;

// ===================================================================

class Parameters : public ::google::protobuf::Message {
 public:
  Parameters();
  virtual ~Parameters();
  
  Parameters(const Parameters& from);
  
  inline Parameters& operator=(const Parameters& from) {
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
  static const Parameters& default_instance();
  
  void Swap(Parameters* other);
  
  // implements Message ----------------------------------------------
  
  Parameters* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Parameters& from);
  void MergeFrom(const Parameters& from);
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
  
  // optional .rec.util.file.VirtualFile file = 1;
  inline bool has_file() const;
  inline void clear_file();
  static const int kFileFieldNumber = 1;
  inline const ::rec::util::file::VirtualFile& file() const;
  inline ::rec::util::file::VirtualFile* mutable_file();
  
  // optional .rec.audio.stretch.Stretch stretch = 2;
  inline bool has_stretch() const;
  inline void clear_stretch();
  static const int kStretchFieldNumber = 2;
  inline const ::rec::audio::stretch::Stretch& stretch() const;
  inline ::rec::audio::stretch::Stretch* mutable_stretch();
  
  // @@protoc_insertion_point(class_scope:rec.slow.Parameters)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::rec::util::file::VirtualFile* file_;
  ::rec::audio::stretch::Stretch* stretch_;
  friend void  protobuf_AddDesc_rec_2fslow_2fParameters_2eproto();
  friend void protobuf_AssignDesc_rec_2fslow_2fParameters_2eproto();
  friend void protobuf_ShutdownFile_rec_2fslow_2fParameters_2eproto();
  
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
  static Parameters* default_instance_;
};
// ===================================================================


// ===================================================================

// Parameters

// optional .rec.util.file.VirtualFile file = 1;
inline bool Parameters::has_file() const {
  return _has_bit(0);
}
inline void Parameters::clear_file() {
  if (file_ != NULL) file_->::rec::util::file::VirtualFile::Clear();
  _clear_bit(0);
}
inline const ::rec::util::file::VirtualFile& Parameters::file() const {
  return file_ != NULL ? *file_ : *default_instance_->file_;
}
inline ::rec::util::file::VirtualFile* Parameters::mutable_file() {
  _set_bit(0);
  if (file_ == NULL) file_ = new ::rec::util::file::VirtualFile;
  return file_;
}

// optional .rec.audio.stretch.Stretch stretch = 2;
inline bool Parameters::has_stretch() const {
  return _has_bit(1);
}
inline void Parameters::clear_stretch() {
  if (stretch_ != NULL) stretch_->::rec::audio::stretch::Stretch::Clear();
  _clear_bit(1);
}
inline const ::rec::audio::stretch::Stretch& Parameters::stretch() const {
  return stretch_ != NULL ? *stretch_ : *default_instance_->stretch_;
}
inline ::rec::audio::stretch::Stretch* Parameters::mutable_stretch() {
  _set_bit(1);
  if (stretch_ == NULL) stretch_ = new ::rec::audio::stretch::Stretch;
  return stretch_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace slow
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2fslow_2fParameters_2eproto__INCLUDED
