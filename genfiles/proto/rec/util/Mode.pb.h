// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/util/Mode.proto

#ifndef PROTOBUF_rec_2futil_2fMode_2eproto__INCLUDED
#define PROTOBUF_rec_2futil_2fMode_2eproto__INCLUDED

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
namespace util {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2futil_2fMode_2eproto();
void protobuf_AssignDesc_rec_2futil_2fMode_2eproto();
void protobuf_ShutdownFile_rec_2futil_2fMode_2eproto();

class Mode;

enum Mode_Action {
  Mode_Action_NONE = 0,
  Mode_Action_DRAG = 1,
  Mode_Action_DRAW_LOOP_POINTS = 2,
  Mode_Action_SET_TIME = 3,
  Mode_Action_TOGGLE_SELECTION = 4,
  Mode_Action_ZOOM_IN = 5,
  Mode_Action_ZOOM_OUT = 6
};
bool Mode_Action_IsValid(int value);
const Mode_Action Mode_Action_Action_MIN = Mode_Action_NONE;
const Mode_Action Mode_Action_Action_MAX = Mode_Action_ZOOM_OUT;
const int Mode_Action_Action_ARRAYSIZE = Mode_Action_Action_MAX + 1;

const ::google::protobuf::EnumDescriptor* Mode_Action_descriptor();
inline const ::std::string& Mode_Action_Name(Mode_Action value) {
  return ::google::protobuf::internal::NameOfEnum(
    Mode_Action_descriptor(), value);
}
inline bool Mode_Action_Parse(
    const ::std::string& name, Mode_Action* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Mode_Action>(
    Mode_Action_descriptor(), name, value);
}
// ===================================================================

class Mode : public ::google::protobuf::Message {
 public:
  Mode();
  virtual ~Mode();
  
  Mode(const Mode& from);
  
  inline Mode& operator=(const Mode& from) {
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
  static const Mode& default_instance();
  
  void Swap(Mode* other);
  
  // implements Message ----------------------------------------------
  
  Mode* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Mode& from);
  void MergeFrom(const Mode& from);
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
  
  typedef Mode_Action Action;
  static const Action NONE = Mode_Action_NONE;
  static const Action DRAG = Mode_Action_DRAG;
  static const Action DRAW_LOOP_POINTS = Mode_Action_DRAW_LOOP_POINTS;
  static const Action SET_TIME = Mode_Action_SET_TIME;
  static const Action TOGGLE_SELECTION = Mode_Action_TOGGLE_SELECTION;
  static const Action ZOOM_IN = Mode_Action_ZOOM_IN;
  static const Action ZOOM_OUT = Mode_Action_ZOOM_OUT;
  static inline bool Action_IsValid(int value) {
    return Mode_Action_IsValid(value);
  }
  static const Action Action_MIN =
    Mode_Action_Action_MIN;
  static const Action Action_MAX =
    Mode_Action_Action_MAX;
  static const int Action_ARRAYSIZE =
    Mode_Action_Action_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Action_descriptor() {
    return Mode_Action_descriptor();
  }
  static inline const ::std::string& Action_Name(Action value) {
    return Mode_Action_Name(value);
  }
  static inline bool Action_Parse(const ::std::string& name,
      Action* value) {
    return Mode_Action_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // optional .rec.util.Mode.Action click = 1 [default = SET_TIME];
  inline bool has_click() const;
  inline void clear_click();
  static const int kClickFieldNumber = 1;
  inline ::rec::util::Mode_Action click() const;
  inline void set_click(::rec::util::Mode_Action value);
  
  // @@protoc_insertion_point(class_scope:rec.util.Mode)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  int click_;
  friend void  protobuf_AddDesc_rec_2futil_2fMode_2eproto();
  friend void protobuf_AssignDesc_rec_2futil_2fMode_2eproto();
  friend void protobuf_ShutdownFile_rec_2futil_2fMode_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
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
  static Mode* default_instance_;
};
// ===================================================================


// ===================================================================

// Mode

// optional .rec.util.Mode.Action click = 1 [default = SET_TIME];
inline bool Mode::has_click() const {
  return _has_bit(0);
}
inline void Mode::clear_click() {
  click_ = 3;
  _clear_bit(0);
}
inline ::rec::util::Mode_Action Mode::click() const {
  return static_cast< ::rec::util::Mode_Action >(click_);
}
inline void Mode::set_click(::rec::util::Mode_Action value) {
  GOOGLE_DCHECK(::rec::util::Mode_Action_IsValid(value));
  _set_bit(0);
  click_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace util
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::rec::util::Mode_Action>() {
  return ::rec::util::Mode_Action_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2futil_2fMode_2eproto__INCLUDED
