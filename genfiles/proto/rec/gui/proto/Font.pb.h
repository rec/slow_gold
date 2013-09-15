// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/gui/proto/Font.proto

#ifndef PROTOBUF_rec_2fgui_2fproto_2fFont_2eproto__INCLUDED
#define PROTOBUF_rec_2fgui_2fproto_2fFont_2eproto__INCLUDED

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
namespace gui {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fgui_2fproto_2fFont_2eproto();
void protobuf_AssignDesc_rec_2fgui_2fproto_2fFont_2eproto();
void protobuf_ShutdownFile_rec_2fgui_2fproto_2fFont_2eproto();

class FontProto;

// ===================================================================

class FontProto : public ::google::protobuf::Message {
 public:
  FontProto();
  virtual ~FontProto();

  FontProto(const FontProto& from);

  inline FontProto& operator=(const FontProto& from) {
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
  static const FontProto& default_instance();

  void Swap(FontProto* other);

  // implements Message ----------------------------------------------

  FontProto* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const FontProto& from);
  void MergeFrom(const FontProto& from);
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

  // optional float height = 1;
  inline bool has_height() const;
  inline void clear_height();
  static const int kHeightFieldNumber = 1;
  inline float height() const;
  inline void set_height(float value);

  // optional float height_delta = 2;
  inline bool has_height_delta() const;
  inline void clear_height_delta();
  static const int kHeightDeltaFieldNumber = 2;
  inline float height_delta() const;
  inline void set_height_delta(float value);

  // optional string typeface_name = 3;
  inline bool has_typeface_name() const;
  inline void clear_typeface_name();
  static const int kTypefaceNameFieldNumber = 3;
  inline const ::std::string& typeface_name() const;
  inline void set_typeface_name(const ::std::string& value);
  inline void set_typeface_name(const char* value);
  inline void set_typeface_name(const char* value, size_t size);
  inline ::std::string* mutable_typeface_name();
  inline ::std::string* release_typeface_name();
  inline void set_allocated_typeface_name(::std::string* typeface_name);

  // optional string typeface_style = 4;
  inline bool has_typeface_style() const;
  inline void clear_typeface_style();
  static const int kTypefaceStyleFieldNumber = 4;
  inline const ::std::string& typeface_style() const;
  inline void set_typeface_style(const ::std::string& value);
  inline void set_typeface_style(const char* value);
  inline void set_typeface_style(const char* value, size_t size);
  inline ::std::string* mutable_typeface_style();
  inline ::std::string* release_typeface_style();
  inline void set_allocated_typeface_style(::std::string* typeface_style);

  // optional bool is_bold = 5;
  inline bool has_is_bold() const;
  inline void clear_is_bold();
  static const int kIsBoldFieldNumber = 5;
  inline bool is_bold() const;
  inline void set_is_bold(bool value);

  // optional bool is_italic = 6;
  inline bool has_is_italic() const;
  inline void clear_is_italic();
  static const int kIsItalicFieldNumber = 6;
  inline bool is_italic() const;
  inline void set_is_italic(bool value);

  // optional bool is_underlined = 7;
  inline bool has_is_underlined() const;
  inline void clear_is_underlined();
  static const int kIsUnderlinedFieldNumber = 7;
  inline bool is_underlined() const;
  inline void set_is_underlined(bool value);

  // @@protoc_insertion_point(class_scope:rec.gui.FontProto)
 private:
  inline void set_has_height();
  inline void clear_has_height();
  inline void set_has_height_delta();
  inline void clear_has_height_delta();
  inline void set_has_typeface_name();
  inline void clear_has_typeface_name();
  inline void set_has_typeface_style();
  inline void clear_has_typeface_style();
  inline void set_has_is_bold();
  inline void clear_has_is_bold();
  inline void set_has_is_italic();
  inline void clear_has_is_italic();
  inline void set_has_is_underlined();
  inline void clear_has_is_underlined();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  float height_;
  float height_delta_;
  ::std::string* typeface_name_;
  ::std::string* typeface_style_;
  bool is_bold_;
  bool is_italic_;
  bool is_underlined_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(7 + 31) / 32];

  friend void  protobuf_AddDesc_rec_2fgui_2fproto_2fFont_2eproto();
  friend void protobuf_AssignDesc_rec_2fgui_2fproto_2fFont_2eproto();
  friend void protobuf_ShutdownFile_rec_2fgui_2fproto_2fFont_2eproto();

  void InitAsDefaultInstance();
  static FontProto* default_instance_;
};
// ===================================================================


// ===================================================================

// FontProto

// optional float height = 1;
inline bool FontProto::has_height() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void FontProto::set_has_height() {
  _has_bits_[0] |= 0x00000001u;
}
inline void FontProto::clear_has_height() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void FontProto::clear_height() {
  height_ = 0;
  clear_has_height();
}
inline float FontProto::height() const {
  return height_;
}
inline void FontProto::set_height(float value) {
  set_has_height();
  height_ = value;
}

// optional float height_delta = 2;
inline bool FontProto::has_height_delta() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void FontProto::set_has_height_delta() {
  _has_bits_[0] |= 0x00000002u;
}
inline void FontProto::clear_has_height_delta() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void FontProto::clear_height_delta() {
  height_delta_ = 0;
  clear_has_height_delta();
}
inline float FontProto::height_delta() const {
  return height_delta_;
}
inline void FontProto::set_height_delta(float value) {
  set_has_height_delta();
  height_delta_ = value;
}

