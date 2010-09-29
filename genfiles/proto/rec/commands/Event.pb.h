// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/commands/Event.proto

#ifndef PROTOBUF_rec_2fcommands_2fEvent_2eproto__INCLUDED
#define PROTOBUF_rec_2fcommands_2fEvent_2eproto__INCLUDED

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
#include "rec/proto/Operation.pb.h"
// @@protoc_insertion_point(includes)

namespace rec {
namespace event {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fcommands_2fEvent_2eproto();
void protobuf_AssignDesc_rec_2fcommands_2fEvent_2eproto();
void protobuf_ShutdownFile_rec_2fcommands_2fEvent_2eproto();

class Source;
class Event;

enum Source_Type {
  Source_Type_MENU = 0,
  Source_Type_KEYBOARD = 1,
  Source_Type_CONTROL = 2,
  Source_Type_AUTOMATIC = 3
};
bool Source_Type_IsValid(int value);
const Source_Type Source_Type_Type_MIN = Source_Type_MENU;
const Source_Type Source_Type_Type_MAX = Source_Type_AUTOMATIC;
const int Source_Type_Type_ARRAYSIZE = Source_Type_Type_MAX + 1;

const ::google::protobuf::EnumDescriptor* Source_Type_descriptor();
inline const ::std::string& Source_Type_Name(Source_Type value) {
  return ::google::protobuf::internal::NameOfEnum(
    Source_Type_descriptor(), value);
}
inline bool Source_Type_Parse(
    const ::std::string& name, Source_Type* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Source_Type>(
    Source_Type_descriptor(), name, value);
}
// ===================================================================

class Source : public ::google::protobuf::Message {
 public:
  Source();
  virtual ~Source();
  
  Source(const Source& from);
  
  inline Source& operator=(const Source& from) {
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
  static const Source& default_instance();
  
  void Swap(Source* other);
  
  // implements Message ----------------------------------------------
  
  Source* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Source& from);
  void MergeFrom(const Source& from);
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
  
