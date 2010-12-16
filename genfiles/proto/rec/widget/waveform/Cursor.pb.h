// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/widget/waveform/Cursor.proto

#ifndef PROTOBUF_rec_2fwidget_2fwaveform_2fCursor_2eproto__INCLUDED
#define PROTOBUF_rec_2fwidget_2fwaveform_2fCursor_2eproto__INCLUDED

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
#include "rec/gui/Geometry.pb.h"
// @@protoc_insertion_point(includes)

namespace rec {
namespace widget {
namespace waveform {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fwidget_2fwaveform_2fCursor_2eproto();
void protobuf_AssignDesc_rec_2fwidget_2fwaveform_2fCursor_2eproto();
void protobuf_ShutdownFile_rec_2fwidget_2fwaveform_2fCursor_2eproto();

class CursorProto;

enum CursorProto_Type {
  CursorProto_Type_NONE = 0,
  CursorProto_Type_PLAYBACK_POSITION = 1,
  CursorProto_Type_LOOP_START = 2,
  CursorProto_Type_LOOP_END = 3
};
bool CursorProto_Type_IsValid(int value);
const CursorProto_Type CursorProto_Type_Type_MIN = CursorProto_Type_NONE;
const CursorProto_Type CursorProto_Type_Type_MAX = CursorProto_Type_LOOP_END;
const int CursorProto_Type_Type_ARRAYSIZE = CursorProto_Type_Type_MAX + 1;

const ::google::protobuf::EnumDescriptor* CursorProto_Type_descriptor();
inline const ::std::string& CursorProto_Type_Name(CursorProto_Type value) {
  return ::google::protobuf::internal::NameOfEnum(
    CursorProto_Type_descriptor(), value);
}
inline bool CursorProto_Type_Parse(
    const ::std::string& name, CursorProto_Type* value) {
  return ::google::protobuf::internal::ParseNamedEnum<CursorProto_Type>(
    CursorProto_Type_descriptor(), name, value);
}
// ===================================================================

class CursorProto : public ::google::protobuf::Message {
 public:
  CursorProto();
  virtual ~CursorProto();
  
  CursorProto(const CursorProto& from);
  
  inline CursorProto& operator=(const CursorProto& from) {
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
  static const CursorProto& default_instance();
  
  void Swap(CursorProto* other);
  
  // implements Message ----------------------------------------------
  
  CursorProto* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CursorProto& from);
  void MergeFrom(const CursorProto& from);
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
  
