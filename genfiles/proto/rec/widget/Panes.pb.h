// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/widget/Panes.proto

#ifndef PROTOBUF_rec_2fwidget_2fPanes_2eproto__INCLUDED
#define PROTOBUF_rec_2fwidget_2fPanes_2eproto__INCLUDED

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
#include "rec/audio/source/Stretchy.pb.h"
#include "rec/audio/source/Runny.pb.h"
#include "rec/util/file/VirtualFile.pb.h"
// @@protoc_insertion_point(includes)

namespace rec {
namespace widget {
namespace pane {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fwidget_2fPanes_2eproto();
void protobuf_AssignDesc_rec_2fwidget_2fPanes_2eproto();
void protobuf_ShutdownFile_rec_2fwidget_2fPanes_2eproto();

class Navigation;
class Directory;

enum Navigation_Tab {
  Navigation_Tab_FILE = 1,
  Navigation_Tab_CD = 2,
  Navigation_Tab_URL = 3
};
bool Navigation_Tab_IsValid(int value);
const Navigation_Tab Navigation_Tab_Tab_MIN = Navigation_Tab_FILE;
const Navigation_Tab Navigation_Tab_Tab_MAX = Navigation_Tab_URL;
const int Navigation_Tab_Tab_ARRAYSIZE = Navigation_Tab_Tab_MAX + 1;

const ::google::protobuf::EnumDescriptor* Navigation_Tab_descriptor();
inline const ::std::string& Navigation_Tab_Name(Navigation_Tab value) {
  return ::google::protobuf::internal::NameOfEnum(
    Navigation_Tab_descriptor(), value);
}
inline bool Navigation_Tab_Parse(
    const ::std::string& name, Navigation_Tab* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Navigation_Tab>(
    Navigation_Tab_descriptor(), name, value);
}
enum Navigation_Orientation {
  Navigation_Orientation_TABS_AT_TOP = 0,
  Navigation_Orientation_TABS_AT_BOTTOM = 1,
  Navigation_Orientation_TABS_AT_LEFT = 2,
  Navigation_Orientation_TABS_AT_RIGHT = 3
};
bool Navigation_Orientation_IsValid(int value);
const Navigation_Orientation Navigation_Orientation_Orientation_MIN = Navigation_Orientation_TABS_AT_TOP;
const Navigation_Orientation Navigation_Orientation_Orientation_MAX = Navigation_Orientation_TABS_AT_RIGHT;
const int Navigation_Orientation_Orientation_ARRAYSIZE = Navigation_Orientation_Orientation_MAX + 1;

const ::google::protobuf::EnumDescriptor* Navigation_Orientation_descriptor();
inline const ::std::string& Navigation_Orientation_Name(Navigation_Orientation value) {
  return ::google::protobuf::internal::NameOfEnum(
    Navigation_Orientation_descriptor(), value);
}
inline bool Navigation_Orientation_Parse(
    const ::std::string& name, Navigation_Orientation* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Navigation_Orientation>(
    Navigation_Orientation_descriptor(), name, value);
}
// ===================================================================

class Navigation : public ::google::protobuf::Message {
 public:
  Navigation();
  virtual ~Navigation();
  
  Navigation(const Navigation& from);
  
  inline Navigation& operator=(const Navigation& from) {
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
  static const Navigation& default_instance();
  
  void Swap(Navigation* other);
  
  // implements Message ----------------------------------------------
  
  Navigation* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Navigation& from);
  void MergeFrom(const Navigation& from);
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
  
  typedef Navigation_Tab Tab;
  static const Tab FILE = Navigation_Tab_FILE;
  static const Tab CD = Navigation_Tab_CD;
  static const Tab URL = Navigation_Tab_URL;
  static inline bool Tab_IsValid(int value) {
    return Navigation_Tab_IsValid(value);
  }
  static const Tab Tab_MIN =
    Navigation_Tab_Tab_MIN;
  static const Tab Tab_MAX =
    Navigation_Tab_Tab_MAX;
  static const int Tab_ARRAYSIZE =
    Navigation_Tab_Tab_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Tab_descriptor() {
    return Navigation_Tab_descriptor();
  }
  static inline const ::std::string& Tab_Name(Tab value) {
    return Navigation_Tab_Name(value);
  }
  static inline bool Tab_Parse(const ::std::string& name,
      Tab* value) {
    return Navigation_Tab_Parse(name, value);
  }
  