// optional string typeface_name = 3;
inline bool FontProto::has_typeface_name() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void FontProto::set_has_typeface_name() {
  _has_bits_[0] |= 0x00000004u;
}
inline void FontProto::clear_has_typeface_name() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void FontProto::clear_typeface_name() {
  if (typeface_name_ != &::google::protobuf::internal::kEmptyString) {
    typeface_name_->clear();
  }
  clear_has_typeface_name();
}
inline const ::std::string& FontProto::typeface_name() const {
  return *typeface_name_;
}
inline void FontProto::set_typeface_name(const ::std::string& value) {
  set_has_typeface_name();
  if (typeface_name_ == &::google::protobuf::internal::kEmptyString) {
    typeface_name_ = new ::std::string;
  }
  typeface_name_->assign(value);
}
inline void FontProto::set_typeface_name(const char* value) {
  set_has_typeface_name();
  if (typeface_name_ == &::google::protobuf::internal::kEmptyString) {
    typeface_name_ = new ::std::string;
  }
  typeface_name_->assign(value);
}
inline void FontProto::set_typeface_name(const char* value, size_t size) {
  set_has_typeface_name();
  if (typeface_name_ == &::google::protobuf::internal::kEmptyString) {
    typeface_name_ = new ::std::string;
  }
  typeface_name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* FontProto::mutable_typeface_name() {
  set_has_typeface_name();
  if (typeface_name_ == &::google::protobuf::internal::kEmptyString) {
    typeface_name_ = new ::std::string;
  }
  return typeface_name_;
}
inline ::std::string* FontProto::release_typeface_name() {
  clear_has_typeface_name();
  if (typeface_name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = typeface_name_;
    typeface_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void FontProto::set_allocated_typeface_name(::std::string* typeface_name) {
  if (typeface_name_ != &::google::protobuf::internal::kEmptyString) {
    delete typeface_name_;
  }
  if (typeface_name) {
    set_has_typeface_name();
    typeface_name_ = typeface_name;
  } else {
    clear_has_typeface_name();
    typeface_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional string typeface_style = 4;
inline bool FontProto::has_typeface_style() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void FontProto::set_has_typeface_style() {
  _has_bits_[0] |= 0x00000008u;
}
inline void FontProto::clear_has_typeface_style() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void FontProto::clear_typeface_style() {
  if (typeface_style_ != &::google::protobuf::internal::kEmptyString) {
    typeface_style_->clear();
  }
  clear_has_typeface_style();
}
inline const ::std::string& FontProto::typeface_style() const {
  return *typeface_style_;
}
inline void FontProto::set_typeface_style(const ::std::string& value) {
  set_has_typeface_style();
  if (typeface_style_ == &::google::protobuf::internal::kEmptyString) {
    typeface_style_ = new ::std::string;
  }
  typeface_style_->assign(value);
}
inline void FontProto::set_typeface_style(const char* value) {
  set_has_typeface_style();
  if (typeface_style_ == &::google::protobuf::internal::kEmptyString) {
    typeface_style_ = new ::std::string;
  }
  typeface_style_->assign(value);
}
inline void FontProto::set_typeface_style(const char* value, size_t size) {
  set_has_typeface_style();
  if (typeface_style_ == &::google::protobuf::internal::kEmptyString) {
    typeface_style_ = new ::std::string;
  }
  typeface_style_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* FontProto::mutable_typeface_style() {
  set_has_typeface_style();
  if (typeface_style_ == &::google::protobuf::internal::kEmptyString) {
    typeface_style_ = new ::std::string;
  }
  return typeface_style_;
}
inline ::std::string* FontProto::release_typeface_style() {
  clear_has_typeface_style();
  if (typeface_style_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = typeface_style_;
    typeface_style_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void FontProto::set_allocated_typeface_style(::std::string* typeface_style) {
  if (typeface_style_ != &::google::protobuf::internal::kEmptyString) {
    delete typeface_style_;
  }
  if (typeface_style) {
    set_has_typeface_style();
    typeface_style_ = typeface_style;
  } else {
    clear_has_typeface_style();
    typeface_style_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional bool is_bold = 5;
inline bool FontProto::has_is_bold() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void FontProto::set_has_is_bold() {
  _has_bits_[0] |= 0x00000010u;
}
inline void FontProto::clear_has_is_bold() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void FontProto::clear_is_bold() {
  is_bold_ = false;
  clear_has_is_bold();
}
inline bool FontProto::is_bold() const {
  return is_bold_;
}
inline void FontProto::set_is_bold(bool value) {
  set_has_is_bold();
  is_bold_ = value;
}

// optional bool is_italic = 6;
inline bool FontProto::has_is_italic() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void FontProto::set_has_is_italic() {
  _has_bits_[0] |= 0x00000020u;
}
inline void FontProto::clear_has_is_italic() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void FontProto::clear_is_italic() {
  is_italic_ = false;
  clear_has_is_italic();
}
inline bool FontProto::is_italic() const {
  return is_italic_;
}
inline void FontProto::set_is_italic(bool value) {
  set_has_is_italic();
  is_italic_ = value;
}

// optional bool is_underlined = 7;
inline bool FontProto::has_is_underlined() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void FontProto::set_has_is_underlined() {
  _has_bits_[0] |= 0x00000040u;
}
inline void FontProto::clear_has_is_underlined() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void FontProto::clear_is_underlined() {
  is_underlined_ = false;
  clear_has_is_underlined();
}
inline bool FontProto::is_underlined() const {
  return is_underlined_;
}
inline void FontProto::set_is_underlined(bool value) {
  set_has_is_underlined();
  is_underlined_ = value;
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

#endif  // PROTOBUF_rec_2fgui_2fproto_2fFont_2eproto__INCLUDED
