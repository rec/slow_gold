// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/widget/tree/Path.proto

#ifndef PROTOBUF_rec_2fwidget_2ftree_2fPath_2eproto__INCLUDED
#define PROTOBUF_rec_2fwidget_2ftree_2fPath_2eproto__INCLUDED

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
namespace widget {
namespace tree {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fwidget_2ftree_2fPath_2eproto();
void protobuf_AssignDesc_rec_2fwidget_2ftree_2fPath_2eproto();
void protobuf_ShutdownFile_rec_2fwidget_2ftree_2fPath_2eproto();

class Path;

// ===================================================================

class Path : public ::google::protobuf::Message {
 public:
  Path();
  virtual ~Path();

  Path(const Path& from);

  inline Path& operator=(const Path& from) {
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
  static const Path& default_instance();

  void Swap(Path* other);

  // implements Message ----------------------------------------------

  Path* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Path& from);
  void MergeFrom(const Path& from);
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

  // repeated string step = 1;
  inline int step_size() const;
  inline void clear_step();
  static const int kStepFieldNumber = 1;
  inline const ::std::string& step(int index) const;
  inline ::std::string* mutable_step(int index);
  inline void set_step(int index, const ::std::string& value);
  inline void set_step(int index, const char* value);
  inline void set_step(int index, const char* value, size_t size);
  inline ::std::string* add_step();
  inline void add_step(const ::std::string& value);
  inline void add_step(const char* value);
  inline void add_step(const char* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& step() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_step();

  // @@protoc_insertion_point(class_scope:rec.widget.tree.Path)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::std::string> step_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_rec_2fwidget_2ftree_2fPath_2eproto();
  friend void protobuf_AssignDesc_rec_2fwidget_2ftree_2fPath_2eproto();
  friend void protobuf_ShutdownFile_rec_2fwidget_2ftree_2fPath_2eproto();

  void InitAsDefaultInstance();
  static Path* default_instance_;
};
// ===================================================================


// ===================================================================

// Path

// repeated string step = 1;
inline int Path::step_size() const {
  return step_.size();
}
inline void Path::clear_step() {
  step_.Clear();
}
inline const ::std::string& Path::step(int index) const {
  return step_.Get(index);
}
inline ::std::string* Path::mutable_step(int index) {
  return step_.Mutable(index);
}
inline void Path::set_step(int index, const ::std::string& value) {
  step_.Mutable(index)->assign(value);
}
inline void Path::set_step(int index, const char* value) {
  step_.Mutable(index)->assign(value);
}
inline void Path::set_step(int index, const char* value, size_t size) {
  step_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Path::add_step() {
  return step_.Add();
}
inline void Path::add_step(const ::std::string& value) {
  step_.Add()->assign(value);
}
inline void Path::add_step(const char* value) {
  step_.Add()->assign(value);
}
inline void Path::add_step(const char* value, size_t size) {
  step_.Add()->assign(reinterpret_cast<const char*>(value), size);
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
Path::step() const {
  return step_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
Path::mutable_step() {
  return &step_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace tree
}  // namespace widget
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2fwidget_2ftree_2fPath_2eproto__INCLUDED