  typedef Navigation_Orientation Orientation;
  static const Orientation TABS_AT_TOP = Navigation_Orientation_TABS_AT_TOP;
  static const Orientation TABS_AT_BOTTOM = Navigation_Orientation_TABS_AT_BOTTOM;
  static const Orientation TABS_AT_LEFT = Navigation_Orientation_TABS_AT_LEFT;
  static const Orientation TABS_AT_RIGHT = Navigation_Orientation_TABS_AT_RIGHT;
  static inline bool Orientation_IsValid(int value) {
    return Navigation_Orientation_IsValid(value);
  }
  static const Orientation Orientation_MIN =
    Navigation_Orientation_Orientation_MIN;
  static const Orientation Orientation_MAX =
    Navigation_Orientation_Orientation_MAX;
  static const int Orientation_ARRAYSIZE =
    Navigation_Orientation_Orientation_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Orientation_descriptor() {
    return Navigation_Orientation_descriptor();
  }
  static inline const ::std::string& Orientation_Name(Orientation value) {
    return Navigation_Orientation_Name(value);
  }
  static inline bool Orientation_Parse(const ::std::string& name,
      Orientation* value) {
    return Navigation_Orientation_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // optional .rec.widget.Widget widget = 1;
  inline bool has_widget() const;
  inline void clear_widget();
  static const int kWidgetFieldNumber = 1;
  inline const ::rec::widget::Widget& widget() const;
  inline ::rec::widget::Widget* mutable_widget();
  
  // optional .rec.util.file.VirtualFile file = 2;
  inline bool has_file() const;
  inline void clear_file();
  static const int kFileFieldNumber = 2;
  inline const ::rec::util::file::VirtualFile& file() const;
  inline ::rec::util::file::VirtualFile* mutable_file();
  
  // optional .rec.widget.pane.Navigation.Tab tab = 3;
  inline bool has_tab() const;
  inline void clear_tab();
  static const int kTabFieldNumber = 3;
  inline ::rec::widget::pane::Navigation_Tab tab() const;
  inline void set_tab(::rec::widget::pane::Navigation_Tab value);
  
  // optional .rec.widget.pane.Navigation.Orientation orientation = 4;
  inline bool has_orientation() const;
  inline void clear_orientation();
  static const int kOrientationFieldNumber = 4;
  inline ::rec::widget::pane::Navigation_Orientation orientation() const;
  inline void set_orientation(::rec::widget::pane::Navigation_Orientation value);
  
  // @@protoc_insertion_point(class_scope:rec.widget.pane.Navigation)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::rec::widget::Widget* widget_;
  ::rec::util::file::VirtualFile* file_;
  int tab_;
  int orientation_;
  friend void  protobuf_AddDesc_rec_2fwidget_2fPanes_2eproto();
  friend void protobuf_AssignDesc_rec_2fwidget_2fPanes_2eproto();
  friend void protobuf_ShutdownFile_rec_2fwidget_2fPanes_2eproto();
  
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
  static Navigation* default_instance_;
};
// -------------------------------------------------------------------

class Directory : public ::google::protobuf::Message {
 public:
  Directory();
  virtual ~Directory();
  
  Directory(const Directory& from);
  
  inline Directory& operator=(const Directory& from) {
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
  static const Directory& default_instance();
  
  void Swap(Directory* other);
  
  // implements Message ----------------------------------------------
  
  Directory* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Directory& from);
  void MergeFrom(const Directory& from);
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
  
  // optional .rec.widget.Widget widget = 1;
  inline bool has_widget() const;
  inline void clear_widget();
  static const int kWidgetFieldNumber = 1;
  inline const ::rec::widget::Widget& widget() const;
  inline ::rec::widget::Widget* mutable_widget();
  
  // optional .rec.util.file.VirtualFile file = 2;
  inline bool has_file() const;
  inline void clear_file();
  static const int kFileFieldNumber = 2;
  inline const ::rec::util::file::VirtualFile& file() const;
  inline ::rec::util::file::VirtualFile* mutable_file();
  
