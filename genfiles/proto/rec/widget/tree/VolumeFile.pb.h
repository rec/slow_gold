// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/widget/tree/VolumeFile.proto

#ifndef PROTOBUF_rec_2fwidget_2ftree_2fVolumeFile_2eproto__INCLUDED
#define PROTOBUF_rec_2fwidget_2ftree_2fVolumeFile_2eproto__INCLUDED

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
#include "rec/widget/Widget.pb.h"
// @@protoc_insertion_point(includes)

namespace rec {
namespace widget {
namespace tree {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fwidget_2ftree_2fVolumeFile_2eproto();
void protobuf_AssignDesc_rec_2fwidget_2ftree_2fVolumeFile_2eproto();
void protobuf_ShutdownFile_rec_2fwidget_2ftree_2fVolumeFile_2eproto();

class Volume;
class VolumeFile;

enum Volume_Type {
  Volume_Type_CD = 1,
  Volume_Type_MUSIC = 2,
  Volume_Type_USER = 3,
  Volume_Type_VOLUME = 4
};
bool Volume_Type_IsValid(int value);
const Volume_Type Volume_Type_Type_MIN = Volume_Type_CD;
const Volume_Type Volume_Type_Type_MAX = Volume_Type_VOLUME;
const int Volume_Type_Type_ARRAYSIZE = Volume_Type_Type_MAX + 1;

const ::google::protobuf::EnumDescriptor* Volume_Type_descriptor();
inline const ::std::string& Volume_Type_Name(Volume_Type value) {
  return ::google::protobuf::internal::NameOfEnum(
    Volume_Type_descriptor(), value);
}
inline bool Volume_Type_Parse(
    const ::std::string& name, Volume_Type* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Volume_Type>(
    Volume_Type_descriptor(), name, value);
}
// ===================================================================

class Volume : public ::google::protobuf::Message {
 public:
  Volume();
  virtual ~Volume();
  
  Volume(const Volume& from);
  
  inline Volume& operator=(const Volume& from) {
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
  static const Volume& default_instance();
  
  void Swap(Volume* other);
  
  // implements Message ----------------------------------------------
  
  Volume* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Volume& from);
  void MergeFrom(const Volume& from);
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
  
