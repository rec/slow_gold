// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/data/proto/Address.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/data/proto/Address.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace rec {
namespace data {

namespace {

const ::google::protobuf::Descriptor* AddressProto_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  AddressProto_reflection_ = NULL;
const ::google::protobuf::Descriptor* AddressProto_Part_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  AddressProto_Part_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* AddressProto_Scope_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2fdata_2fproto_2fAddress_2eproto() {
  protobuf_AddDesc_rec_2fdata_2fproto_2fAddress_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/data/proto/Address.proto");
  GOOGLE_CHECK(file != NULL);
  AddressProto_descriptor_ = file->message_type(0);
  static const int AddressProto_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AddressProto, part_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AddressProto, scope_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AddressProto, type_name_),
  };
  AddressProto_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      AddressProto_descriptor_,
      AddressProto::default_instance_,
      AddressProto_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AddressProto, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AddressProto, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(AddressProto));
  AddressProto_Part_descriptor_ = AddressProto_descriptor_->nested_type(0);
  static const int AddressProto_Part_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AddressProto_Part, index_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AddressProto_Part, name_),
  };
  AddressProto_Part_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      AddressProto_Part_descriptor_,
      AddressProto_Part::default_instance_,
      AddressProto_Part_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AddressProto_Part, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AddressProto_Part, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(AddressProto_Part));
  AddressProto_Scope_descriptor_ = AddressProto_descriptor_->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2fdata_2fproto_2fAddress_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    AddressProto_descriptor_, &AddressProto::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    AddressProto_Part_descriptor_, &AddressProto_Part::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2fdata_2fproto_2fAddress_2eproto() {
  delete AddressProto::default_instance_;
  delete AddressProto_reflection_;
  delete AddressProto_Part::default_instance_;
  delete AddressProto_Part_reflection_;
}

void protobuf_AddDesc_rec_2fdata_2fproto_2fAddress_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\034rec/data/proto/Address.proto\022\010rec.data"
    "\"\311\001\n\014AddressProto\022)\n\004part\030\001 \003(\0132\033.rec.da"
    "ta.AddressProto.Part\022+\n\005scope\030\002 \001(\0162\034.re"
    "c.data.AddressProto.Scope\022\021\n\ttype_name\030\003"
    " \001(\t\032#\n\004Part\022\r\n\005index\030\001 \001(\r\022\014\n\004name\030\002 \001("
    "\t\")\n\005Scope\022\016\n\nFILE_SCOPE\020\000\022\020\n\014GLOBAL_SCO"
    "PE\020\001", 244);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/data/proto/Address.proto", &protobuf_RegisterTypes);
  AddressProto::default_instance_ = new AddressProto();
  AddressProto_Part::default_instance_ = new AddressProto_Part();
  AddressProto::default_instance_->InitAsDefaultInstance();
  AddressProto_Part::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2fdata_2fproto_2fAddress_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2fdata_2fproto_2fAddress_2eproto {
  StaticDescriptorInitializer_rec_2fdata_2fproto_2fAddress_2eproto() {
    protobuf_AddDesc_rec_2fdata_2fproto_2fAddress_2eproto();
  }
} static_descriptor_initializer_rec_2fdata_2fproto_2fAddress_2eproto_;

// ===================================================================

const ::google::protobuf::EnumDescriptor* AddressProto_Scope_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return AddressProto_Scope_descriptor_;
}
bool AddressProto_Scope_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const AddressProto_Scope AddressProto::FILE_SCOPE;
const AddressProto_Scope AddressProto::GLOBAL_SCOPE;
const AddressProto_Scope AddressProto::Scope_MIN;
const AddressProto_Scope AddressProto::Scope_MAX;
const int AddressProto::Scope_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int AddressProto_Part::kIndexFieldNumber;
const int AddressProto_Part::kNameFieldNumber;
#endif  // !_MSC_VER

AddressProto_Part::AddressProto_Part()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void AddressProto_Part::InitAsDefaultInstance() {
}

AddressProto_Part::AddressProto_Part(const AddressProto_Part& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void AddressProto_Part::SharedCtor() {
  _cached_size_ = 0;
  index_ = 0u;
  name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

AddressProto_Part::~AddressProto_Part() {
  SharedDtor();
}

void AddressProto_Part::SharedDtor() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    delete name_;
  }
  if (this != default_instance_) {
  }
}

void AddressProto_Part::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* AddressProto_Part::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return AddressProto_Part_descriptor_;
}

const AddressProto_Part& AddressProto_Part::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fdata_2fproto_2fAddress_2eproto();
  return *default_instance_;
}

AddressProto_Part* AddressProto_Part::default_instance_ = NULL;

AddressProto_Part* AddressProto_Part::New() const {
  return new AddressProto_Part;
}

void AddressProto_Part::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    index_ = 0u;
    if (has_name()) {
      if (name_ != &::google::protobuf::internal::kEmptyString) {
        name_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool AddressProto_Part::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 index = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &index_)));
          set_has_index();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_name;
        break;
      }

      // optional string name = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
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

