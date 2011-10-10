// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/data/commands/Action.proto

#ifndef PROTOBUF_rec_2fdata_2fcommands_2fAction_2eproto__INCLUDED
#define PROTOBUF_rec_2fdata_2fcommands_2fAction_2eproto__INCLUDED

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
#include "rec/data/Operation.pb.h"
#include "rec/util/file/VirtualFile.pb.h"
// @@protoc_insertion_point(includes)

namespace rec {
namespace data {
namespace commands {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fdata_2fcommands_2fAction_2eproto();
void protobuf_AssignDesc_rec_2fdata_2fcommands_2fAction_2eproto();
void protobuf_ShutdownFile_rec_2fdata_2fcommands_2fAction_2eproto();

class Source;
class Action;

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
  
  // optional .rec.data.commands.Source.Type type = 1;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline ::rec::data::commands::Source_Type type() const;
  inline void set_type(::rec::data::commands::Source_Type value);
  
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
  
  // @@protoc_insertion_point(class_scope:rec.data.commands.Source)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  int type_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > index_;
  ::google::protobuf::uint32 modifier_keys_;
  friend void  protobuf_AddDesc_rec_2fdata_2fcommands_2fAction_2eproto();
  friend void protobuf_AssignDesc_rec_2fdata_2fcommands_2fAction_2eproto();
  friend void protobuf_ShutdownFile_rec_2fdata_2fcommands_2fAction_2eproto();
  
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

class Action : public ::google::protobuf::Message {
 public:
  Action();
  virtual ~Action();
  
  Action(const Action& from);
  
  inline Action& operator=(const Action& from) {
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
  static const Action& default_instance();
  
  void Swap(Action* other);
  
  // implements Message ----------------------------------------------
  
  Action* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Action& from);
  void MergeFrom(const Action& from);
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
  
  // optional uint64 index = 2;
  inline bool has_index() const;
  inline void clear_index();
  static const int kIndexFieldNumber = 2;
  inline ::google::protobuf::uint64 index() const;
  inline void set_index(::google::protobuf::uint64 value);
  
  // repeated .rec.data.commands.Source source = 3;
  inline int source_size() const;
  inline void clear_source();
  static const int kSourceFieldNumber = 3;
  inline const ::rec::data::commands::Source& source(int index) const;
  inline ::rec::data::commands::Source* mutable_source(int index);
  inline ::rec::data::commands::Source* add_source();
  inline const ::google::protobuf::RepeatedPtrField< ::rec::data::commands::Source >&
      source() const;
  inline ::google::protobuf::RepeatedPtrField< ::rec::data::commands::Source >*
      mutable_source();
  
  // optional .rec.util.file.VirtualFile file = 4;
  inline bool has_file() const;
  inline void clear_file();
  static const int kFileFieldNumber = 4;
  inline const ::rec::util::file::VirtualFile& file() const;
  inline ::rec::util::file::VirtualFile* mutable_file();
  
  // optional string type_name = 5;
  inline bool has_type_name() const;
  inline void clear_type_name();
  static const int kTypeNameFieldNumber = 5;
  inline const ::std::string& type_name() const;
  inline void set_type_name(const ::std::string& value);
  inline void set_type_name(const char* value);
  inline void set_type_name(const char* value, size_t size);
  inline ::std::string* mutable_type_name();
  
  // optional .rec.data.OperationList operations = 6;
  inline bool has_operations() const;
  inline void clear_operations();
  static const int kOperationsFieldNumber = 6;
  inline const ::rec::data::OperationList& operations() const;
  inline ::rec::data::OperationList* mutable_operations();
  
  // optional .rec.data.OperationList undo = 7;
  inline bool has_undo() const;
  inline void clear_undo();
  static const int kUndoFieldNumber = 7;
  inline const ::rec::data::OperationList& undo() const;
  inline ::rec::data::OperationList* mutable_undo();
  
