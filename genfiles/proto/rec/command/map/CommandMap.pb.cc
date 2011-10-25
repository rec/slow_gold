// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/command/map/CommandMap.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace rec {
namespace command {

namespace {

const ::google::protobuf::Descriptor* CommandMapEntry_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  CommandMapEntry_reflection_ = NULL;
const ::google::protobuf::Descriptor* CommandMapProto_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  CommandMapProto_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2fcommand_2fmap_2fCommandMap_2eproto() {
  protobuf_AddDesc_rec_2fcommand_2fmap_2fCommandMap_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/command/map/CommandMap.proto");
  GOOGLE_CHECK(file != NULL);
  CommandMapEntry_descriptor_ = file->message_type(0);
  static const int CommandMapEntry_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CommandMapEntry, command_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CommandMapEntry, key_),
  };
  CommandMapEntry_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      CommandMapEntry_descriptor_,
      CommandMapEntry::default_instance_,
      CommandMapEntry_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CommandMapEntry, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CommandMapEntry, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(CommandMapEntry));
  CommandMapProto_descriptor_ = file->message_type(1);
  static const int CommandMapProto_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CommandMapProto, entry_),
  };
  CommandMapProto_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      CommandMapProto_descriptor_,
      CommandMapProto::default_instance_,
      CommandMapProto_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CommandMapProto, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CommandMapProto, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(CommandMapProto));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2fcommand_2fmap_2fCommandMap_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    CommandMapEntry_descriptor_, &CommandMapEntry::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    CommandMapProto_descriptor_, &CommandMapProto::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2fcommand_2fmap_2fCommandMap_2eproto() {
  delete CommandMapEntry::default_instance_;
  delete CommandMapEntry_reflection_;
  delete CommandMapProto::default_instance_;
  delete CommandMapProto_reflection_;
}

void protobuf_AddDesc_rec_2fcommand_2fmap_2fCommandMap_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::rec::command::protobuf_AddDesc_rec_2fcommand_2fCommand_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n rec/command/map/CommandMap.proto\022\013rec."
    "command\032\031rec/command/Command.proto\"J\n\017Co"
    "mmandMapEntry\022*\n\007command\030\001 \001(\0162\031.rec.com"
    "mand.Command.Type\022\013\n\003key\030\002 \003(\014\">\n\017Comman"
    "dMapProto\022+\n\005entry\030\001 \003(\0132\034.rec.command.C"
    "ommandMapEntry", 214);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/command/map/CommandMap.proto", &protobuf_RegisterTypes);
  CommandMapEntry::default_instance_ = new CommandMapEntry();
  CommandMapProto::default_instance_ = new CommandMapProto();
  CommandMapEntry::default_instance_->InitAsDefaultInstance();
  CommandMapProto::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2fcommand_2fmap_2fCommandMap_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2fcommand_2fmap_2fCommandMap_2eproto {
  StaticDescriptorInitializer_rec_2fcommand_2fmap_2fCommandMap_2eproto() {
    protobuf_AddDesc_rec_2fcommand_2fmap_2fCommandMap_2eproto();
  }
} static_descriptor_initializer_rec_2fcommand_2fmap_2fCommandMap_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int CommandMapEntry::kCommandFieldNumber;
const int CommandMapEntry::kKeyFieldNumber;
#endif  // !_MSC_VER

CommandMapEntry::CommandMapEntry()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void CommandMapEntry::InitAsDefaultInstance() {
}

CommandMapEntry::CommandMapEntry(const CommandMapEntry& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void CommandMapEntry::SharedCtor() {
  _cached_size_ = 0;
  command_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

CommandMapEntry::~CommandMapEntry() {
  SharedDtor();
}

void CommandMapEntry::SharedDtor() {
  if (this != default_instance_) {
  }
}

void CommandMapEntry::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* CommandMapEntry::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return CommandMapEntry_descriptor_;
}

const CommandMapEntry& CommandMapEntry::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fcommand_2fmap_2fCommandMap_2eproto();  return *default_instance_;
}

CommandMapEntry* CommandMapEntry::default_instance_ = NULL;

CommandMapEntry* CommandMapEntry::New() const {
  return new CommandMapEntry;
}

