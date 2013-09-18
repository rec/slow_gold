// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/gui/proto/Resizer.proto

#ifndef PROTOBUF_rec_2fgui_2fproto_2fResizer_2eproto__INCLUDED
#define PROTOBUF_rec_2fgui_2fproto_2fResizer_2eproto__INCLUDED

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
#include "rec/data/proto/Address.pb.h"
// @@protoc_insertion_point(includes)

namespace rec {
namespace gui {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fgui_2fproto_2fResizer_2eproto();
void protobuf_AssignDesc_rec_2fgui_2fproto_2fResizer_2eproto();
void protobuf_ShutdownFile_rec_2fgui_2fproto_2fResizer_2eproto();

class ResizerProto;

// ===================================================================

class ResizerProto : public ::google::protobuf::Message {
 public:
  ResizerProto();
  virtual ~ResizerProto();

  ResizerProto(const ResizerProto& from);

  inline ResizerProto& operator=(const ResizerProto& from) {
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
  static const ResizerProto& default_instance();

  void Swap(ResizerProto* other);

  // implements Message ----------------------------------------------

  ResizerProto* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ResizerProto& from);
  void MergeFrom(const ResizerProto& from);
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

  // optional string size = 1;
  inline bool has_size() const;
  inline void clear_size();
  static const int kSizeFieldNumber = 1;
  inline const ::std::string& size() const;
  inline void set_size(const ::std::string& value);
  inline void set_size(const char* value);
  inline void set_size(const char* value, size_t size);
  inline ::std::string* mutable_size();
  inline ::std::string* release_size();
  inline void set_allocated_size(::std::string* size);

  // optional string min_value = 2;
  inline bool has_min_value() const;
  inline void clear_min_value();
  static const int kMinValueFieldNumber = 2;
  inline const ::std::string& min_value() const;
  inline void set_min_value(const ::std::string& value);
  inline void set_min_value(const char* value);
  inline void set_min_value(const char* value, size_t size);
  inline ::std::string* mutable_min_value();
  inline ::std::string* release_min_value();
  inline void set_allocated_min_value(::std::string* min_value);

  // optional .rec.data.AddressProto address = 3;
  inline bool has_address() const;
  inline void clear_address();
  static const int kAddressFieldNumber = 3;
  inline const ::rec::data::AddressProto& address() const;
  inline ::rec::data::AddressProto* mutable_address();
  inline ::rec::data::AddressProto* release_address();
  inline void set_allocated_address(::rec::data::AddressProto* address);

  // @@protoc_insertion_point(class_scope:rec.gui.ResizerProto)
 private:
  inline void set_has_size();
  inline void clear_has_size();
  inline void set_has_min_value();
  inline void clear_has_min_value();
  inline void set_has_address();
  inline void clear_has_address();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* size_;
  ::std::string* min_value_;
  ::rec::data::AddressProto* address_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_rec_2fgui_2fproto_2fResizer_2eproto();
  friend void protobuf_AssignDesc_rec_2fgui_2fproto_2fResizer_2eproto();
  friend void protobuf_ShutdownFile_rec_2fgui_2fproto_2fResizer_2eproto();

