// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/gui/Time.proto

#ifndef PROTOBUF_rec_2fgui_2fTime_2eproto__INCLUDED
#define PROTOBUF_rec_2fgui_2fTime_2eproto__INCLUDED

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
#include "rec/gui/Font.pb.h"
#include "rec/gui/Color.pb.h"
// @@protoc_insertion_point(includes)

namespace rec {
namespace gui {
namespace time {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fgui_2fTime_2eproto();
void protobuf_AssignDesc_rec_2fgui_2fTime_2eproto();
void protobuf_ShutdownFile_rec_2fgui_2fTime_2eproto();

class Text;
class Text_Separator;
class Text_Fields;
class Bar;
class Dial;
class Time;

enum Dial_Direction {
  Dial_Direction_CLOCKWISE = 1,
  Dial_Direction_COUNTER_CLOCKWISE = 2
};
bool Dial_Direction_IsValid(int value);
const Dial_Direction Dial_Direction_Direction_MIN = Dial_Direction_CLOCKWISE;
const Dial_Direction Dial_Direction_Direction_MAX = Dial_Direction_COUNTER_CLOCKWISE;
const int Dial_Direction_Direction_ARRAYSIZE = Dial_Direction_Direction_MAX + 1;

const ::google::protobuf::EnumDescriptor* Dial_Direction_descriptor();
inline const ::std::string& Dial_Direction_Name(Dial_Direction value) {
  return ::google::protobuf::internal::NameOfEnum(
    Dial_Direction_descriptor(), value);
}
inline bool Dial_Direction_Parse(
    const ::std::string& name, Dial_Direction* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Dial_Direction>(
    Dial_Direction_descriptor(), name, value);
}
// ===================================================================

class Text_Separator : public ::google::protobuf::Message {
 public:
  Text_Separator();
  virtual ~Text_Separator();
  
  Text_Separator(const Text_Separator& from);
  
  inline Text_Separator& operator=(const Text_Separator& from) {
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
  static const Text_Separator& default_instance();
  
  void Swap(Text_Separator* other);
  
  // implements Message ----------------------------------------------
  
  Text_Separator* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Text_Separator& from);
  void MergeFrom(const Text_Separator& from);
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
  
  // optional string separator = 1;
  inline bool has_separator() const;
  inline void clear_separator();
  static const int kSeparatorFieldNumber = 1;
  inline const ::std::string& separator() const;
  inline void set_separator(const ::std::string& value);
  inline void set_separator(const char* value);
  inline void set_separator(const char* value, size_t size);
  inline ::std::string* mutable_separator();
  
  // optional uint32 width = 2;
  inline bool has_width() const;
  inline void clear_width();
  static const int kWidthFieldNumber = 2;
  inline ::google::protobuf::uint32 width() const;
  inline void set_width(::google::protobuf::uint32 value);
  
  // optional bool flash = 3 [default = true];
  inline bool has_flash() const;
  inline void clear_flash();
  static const int kFlashFieldNumber = 3;
  inline bool flash() const;
  inline void set_flash(bool value);
  
  // @@protoc_insertion_point(class_scope:rec.gui.time.Text.Separator)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::std::string* separator_;
  static const ::std::string _default_separator_;
  ::google::protobuf::uint32 width_;
  bool flash_;
  friend void  protobuf_AddDesc_rec_2fgui_2fTime_2eproto();
  friend void protobuf_AssignDesc_rec_2fgui_2fTime_2eproto();
  friend void protobuf_ShutdownFile_rec_2fgui_2fTime_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
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
  static Text_Separator* default_instance_;
};
// -------------------------------------------------------------------

class Text_Fields : public ::google::protobuf::Message {
 public:
  Text_Fields();
  virtual ~Text_Fields();
  
  Text_Fields(const Text_Fields& from);
  
  inline Text_Fields& operator=(const Text_Fields& from) {
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
  static const Text_Fields& default_instance();
  
  void Swap(Text_Fields* other);
  
  // implements Message ----------------------------------------------
  
  Text_Fields* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Text_Fields& from);
  void MergeFrom(const Text_Fields& from);
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
  