  // @@protoc_insertion_point(class_scope:rec.data.commands.Action)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::google::protobuf::uint64 timestamp_;
  ::google::protobuf::uint64 index_;
  ::google::protobuf::RepeatedPtrField< ::rec::data::commands::Source > source_;
  ::rec::util::file::VirtualFile* file_;
  ::std::string* type_name_;
  static const ::std::string _default_type_name_;
  ::rec::data::OperationList* operations_;
  ::rec::data::OperationList* undo_;
  friend void  protobuf_AddDesc_rec_2fdata_2fcommands_2fAction_2eproto();
  friend void protobuf_AssignDesc_rec_2fdata_2fcommands_2fAction_2eproto();
  friend void protobuf_ShutdownFile_rec_2fdata_2fcommands_2fAction_2eproto();
  
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
  static Action* default_instance_;
};
// ===================================================================


// ===================================================================

// Source

// optional .rec.data.commands.Source.Type type = 1;
inline bool Source::has_type() const {
  return _has_bit(0);
}
inline void Source::clear_type() {
  type_ = 0;
  _clear_bit(0);
}
inline ::rec::data::commands::Source_Type Source::type() const {
  return static_cast< ::rec::data::commands::Source_Type >(type_);
}
inline void Source::set_type(::rec::data::commands::Source_Type value) {
  GOOGLE_DCHECK(::rec::data::commands::Source_Type_IsValid(value));
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

// Action

// optional uint64 timestamp = 1;
inline bool Action::has_timestamp() const {
  return _has_bit(0);
}
inline void Action::clear_timestamp() {
  timestamp_ = GOOGLE_ULONGLONG(0);
  _clear_bit(0);
}
inline ::google::protobuf::uint64 Action::timestamp() const {
  return timestamp_;
}
inline void Action::set_timestamp(::google::protobuf::uint64 value) {
  _set_bit(0);
  timestamp_ = value;
}

// optional uint64 index = 2;
inline bool Action::has_index() const {
  return _has_bit(1);
}
inline void Action::clear_index() {
  index_ = GOOGLE_ULONGLONG(0);
  _clear_bit(1);
}
inline ::google::protobuf::uint64 Action::index() const {
  return index_;
}
inline void Action::set_index(::google::protobuf::uint64 value) {
  _set_bit(1);
  index_ = value;
}

// repeated .rec.data.commands.Source source = 3;
inline int Action::source_size() const {
  return source_.size();
}
inline void Action::clear_source() {
  source_.Clear();
}
inline const ::rec::data::commands::Source& Action::source(int index) const {
  return source_.Get(index);
}
inline ::rec::data::commands::Source* Action::mutable_source(int index) {
  return source_.Mutable(index);
}
inline ::rec::data::commands::Source* Action::add_source() {
  return source_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::rec::data::commands::Source >&
Action::source() const {
  return source_;
}
inline ::google::protobuf::RepeatedPtrField< ::rec::data::commands::Source >*
Action::mutable_source() {
  return &source_;
}

// optional .rec.util.file.VirtualFile file = 4;
inline bool Action::has_file() const {
  return _has_bit(3);
}
inline void Action::clear_file() {
  if (file_ != NULL) file_->::rec::util::file::VirtualFile::Clear();
  _clear_bit(3);
}
inline const ::rec::util::file::VirtualFile& Action::file() const {
  return file_ != NULL ? *file_ : *default_instance_->file_;
}
inline ::rec::util::file::VirtualFile* Action::mutable_file() {
  _set_bit(3);
  if (file_ == NULL) file_ = new ::rec::util::file::VirtualFile;
  return file_;
}

// optional string type_name = 5;
inline bool Action::has_type_name() const {
  return _has_bit(4);
}
inline void Action::clear_type_name() {
  if (type_name_ != &_default_type_name_) {
    type_name_->clear();
  }
  _clear_bit(4);
}
inline const ::std::string& Action::type_name() const {
  return *type_name_;
}
inline void Action::set_type_name(const ::std::string& value) {
  _set_bit(4);
  if (type_name_ == &_default_type_name_) {
    type_name_ = new ::std::string;
  }
  type_name_->assign(value);
}
inline void Action::set_type_name(const char* value) {
  _set_bit(4);
  if (type_name_ == &_default_type_name_) {
    type_name_ = new ::std::string;
  }
  type_name_->assign(value);
}
inline void Action::set_type_name(const char* value, size_t size) {
  _set_bit(4);
  if (type_name_ == &_default_type_name_) {
    type_name_ = new ::std::string;
  }
  type_name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Action::mutable_type_name() {
  _set_bit(4);
  if (type_name_ == &_default_type_name_) {
    type_name_ = new ::std::string;
  }
  return type_name_;
}

// optional .rec.data.OperationList operations = 6;
inline bool Action::has_operations() const {
  return _has_bit(5);
}
inline void Action::clear_operations() {
  if (operations_ != NULL) operations_->::rec::data::OperationList::Clear();
  _clear_bit(5);
}
inline const ::rec::data::OperationList& Action::operations() const {
  return operations_ != NULL ? *operations_ : *default_instance_->operations_;
}
inline ::rec::data::OperationList* Action::mutable_operations() {
  _set_bit(5);
  if (operations_ == NULL) operations_ = new ::rec::data::OperationList;
  return operations_;
}

// optional .rec.data.OperationList undo = 7;
inline bool Action::has_undo() const {
  return _has_bit(6);
}
inline void Action::clear_undo() {
  if (undo_ != NULL) undo_->::rec::data::OperationList::Clear();
  _clear_bit(6);
}
inline const ::rec::data::OperationList& Action::undo() const {
  return undo_ != NULL ? *undo_ : *default_instance_->undo_;
}
inline ::rec::data::OperationList* Action::mutable_undo() {
  _set_bit(6);
  if (undo_ == NULL) undo_ = new ::rec::data::OperationList;
  return undo_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace commands
}  // namespace data
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::rec::data::commands::Source_Type>() {
  return ::rec::data::commands::Source_Type_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2fdata_2fcommands_2fAction_2eproto__INCLUDED