  void InitAsDefaultInstance();
  static ResizerProto* default_instance_;
};
// ===================================================================


// ===================================================================

// ResizerProto

// optional string size = 1;
inline bool ResizerProto::has_size() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ResizerProto::set_has_size() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ResizerProto::clear_has_size() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ResizerProto::clear_size() {
  if (size_ != &::google::protobuf::internal::kEmptyString) {
    size_->clear();
  }
  clear_has_size();
}
inline const ::std::string& ResizerProto::size() const {
  return *size_;
}
inline void ResizerProto::set_size(const ::std::string& value) {
  set_has_size();
  if (size_ == &::google::protobuf::internal::kEmptyString) {
    size_ = new ::std::string;
  }
  size_->assign(value);
}
inline void ResizerProto::set_size(const char* value) {
  set_has_size();
  if (size_ == &::google::protobuf::internal::kEmptyString) {
    size_ = new ::std::string;
  }
  size_->assign(value);
}
inline void ResizerProto::set_size(const char* value, size_t size) {
  set_has_size();
  if (size_ == &::google::protobuf::internal::kEmptyString) {
    size_ = new ::std::string;
  }
  size_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* ResizerProto::mutable_size() {
  set_has_size();
  if (size_ == &::google::protobuf::internal::kEmptyString) {
    size_ = new ::std::string;
  }
  return size_;
}
inline ::std::string* ResizerProto::release_size() {
  clear_has_size();
  if (size_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = size_;
    size_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void ResizerProto::set_allocated_size(::std::string* size) {
  if (size_ != &::google::protobuf::internal::kEmptyString) {
    delete size_;
  }
  if (size) {
    set_has_size();
    size_ = size;
  } else {
    clear_has_size();
    size_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional string min_value = 2;
inline bool ResizerProto::has_min_value() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ResizerProto::set_has_min_value() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ResizerProto::clear_has_min_value() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ResizerProto::clear_min_value() {
  if (min_value_ != &::google::protobuf::internal::kEmptyString) {
    min_value_->clear();
  }
  clear_has_min_value();
}
inline const ::std::string& ResizerProto::min_value() const {
  return *min_value_;
}
inline void ResizerProto::set_min_value(const ::std::string& value) {
  set_has_min_value();
  if (min_value_ == &::google::protobuf::internal::kEmptyString) {
    min_value_ = new ::std::string;
  }
  min_value_->assign(value);
}
inline void ResizerProto::set_min_value(const char* value) {
  set_has_min_value();
  if (min_value_ == &::google::protobuf::internal::kEmptyString) {
    min_value_ = new ::std::string;
  }
  min_value_->assign(value);
}
inline void ResizerProto::set_min_value(const char* value, size_t size) {
  set_has_min_value();
  if (min_value_ == &::google::protobuf::internal::kEmptyString) {
    min_value_ = new ::std::string;
  }
  min_value_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* ResizerProto::mutable_min_value() {
  set_has_min_value();
  if (min_value_ == &::google::protobuf::internal::kEmptyString) {
    min_value_ = new ::std::string;
  }
  return min_value_;
}
inline ::std::string* ResizerProto::release_min_value() {
  clear_has_min_value();
  if (min_value_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = min_value_;
    min_value_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void ResizerProto::set_allocated_min_value(::std::string* min_value) {
  if (min_value_ != &::google::protobuf::internal::kEmptyString) {
    delete min_value_;
  }
  if (min_value) {
    set_has_min_value();
    min_value_ = min_value;
  } else {
    clear_has_min_value();
    min_value_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional .rec.data.AddressProto address = 3;
inline bool ResizerProto::has_address() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ResizerProto::set_has_address() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ResizerProto::clear_has_address() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ResizerProto::clear_address() {
  if (address_ != NULL) address_->::rec::data::AddressProto::Clear();
  clear_has_address();
}
inline const ::rec::data::AddressProto& ResizerProto::address() const {
  return address_ != NULL ? *address_ : *default_instance_->address_;
}
inline ::rec::data::AddressProto* ResizerProto::mutable_address() {
  set_has_address();
  if (address_ == NULL) address_ = new ::rec::data::AddressProto;
  return address_;
}
inline ::rec::data::AddressProto* ResizerProto::release_address() {
  clear_has_address();
  ::rec::data::AddressProto* temp = address_;
  address_ = NULL;
  return temp;
}
inline void ResizerProto::set_allocated_address(::rec::data::AddressProto* address) {
  delete address_;
  address_ = address;
  if (address) {
    set_has_address();
  } else {
    clear_has_address();
  }
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

#endif  // PROTOBUF_rec_2fgui_2fproto_2fResizer_2eproto__INCLUDED
