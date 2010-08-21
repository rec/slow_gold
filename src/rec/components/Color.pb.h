// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/components/Color.proto

#ifndef PROTOBUF_rec_2fcomponents_2fColor_2eproto__INCLUDED
#define PROTOBUF_rec_2fcomponents_2fColor_2eproto__INCLUDED

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
// @@protoc_insertion_point(includes)

namespace rec {
namespace gui {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fcomponents_2fColor_2eproto();
void protobuf_AssignDesc_rec_2fcomponents_2fColor_2eproto();
void protobuf_ShutdownFile_rec_2fcomponents_2fColor_2eproto();

class Color;

// ===================================================================

class Color : public ::google::protobuf::Message {
 public:
  Color();
  virtual ~Color();
  
  Color(const Color& from);
  
  inline Color& operator=(const Color& from) {
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
  static const Color& default_instance();
  
  void Swap(Color* other);
  
  // implements Message ----------------------------------------------
  
  Color* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Color& from);
  void MergeFrom(const Color& from);
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
  
  // optional uint32 rgb = 1 [default = 0];
  inline bool has_rgb() const;
  inline void clear_rgb();
  static const int kRgbFieldNumber = 1;
  inline ::google::protobuf::uint32 rgb() const;
  inline void set_rgb(::google::protobuf::uint32 value);
  
  // optional uint32 alpha = 2 [default = 255];
  inline bool has_alpha() const;
  inline void clear_alpha();
  static const int kAlphaFieldNumber = 2;
  inline ::google::protobuf::uint32 alpha() const;
  inline void set_alpha(::google::protobuf::uint32 value);
  
  // optional uint32 red = 3 [default = 0];
  inline bool has_red() const;
  inline void clear_red();
  static const int kRedFieldNumber = 3;
  inline ::google::protobuf::uint32 red() const;
  inline void set_red(::google::protobuf::uint32 value);
  
  // optional uint32 green = 4 [default = 0];
  inline bool has_green() const;
  inline void clear_green();
  static const int kGreenFieldNumber = 4;
  inline ::google::protobuf::uint32 green() const;
  inline void set_green(::google::protobuf::uint32 value);
  
  // optional uint32 blue = 5 [default = 0];
  inline bool has_blue() const;
  inline void clear_blue();
  static const int kBlueFieldNumber = 5;
  inline ::google::protobuf::uint32 blue() const;
  inline void set_blue(::google::protobuf::uint32 value);
  
  // optional uint32 argb = 6 [default = 4278190080];
  inline bool has_argb() const;
  inline void clear_argb();
  static const int kArgbFieldNumber = 6;
  inline ::google::protobuf::uint32 argb() const;
  inline void set_argb(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:rec.gui.Color)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::google::protobuf::uint32 rgb_;
  ::google::protobuf::uint32 alpha_;
  ::google::protobuf::uint32 red_;
  ::google::protobuf::uint32 green_;
  ::google::protobuf::uint32 blue_;
  ::google::protobuf::uint32 argb_;
  friend void  protobuf_AddDesc_rec_2fcomponents_2fColor_2eproto();
  friend void protobuf_AssignDesc_rec_2fcomponents_2fColor_2eproto();
  friend void protobuf_ShutdownFile_rec_2fcomponents_2fColor_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(6 + 31) / 32];
  
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
  static Color* default_instance_;
};
// ===================================================================


// ===================================================================

// Color

// optional uint32 rgb = 1 [default = 0];
inline bool Color::has_rgb() const {
  return _has_bit(0);
}
inline void Color::clear_rgb() {
  rgb_ = 0u;
  _clear_bit(0);
}
inline ::google::protobuf::uint32 Color::rgb() const {
  return rgb_;
}
inline void Color::set_rgb(::google::protobuf::uint32 value) {
  _set_bit(0);
  rgb_ = value;
}

// optional uint32 alpha = 2 [default = 255];
inline bool Color::has_alpha() const {
  return _has_bit(1);
}
inline void Color::clear_alpha() {
  alpha_ = 255u;
  _clear_bit(1);
}
inline ::google::protobuf::uint32 Color::alpha() const {
  return alpha_;
}
inline void Color::set_alpha(::google::protobuf::uint32 value) {
  _set_bit(1);
  alpha_ = value;
}

// optional uint32 red = 3 [default = 0];
inline bool Color::has_red() const {
  return _has_bit(2);
}
inline void Color::clear_red() {
  red_ = 0u;
  _clear_bit(2);
}
inline ::google::protobuf::uint32 Color::red() const {
  return red_;
}
inline void Color::set_red(::google::protobuf::uint32 value) {
  _set_bit(2);
  red_ = value;
}

// optional uint32 green = 4 [default = 0];
inline bool Color::has_green() const {
  return _has_bit(3);
}
inline void Color::clear_green() {
  green_ = 0u;
  _clear_bit(3);
}
inline ::google::protobuf::uint32 Color::green() const {
  return green_;
}
inline void Color::set_green(::google::protobuf::uint32 value) {
  _set_bit(3);
  green_ = value;
}

// optional uint32 blue = 5 [default = 0];
inline bool Color::has_blue() const {
  return _has_bit(4);
}
inline void Color::clear_blue() {
  blue_ = 0u;
  _clear_bit(4);
}
inline ::google::protobuf::uint32 Color::blue() const {
  return blue_;
}
inline void Color::set_blue(::google::protobuf::uint32 value) {
  _set_bit(4);
  blue_ = value;
}

// optional uint32 argb = 6 [default = 4278190080];
inline bool Color::has_argb() const {
  return _has_bit(5);
}
inline void Color::clear_argb() {
  argb_ = 4278190080u;
  _clear_bit(5);
}
inline ::google::protobuf::uint32 Color::argb() const {
  return argb_;
}
inline void Color::set_argb(::google::protobuf::uint32 value) {
  _set_bit(5);
  argb_ = value;
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

#endif  // PROTOBUF_rec_2fcomponents_2fColor_2eproto__INCLUDED
