// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/util/thread/Thread.proto

#ifndef PROTOBUF_rec_2futil_2fthread_2fThread_2eproto__INCLUDED
#define PROTOBUF_rec_2futil_2fthread_2fThread_2eproto__INCLUDED

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
namespace thread {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2futil_2fthread_2fThread_2eproto();
void protobuf_AssignDesc_rec_2futil_2fthread_2fThread_2eproto();
void protobuf_ShutdownFile_rec_2futil_2fthread_2fThread_2eproto();

class ThreadDescription;

// ===================================================================

class ThreadDescription : public ::google::protobuf::Message {
 public:
  ThreadDescription();
  virtual ~ThreadDescription();
  
  ThreadDescription(const ThreadDescription& from);
  
  inline ThreadDescription& operator=(const ThreadDescription& from) {
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
  static const ThreadDescription& default_instance();
  
  void Swap(ThreadDescription* other);
  
  // implements Message ----------------------------------------------
  
  ThreadDescription* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ThreadDescription& from);
  void MergeFrom(const ThreadDescription& from);
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
  
  // optional uint32 priority = 1 [default = 4];
  inline bool has_priority() const;
  inline void clear_priority();
  static const int kPriorityFieldNumber = 1;
  inline ::google::protobuf::uint32 priority() const;
  inline void set_priority(::google::protobuf::uint32 value);
  
  // optional uint32 period = 2 [default = 100];
  inline bool has_period() const;
  inline void clear_period();
  static const int kPeriodFieldNumber = 2;
  inline ::google::protobuf::uint32 period() const;
  inline void set_period(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:rec.util.thread.ThreadDescription)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::google::protobuf::uint32 priority_;
  ::google::protobuf::uint32 period_;
  friend void  protobuf_AddDesc_rec_2futil_2fthread_2fThread_2eproto();
  friend void protobuf_AssignDesc_rec_2futil_2fthread_2fThread_2eproto();
  friend void protobuf_ShutdownFile_rec_2futil_2fthread_2fThread_2eproto();
  
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
  static ThreadDescription* default_instance_;
};
// ===================================================================


// ===================================================================

// ThreadDescription

// optional uint32 priority = 1 [default = 4];
inline bool ThreadDescription::has_priority() const {
  return _has_bit(0);
}
inline void ThreadDescription::clear_priority() {
  priority_ = 4u;
  _clear_bit(0);
}
inline ::google::protobuf::uint32 ThreadDescription::priority() const {
  return priority_;
}
inline void ThreadDescription::set_priority(::google::protobuf::uint32 value) {
  _set_bit(0);
  priority_ = value;
}

// optional uint32 period = 2 [default = 100];
inline bool ThreadDescription::has_period() const {
  return _has_bit(1);
}
inline void ThreadDescription::clear_period() {
  period_ = 100u;
  _clear_bit(1);
}
inline ::google::protobuf::uint32 ThreadDescription::period() const {
  return period_;
}
inline void ThreadDescription::set_period(::google::protobuf::uint32 value) {
  _set_bit(1);
  period_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace thread
}  // namespace util
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2futil_2fthread_2fThread_2eproto__INCLUDED