  // optional bool hours = 1 [default = false];
  inline bool has_hours() const;
  inline void clear_hours();
  static const int kHoursFieldNumber = 1;
  inline bool hours() const;
  inline void set_hours(bool value);
  
  // optional bool minutes = 2 [default = true];
  inline bool has_minutes() const;
  inline void clear_minutes();
  static const int kMinutesFieldNumber = 2;
  inline bool minutes() const;
  inline void set_minutes(bool value);
  
  // optional bool seconds = 3 [default = true];
  inline bool has_seconds() const;
  inline void clear_seconds();
  static const int kSecondsFieldNumber = 3;
  inline bool seconds() const;
  inline void set_seconds(bool value);
  
  // optional bool milliseconds = 4 [default = true];
  inline bool has_milliseconds() const;
  inline void clear_milliseconds();
  static const int kMillisecondsFieldNumber = 4;
  inline bool milliseconds() const;
  inline void set_milliseconds(bool value);
  
  // optional bool frames = 5 [default = false];
  inline bool has_frames() const;
  inline void clear_frames();
  static const int kFramesFieldNumber = 5;
  inline bool frames() const;
  inline void set_frames(bool value);
  
  // @@protoc_insertion_point(class_scope:rec.gui.time.Text.Fields)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  bool hours_;
  bool minutes_;
  bool seconds_;
  bool milliseconds_;
  bool frames_;
  friend void  protobuf_AddDesc_rec_2fgui_2fTime_2eproto();
  friend void protobuf_AssignDesc_rec_2fgui_2fTime_2eproto();
  friend void protobuf_ShutdownFile_rec_2fgui_2fTime_2eproto();
  
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
  static Text_Fields* default_instance_;
};
// -------------------------------------------------------------------

class Text : public ::google::protobuf::Message {
 public:
  Text();
  virtual ~Text();
  
  Text(const Text& from);
  
  inline Text& operator=(const Text& from) {
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
  static const Text& default_instance();
  
  void Swap(Text* other);
  
  // implements Message ----------------------------------------------
  
  Text* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Text& from);
  void MergeFrom(const Text& from);
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
  
  typedef Text_Separator Separator;
  typedef Text_Fields Fields;
  
  // accessors -------------------------------------------------------
  
  // optional string name = 5;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 5;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  
  // optional .rec.gui.FontDesc font = 1;
  inline bool has_font() const;
  inline void clear_font();
  static const int kFontFieldNumber = 1;
  inline const ::rec::gui::FontDesc& font() const;
  inline ::rec::gui::FontDesc* mutable_font();
  
  // optional .rec.gui.time.Text.Separator separator = 2;
  inline bool has_separator() const;
  inline void clear_separator();
  static const int kSeparatorFieldNumber = 2;
  inline const ::rec::gui::time::Text_Separator& separator() const;
  inline ::rec::gui::time::Text_Separator* mutable_separator();
  
  // optional .rec.gui.time.Text.Fields fields = 3;
  inline bool has_fields() const;
  inline void clear_fields();
  static const int kFieldsFieldNumber = 3;
  inline const ::rec::gui::time::Text_Fields& fields() const;
  inline ::rec::gui::time::Text_Fields* mutable_fields();
  
  // optional uint32 margin = 4 [default = 2];
  inline bool has_margin() const;
  inline void clear_margin();
  static const int kMarginFieldNumber = 4;
  inline ::google::protobuf::uint32 margin() const;
  inline void set_margin(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:rec.gui.time.Text)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::std::string* name_;
  static const ::std::string _default_name_;
  ::rec::gui::FontDesc* font_;
  ::rec::gui::time::Text_Separator* separator_;
  ::rec::gui::time::Text_Fields* fields_;
  ::google::protobuf::uint32 margin_;
  friend void  protobuf_AddDesc_rec_2fgui_2fTime_2eproto();
  friend void protobuf_AssignDesc_rec_2fgui_2fTime_2eproto();
  friend void protobuf_ShutdownFile_rec_2fgui_2fTime_2eproto();
  
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
  static Text* default_instance_;
};
// -------------------------------------------------------------------

class Bar : public ::google::protobuf::Message {
 public:
  Bar();
  virtual ~Bar();
  