void CommandMapEntry::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    command_ = 0;
  }
  key_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool CommandMapEntry::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .rec.command.Command.Type command = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::rec::command::Command_Type_IsValid(value)) {
            set_command(static_cast< ::rec::command::Command_Type >(value));
          } else {
            mutable_unknown_fields()->AddVarint(1, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_key;
        break;
      }
      
      // repeated bytes key = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_key:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->add_key()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_key;
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void CommandMapEntry::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .rec.command.Command.Type command = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->command(), output);
  }
  
  // repeated bytes key = 2;
  for (int i = 0; i < this->key_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteBytes(
      2, this->key(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* CommandMapEntry::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .rec.command.Command.Type command = 1;
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->command(), target);
  }
  
  // repeated bytes key = 2;
  for (int i = 0; i < this->key_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteBytesToArray(2, this->key(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int CommandMapEntry::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .rec.command.Command.Type command = 1;
    if (has_command()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->command());
    }
    
  }
  // repeated bytes key = 2;
  total_size += 1 * this->key_size();
  for (int i = 0; i < this->key_size(); i++) {
    total_size += ::google::protobuf::internal::WireFormatLite::BytesSize(
      this->key(i));
  }
  
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void CommandMapEntry::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const CommandMapEntry* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const CommandMapEntry*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void CommandMapEntry::MergeFrom(const CommandMapEntry& from) {
  GOOGLE_CHECK_NE(&from, this);
  key_.MergeFrom(from.key_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_command(from.command());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void CommandMapEntry::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void CommandMapEntry::CopyFrom(const CommandMapEntry& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CommandMapEntry::IsInitialized() const {
  
  return true;
}

void CommandMapEntry::Swap(CommandMapEntry* other) {
  if (other != this) {
    std::swap(command_, other->command_);
    key_.Swap(&other->key_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata CommandMapEntry::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = CommandMapEntry_descriptor_;
  metadata.reflection = CommandMapEntry_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int CommandMapProto::kEntryFieldNumber;
#endif  // !_MSC_VER

CommandMapProto::CommandMapProto()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void CommandMapProto::InitAsDefaultInstance() {
}

CommandMapProto::CommandMapProto(const CommandMapProto& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void CommandMapProto::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

CommandMapProto::~CommandMapProto() {
  SharedDtor();
}

void CommandMapProto::SharedDtor() {
  if (this != default_instance_) {
  }
}

void CommandMapProto::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* CommandMapProto::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return CommandMapProto_descriptor_;
}

const CommandMapProto& CommandMapProto::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fcommand_2fmap_2fCommandMap_2eproto();  return *default_instance_;
}

CommandMapProto* CommandMapProto::default_instance_ = NULL;

CommandMapProto* CommandMapProto::New() const {
  return new CommandMapProto;
}

void CommandMapProto::Clear() {
  entry_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool CommandMapProto::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .rec.command.CommandMapEntry entry = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_entry:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_entry()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_entry;
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void CommandMapProto::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .rec.command.CommandMapEntry entry = 1;
  for (int i = 0; i < this->entry_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->entry(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* CommandMapProto::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .rec.command.CommandMapEntry entry = 1;
  for (int i = 0; i < this->entry_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->entry(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int CommandMapProto::ByteSize() const {
  int total_size = 0;
  
  // repeated .rec.command.CommandMapEntry entry = 1;
  total_size += 1 * this->entry_size();
  for (int i = 0; i < this->entry_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->entry(i));
  }
  
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void CommandMapProto::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const CommandMapProto* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const CommandMapProto*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void CommandMapProto::MergeFrom(const CommandMapProto& from) {
  GOOGLE_CHECK_NE(&from, this);
  entry_.MergeFrom(from.entry_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void CommandMapProto::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void CommandMapProto::CopyFrom(const CommandMapProto& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CommandMapProto::IsInitialized() const {
  
  return true;
}

void CommandMapProto::Swap(CommandMapProto* other) {
  if (other != this) {
    entry_.Swap(&other->entry_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata CommandMapProto::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = CommandMapProto_descriptor_;
  metadata.reflection = CommandMapProto_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace command
}  // namespace rec

// @@protoc_insertion_point(global_scope)