  typedef Volume_Type Type;
  static const Type CD = Volume_Type_CD;
  static const Type MUSIC = Volume_Type_MUSIC;
  static const Type USER = Volume_Type_USER;
  static const Type VOLUME = Volume_Type_VOLUME;
  static inline bool Type_IsValid(int value) {
    return Volume_Type_IsValid(value);
  }
  static const Type Type_MIN =
    Volume_Type_Type_MIN;
  static const Type Type_MAX =
    Volume_Type_Type_MAX;
  static const int Type_ARRAYSIZE =
    Volume_Type_Type_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Type_descriptor() {
    return Volume_Type_descriptor();
  }
  static inline const ::std::string& Type_Name(Type value) {
    return Volume_Type_Name(value);
  }
  static inline bool Type_Parse(const ::std::string& name,
      Type* value) {
    return Volume_Type_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // optional .rec.widget.tree.Volume.Type type = 1;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline ::rec::widget::tree::Volume_Type type() const;
  inline void set_type(::rec::widget::tree::Volume_Type value);
  
  // repeated string name = 2;
  inline int name_size() const;
  inline void clear_name();
  static const int kNameFieldNumber = 2;
  inline const ::std::string& name(int index) const;
  inline ::std::string* mutable_name(int index);
  inline void set_name(int index, const ::std::string& value);
  inline void set_name(int index, const char* value);
  inline void set_name(int index, const char* value, size_t size);
  inline ::std::string* add_name();
  inline void add_name(const ::std::string& value);
  inline void add_name(const char* value);
  inline void add_name(const char* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& name() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_name();
  
  // @@protoc_insertion_point(class_scope:rec.widget.tree.Volume)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  int type_;
  ::google::protobuf::RepeatedPtrField< ::std::string> name_;
  friend void  protobuf_AddDesc_rec_2fwidget_2ftree_2fVolumeFile_2eproto();
  friend void protobuf_AssignDesc_rec_2fwidget_2ftree_2fVolumeFile_2eproto();
  friend void protobuf_ShutdownFile_rec_2fwidget_2ftree_2fVolumeFile_2eproto();
  
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
  static Volume* default_instance_;
};
// -------------------------------------------------------------------

class VolumeFile : public ::google::protobuf::Message {
 public:
  VolumeFile();
  virtual ~VolumeFile();
  
  VolumeFile(const VolumeFile& from);
  
  inline VolumeFile& operator=(const VolumeFile& from) {
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
  static const VolumeFile& default_instance();
  
  void Swap(VolumeFile* other);
  
  // implements Message ----------------------------------------------
  
  VolumeFile* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const VolumeFile& from);
  void MergeFrom(const VolumeFile& from);
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
  
  // optional .rec.widget.tree.Volume volume = 1;
  inline bool has_volume() const;
  inline void clear_volume();
  static const int kVolumeFieldNumber = 1;
  inline const ::rec::widget::tree::Volume& volume() const;
  inline ::rec::widget::tree::Volume* mutable_volume();
  
  // repeated string path = 2;
  inline int path_size() const;
  inline void clear_path();
  static const int kPathFieldNumber = 2;
  inline const ::std::string& path(int index) const;
  inline ::std::string* mutable_path(int index);
  inline void set_path(int index, const ::std::string& value);
  inline void set_path(int index, const char* value);
  inline void set_path(int index, const char* value, size_t size);
  inline ::std::string* add_path();
  inline void add_path(const ::std::string& value);
  inline void add_path(const char* value);
  inline void add_path(const char* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& path() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_path();
  
  // @@protoc_insertion_point(class_scope:rec.widget.tree.VolumeFile)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::rec::widget::tree::Volume* volume_;
  ::google::protobuf::RepeatedPtrField< ::std::string> path_;
  friend void  protobuf_AddDesc_rec_2fwidget_2ftree_2fVolumeFile_2eproto();
  friend void protobuf_AssignDesc_rec_2fwidget_2ftree_2fVolumeFile_2eproto();
  friend void protobuf_ShutdownFile_rec_2fwidget_2ftree_2fVolumeFile_2eproto();
  
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
  static VolumeFile* default_instance_;
};
// ===================================================================


// ===================================================================

// Volume

// optional .rec.widget.tree.Volume.Type type = 1;
inline bool Volume::has_type() const {
  return _has_bit(0);
}
inline void Volume::clear_type() {
  type_ = 1;
  _clear_bit(0);
}
inline ::rec::widget::tree::Volume_Type Volume::type() const {
  return static_cast< ::rec::widget::tree::Volume_Type >(type_);
}
inline void Volume::set_type(::rec::widget::tree::Volume_Type value) {
  GOOGLE_DCHECK(::rec::widget::tree::Volume_Type_IsValid(value));
  _set_bit(0);
  type_ = value;
}

// repeated string name = 2;
inline int Volume::name_size() const {
  return name_.size();
}
inline void Volume::clear_name() {
  name_.Clear();
}
inline const ::std::string& Volume::name(int index) const {
  return name_.Get(index);
}
inline ::std::string* Volume::mutable_name(int index) {
  return name_.Mutable(index);
}
inline void Volume::set_name(int index, const ::std::string& value) {
  name_.Mutable(index)->assign(value);
}
inline void Volume::set_name(int index, const char* value) {
  name_.Mutable(index)->assign(value);
}
inline void Volume::set_name(int index, const char* value, size_t size) {
  name_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Volume::add_name() {
  return name_.Add();
}
inline void Volume::add_name(const ::std::string& value) {
  name_.Add()->assign(value);
}
inline void Volume::add_name(const char* value) {
  name_.Add()->assign(value);
}
inline void Volume::add_name(const char* value, size_t size) {
  name_.Add()->assign(reinterpret_cast<const char*>(value), size);
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
Volume::name() const {
  return name_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
Volume::mutable_name() {
  return &name_;
}

// -------------------------------------------------------------------

// VolumeFile

// optional .rec.widget.tree.Volume volume = 1;
inline bool VolumeFile::has_volume() const {
  return _has_bit(0);
}
inline void VolumeFile::clear_volume() {
  if (volume_ != NULL) volume_->::rec::widget::tree::Volume::Clear();
  _clear_bit(0);
}
inline const ::rec::widget::tree::Volume& VolumeFile::volume() const {
  return volume_ != NULL ? *volume_ : *default_instance_->volume_;
}
inline ::rec::widget::tree::Volume* VolumeFile::mutable_volume() {
  _set_bit(0);
  if (volume_ == NULL) volume_ = new ::rec::widget::tree::Volume;
  return volume_;
}

// repeated string path = 2;
inline int VolumeFile::path_size() const {
  return path_.size();
}
inline void VolumeFile::clear_path() {
  path_.Clear();
}
inline const ::std::string& VolumeFile::path(int index) const {
  return path_.Get(index);
}
inline ::std::string* VolumeFile::mutable_path(int index) {
  return path_.Mutable(index);
}
inline void VolumeFile::set_path(int index, const ::std::string& value) {
  path_.Mutable(index)->assign(value);
}
inline void VolumeFile::set_path(int index, const char* value) {
  path_.Mutable(index)->assign(value);
}
inline void VolumeFile::set_path(int index, const char* value, size_t size) {
  path_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
}
inline ::std::string* VolumeFile::add_path() {
  return path_.Add();
}
inline void VolumeFile::add_path(const ::std::string& value) {
  path_.Add()->assign(value);
}
inline void VolumeFile::add_path(const char* value) {
  path_.Add()->assign(value);
}
inline void VolumeFile::add_path(const char* value, size_t size) {
  path_.Add()->assign(reinterpret_cast<const char*>(value), size);
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
VolumeFile::path() const {
  return path_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
VolumeFile::mutable_path() {
  return &path_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace tree
}  // namespace widget
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::rec::widget::tree::Volume_Type>() {
  return ::rec::widget::tree::Volume_Type_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2fwidget_2ftree_2fVolumeFile_2eproto__INCLUDED
