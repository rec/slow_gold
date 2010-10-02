// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/gui/Component.proto

#ifndef PROTOBUF_rec_2fgui_2fComponent_2eproto__INCLUDED
#define PROTOBUF_rec_2fgui_2fComponent_2eproto__INCLUDED

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
#include "rec/gui/Color.pb.h"
#include "rec/gui/Font.pb.h"
#include "rec/gui/Geometry.pb.h"
// @@protoc_insertion_point(includes)

namespace rec {
namespace gui {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fgui_2fComponent_2eproto();
void protobuf_AssignDesc_rec_2fgui_2fComponent_2eproto();
void protobuf_ShutdownFile_rec_2fgui_2fComponent_2eproto();

class ComponentDesc;

// ===================================================================

class ComponentDesc : public ::google::protobuf::Message {
 public:
  ComponentDesc();
  virtual ~ComponentDesc();
  
  ComponentDesc(const ComponentDesc& from);
  
  inline ComponentDesc& operator=(const ComponentDesc& from) {
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
  static const ComponentDesc& default_instance();
  
  void Swap(ComponentDesc* other);
  
  // implements Message ----------------------------------------------
  
  ComponentDesc* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ComponentDesc& from);
  void MergeFrom(const ComponentDesc& from);
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
  
  // optional .rec.gui.color.Colors colors = 1;
  inline bool has_colors() const;
  inline void clear_colors();
  static const int kColorsFieldNumber = 1;
  inline const ::rec::gui::color::Colors& colors() const;
  inline ::rec::gui::color::Colors* mutable_colors();
  
  // optional .rec.gui.FontDesc font = 2;
  inline bool has_font() const;
  inline void clear_font();
  static const int kFontFieldNumber = 2;
  inline const ::rec::gui::FontDesc& font() const;
  inline ::rec::gui::FontDesc* mutable_font();
  
  // optional uint32 margin = 3 [default = 2];
  inline bool has_margin() const;
  inline void clear_margin();
  static const int kMarginFieldNumber = 3;
  inline ::google::protobuf::uint32 margin() const;
  inline void set_margin(::google::protobuf::uint32 value);
  
  // optional bool transparent = 4;
  inline bool has_transparent() const;
  inline void clear_transparent();
  static const int kTransparentFieldNumber = 4;
  inline bool transparent() const;
  inline void set_transparent(bool value);
  
  // @@protoc_insertion_point(class_scope:rec.gui.ComponentDesc)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::rec::gui::color::Colors* colors_;
  ::rec::gui::FontDesc* font_;
  ::google::protobuf::uint32 margin_;
  bool transparent_;
  friend void  protobuf_AddDesc_rec_2fgui_2fComponent_2eproto();
  friend void protobuf_AssignDesc_rec_2fgui_2fComponent_2eproto();
  friend void protobuf_ShutdownFile_rec_2fgui_2fComponent_2eproto();
  
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
  static ComponentDesc* default_instance_;
};
// ===================================================================


// ===================================================================

// ComponentDesc

// optional .rec.gui.color.Colors colors = 1;
inline bool ComponentDesc::has_colors() const {
  return _has_bit(0);
}
inline void ComponentDesc::clear_colors() {
  if (colors_ != NULL) colors_->::rec::gui::color::Colors::Clear();
  _clear_bit(0);
}
inline const ::rec::gui::color::Colors& ComponentDesc::colors() const {
  return colors_ != NULL ? *colors_ : *default_instance_->colors_;
}
inline ::rec::gui::color::Colors* ComponentDesc::mutable_colors() {
  _set_bit(0);
  if (colors_ == NULL) colors_ = new ::rec::gui::color::Colors;
  return colors_;
}

// optional .rec.gui.FontDesc font = 2;
inline bool ComponentDesc::has_font() const {
  return _has_bit(1);
}
inline void ComponentDesc::clear_font() {
  if (font_ != NULL) font_->::rec::gui::FontDesc::Clear();
  _clear_bit(1);
}
inline const ::rec::gui::FontDesc& ComponentDesc::font() const {
  return font_ != NULL ? *font_ : *default_instance_->font_;
}
inline ::rec::gui::FontDesc* ComponentDesc::mutable_font() {
  _set_bit(1);
  if (font_ == NULL) font_ = new ::rec::gui::FontDesc;
  return font_;
}

// optional uint32 margin = 3 [default = 2];
inline bool ComponentDesc::has_margin() const {
  return _has_bit(2);
}
inline void ComponentDesc::clear_margin() {
  margin_ = 2u;
  _clear_bit(2);
}
inline ::google::protobuf::uint32 ComponentDesc::margin() const {
  return margin_;
}
inline void ComponentDesc::set_margin(::google::protobuf::uint32 value) {
  _set_bit(2);
  margin_ = value;
}

// optional bool transparent = 4;
inline bool ComponentDesc::has_transparent() const {
  return _has_bit(3);
}
inline void ComponentDesc::clear_transparent() {
  transparent_ = false;
  _clear_bit(3);
}
inline bool ComponentDesc::transparent() const {
  return transparent_;
}
inline void ComponentDesc::set_transparent(bool value) {
  _set_bit(3);
  transparent_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace gui
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2fgui_2fComponent_2eproto__INCLUDED
