// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/slow/app/AppLayout.proto

#ifndef PROTOBUF_rec_2fslow_2fapp_2fAppLayout_2eproto__INCLUDED
#define PROTOBUF_rec_2fslow_2fapp_2fAppLayout_2eproto__INCLUDED

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
void  protobuf_AddDesc_rec_2fslow_2fapp_2fAppLayout_2eproto();
void protobuf_AssignDesc_rec_2fslow_2fapp_2fAppLayout_2eproto();
void protobuf_ShutdownFile_rec_2fslow_2fapp_2fAppLayout_2eproto();

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
  
  // optional .rec.gui.Rectangle bounds = 1;
  inline bool has_bounds() const;
  inline void clear_bounds();
  static const int kBoundsFieldNumber = 1;
  inline const ::rec::gui::Rectangle& bounds() const;
  inline ::rec::gui::Rectangle* mutable_bounds();
  
  // optional uint32 directory_y = 2 [default = 350];
  inline bool has_directory_y() const;
  inline void clear_directory_y();
  static const int kDirectoryYFieldNumber = 2;
  inline ::google::protobuf::uint32 directory_y() const;
  inline void set_directory_y(::google::protobuf::uint32 value);
  
  // optional uint32 waveform_y = 3 [default = 500];
  inline bool has_waveform_y() const;
  inline void clear_waveform_y();
  static const int kWaveformYFieldNumber = 3;
  inline ::google::protobuf::uint32 waveform_y() const;
  inline void set_waveform_y(::google::protobuf::uint32 value);
  
  // optional uint32 loops_x = 4 [default = 800];
  inline bool has_loops_x() const;
  inline void clear_loops_x();
  static const int kLoopsXFieldNumber = 4;
  inline ::google::protobuf::uint32 loops_x() const;
  inline void set_loops_x(::google::protobuf::uint32 value);
  
  // optional uint32 clock_x = 5 [default = 600];
  inline bool has_clock_x() const;
  inline void clear_clock_x();
  static const int kClockXFieldNumber = 5;
  inline ::google::protobuf::uint32 clock_x() const;
  inline void set_clock_x(::google::protobuf::uint32 value);
  
  // optional uint32 stretchy_y = 6 [default = 200];
  inline bool has_stretchy_y() const;
  inline void clear_stretchy_y();
  static const int kStretchyYFieldNumber = 6;
  inline ::google::protobuf::uint32 stretchy_y() const;
  inline void set_stretchy_y(::google::protobuf::uint32 value);
  
  // optional uint32 songdata_x = 7 [default = 600];
  inline bool has_songdata_x() const;
  inline void clear_songdata_x();
  static const int kSongdataXFieldNumber = 7;
  inline ::google::protobuf::uint32 songdata_x() const;
  inline void set_songdata_x(::google::protobuf::uint32 value);
  
  // optional bool full_directory = 8 [default = false];
  inline bool has_full_directory() const;
  inline void clear_full_directory();
  static const int kFullDirectoryFieldNumber = 8;
  inline bool full_directory() const;
  inline void set_full_directory(bool value);
  
  // optional bool full_waveform = 9 [default = false];
  inline bool has_full_waveform() const;
  inline void clear_full_waveform();
  static const int kFullWaveformFieldNumber = 9;
  inline bool full_waveform() const;
  inline void set_full_waveform(bool value);
  
  // optional bool full_controller = 10 [default = false];
  inline bool has_full_controller() const;
  inline void clear_full_controller();
  static const int kFullControllerFieldNumber = 10;
  inline bool full_controller() const;
  inline void set_full_controller(bool value);
  
  // @@protoc_insertion_point(class_scope:rec.slow.AppLayout)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::rec::gui::Rectangle* bounds_;
  ::google::protobuf::uint32 directory_y_;
  ::google::protobuf::uint32 waveform_y_;
  ::google::protobuf::uint32 loops_x_;
  ::google::protobuf::uint32 clock_x_;
  ::google::protobuf::uint32 stretchy_y_;
  ::google::protobuf::uint32 songdata_x_;
  bool full_directory_;
  bool full_waveform_;
  bool full_controller_;
  friend void  protobuf_AddDesc_rec_2fslow_2fapp_2fAppLayout_2eproto();
  friend void protobuf_AssignDesc_rec_2fslow_2fapp_2fAppLayout_2eproto();
  friend void protobuf_ShutdownFile_rec_2fslow_2fapp_2fAppLayout_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(10 + 31) / 32];
  
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