  typedef Source_Type Type;
  static const Type MENU = Source_Type_MENU;
  static const Type KEYBOARD = Source_Type_KEYBOARD;
  static const Type CONTROL = Source_Type_CONTROL;
  static const Type AUTOMATIC = Source_Type_AUTOMATIC;
  static inline bool Type_IsValid(int value) {
    return Source_Type_IsValid(value);
  }
  static const Type Type_MIN =
    Source_Type_Type_MIN;
  static const Type Type_MAX =
    Source_Type_Type_MAX;
  static const int Type_ARRAYSIZE =
    Source_Type_Type_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Type_descriptor() {
    return Source_Type_descriptor();
  }
  static inline const ::std::string& Type_Name(Type value) {
    return Source_Type_Name(value);
  }
  static inline bool Type_Parse(const ::std::string& name,
      Type* value) {
    return Source_Type_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // optional .rec.event.Source.Type type = 1;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline ::rec::event::Source_Type type() const;
  inline void set_type(::rec::event::Source_Type value);
  
  // repeated uint32 index = 2;
  inline int index_size() const;
  inline void clear_index();
  static const int kIndexFieldNumber = 2;
  inline ::google::protobuf::uint32 index(int index) const;
  inline void set_index(int index, ::google::protobuf::uint32 value);
  inline void add_index(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      index() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_index();
  
  // optional uint32 modifier_keys = 3;
  inline bool has_modifier_keys() const;
  inline void clear_modifier_keys();
  static const int kModifierKeysFieldNumber = 3;
  inline ::google::protobuf::uint32 modifier_keys() const;
  inline void set_modifier_keys(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:rec.event.Source)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  int type_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > index_;
  ::google::protobuf::uint32 modifier_keys_;
  friend void  protobuf_AddDesc_rec_2fcommands_2fEvent_2eproto();
  friend void protobuf_AssignDesc_rec_2fcommands_2fEvent_2eproto();
  friend void protobuf_ShutdownFile_rec_2fcommands_2fEvent_2eproto();
  
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
  static Source* default_instance_;
};
// -------------------------------------------------------------------

class Event : public ::google::protobuf::Message {
 public:
  Event();
  virtual ~Event();
  
  Event(const Event& from);
  
  inline Event& operator=(const Event& from) {
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
  static const Event& default_instance();
  
  void Swap(Event* other);
  
  // implements Message ----------------------------------------------
  
  Event* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Event& from);
  void MergeFrom(const Event& from);
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
  
  // optional uint64 timestamp = 1;
  inline bool has_timestamp() const;
  inline void clear_timestamp();
  static const int kTimestampFieldNumber = 1;
  inline ::google::protobuf::uint64 timestamp() const;
  inline void set_timestamp(::google::protobuf::uint64 value);
  
  // repeated .rec.event.Source source = 2;
  inline int source_size() const;
  inline void clear_source();
  static const int kSourceFieldNumber = 2;
  inline const ::rec::event::Source& source(int index) const;
  inline ::rec::event::Source* mutable_source(int index);
  inline ::rec::event::Source* add_source();
  inline const ::google::protobuf::RepeatedPtrField< ::rec::event::Source >&
      source() const;
  inline ::google::protobuf::RepeatedPtrField< ::rec::event::Source >*
      mutable_source();
  
  // repeated .rec.proto.Operation operation = 3;
  inline int operation_size() const;
  inline void clear_operation();
  static const int kOperationFieldNumber = 3;
  inline const ::rec::proto::Operation& operation(int index) const;
  inline ::rec::proto::Operation* mutable_operation(int index);
  inline ::rec::proto::Operation* add_operation();
  inline const ::google::protobuf::RepeatedPtrField< ::rec::proto::Operation >&
      operation() const;
  inline ::google::protobuf::RepeatedPtrField< ::rec::proto::Operation >*
      mutable_operation();
  
  // @@protoc_insertion_point(class_scope:rec.event.Event)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::google::protobuf::uint64 timestamp_;
  ::google::protobuf::RepeatedPtrField< ::rec::event::Source > source_;
  ::google::protobuf::RepeatedPtrField< ::rec::proto::Operation > operation_;
  friend void  protobuf_AddDesc_rec_2fcommands_2fEvent_2eproto();
  friend void protobuf_AssignDesc_rec_2fcommands_2fEvent_2eproto();
  friend void protobuf_ShutdownFile_rec_2fcommands_2fEvent_2eproto();
  
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
  static Event* default_instance_;
};
// ===================================================================


// ===================================================================

// Source

// optional .rec.event.Source.Type type = 1;
inline bool Source::has_type() const {
  return _has_bit(0);
}
inline void Source::clear_type() {
  type_ = 0;
  _clear_bit(0);
}
inline ::rec::event::Source_Type Source::type() const {
  return static_cast< ::rec::event::Source_Type >(type_);
}
inline void Source::set_type(::rec::event::Source_Type value) {
  GOOGLE_DCHECK(::rec::event::Source_Type_IsValid(value));
  _set_bit(0);
  type_ = value;
}

// repeated uint32 index = 2;
inline int Source::index_size() const {
  return index_.size();
}
inline void Source::clear_index() {
  index_.Clear();
}
inline ::google::protobuf::uint32 Source::index(int index) const {
  return index_.Get(index);
}
inline void Source::set_index(int index, ::google::protobuf::uint32 value) {
  index_.Set(index, value);
}
inline void Source::add_index(::google::protobuf::uint32 value) {
  index_.Add(value);
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
Source::index() const {
  return index_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
Source::mutable_index() {
  return &index_;
}

// optional uint32 modifier_keys = 3;
inline bool Source::has_modifier_keys() const {
  return _has_bit(2);
}
inline void Source::clear_modifier_keys() {
  modifier_keys_ = 0u;
  _clear_bit(2);
}
inline ::google::protobuf::uint32 Source::modifier_keys() const {
  return modifier_keys_;
}
inline void Source::set_modifier_keys(::google::protobuf::uint32 value) {
  _set_bit(2);
  modifier_keys_ = value;
}

// -------------------------------------------------------------------

// Event

// optional uint64 timestamp = 1;
inline bool Event::has_timestamp() const {
  return _has_bit(0);
}
inline void Event::clear_timestamp() {
  timestamp_ = GOOGLE_ULONGLONG(0);
  _clear_bit(0);
}
inline ::google::protobuf::uint64 Event::timestamp() const {
  return timestamp_;
}
inline void Event::set_timestamp(::google::protobuf::uint64 value) {
  _set_bit(0);
  timestamp_ = value;
}

// repeated .rec.event.Source source = 2;
inline int Event::source_size() const {
  return source_.size();
}
inline void Event::clear_source() {
  source_.Clear();
}
inline const ::rec::event::Source& Event::source(int index) const {
  return source_.Get(index);
}
inline ::rec::event::Source* Event::mutable_source(int index) {
  return source_.Mutable(index);
}
inline ::rec::event::Source* Event::add_source() {
  return source_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::rec::event::Source >&
Event::source() const {
  return source_;
}
inline ::google::protobuf::RepeatedPtrField< ::rec::event::Source >*
Event::mutable_source() {
  return &source_;
}

// repeated .rec.proto.Operation operation = 3;
inline int Event::operation_size() const {
  return operation_.size();
}
inline void Event::clear_operation() {
  operation_.Clear();
}
inline const ::rec::proto::Operation& Event::operation(int index) const {
  return operation_.Get(index);
}
inline ::rec::proto::Operation* Event::mutable_operation(int index) {
  return operation_.Mutable(index);
}
inline ::rec::proto::Operation* Event::add_operation() {
  return operation_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::rec::proto::Operation >&
Event::operation() const {
  return operation_;
}
inline ::google::protobuf::RepeatedPtrField< ::rec::proto::Operation >*
Event::mutable_operation() {
  return &operation_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace event
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::rec::event::Source_Type>() {
  return ::rec::event::Source_Type_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2fcommands_2fEvent_2eproto__INCLUDED
