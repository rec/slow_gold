// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/gui/proto/Resizer.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/gui/proto/Resizer.pb.h"

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
namespace gui {

namespace {

const ::google::protobuf::Descriptor* ResizerProto_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ResizerProto_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2fgui_2fproto_2fResizer_2eproto() {
  protobuf_AddDesc_rec_2fgui_2fproto_2fResizer_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/gui/proto/Resizer.proto");
  GOOGLE_CHECK(file != NULL);
  ResizerProto_descriptor_ = file->message_type(0);
  static const int ResizerProto_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ResizerProto, size_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ResizerProto, min_value_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ResizerProto, address_),
  };
  ResizerProto_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ResizerProto_descriptor_,
      ResizerProto::default_instance_,
      ResizerProto_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ResizerProto, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ResizerProto, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ResizerProto));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2fgui_2fproto_2fResizer_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ResizerProto_descriptor_, &ResizerProto::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2fgui_2fproto_2fResizer_2eproto() {
  delete ResizerProto::default_instance_;
  delete ResizerProto_reflection_;
}

void protobuf_AddDesc_rec_2fgui_2fproto_2fResizer_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::rec::data::protobuf_AddDesc_rec_2fdata_2fproto_2fAddress_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\033rec/gui/proto/Resizer.proto\022\007rec.gui\032\034"
    "rec/data/proto/Address.proto\"X\n\014ResizerP"
    "roto\022\014\n\004size\030\001 \001(\t\022\021\n\tmin_value\030\002 \001(\t\022\'\n"
    "\007address\030\003 \001(\0132\026.rec.data.AddressProto", 158);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/gui/proto/Resizer.proto", &protobuf_RegisterTypes);
  ResizerProto::default_instance_ = new ResizerProto();
  ResizerProto::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2fgui_2fproto_2fResizer_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2fgui_2fproto_2fResizer_2eproto {
  StaticDescriptorInitializer_rec_2fgui_2fproto_2fResizer_2eproto() {
    protobuf_AddDesc_rec_2fgui_2fproto_2fResizer_2eproto();
  }
} static_descriptor_initializer_rec_2fgui_2fproto_2fResizer_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int ResizerProto::kSizeFieldNumber;
const int ResizerProto::kMinValueFieldNumber;
const int ResizerProto::kAddressFieldNumber;
#endif  // !_MSC_VER

ResizerProto::ResizerProto()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void ResizerProto::InitAsDefaultInstance() {
  address_ = const_cast< ::rec::data::AddressProto*>(&::rec::data::AddressProto::default_instance());
}

ResizerProto::ResizerProto(const ResizerProto& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void ResizerProto::SharedCtor() {
  _cached_size_ = 0;
  size_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  min_value_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  address_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ResizerProto::~ResizerProto() {
  SharedDtor();
}

void ResizerProto::SharedDtor() {
  if (size_ != &::google::protobuf::internal::kEmptyString) {
    delete size_;
  }
  if (min_value_ != &::google::protobuf::internal::kEmptyString) {
    delete min_value_;
  }
  if (this != default_instance_) {
    delete address_;
  }
}

void ResizerProto::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ResizerProto::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ResizerProto_descriptor_;
}

const ResizerProto& ResizerProto::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fgui_2fproto_2fResizer_2eproto();
  return *default_instance_;
}

ResizerProto* ResizerProto::default_instance_ = NULL;

ResizerProto* ResizerProto::New() const {
  return new ResizerProto;
}

void ResizerProto::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_size()) {
      if (size_ != &::google::protobuf::internal::kEmptyString) {
        size_->clear();
      }
    }
    if (has_min_value()) {
      if (min_value_ != &::google::protobuf::internal::kEmptyString) {
        min_value_->clear();
      }
    }
    if (has_address()) {
      if (address_ != NULL) address_->::rec::data::AddressProto::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ResizerProto::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string size = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_size()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->size().data(), this->size().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_min_value;
        break;
      }

      // optional string min_value = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_min_value:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_min_value()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->min_value().data(), this->min_value().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_address;
        break;
      }

      // optional .rec.data.AddressProto address = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_address:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_address()));
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

void ResizerProto::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional string size = 1;
  if (has_size()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->size().data(), this->size().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->size(), output);
  }

  // optional string min_value = 2;
  if (has_min_value()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->min_value().data(), this->min_value().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->min_value(), output);
  }

  // optional .rec.data.AddressProto address = 3;
  if (has_address()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->address(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* ResizerProto::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional string size = 1;
  if (has_size()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->size().data(), this->size().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->size(), target);
  }

  // optional string min_value = 2;
  if (has_min_value()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->min_value().data(), this->min_value().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->min_value(), target);
  }

  // optional .rec.data.AddressProto address = 3;
  if (has_address()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->address(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int ResizerProto::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string size = 1;
    if (has_size()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->size());
    }

    // optional string min_value = 2;
    if (has_min_value()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->min_value());
    }

    // optional .rec.data.AddressProto address = 3;
    if (has_address()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->address());
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

void ResizerProto::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ResizerProto* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ResizerProto*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ResizerProto::MergeFrom(const ResizerProto& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_size()) {
      set_size(from.size());
    }
    if (from.has_min_value()) {
      set_min_value(from.min_value());
    }
    if (from.has_address()) {
      mutable_address()->::rec::data::AddressProto::MergeFrom(from.address());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ResizerProto::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ResizerProto::CopyFrom(const ResizerProto& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ResizerProto::IsInitialized() const {

  return true;
}

void ResizerProto::Swap(ResizerProto* other) {
  if (other != this) {
    std::swap(size_, other->size_);
    std::swap(min_value_, other->min_value_);
    std::swap(address_, other->address_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ResizerProto::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ResizerProto_descriptor_;
  metadata.reflection = ResizerProto_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace gui
}  // namespace rec

// @@protoc_insertion_point(global_scope)