  Bar(const Bar& from);
  
  inline Bar& operator=(const Bar& from) {
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
  static const Bar& default_instance();
  
  void Swap(Bar* other);
  
  // implements Message ----------------------------------------------
  
  Bar* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Bar& from);
  void MergeFrom(const Bar& from);
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
  
  // @@protoc_insertion_point(class_scope:rec.gui.time.Bar)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  friend void  protobuf_AddDesc_rec_2fgui_2fTime_2eproto();
  friend void protobuf_AssignDesc_rec_2fgui_2fTime_2eproto();
  friend void protobuf_ShutdownFile_rec_2fgui_2fTime_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[1];
  
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
  static Bar* default_instance_;
};
// -------------------------------------------------------------------

class Dial : public ::google::protobuf::Message {
 public:
  Dial();
  virtual ~Dial();
  
  Dial(const Dial& from);
  
  inline Dial& operator=(const Dial& from) {
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
  static const Dial& default_instance();
  
  void Swap(Dial* other);
  
  // implements Message ----------------------------------------------
  
  Dial* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Dial& from);
  void MergeFrom(const Dial& from);
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
  
  typedef Dial_Direction Direction;
  static const Direction CLOCKWISE = Dial_Direction_CLOCKWISE;
  static const Direction COUNTER_CLOCKWISE = Dial_Direction_COUNTER_CLOCKWISE;
  static inline bool Direction_IsValid(int value) {
    return Dial_Direction_IsValid(value);
  }
  static const Direction Direction_MIN =
    Dial_Direction_Direction_MIN;
  static const Direction Direction_MAX =
    Dial_Direction_Direction_MAX;
  static const int Direction_ARRAYSIZE =
    Dial_Direction_Direction_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Direction_descriptor() {
    return Dial_Direction_descriptor();
  }
  static inline const ::std::string& Direction_Name(Direction value) {
    return Dial_Direction_Name(value);
  }
  static inline bool Direction_Parse(const ::std::string& name,
      Direction* value) {
    return Dial_Direction_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // optional string name = 1;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 1;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  
  // optional uint32 outline = 2;
  inline bool has_outline() const;
  inline void clear_outline();
  static const int kOutlineFieldNumber = 2;
  inline ::google::protobuf::uint32 outline() const;
  inline void set_outline(::google::protobuf::uint32 value);
  
  // optional .rec.gui.time.Dial.Direction direction = 3 [default = CLOCKWISE];
  inline bool has_direction() const;
  inline void clear_direction();
  static const int kDirectionFieldNumber = 3;
  inline ::rec::gui::time::Dial_Direction direction() const;
  inline void set_direction(::rec::gui::time::Dial_Direction value);
  
  // optional bool display_lap_count = 4;
  inline bool has_display_lap_count() const;
  inline void clear_display_lap_count();
  static const int kDisplayLapCountFieldNumber = 4;
  inline bool display_lap_count() const;
  inline void set_display_lap_count(bool value);
  
  // optional .rec.gui.FontDesc font = 5;
  inline bool has_font() const;
  inline void clear_font();
  static const int kFontFieldNumber = 5;
  inline const ::rec::gui::FontDesc& font() const;
  inline ::rec::gui::FontDesc* mutable_font();
  
  // optional uint32 margin = 6 [default = 2];
  inline bool has_margin() const;
  inline void clear_margin();
  static const int kMarginFieldNumber = 6;
  inline ::google::protobuf::uint32 margin() const;
  inline void set_margin(::google::protobuf::uint32 value);
  
  // optional float zero_point = 7;
  inline bool has_zero_point() const;
  inline void clear_zero_point();
  static const int kZeroPointFieldNumber = 7;
  inline float zero_point() const;
  inline void set_zero_point(float value);
  
  // optional bool empty_on_zero = 8 [default = true];
  inline bool has_empty_on_zero() const;
  inline void clear_empty_on_zero();
  static const int kEmptyOnZeroFieldNumber = 8;
  inline bool empty_on_zero() const;
  inline void set_empty_on_zero(bool value);
  
  // @@protoc_insertion_point(class_scope:rec.gui.time.Dial)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::std::string* name_;
  static const ::std::string _default_name_;
  ::google::protobuf::uint32 outline_;
  int direction_;
  bool display_lap_count_;
  ::rec::gui::FontDesc* font_;
  ::google::protobuf::uint32 margin_;
  float zero_point_;
  bool empty_on_zero_;
  friend void  protobuf_AddDesc_rec_2fgui_2fTime_2eproto();
  friend void protobuf_AssignDesc_rec_2fgui_2fTime_2eproto();
  friend void protobuf_ShutdownFile_rec_2fgui_2fTime_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(8 + 31) / 32];
  
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
  static Dial* default_instance_;
};
// -------------------------------------------------------------------

class Time : public ::google::protobuf::Message {
 public:
  Time();
  virtual ~Time();
  
