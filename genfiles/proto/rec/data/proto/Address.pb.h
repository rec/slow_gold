// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/data/proto/Address.proto

#ifndef PROTOBUF_rec_2fdata_2fproto_2fAddress_2eproto__INCLUDED
#define PROTOBUF_rec_2fdata_2fproto_2fAddress_2eproto__INCLUDED

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
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace rec {
namespace data {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fdata_2fproto_2fAddress_2eproto();
void protobuf_AssignDesc_rec_2fdata_2fproto_2fAddress_2eproto();
void protobuf_ShutdownFile_rec_2fdata_2fproto_2fAddress_2eproto();

class AddressProto;
class AddressProto_Part;

enum AddressProto_Scope {
  AddressProto_Scope_FILE_SCOPE = 0,
  AddressProto_Scope_GLOBAL_SCOPE = 1
};
bool AddressProto_Scope_IsValid(int value);
const AddressProto_Scope AddressProto_Scope_Scope_MIN = AddressProto_Scope_FILE_SCOPE;
const AddressProto_Scope AddressProto_Scope_Scope_MAX = AddressProto_Scope_GLOBAL_SCOPE;
const int AddressProto_Scope_Scope_ARRAYSIZE = AddressProto_Scope_Scope_MAX + 1;

const ::google::protobuf::EnumDescriptor* AddressProto_Scope_descriptor();
inline const ::std::string& AddressProto_Scope_Name(AddressProto_Scope value) {
  return ::google::protobuf::internal::NameOfEnum(
    AddressProto_Scope_descriptor(), value);
}
inline bool AddressProto_Scope_Parse(
    const ::std::string& name, AddressProto_Scope* value) {
  return ::google::protobuf::internal::ParseNamedEnum<AddressProto_Scope>(
    AddressProto_Scope_descriptor(), name, value);
}
// ===================================================================

class AddressProto_Part : public ::google::protobuf::Message {
 public:
  AddressProto_Part();
  virtual ~AddressProto_Part();

  AddressProto_Part(const AddressProto_Part& from);

  inline AddressProto_Part& operator=(const AddressProto_Part& from) {
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
  static const AddressProto_Part& default_instance();

  void Swap(AddressProto_Part* other);

  // implements Message ----------------------------------------------

  AddressProto_Part* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AddressProto_Part& from);
  void MergeFrom(const AddressProto_Part& from);
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

  // optional uint32 index = 1;
  inline bool has_index() const;
  inline void clear_index();
  static const int kIndexFieldNumber = 1;
  inline ::google::protobuf::uint32 index() const;
  inline void set_index(::google::protobuf::uint32 value);

  // optional string name = 2;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 2;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // @@protoc_insertion_point(class_scope:rec.data.AddressProto.Part)
 private:
  inline void set_has_index();
  inline void clear_has_index();
  inline void set_has_name();
  inline void clear_has_name();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* name_;
  ::google::protobuf::uint32 index_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_rec_2fdata_2fproto_2fAddress_2eproto();
  friend void protobuf_AssignDesc_rec_2fdata_2fproto_2fAddress_2eproto();
  friend void protobuf_ShutdownFile_rec_2fdata_2fproto_2fAddress_2eproto();

  void InitAsDefaultInstance();
  static AddressProto_Part* default_instance_;
};
// -------------------------------------------------------------------

class AddressProto : public ::google::protobuf::Message {
 public:
  AddressProto();
  virtual ~AddressProto();

  AddressProto(const AddressProto& from);

  inline AddressProto& operator=(const AddressProto& from) {
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
  static const AddressProto& default_instance();

  void Swap(AddressProto* other);

  // implements Message ----------------------------------------------

  AddressProto* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AddressProto& from);
  void MergeFrom(const AddressProto& from);
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

  typedef AddressProto_Part Part;

  typedef AddressProto_Scope Scope;
  static const Scope FILE_SCOPE = AddressProto_Scope_FILE_SCOPE;
  static const Scope GLOBAL_SCOPE = AddressProto_Scope_GLOBAL_SCOPE;
  static inline bool Scope_IsValid(int value) {
    return AddressProto_Scope_IsValid(value);
  }
  static const Scope Scope_MIN =
    AddressProto_Scope_Scope_MIN;
  static const Scope Scope_MAX =
    AddressProto_Scope_Scope_MAX;
  static const int Scope_ARRAYSIZE =
    AddressProto_Scope_Scope_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Scope_descriptor() {
    return AddressProto_Scope_descriptor();
  }
  static inline const ::std::string& Scope_Name(Scope value) {
    return AddressProto_Scope_Name(value);
  }
  static inline bool Scope_Parse(const ::std::string& name,
      Scope* value) {
    return AddressProto_Scope_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // repeated .rec.data.AddressProto.Part part = 1;
  inline int part_size() const;
  inline void clear_part();
  static const int kPartFieldNumber = 1;
  inline const ::rec::data::AddressProto_Part& part(int index) const;
  inline ::rec::data::AddressProto_Part* mutable_part(int index);
  inline ::rec::data::AddressProto_Part* add_part();
  inline const ::google::protobuf::RepeatedPtrField< ::rec::data::AddressProto_Part >&
      part() const;
  inline ::google::protobuf::RepeatedPtrField< ::rec::data::AddressProto_Part >*
      mutable_part();

  // optional .rec.data.AddressProto.Scope scope = 2;
  inline bool has_scope() const;
  inline void clear_scope();
  static const int kScopeFieldNumber = 2;
  inline ::rec::data::AddressProto_Scope scope() const;
  inline void set_scope(::rec::data::AddressProto_Scope value);

  // @@protoc_insertion_point(class_scope:rec.data.AddressProto)
 private:
  inline void set_has_scope();
  inline void clear_has_scope();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::rec::data::AddressProto_Part > part_;
  int scope_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_rec_2fdata_2fproto_2fAddress_2eproto();
  friend void protobuf_AssignDesc_rec_2fdata_2fproto_2fAddress_2eproto();
  friend void protobuf_ShutdownFile_rec_2fdata_2fproto_2fAddress_2eproto();

  void InitAsDefaultInstance();
  static AddressProto* default_instance_;
};
// ===================================================================


// ===================================================================

// AddressProto_Part

// optional uint32 index = 1;
inline bool AddressProto_Part::has_index() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AddressProto_Part::set_has_index() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AddressProto_Part::clear_has_index() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AddressProto_Part::clear_index() {
  index_ = 0u;
  clear_has_index();
}
inline ::google::protobuf::uint32 AddressProto_Part::index() const {
  return index_;
}
inline void AddressProto_Part::set_index(::google::protobuf::uint32 value) {
  set_has_index();
  index_ = value;
}

// optional string name = 2;
inline bool AddressProto_Part::has_name() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AddressProto_Part::set_has_name() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AddressProto_Part::clear_has_name() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AddressProto_Part::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& AddressProto_Part::name() const {
  return *name_;
}
inline void AddressProto_Part::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void AddressProto_Part::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void AddressProto_Part::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* AddressProto_Part::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* AddressProto_Part::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void AddressProto_Part::set_allocated_name(::std::string* name) {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    delete name_;
  }
  if (name) {
    set_has_name();
    name_ = name;
  } else {
    clear_has_name();
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// AddressProto

// repeated .rec.data.AddressProto.Part part = 1;
inline int AddressProto::part_size() const {
  return part_.size();
}
inline void AddressProto::clear_part() {
  part_.Clear();
}
inline const ::rec::data::AddressProto_Part& AddressProto::part(int index) const {
  return part_.Get(index);
}
inline ::rec::data::AddressProto_Part* AddressProto::mutable_part(int index) {
  return part_.Mutable(index);
}
inline ::rec::data::AddressProto_Part* AddressProto::add_part() {
  return part_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::rec::data::AddressProto_Part >&
AddressProto::part() const {
  return part_;
}
inline ::google::protobuf::RepeatedPtrField< ::rec::data::AddressProto_Part >*
AddressProto::mutable_part() {
  return &part_;
}

// optional .rec.data.AddressProto.Scope scope = 2;
inline bool AddressProto::has_scope() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AddressProto::set_has_scope() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AddressProto::clear_has_scope() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AddressProto::clear_scope() {
  scope_ = 0;
  clear_has_scope();
}
inline ::rec::data::AddressProto_Scope AddressProto::scope() const {
  return static_cast< ::rec::data::AddressProto_Scope >(scope_);
}
inline void AddressProto::set_scope(::rec::data::AddressProto_Scope value) {
  assert(::rec::data::AddressProto_Scope_IsValid(value));
  set_has_scope();
  scope_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace data
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::rec::data::AddressProto_Scope>() {
  return ::rec::data::AddressProto_Scope_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2fdata_2fproto_2fAddress_2eproto__INCLUDED
