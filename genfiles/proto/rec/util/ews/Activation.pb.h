// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/util/ews/Activation.proto

#ifndef PROTOBUF_rec_2futil_2fews_2fActivation_2eproto__INCLUDED
#define PROTOBUF_rec_2futil_2fews_2fActivation_2eproto__INCLUDED

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
namespace util {
namespace ews {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2futil_2fews_2fActivation_2eproto();
void protobuf_AssignDesc_rec_2futil_2fews_2fActivation_2eproto();
void protobuf_ShutdownFile_rec_2futil_2fews_2fActivation_2eproto();

class Activation;

// ===================================================================

class Activation : public ::google::protobuf::Message {
 public:
  Activation();
  virtual ~Activation();

  Activation(const Activation& from);

  inline Activation& operator=(const Activation& from) {
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
  static const Activation& default_instance();

  void Swap(Activation* other);

  // implements Message ----------------------------------------------

  Activation* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Activation& from);
  void MergeFrom(const Activation& from);
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

  // optional string samples = 1;
  inline bool has_samples() const;
  inline void clear_samples();
  static const int kSamplesFieldNumber = 1;
  inline const ::std::string& samples() const;
  inline void set_samples(const ::std::string& value);
  inline void set_samples(const char* value);
  inline void set_samples(const char* value, size_t size);
  inline ::std::string* mutable_samples();
  inline ::std::string* release_samples();
  inline void set_allocated_samples(::std::string* samples);

  // optional string rate = 2;
  inline bool has_rate() const;
  inline void clear_rate();
  static const int kRateFieldNumber = 2;
  inline const ::std::string& rate() const;
  inline void set_rate(const ::std::string& value);
  inline void set_rate(const char* value);
  inline void set_rate(const char* value, size_t size);
  inline ::std::string* mutable_rate();
  inline ::std::string* release_rate();
  inline void set_allocated_rate(::std::string* rate);

  // @@protoc_insertion_point(class_scope:rec.util.ews.Activation)
 private:
  inline void set_has_samples();
  inline void clear_has_samples();
  inline void set_has_rate();
  inline void clear_has_rate();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* samples_;
  ::std::string* rate_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_rec_2futil_2fews_2fActivation_2eproto();
  friend void protobuf_AssignDesc_rec_2futil_2fews_2fActivation_2eproto();
  friend void protobuf_ShutdownFile_rec_2futil_2fews_2fActivation_2eproto();

  void InitAsDefaultInstance();
  static Activation* default_instance_;
};
// ===================================================================


// ===================================================================

// Activation

// optional string samples = 1;
inline bool Activation::has_samples() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Activation::set_has_samples() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Activation::clear_has_samples() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Activation::clear_samples() {
  if (samples_ != &::google::protobuf::internal::kEmptyString) {
    samples_->clear();
  }
  clear_has_samples();
}
inline const ::std::string& Activation::samples() const {
  return *samples_;
}
inline void Activation::set_samples(const ::std::string& value) {
  set_has_samples();
  if (samples_ == &::google::protobuf::internal::kEmptyString) {
    samples_ = new ::std::string;
  }
  samples_->assign(value);
}
inline void Activation::set_samples(const char* value) {
  set_has_samples();
  if (samples_ == &::google::protobuf::internal::kEmptyString) {
    samples_ = new ::std::string;
  }
  samples_->assign(value);
}
inline void Activation::set_samples(const char* value, size_t size) {
  set_has_samples();
  if (samples_ == &::google::protobuf::internal::kEmptyString) {
    samples_ = new ::std::string;
  }
  samples_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Activation::mutable_samples() {
  set_has_samples();
  if (samples_ == &::google::protobuf::internal::kEmptyString) {
    samples_ = new ::std::string;
  }
  return samples_;
}
inline ::std::string* Activation::release_samples() {
  clear_has_samples();
  if (samples_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = samples_;
    samples_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Activation::set_allocated_samples(::std::string* samples) {
  if (samples_ != &::google::protobuf::internal::kEmptyString) {
    delete samples_;
  }
  if (samples) {
    set_has_samples();
    samples_ = samples;
  } else {
    clear_has_samples();
    samples_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional string rate = 2;
inline bool Activation::has_rate() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Activation::set_has_rate() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Activation::clear_has_rate() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Activation::clear_rate() {
  if (rate_ != &::google::protobuf::internal::kEmptyString) {
    rate_->clear();
  }
  clear_has_rate();
}
inline const ::std::string& Activation::rate() const {
  return *rate_;
}
inline void Activation::set_rate(const ::std::string& value) {
  set_has_rate();
  if (rate_ == &::google::protobuf::internal::kEmptyString) {
    rate_ = new ::std::string;
  }
  rate_->assign(value);
}
inline void Activation::set_rate(const char* value) {
  set_has_rate();
  if (rate_ == &::google::protobuf::internal::kEmptyString) {
    rate_ = new ::std::string;
  }
  rate_->assign(value);
}
inline void Activation::set_rate(const char* value, size_t size) {
  set_has_rate();
  if (rate_ == &::google::protobuf::internal::kEmptyString) {
    rate_ = new ::std::string;
  }
  rate_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Activation::mutable_rate() {
  set_has_rate();
  if (rate_ == &::google::protobuf::internal::kEmptyString) {
    rate_ = new ::std::string;
  }
  return rate_;
}
inline ::std::string* Activation::release_rate() {
  clear_has_rate();
  if (rate_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = rate_;
    rate_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Activation::set_allocated_rate(::std::string* rate) {
  if (rate_ != &::google::protobuf::internal::kEmptyString) {
    delete rate_;
  }
  if (rate) {
    set_has_rate();
    rate_ = rate;
  } else {
    clear_has_rate();
    rate_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ews
}  // namespace util
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2futil_2fews_2fActivation_2eproto__INCLUDED