  Time(const Time& from);
  
  inline Time& operator=(const Time& from) {
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
  static const Time& default_instance();
  
  void Swap(Time* other);
  
  // implements Message ----------------------------------------------
  
  Time* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Time& from);
  void MergeFrom(const Time& from);
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
  
  // optional .rec.gui.time.Text text = 1;
  inline bool has_text() const;
  inline void clear_text();
  static const int kTextFieldNumber = 1;
  inline const ::rec::gui::time::Text& text() const;
  inline ::rec::gui::time::Text* mutable_text();
  
  // optional .rec.gui.time.Dial dial = 2;
  inline bool has_dial() const;
  inline void clear_dial();
  static const int kDialFieldNumber = 2;
  inline const ::rec::gui::time::Dial& dial() const;
  inline ::rec::gui::time::Dial* mutable_dial();
  
  // optional .rec.gui.time.Bar bar = 3;
  inline bool has_bar() const;
  inline void clear_bar();
  static const int kBarFieldNumber = 3;
  inline const ::rec::gui::time::Bar& bar() const;
  inline ::rec::gui::time::Bar* mutable_bar();
  
  // @@protoc_insertion_point(class_scope:rec.gui.time.Time)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::rec::gui::time::Text* text_;
  ::rec::gui::time::Dial* dial_;
  ::rec::gui::time::Bar* bar_;
  friend void  protobuf_AddDesc_rec_2fgui_2fTime_2eproto();
  friend void protobuf_AssignDesc_rec_2fgui_2fTime_2eproto();
  friend void protobuf_ShutdownFile_rec_2fgui_2fTime_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
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
  static Time* default_instance_;
};
// ===================================================================


// ===================================================================

// Text_Separator

// optional string separator = 1;
inline bool Text_Separator::has_separator() const {
  return _has_bit(0);
}
inline void Text_Separator::clear_separator() {
  if (separator_ != &_default_separator_) {
    separator_->clear();
  }
  _clear_bit(0);
}
inline const ::std::string& Text_Separator::separator() const {
  return *separator_;
}
inline void Text_Separator::set_separator(const ::std::string& value) {
  _set_bit(0);
  if (separator_ == &_default_separator_) {
    separator_ = new ::std::string;
  }
  separator_->assign(value);
}
inline void Text_Separator::set_separator(const char* value) {
  _set_bit(0);
  if (separator_ == &_default_separator_) {
    separator_ = new ::std::string;
  }
  separator_->assign(value);
}
inline void Text_Separator::set_separator(const char* value, size_t size) {
  _set_bit(0);
  if (separator_ == &_default_separator_) {
    separator_ = new ::std::string;
  }
  separator_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Text_Separator::mutable_separator() {
  _set_bit(0);
  if (separator_ == &_default_separator_) {
    separator_ = new ::std::string;
  }
  return separator_;
}

// optional uint32 width = 2;
inline bool Text_Separator::has_width() const {
  return _has_bit(1);
}
inline void Text_Separator::clear_width() {
  width_ = 0u;
  _clear_bit(1);
}
inline ::google::protobuf::uint32 Text_Separator::width() const {
  return width_;
}
inline void Text_Separator::set_width(::google::protobuf::uint32 value) {
  _set_bit(1);
  width_ = value;
}

// optional bool flash = 3 [default = true];
inline bool Text_Separator::has_flash() const {
  return _has_bit(2);
}
inline void Text_Separator::clear_flash() {
  flash_ = true;
  _clear_bit(2);
}
inline bool Text_Separator::flash() const {
  return flash_;
}
inline void Text_Separator::set_flash(bool value) {
  _set_bit(2);
  flash_ = value;
}

// -------------------------------------------------------------------

// Text_Fields

// optional bool hours = 1 [default = false];
inline bool Text_Fields::has_hours() const {
  return _has_bit(0);
}
inline void Text_Fields::clear_hours() {
  hours_ = false;
  _clear_bit(0);
}
inline bool Text_Fields::hours() const {
  return hours_;
}
inline void Text_Fields::set_hours(bool value) {
  _set_bit(0);
  hours_ = value;
}

// optional bool minutes = 2 [default = true];
inline bool Text_Fields::has_minutes() const {
  return _has_bit(1);
}
inline void Text_Fields::clear_minutes() {
  minutes_ = true;
  _clear_bit(1);
}
inline bool Text_Fields::minutes() const {
  return minutes_;
}
inline void Text_Fields::set_minutes(bool value) {
  _set_bit(1);
  minutes_ = value;
}

// optional bool seconds = 3 [default = true];
inline bool Text_Fields::has_seconds() const {
  return _has_bit(2);
}
inline void Text_Fields::clear_seconds() {
  seconds_ = true;
  _clear_bit(2);
}
inline bool Text_Fields::seconds() const {
  return seconds_;
}
inline void Text_Fields::set_seconds(bool value) {
  _set_bit(2);
  seconds_ = value;
}

// optional bool milliseconds = 4 [default = true];
inline bool Text_Fields::has_milliseconds() const {
  return _has_bit(3);
}
inline void Text_Fields::clear_milliseconds() {
  milliseconds_ = true;
  _clear_bit(3);
}
inline bool Text_Fields::milliseconds() const {
  return milliseconds_;
}
inline void Text_Fields::set_milliseconds(bool value) {
  _set_bit(3);
  milliseconds_ = value;
}

// optional bool frames = 5 [default = false];
inline bool Text_Fields::has_frames() const {
  return _has_bit(4);
}
inline void Text_Fields::clear_frames() {
  frames_ = false;
  _clear_bit(4);
}
inline bool Text_Fields::frames() const {
  return frames_;
}
inline void Text_Fields::set_frames(bool value) {
  _set_bit(4);
  frames_ = value;
}

// -------------------------------------------------------------------

// Text

// optional string name = 5;
inline bool Text::has_name() const {
  return _has_bit(0);
}
inline void Text::clear_name() {
  if (name_ != &_default_name_) {
    name_->clear();
  }
  _clear_bit(0);
}
inline const ::std::string& Text::name() const {
  return *name_;
}
inline void Text::set_name(const ::std::string& value) {
  _set_bit(0);
  if (name_ == &_default_name_) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Text::set_name(const char* value) {
  _set_bit(0);
  if (name_ == &_default_name_) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Text::set_name(const char* value, size_t size) {
  _set_bit(0);
  if (name_ == &_default_name_) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Text::mutable_name() {
  _set_bit(0);
  if (name_ == &_default_name_) {
    name_ = new ::std::string;
  }
  return name_;
}

// optional .rec.gui.FontDesc font = 1;
inline bool Text::has_font() const {
  return _has_bit(1);
}
inline void Text::clear_font() {
  if (font_ != NULL) font_->::rec::gui::FontDesc::Clear();
  _clear_bit(1);
}
inline const ::rec::gui::FontDesc& Text::font() const {
  return font_ != NULL ? *font_ : *default_instance_->font_;
}
inline ::rec::gui::FontDesc* Text::mutable_font() {
  _set_bit(1);
  if (font_ == NULL) font_ = new ::rec::gui::FontDesc;
  return font_;
}

// optional .rec.gui.time.Text.Separator separator = 2;
inline bool Text::has_separator() const {
  return _has_bit(2);
}
inline void Text::clear_separator() {
  if (separator_ != NULL) separator_->::rec::gui::time::Text_Separator::Clear();
  _clear_bit(2);
}
inline const ::rec::gui::time::Text_Separator& Text::separator() const {
  return separator_ != NULL ? *separator_ : *default_instance_->separator_;
}
inline ::rec::gui::time::Text_Separator* Text::mutable_separator() {
  _set_bit(2);
  if (separator_ == NULL) separator_ = new ::rec::gui::time::Text_Separator;
  return separator_;
}

// optional .rec.gui.time.Text.Fields fields = 3;
inline bool Text::has_fields() const {
  return _has_bit(3);
}
inline void Text::clear_fields() {
  if (fields_ != NULL) fields_->::rec::gui::time::Text_Fields::Clear();
  _clear_bit(3);
}
inline const ::rec::gui::time::Text_Fields& Text::fields() const {
  return fields_ != NULL ? *fields_ : *default_instance_->fields_;
}
inline ::rec::gui::time::Text_Fields* Text::mutable_fields() {
  _set_bit(3);
  if (fields_ == NULL) fields_ = new ::rec::gui::time::Text_Fields;
  return fields_;
}

// optional uint32 margin = 4 [default = 2];
inline bool Text::has_margin() const {
  return _has_bit(4);
}
inline void Text::clear_margin() {
  margin_ = 2u;
  _clear_bit(4);
}
inline ::google::protobuf::uint32 Text::margin() const {
  return margin_;
}
inline void Text::set_margin(::google::protobuf::uint32 value) {
  _set_bit(4);
  margin_ = value;
}

// -------------------------------------------------------------------

// Bar

// -------------------------------------------------------------------

// Dial

// optional string name = 1;
inline bool Dial::has_name() const {
  return _has_bit(0);
}
inline void Dial::clear_name() {
  if (name_ != &_default_name_) {
    name_->clear();
  }
  _clear_bit(0);
}
inline const ::std::string& Dial::name() const {
  return *name_;
}
inline void Dial::set_name(const ::std::string& value) {
  _set_bit(0);
  if (name_ == &_default_name_) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Dial::set_name(const char* value) {
  _set_bit(0);
  if (name_ == &_default_name_) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Dial::set_name(const char* value, size_t size) {
  _set_bit(0);
  if (name_ == &_default_name_) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Dial::mutable_name() {
  _set_bit(0);
  if (name_ == &_default_name_) {
    name_ = new ::std::string;
  }
  return name_;
}

// optional uint32 outline = 2;
inline bool Dial::has_outline() const {
  return _has_bit(1);
}
inline void Dial::clear_outline() {
  outline_ = 0u;
  _clear_bit(1);
}
inline ::google::protobuf::uint32 Dial::outline() const {
  return outline_;
}
inline void Dial::set_outline(::google::protobuf::uint32 value) {
  _set_bit(1);
  outline_ = value;
}

// optional .rec.gui.time.Dial.Direction direction = 3 [default = CLOCKWISE];
inline bool Dial::has_direction() const {
  return _has_bit(2);
}
inline void Dial::clear_direction() {
  direction_ = 1;
  _clear_bit(2);
}
inline ::rec::gui::time::Dial_Direction Dial::direction() const {
  return static_cast< ::rec::gui::time::Dial_Direction >(direction_);
}
inline void Dial::set_direction(::rec::gui::time::Dial_Direction value) {
  GOOGLE_DCHECK(::rec::gui::time::Dial_Direction_IsValid(value));
  _set_bit(2);
  direction_ = value;
}

// optional bool display_lap_count = 4;
inline bool Dial::has_display_lap_count() const {
  return _has_bit(3);
}
inline void Dial::clear_display_lap_count() {
  display_lap_count_ = false;
  _clear_bit(3);
}
inline bool Dial::display_lap_count() const {
  return display_lap_count_;
}
inline void Dial::set_display_lap_count(bool value) {
  _set_bit(3);
  display_lap_count_ = value;
}

// optional .rec.gui.FontDesc font = 5;
inline bool Dial::has_font() const {
  return _has_bit(4);
}
inline void Dial::clear_font() {
  if (font_ != NULL) font_->::rec::gui::FontDesc::Clear();
  _clear_bit(4);
}
inline const ::rec::gui::FontDesc& Dial::font() const {
  return font_ != NULL ? *font_ : *default_instance_->font_;
}
inline ::rec::gui::FontDesc* Dial::mutable_font() {
  _set_bit(4);
  if (font_ == NULL) font_ = new ::rec::gui::FontDesc;
  return font_;
}

// optional uint32 margin = 6 [default = 2];
inline bool Dial::has_margin() const {
  return _has_bit(5);
}
inline void Dial::clear_margin() {
  margin_ = 2u;
  _clear_bit(5);
}
inline ::google::protobuf::uint32 Dial::margin() const {
  return margin_;
}
inline void Dial::set_margin(::google::protobuf::uint32 value) {
  _set_bit(5);
  margin_ = value;
}

// optional float zero_point = 7;
inline bool Dial::has_zero_point() const {
  return _has_bit(6);
}
inline void Dial::clear_zero_point() {
  zero_point_ = 0;
  _clear_bit(6);
}
inline float Dial::zero_point() const {
  return zero_point_;
}
inline void Dial::set_zero_point(float value) {
  _set_bit(6);
  zero_point_ = value;
}

// optional bool empty_on_zero = 8 [default = true];
inline bool Dial::has_empty_on_zero() const {
  return _has_bit(7);
}
inline void Dial::clear_empty_on_zero() {
  empty_on_zero_ = true;
  _clear_bit(7);
}
inline bool Dial::empty_on_zero() const {
  return empty_on_zero_;
}
inline void Dial::set_empty_on_zero(bool value) {
  _set_bit(7);
  empty_on_zero_ = value;
}

// -------------------------------------------------------------------

// Time

// optional .rec.gui.time.Text text = 1;
inline bool Time::has_text() const {
  return _has_bit(0);
}
inline void Time::clear_text() {
  if (text_ != NULL) text_->::rec::gui::time::Text::Clear();
  _clear_bit(0);
}
inline const ::rec::gui::time::Text& Time::text() const {
  return text_ != NULL ? *text_ : *default_instance_->text_;
}
inline ::rec::gui::time::Text* Time::mutable_text() {
  _set_bit(0);
  if (text_ == NULL) text_ = new ::rec::gui::time::Text;
  return text_;
}

// optional .rec.gui.time.Dial dial = 2;
inline bool Time::has_dial() const {
  return _has_bit(1);
}
inline void Time::clear_dial() {
  if (dial_ != NULL) dial_->::rec::gui::time::Dial::Clear();
  _clear_bit(1);
}
inline const ::rec::gui::time::Dial& Time::dial() const {
  return dial_ != NULL ? *dial_ : *default_instance_->dial_;
}
inline ::rec::gui::time::Dial* Time::mutable_dial() {
  _set_bit(1);
  if (dial_ == NULL) dial_ = new ::rec::gui::time::Dial;
  return dial_;
}

// optional .rec.gui.time.Bar bar = 3;
inline bool Time::has_bar() const {
  return _has_bit(2);
}
inline void Time::clear_bar() {
  if (bar_ != NULL) bar_->::rec::gui::time::Bar::Clear();
  _clear_bit(2);
}
inline const ::rec::gui::time::Bar& Time::bar() const {
  return bar_ != NULL ? *bar_ : *default_instance_->bar_;
}
inline ::rec::gui::time::Bar* Time::mutable_bar() {
  _set_bit(2);
  if (bar_ == NULL) bar_ = new ::rec::gui::time::Bar;
  return bar_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace time
}  // namespace gui
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::rec::gui::time::Dial_Direction>() {
  return ::rec::gui::time::Dial_Direction_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2fgui_2fTime_2eproto__INCLUDED