// optional .rec.gui.Rectangle bounds = 1;
inline bool AppLayout::has_bounds() const {
  return _has_bit(0);
}
inline void AppLayout::clear_bounds() {
  if (bounds_ != NULL) bounds_->::rec::gui::Rectangle::Clear();
  _clear_bit(0);
}
inline const ::rec::gui::Rectangle& AppLayout::bounds() const {
  return bounds_ != NULL ? *bounds_ : *default_instance_->bounds_;
}
inline ::rec::gui::Rectangle* AppLayout::mutable_bounds() {
  _set_bit(0);
  if (bounds_ == NULL) bounds_ = new ::rec::gui::Rectangle;
  return bounds_;
}

// optional uint32 directory_y = 2 [default = 350];
inline bool AppLayout::has_directory_y() const {
  return _has_bit(1);
}
inline void AppLayout::clear_directory_y() {
  directory_y_ = 350u;
  _clear_bit(1);
}
inline ::google::protobuf::uint32 AppLayout::directory_y() const {
  return directory_y_;
}
inline void AppLayout::set_directory_y(::google::protobuf::uint32 value) {
  _set_bit(1);
  directory_y_ = value;
}

// optional uint32 waveform_y = 3 [default = 500];
inline bool AppLayout::has_waveform_y() const {
  return _has_bit(2);
}
inline void AppLayout::clear_waveform_y() {
  waveform_y_ = 500u;
  _clear_bit(2);
}
inline ::google::protobuf::uint32 AppLayout::waveform_y() const {
  return waveform_y_;
}
inline void AppLayout::set_waveform_y(::google::protobuf::uint32 value) {
  _set_bit(2);
  waveform_y_ = value;
}

// optional uint32 loops_x = 4 [default = 800];
inline bool AppLayout::has_loops_x() const {
  return _has_bit(3);
}
inline void AppLayout::clear_loops_x() {
  loops_x_ = 800u;
  _clear_bit(3);
}
inline ::google::protobuf::uint32 AppLayout::loops_x() const {
  return loops_x_;
}
inline void AppLayout::set_loops_x(::google::protobuf::uint32 value) {
  _set_bit(3);
  loops_x_ = value;
}

// optional uint32 clock_x = 5 [default = 600];
inline bool AppLayout::has_clock_x() const {
  return _has_bit(4);
}
inline void AppLayout::clear_clock_x() {
  clock_x_ = 600u;
  _clear_bit(4);
}
inline ::google::protobuf::uint32 AppLayout::clock_x() const {
  return clock_x_;
}
inline void AppLayout::set_clock_x(::google::protobuf::uint32 value) {
  _set_bit(4);
  clock_x_ = value;
}

// optional uint32 stretchy_y = 6 [default = 200];
inline bool AppLayout::has_stretchy_y() const {
  return _has_bit(5);
}
inline void AppLayout::clear_stretchy_y() {
  stretchy_y_ = 200u;
  _clear_bit(5);
}
inline ::google::protobuf::uint32 AppLayout::stretchy_y() const {
  return stretchy_y_;
}
inline void AppLayout::set_stretchy_y(::google::protobuf::uint32 value) {
  _set_bit(5);
  stretchy_y_ = value;
}

// optional uint32 songdata_x = 7 [default = 600];
inline bool AppLayout::has_songdata_x() const {
  return _has_bit(6);
}
inline void AppLayout::clear_songdata_x() {
  songdata_x_ = 600u;
  _clear_bit(6);
}
inline ::google::protobuf::uint32 AppLayout::songdata_x() const {
  return songdata_x_;
}
inline void AppLayout::set_songdata_x(::google::protobuf::uint32 value) {
  _set_bit(6);
  songdata_x_ = value;
}

// optional bool full_directory = 8 [default = false];
inline bool AppLayout::has_full_directory() const {
  return _has_bit(7);
}
inline void AppLayout::clear_full_directory() {
  full_directory_ = false;
  _clear_bit(7);
}
inline bool AppLayout::full_directory() const {
  return full_directory_;
}
inline void AppLayout::set_full_directory(bool value) {
  _set_bit(7);
  full_directory_ = value;
}

// optional bool full_waveform = 9 [default = false];
inline bool AppLayout::has_full_waveform() const {
  return _has_bit(8);
}
inline void AppLayout::clear_full_waveform() {
  full_waveform_ = false;
  _clear_bit(8);
}
inline bool AppLayout::full_waveform() const {
  return full_waveform_;
}
inline void AppLayout::set_full_waveform(bool value) {
  _set_bit(8);
  full_waveform_ = value;
}

// optional bool full_controller = 10 [default = false];
inline bool AppLayout::has_full_controller() const {
  return _has_bit(9);
}
inline void AppLayout::clear_full_controller() {
  full_controller_ = false;
  _clear_bit(9);
}
inline bool AppLayout::full_controller() const {
  return full_controller_;
}
inline void AppLayout::set_full_controller(bool value) {
  _set_bit(9);
  full_controller_ = value;
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

#endif  // PROTOBUF_rec_2fslow_2fapp_2fAppLayout_2eproto__INCLUDED
