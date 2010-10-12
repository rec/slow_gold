// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/data/proto/Address.proto

#ifndef PROTOBUF_rec_2fdata_2fproto_2fAddress_2eproto__INCLUDED
#define PROTOBUF_rec_2fdata_2fproto_2fAddress_2eproto__INCLUDED

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
namespace proto {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fdata_2fproto_2fAddress_2eproto();
void protobuf_AssignDesc_rec_2fdata_2fproto_2fAddress_2eproto();
void protobuf_ShutdownFile_rec_2fdata_2fproto_2fAddress_2eproto();

class Address;
class Address_Field;

// ===================================================================

class Address_Field : public ::google::protobuf::Message {
 public:
  Address_Field();
  virtual ~Address_Field();
  
  Address_Field(const Address_Field& from);
  
  inline Address_Field& operator=(const Address_Field& from) {
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
  static const Address_Field& default_instance();
  
  void Swap(Address_Field* other);
  
  // implements Message ----------------------------------------------
  
  Address_Field* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Address_Field& from);
  void MergeFrom(const Address_Field& from);
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
  
  // optional int32 index = 1;
  inline bool has_index() const;
  inline void clear_index();
  static const int kIndexFieldNumber = 1;
  inline ::google::protobuf::int32 index() const;
  inline void set_index(::google::protobuf::int32 value);
  
  // optional string name = 2;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 2;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  
  // @@protoc_insertion_point(class_scope:rec.proto.Address.Field)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::google::protobuf::int32 index_;
  ::std::string* name_;
  static const ::std::string _default_name_;
  friend void  protobuf_AddDesc_rec_2fdata_2fproto_2fAddress_2eproto();
  friend void protobuf_AssignDesc_rec_2fdata_2fproto_2fAddress_2eproto();
  friend void protobuf_ShutdownFile_rec_2fdata_2fproto_2fAddress_2eproto();
  
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
  static Address_Field* default_instance_;
};
// -------------------------------------------------------------------

class Address : public ::google::protobuf::Message {
 public:
  Address();
  virtual ~Address();
  
  Address(const Address& from);
  
  inline Address& operator=(const Address& from) {
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
  static const Address& default_instance();
  
  void Swap(Address* other);
  
  // implements Message ----------------------------------------------
  
  Address* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Address& from);
  void MergeFrom(const Address& from);
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
  
  typedef Address_Field Field;
  
  // accessors -------------------------------------------------------
  
  // repeated .rec.proto.Address.Field field = 1;
  inline int field_size() const;
  inline void clear_field();
  static const int kFieldFieldNumber = 1;
  inline const ::rec::proto::Address_Field& field(int index) const;
  inline ::rec::proto::Address_Field* mutable_field(int index);
  inline ::rec::proto::Address_Field* add_field();
  inline const ::google::protobuf::RepeatedPtrField< ::rec::proto::Address_Field >&
      field() const;
  inline ::google::protobuf::RepeatedPtrField< ::rec::proto::Address_Field >*
      mutable_field();
  
  // @@protoc_insertion_point(class_scope:rec.proto.Address)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::google::protobuf::RepeatedPtrField< ::rec::proto::Address_Field > field_;
  friend void  protobuf_AddDesc_rec_2fdata_2fproto_2fAddress_2eproto();
  friend void protobuf_AssignDesc_rec_2fdata_2fproto_2fAddress_2eproto();
  friend void protobuf_ShutdownFile_rec_2fdata_2fproto_2fAddress_2eproto();
  
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
  static Address* default_instance_;
};
// ===================================================================


// ===================================================================

// Address_Field

// optional int32 index = 1;
inline bool Address_Field::has_index() const {
  return _has_bit(0);
}
inline void Address_Field::clear_index() {
  index_ = 0;
  _clear_bit(0);
}
inline ::google::protobuf::int32 Address_Field::index() const {
  return index_;
}
inline void Address_Field::set_index(::google::protobuf::int32 value) {
  _set_bit(0);
  index_ = value;
}

// optional string name = 2;
inline bool Address_Field::has_name() const {
  return _has_bit(1);
}
inline void Address_Field::clear_name() {
  if (name_ != &_default_name_) {
    name_->clear();
  }
  _clear_bit(1);
}
inline const ::std::string& Address_Field::name() const {
  return *name_;
}
inline void Address_Field::set_name(const ::std::string& value) {
  _set_bit(1);
  if (name_ == &_default_name_) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Address_Field::set_name(const char* value) {
  _set_bit(1);
  if (name_ == &_default_name_) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Address_Field::set_name(const char* value, size_t size) {
  _set_bit(1);
  if (name_ == &_default_name_) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Address_Field::mutable_name() {
  _set_bit(1);
  if (name_ == &_default_name_) {
    name_ = new ::std::string;
  }
  return name_;
}

// -------------------------------------------------------------------

// Address

// repeated .rec.proto.Address.Field field = 1;
inline int Address::field_size() const {
  return field_.size();
}
inline void Address::clear_field() {
  field_.Clear();
}
inline const ::rec::proto::Address_Field& Address::field(int index) const {
  return field_.Get(index);
}
inline ::rec::proto::Address_Field* Address::mutable_field(int index) {
  return field_.Mutable(index);
}
inline ::rec::proto::Address_Field* Address::add_field() {
  return field_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::rec::proto::Address_Field >&
Address::field() const {
  return field_;
}
inline ::google::protobuf::RepeatedPtrField< ::rec::proto::Address_Field >*
Address::mutable_field() {
  return &field_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2fdata_2fproto_2fAddress_2eproto__INCLUDED