void AddressProto_Part::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional uint32 index = 1;
  if (has_index()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->index(), output);
  }

  // optional string name = 2;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->name(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* AddressProto_Part::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional uint32 index = 1;
  if (has_index()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->index(), target);
  }

  // optional string name = 2;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->name(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int AddressProto_Part::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint32 index = 1;
    if (has_index()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->index());
    }

    // optional string name = 2;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->name());
    }

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

void AddressProto_Part::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const AddressProto_Part* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const AddressProto_Part*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void AddressProto_Part::MergeFrom(const AddressProto_Part& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_index()) {
      set_index(from.index());
    }
    if (from.has_name()) {
      set_name(from.name());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void AddressProto_Part::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AddressProto_Part::CopyFrom(const AddressProto_Part& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AddressProto_Part::IsInitialized() const {

  return true;
}

void AddressProto_Part::Swap(AddressProto_Part* other) {
  if (other != this) {
    std::swap(index_, other->index_);
    std::swap(name_, other->name_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata AddressProto_Part::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = AddressProto_Part_descriptor_;
  metadata.reflection = AddressProto_Part_reflection_;
  return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int AddressProto::kPartFieldNumber;
const int AddressProto::kScopeFieldNumber;
const int AddressProto::kTypeNameFieldNumber;
#endif  // !_MSC_VER

AddressProto::AddressProto()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void AddressProto::InitAsDefaultInstance() {
}

AddressProto::AddressProto(const AddressProto& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void AddressProto::SharedCtor() {
  _cached_size_ = 0;
  scope_ = 0;
  type_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

AddressProto::~AddressProto() {
  SharedDtor();
}

void AddressProto::SharedDtor() {
  if (type_name_ != &::google::protobuf::internal::kEmptyString) {
    delete type_name_;
  }
  if (this != default_instance_) {
  }
}

void AddressProto::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* AddressProto::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return AddressProto_descriptor_;
}

const AddressProto& AddressProto::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fdata_2fproto_2fAddress_2eproto();
  return *default_instance_;
}

AddressProto* AddressProto::default_instance_ = NULL;

AddressProto* AddressProto::New() const {
  return new AddressProto;
}

void AddressProto::Clear() {
  if (_has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    scope_ = 0;
    if (has_type_name()) {
      if (type_name_ != &::google::protobuf::internal::kEmptyString) {
        type_name_->clear();
      }
    }
  }
  part_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool AddressProto::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .rec.data.AddressProto.Part part = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_part:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_part()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_part;
        if (input->ExpectTag(16)) goto parse_scope;
        break;
      }

      // optional .rec.data.AddressProto.Scope scope = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_scope:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::rec::data::AddressProto_Scope_IsValid(value)) {
            set_scope(static_cast< ::rec::data::AddressProto_Scope >(value));
          } else {
            mutable_unknown_fields()->AddVarint(2, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_type_name;
        break;
      }

      // optional string type_name = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_type_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_type_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->type_name().data(), this->type_name().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
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

void AddressProto::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .rec.data.AddressProto.Part part = 1;
  for (int i = 0; i < this->part_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->part(i), output);
  }

  // optional .rec.data.AddressProto.Scope scope = 2;
  if (has_scope()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      2, this->scope(), output);
  }

  // optional string type_name = 3;
  if (has_type_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->type_name().data(), this->type_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->type_name(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* AddressProto::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .rec.data.AddressProto.Part part = 1;
  for (int i = 0; i < this->part_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->part(i), target);
  }

  // optional .rec.data.AddressProto.Scope scope = 2;
  if (has_scope()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      2, this->scope(), target);
  }

  // optional string type_name = 3;
  if (has_type_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->type_name().data(), this->type_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->type_name(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int AddressProto::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    // optional .rec.data.AddressProto.Scope scope = 2;
    if (has_scope()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->scope());
    }

    // optional string type_name = 3;
    if (has_type_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->type_name());
    }

  }
  // repeated .rec.data.AddressProto.Part part = 1;
  total_size += 1 * this->part_size();
  for (int i = 0; i < this->part_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->part(i));
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

void AddressProto::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const AddressProto* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const AddressProto*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void AddressProto::MergeFrom(const AddressProto& from) {
  GOOGLE_CHECK_NE(&from, this);
  part_.MergeFrom(from.part_);
  if (from._has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    if (from.has_scope()) {
      set_scope(from.scope());
    }
    if (from.has_type_name()) {
      set_type_name(from.type_name());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void AddressProto::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AddressProto::CopyFrom(const AddressProto& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AddressProto::IsInitialized() const {

  return true;
}

void AddressProto::Swap(AddressProto* other) {
  if (other != this) {
    part_.Swap(&other->part_);
    std::swap(scope_, other->scope_);
    std::swap(type_name_, other->type_name_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata AddressProto::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = AddressProto_descriptor_;
  metadata.reflection = AddressProto_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace data
}  // namespace rec

// @@protoc_insertion_point(global_scope)