  typedef CursorProto_Type Type;
  static const Type NONE = CursorProto_Type_NONE;
  static const Type PLAYBACK_POSITION = CursorProto_Type_PLAYBACK_POSITION;
  static const Type LOOP_START = CursorProto_Type_LOOP_START;
  static const Type LOOP_END = CursorProto_Type_LOOP_END;
  static inline bool Type_IsValid(int value) {
    return CursorProto_Type_IsValid(value);
  }
  static const Type Type_MIN =
    CursorProto_Type_Type_MIN;
  static const Type Type_MAX =
    CursorProto_Type_Type_MAX;
  static const int Type_ARRAYSIZE =
    CursorProto_Type_Type_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Type_descriptor() {
    return CursorProto_Type_descriptor();
  }
  static inline const ::std::string& Type_Name(Type value) {
    return CursorProto_Type_Name(value);
  }
  static inline bool Type_Parse(const ::std::string& name,
      Type* value) {
    return CursorProto_Type_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // optional .rec.widget.Widget widget = 1;
  inline bool has_widget() const;
  inline void clear_widget();
  static const int kWidgetFieldNumber = 1;
  inline const ::rec::widget::Widget& widget() const;
  inline ::rec::widget::Widget* mutable_widget();
  
  // optional uint32 width = 2 [default = 1];
  inline bool has_width() const;
  inline void clear_width();
  static const int kWidthFieldNumber = 2;
  inline ::google::protobuf::uint32 width() const;
  inline void set_width(::google::protobuf::uint32 value);
  
  // optional uint32 display_width = 3 [default = 3];
  inline bool has_display_width() const;
  inline void clear_display_width();
  static const int kDisplayWidthFieldNumber = 3;
  inline ::google::protobuf::uint32 display_width() const;
  inline void set_display_width(::google::protobuf::uint32 value);
  
  // optional .rec.widget.waveform.CursorProto.Type type = 4 [default = PLAYBACK_POSITION];
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 4;
  inline ::rec::widget::waveform::CursorProto_Type type() const;
  inline void set_type(::rec::widget::waveform::CursorProto_Type value);
  
  // optional .rec.gui.Line line = 5;
  inline bool has_line() const;
  inline void clear_line();
  static const int kLineFieldNumber = 5;
  inline const ::rec::gui::Line& line() const;
  inline ::rec::gui::Line* mutable_line();
  
  // @@protoc_insertion_point(class_scope:rec.widget.waveform.CursorProto)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::rec::widget::Widget* widget_;
  ::google::protobuf::uint32 width_;
  ::google::protobuf::uint32 display_width_;
  int type_;
  ::rec::gui::Line* line_;
  friend void  protobuf_AddDesc_rec_2fwidget_2fwaveform_2fCursor_2eproto();
  friend void protobuf_AssignDesc_rec_2fwidget_2fwaveform_2fCursor_2eproto();
  friend void protobuf_ShutdownFile_rec_2fwidget_2fwaveform_2fCursor_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];
  
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
  static CursorProto* default_instance_;
};
// ===================================================================


// ===================================================================

// CursorProto

// optional .rec.widget.Widget widget = 1;
inline bool CursorProto::has_widget() const {
  return _has_bit(0);
}
inline void CursorProto::clear_widget() {
  if (widget_ != NULL) widget_->::rec::widget::Widget::Clear();
  _clear_bit(0);
}
inline const ::rec::widget::Widget& CursorProto::widget() const {
  return widget_ != NULL ? *widget_ : *default_instance_->widget_;
}
inline ::rec::widget::Widget* CursorProto::mutable_widget() {
  _set_bit(0);
  if (widget_ == NULL) widget_ = new ::rec::widget::Widget;
  return widget_;
}

// optional uint32 width = 2 [default = 1];
inline bool CursorProto::has_width() const {
  return _has_bit(1);
}
inline void CursorProto::clear_width() {
  width_ = 1u;
  _clear_bit(1);
}
inline ::google::protobuf::uint32 CursorProto::width() const {
  return width_;
}
inline void CursorProto::set_width(::google::protobuf::uint32 value) {
  _set_bit(1);
  width_ = value;
}

// optional uint32 display_width = 3 [default = 3];
inline bool CursorProto::has_display_width() const {
  return _has_bit(2);
}
inline void CursorProto::clear_display_width() {
  display_width_ = 3u;
  _clear_bit(2);
}
inline ::google::protobuf::uint32 CursorProto::display_width() const {
  return display_width_;
}
inline void CursorProto::set_display_width(::google::protobuf::uint32 value) {
  _set_bit(2);
  display_width_ = value;
}

// optional .rec.widget.waveform.CursorProto.Type type = 4 [default = PLAYBACK_POSITION];
inline bool CursorProto::has_type() const {
  return _has_bit(3);
}
inline void CursorProto::clear_type() {
  type_ = 1;
  _clear_bit(3);
}
inline ::rec::widget::waveform::CursorProto_Type CursorProto::type() const {
  return static_cast< ::rec::widget::waveform::CursorProto_Type >(type_);
}
inline void CursorProto::set_type(::rec::widget::waveform::CursorProto_Type value) {
  GOOGLE_DCHECK(::rec::widget::waveform::CursorProto_Type_IsValid(value));
  _set_bit(3);
  type_ = value;
}

// optional .rec.gui.Line line = 5;
inline bool CursorProto::has_line() const {
  return _has_bit(4);
}
inline void CursorProto::clear_line() {
  if (line_ != NULL) line_->::rec::gui::Line::Clear();
  _clear_bit(4);
}
inline const ::rec::gui::Line& CursorProto::line() const {
  return line_ != NULL ? *line_ : *default_instance_->line_;
}
inline ::rec::gui::Line* CursorProto::mutable_line() {
  _set_bit(4);
  if (line_ == NULL) line_ = new ::rec::gui::Line;
  return line_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::rec::widget::waveform::CursorProto_Type>() {
  return ::rec::widget::waveform::CursorProto_Type_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2fwidget_2fwaveform_2fCursor_2eproto__INCLUDED
