// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/command/CommandMap.proto

#ifndef PROTOBUF_rec_2fcommand_2fCommandMap_2eproto__INCLUDED
#define PROTOBUF_rec_2fcommand_2fCommandMap_2eproto__INCLUDED

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
#include "rec/command/Command.pb.h"
// @@protoc_insertion_point(includes)

namespace rec {
namespace command {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fcommand_2fCommandMap_2eproto();
void protobuf_AssignDesc_rec_2fcommand_2fCommandMap_2eproto();
void protobuf_ShutdownFile_rec_2fcommand_2fCommandMap_2eproto();

class CommandMapEntry;
class CommandMapProto;

// ===================================================================

class CommandMapEntry : public ::google::protobuf::Message {
 public:
  CommandMapEntry();
  virtual ~CommandMapEntry();
  
  CommandMapEntry(const CommandMapEntry& from);
  
  inline CommandMapEntry& operator=(const CommandMapEntry& from) {
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
  static const CommandMapEntry& default_instance();
  
  void Swap(CommandMapEntry* other);
  
  // implements Message ----------------------------------------------
  
  CommandMapEntry* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CommandMapEntry& from);
  void MergeFrom(const CommandMapEntry& from);
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
  
  // optional bytes key = 1;
  inline bool has_key() const;
  inline void clear_key();
  static const int kKeyFieldNumber = 1;
  inline const ::std::string& key() const;
  inline void set_key(const ::std::string& value);
  inline void set_key(const char* value);
  inline void set_key(const void* value, size_t size);
  inline ::std::string* mutable_key();
  
  // optional .rec.command.Command.Type command = 2;
  inline bool has_command() const;
  inline void clear_command();
  static const int kCommandFieldNumber = 2;
  inline ::rec::command::Command_Type command() const;
  inline void set_command(::rec::command::Command_Type value);
  
  // @@protoc_insertion_point(class_scope:rec.command.CommandMapEntry)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::std::string* key_;
  static const ::std::string _default_key_;
  int command_;
  friend void  protobuf_AddDesc_rec_2fcommand_2fCommandMap_2eproto();
  friend void protobuf_AssignDesc_rec_2fcommand_2fCommandMap_2eproto();
  friend void protobuf_ShutdownFile_rec_2fcommand_2fCommandMap_2eproto();
  
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
  static CommandMapEntry* default_instance_;
};
// -------------------------------------------------------------------

class CommandMapProto : public ::google::protobuf::Message {
 public:
  CommandMapProto();
  virtual ~CommandMapProto();
  
  CommandMapProto(const CommandMapProto& from);
  
  inline CommandMapProto& operator=(const CommandMapProto& from) {
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
  static const CommandMapProto& default_instance();
  
  void Swap(CommandMapProto* other);
  
  // implements Message ----------------------------------------------
  
  CommandMapProto* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CommandMapProto& from);
  void MergeFrom(const CommandMapProto& from);
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
  
  // repeated .rec.command.CommandMapEntry entry = 1;
  inline int entry_size() const;
  inline void clear_entry();
  static const int kEntryFieldNumber = 1;
  inline const ::rec::command::CommandMapEntry& entry(int index) const;
  inline ::rec::command::CommandMapEntry* mutable_entry(int index);
  inline ::rec::command::CommandMapEntry* add_entry();
  inline const ::google::protobuf::RepeatedPtrField< ::rec::command::CommandMapEntry >&
      entry() const;
  inline ::google::protobuf::RepeatedPtrField< ::rec::command::CommandMapEntry >*
      mutable_entry();
  
  // @@protoc_insertion_point(class_scope:rec.command.CommandMapProto)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::google::protobuf::RepeatedPtrField< ::rec::command::CommandMapEntry > entry_;
  friend void  protobuf_AddDesc_rec_2fcommand_2fCommandMap_2eproto();
  friend void protobuf_AssignDesc_rec_2fcommand_2fCommandMap_2eproto();
  friend void protobuf_ShutdownFile_rec_2fcommand_2fCommandMap_2eproto();
  
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
  static CommandMapProto* default_instance_;
};
// ===================================================================


// ===================================================================

// CommandMapEntry

// optional bytes key = 1;
inline bool CommandMapEntry::has_key() const {
  return _has_bit(0);
}
inline void CommandMapEntry::clear_key() {
  if (key_ != &_default_key_) {
    key_->clear();
  }
  _clear_bit(0);
}
inline const ::std::string& CommandMapEntry::key() const {
  return *key_;
}
inline void CommandMapEntry::set_key(const ::std::string& value) {
  _set_bit(0);
  if (key_ == &_default_key_) {
    key_ = new ::std::string;
  }
  key_->assign(value);
}
inline void CommandMapEntry::set_key(const char* value) {
  _set_bit(0);
  if (key_ == &_default_key_) {
    key_ = new ::std::string;
  }
  key_->assign(value);
}
inline void CommandMapEntry::set_key(const void* value, size_t size) {
  _set_bit(0);
  if (key_ == &_default_key_) {
    key_ = new ::std::string;
  }
  key_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* CommandMapEntry::mutable_key() {
  _set_bit(0);
  if (key_ == &_default_key_) {
    key_ = new ::std::string;
  }
  return key_;
}

// optional .rec.command.Command.Type command = 2;
inline bool CommandMapEntry::has_command() const {
  return _has_bit(1);
}
inline void CommandMapEntry::clear_command() {
  command_ = 0;
  _clear_bit(1);
}
inline ::rec::command::Command_Type CommandMapEntry::command() const {
  return static_cast< ::rec::command::Command_Type >(command_);
}
inline void CommandMapEntry::set_command(::rec::command::Command_Type value) {
  GOOGLE_DCHECK(::rec::command::Command_Type_IsValid(value));
  _set_bit(1);
  command_ = value;
}

// -------------------------------------------------------------------

// CommandMapProto

// repeated .rec.command.CommandMapEntry entry = 1;
inline int CommandMapProto::entry_size() const {
  return entry_.size();
}
inline void CommandMapProto::clear_entry() {
  entry_.Clear();
}
inline const ::rec::command::CommandMapEntry& CommandMapProto::entry(int index) const {
  return entry_.Get(index);
}
inline ::rec::command::CommandMapEntry* CommandMapProto::mutable_entry(int index) {
  return entry_.Mutable(index);
}
inline ::rec::command::CommandMapEntry* CommandMapProto::add_entry() {
  return entry_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::rec::command::CommandMapEntry >&
CommandMapProto::entry() const {
  return entry_;
}
inline ::google::protobuf::RepeatedPtrField< ::rec::command::CommandMapEntry >*
CommandMapProto::mutable_entry() {
  return &entry_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace command
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2fcommand_2fCommandMap_2eproto__INCLUDED