  // @@protoc_insertion_point(class_scope:rec.widget.pane.Directory)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::rec::widget::Widget* widget_;
  ::rec::util::file::VirtualFile* file_;
  friend void  protobuf_AddDesc_rec_2fwidget_2fPanes_2eproto();
  friend void protobuf_AssignDesc_rec_2fwidget_2fPanes_2eproto();
  friend void protobuf_ShutdownFile_rec_2fwidget_2fPanes_2eproto();
  
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
  static Directory* default_instance_;
};
// ===================================================================


// ===================================================================

// Navigation

// optional .rec.widget.Widget widget = 1;
inline bool Navigation::has_widget() const {
  return _has_bit(0);
}
inline void Navigation::clear_widget() {
  if (widget_ != NULL) widget_->::rec::widget::Widget::Clear();
  _clear_bit(0);
}
inline const ::rec::widget::Widget& Navigation::widget() const {
  return widget_ != NULL ? *widget_ : *default_instance_->widget_;
}
inline ::rec::widget::Widget* Navigation::mutable_widget() {
  _set_bit(0);
  if (widget_ == NULL) widget_ = new ::rec::widget::Widget;
  return widget_;
}

// optional .rec.util.file.VirtualFile file = 2;
inline bool Navigation::has_file() const {
  return _has_bit(1);
}
inline void Navigation::clear_file() {
  if (file_ != NULL) file_->::rec::util::file::VirtualFile::Clear();
  _clear_bit(1);
}
inline const ::rec::util::file::VirtualFile& Navigation::file() const {
  return file_ != NULL ? *file_ : *default_instance_->file_;
}
inline ::rec::util::file::VirtualFile* Navigation::mutable_file() {
  _set_bit(1);
  if (file_ == NULL) file_ = new ::rec::util::file::VirtualFile;
  return file_;
}

// optional .rec.widget.pane.Navigation.Tab tab = 3;
inline bool Navigation::has_tab() const {
  return _has_bit(2);
}
inline void Navigation::clear_tab() {
  tab_ = 1;
  _clear_bit(2);
}
inline ::rec::widget::pane::Navigation_Tab Navigation::tab() const {
  return static_cast< ::rec::widget::pane::Navigation_Tab >(tab_);
}
inline void Navigation::set_tab(::rec::widget::pane::Navigation_Tab value) {
  GOOGLE_DCHECK(::rec::widget::pane::Navigation_Tab_IsValid(value));
  _set_bit(2);
  tab_ = value;
}

// optional .rec.widget.pane.Navigation.Orientation orientation = 4;
inline bool Navigation::has_orientation() const {
  return _has_bit(3);
}
inline void Navigation::clear_orientation() {
  orientation_ = 0;
  _clear_bit(3);
}
inline ::rec::widget::pane::Navigation_Orientation Navigation::orientation() const {
  return static_cast< ::rec::widget::pane::Navigation_Orientation >(orientation_);
}
inline void Navigation::set_orientation(::rec::widget::pane::Navigation_Orientation value) {
  GOOGLE_DCHECK(::rec::widget::pane::Navigation_Orientation_IsValid(value));
  _set_bit(3);
  orientation_ = value;
}

// -------------------------------------------------------------------

// Directory

// optional .rec.widget.Widget widget = 1;
inline bool Directory::has_widget() const {
  return _has_bit(0);
}
inline void Directory::clear_widget() {
  if (widget_ != NULL) widget_->::rec::widget::Widget::Clear();
  _clear_bit(0);
}
inline const ::rec::widget::Widget& Directory::widget() const {
  return widget_ != NULL ? *widget_ : *default_instance_->widget_;
}
inline ::rec::widget::Widget* Directory::mutable_widget() {
  _set_bit(0);
  if (widget_ == NULL) widget_ = new ::rec::widget::Widget;
  return widget_;
}

// optional .rec.util.file.VirtualFile file = 2;
inline bool Directory::has_file() const {
  return _has_bit(1);
}
inline void Directory::clear_file() {
  if (file_ != NULL) file_->::rec::util::file::VirtualFile::Clear();
  _clear_bit(1);
}
inline const ::rec::util::file::VirtualFile& Directory::file() const {
  return file_ != NULL ? *file_ : *default_instance_->file_;
}
inline ::rec::util::file::VirtualFile* Directory::mutable_file() {
  _set_bit(1);
  if (file_ == NULL) file_ = new ::rec::util::file::VirtualFile;
  return file_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pane
}  // namespace widget
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::rec::widget::pane::Navigation_Tab>() {
  return ::rec::widget::pane::Navigation_Tab_descriptor();
}
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::rec::widget::pane::Navigation_Orientation>() {
  return ::rec::widget::pane::Navigation_Orientation_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2fwidget_2fPanes_2eproto__INCLUDED
