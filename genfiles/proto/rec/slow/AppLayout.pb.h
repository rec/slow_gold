// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/slow/AppLayout.proto

#ifndef PROTOBUF_rec_2fslow_2fAppLayout_2eproto__INCLUDED
#define PROTOBUF_rec_2fslow_2fAppLayout_2eproto__INCLUDED

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
#include "rec/gui/Geometry.pb.h"
// @@protoc_insertion_point(includes)

namespace rec {
namespace slow {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fslow_2fAppLayout_2eproto();
void protobuf_AssignDesc_rec_2fslow_2fAppLayout_2eproto();
void protobuf_ShutdownFile_rec_2fslow_2fAppLayout_2eproto();

class AppLayout;

// ===================================================================

class AppLayout : public ::google::protobuf::Message {
 public:
  AppLayout();
  virtual ~AppLayout();
  
  AppLayout(const AppLayout& from);
  
  inline AppLayout& operator=(const AppLayout& from) {
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
  static const AppLayout& default_instance();
  
  void Swap(AppLayout* other);
  
  // implements Message ----------------------------------------------
  
  AppLayout* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AppLayout& from);
  void MergeFrom(const AppLayout& from);
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
  
  // optional uint32 navigation_y = 1;
  inline bool has_navigation_y() const;
  inline void clear_navigation_y();
  static const int kNavigationYFieldNumber = 1;
  inline ::google::protobuf::uint32 navigation_y() const;
  inline void set_navigation_y(::google::protobuf::uint32 value);
  
  // optional uint32 waveform_y = 2;
  inline bool has_waveform_y() const;
  inline void clear_waveform_y();
  static const int kWaveformYFieldNumber = 2;
  inline ::google::protobuf::uint32 waveform_y() const;
  inline void set_waveform_y(::google::protobuf::uint32 value);
  
  // optional uint32 directory_x = 3;
  inline bool has_directory_x() const;
  inline void clear_directory_x();
  static const int kDirectoryXFieldNumber = 3;
  inline ::google::protobuf::uint32 directory_x() const;
  inline void set_directory_x(::google::protobuf::uint32 value);
  
  // optional uint32 metadata_x = 4;
  inline bool has_metadata_x() const;
  inline void clear_metadata_x();
  static const int kMetadataXFieldNumber = 4;
  inline ::google::protobuf::uint32 metadata_x() const;
  inline void set_metadata_x(::google::protobuf::uint32 value);
  
  // optional uint32 help_x = 5;
  inline bool has_help_x() const;
  inline void clear_help_x();
  static const int kHelpXFieldNumber = 5;
  inline ::google::protobuf::uint32 help_x() const;
  inline void set_help_x(::google::protobuf::uint32 value);
  
  // optional uint32 transform_x = 6;
  inline bool has_transform_x() const;
  inline void clear_transform_x();
  static const int kTransformXFieldNumber = 6;
  inline ::google::protobuf::uint32 transform_x() const;
  inline void set_transform_x(::google::protobuf::uint32 value);
  
  // optional uint32 control_x = 7;
  inline bool has_control_x() const;
  inline void clear_control_x();
  static const int kControlXFieldNumber = 7;
  inline ::google::protobuf::uint32 control_x() const;
  inline void set_control_x(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:rec.slow.AppLayout)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::google::protobuf::uint32 navigation_y_;
  ::google::protobuf::uint32 waveform_y_;
  ::google::protobuf::uint32 directory_x_;
  ::google::protobuf::uint32 metadata_x_;
  ::google::protobuf::uint32 help_x_;
  ::google::protobuf::uint32 transform_x_;
  ::google::protobuf::uint32 control_x_;
  friend void  protobuf_AddDesc_rec_2fslow_2fAppLayout_2eproto();
  friend void protobuf_AssignDesc_rec_2fslow_2fAppLayout_2eproto();
  friend void protobuf_ShutdownFile_rec_2fslow_2fAppLayout_2eproto();
  
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
  static AppLayout* default_instance_;
};
// ===================================================================


// ===================================================================

// AppLayout

// optional uint32 navigation_y = 1;
inline bool AppLayout::has_navigation_y() const {
  return _has_bit(0);
}
inline void AppLayout::clear_navigation_y() {
  navigation_y_ = 0u;
  _clear_bit(0);
}
inline ::google::protobuf::uint32 AppLayout::navigation_y() const {
  return navigation_y_;
}
inline void AppLayout::set_navigation_y(::google::protobuf::uint32 value) {
  _set_bit(0);
  navigation_y_ = value;
}

// optional uint32 waveform_y = 2;
inline bool AppLayout::has_waveform_y() const {
  return _has_bit(1);
}
inline void AppLayout::clear_waveform_y() {
  waveform_y_ = 0u;
  _clear_bit(1);
}
inline ::google::protobuf::uint32 AppLayout::waveform_y() const {
  return waveform_y_;
}
inline void AppLayout::set_waveform_y(::google::protobuf::uint32 value) {
  _set_bit(1);
  waveform_y_ = value;
}

// optional uint32 directory_x = 3;
inline bool AppLayout::has_directory_x() const {
  return _has_bit(2);
}
inline void AppLayout::clear_directory_x() {
  directory_x_ = 0u;
  _clear_bit(2);
}
inline ::google::protobuf::uint32 AppLayout::directory_x() const {
  return directory_x_;
}
inline void AppLayout::set_directory_x(::google::protobuf::uint32 value) {
  _set_bit(2);
  directory_x_ = value;
}

// optional uint32 metadata_x = 4;
inline bool AppLayout::has_metadata_x() const {
  return _has_bit(3);
}
inline void AppLayout::clear_metadata_x() {
  metadata_x_ = 0u;
  _clear_bit(3);
}
inline ::google::protobuf::uint32 AppLayout::metadata_x() const {
  return metadata_x_;
}
inline void AppLayout::set_metadata_x(::google::protobuf::uint32 value) {
  _set_bit(3);
  metadata_x_ = value;
}

// optional uint32 help_x = 5;
inline bool AppLayout::has_help_x() const {
  return _has_bit(4);
}
inline void AppLayout::clear_help_x() {
  help_x_ = 0u;
  _clear_bit(4);
}
inline ::google::protobuf::uint32 AppLayout::help_x() const {
  return help_x_;
}
inline void AppLayout::set_help_x(::google::protobuf::uint32 value) {
  _set_bit(4);
  help_x_ = value;
}

// optional uint32 transform_x = 6;
inline bool AppLayout::has_transform_x() const {
  return _has_bit(5);
}
inline void AppLayout::clear_transform_x() {
  transform_x_ = 0u;
  _clear_bit(5);
}
inline ::google::protobuf::uint32 AppLayout::transform_x() const {
  return transform_x_;
}
inline void AppLayout::set_transform_x(::google::protobuf::uint32 value) {
  _set_bit(5);
  transform_x_ = value;
}

// optional uint32 control_x = 7;
inline bool AppLayout::has_control_x() const {
  return _has_bit(6);
}
inline void AppLayout::clear_control_x() {
  control_x_ = 0u;
  _clear_bit(6);
}
inline ::google::protobuf::uint32 AppLayout::control_x() const {
  return control_x_;
}
inline void AppLayout::set_control_x(::google::protobuf::uint32 value) {
  _set_bit(6);
  control_x_ = value;
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

#endif  // PROTOBUF_rec_2fslow_2fAppLayout_2eproto__INCLUDED
