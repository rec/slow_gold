// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/gui/proto/Panel.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/gui/proto/Panel.pb.h"

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

const ::google::protobuf::Descriptor* PanelProto_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  PanelProto_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* PanelProto_Orientation_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2fgui_2fproto_2fPanel_2eproto() {
  protobuf_AddDesc_rec_2fgui_2fproto_2fPanel_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/gui/proto/Panel.proto");
  GOOGLE_CHECK(file != NULL);
  PanelProto_descriptor_ = file->message_type(0);
  static const int PanelProto_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PanelProto, orientation_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PanelProto, resize_other_dimension_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PanelProto, is_main_),
  };
  PanelProto_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      PanelProto_descriptor_,
      PanelProto::default_instance_,
      PanelProto_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PanelProto, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PanelProto, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(PanelProto));
  PanelProto_Orientation_descriptor_ = PanelProto_descriptor_->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2fgui_2fproto_2fPanel_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    PanelProto_descriptor_, &PanelProto::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2fgui_2fproto_2fPanel_2eproto() {
  delete PanelProto::default_instance_;
  delete PanelProto_reflection_;
}

void protobuf_AddDesc_rec_2fgui_2fproto_2fPanel_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\031rec/gui/proto/Panel.proto\022\007rec.gui\"\246\001\n"
    "\nPanelProto\0224\n\013orientation\030\001 \001(\0162\037.rec.g"
    "ui.PanelProto.Orientation\022$\n\026resize_othe"
    "r_dimension\030\003 \001(\010:\004true\022\017\n\007is_main\030\004 \001(\010"
    "\"+\n\013Orientation\022\016\n\nHORIZONTAL\020\000\022\014\n\010VERTI"
    "CAL\020\001", 205);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/gui/proto/Panel.proto", &protobuf_RegisterTypes);
  PanelProto::default_instance_ = new PanelProto();
  PanelProto::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2fgui_2fproto_2fPanel_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2fgui_2fproto_2fPanel_2eproto {
  StaticDescriptorInitializer_rec_2fgui_2fproto_2fPanel_2eproto() {
    protobuf_AddDesc_rec_2fgui_2fproto_2fPanel_2eproto();
  }
} static_descriptor_initializer_rec_2fgui_2fproto_2fPanel_2eproto_;

// ===================================================================

const ::google::protobuf::EnumDescriptor* PanelProto_Orientation_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return PanelProto_Orientation_descriptor_;
}
bool PanelProto_Orientation_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const PanelProto_Orientation PanelProto::HORIZONTAL;
const PanelProto_Orientation PanelProto::VERTICAL;
const PanelProto_Orientation PanelProto::Orientation_MIN;
const PanelProto_Orientation PanelProto::Orientation_MAX;
const int PanelProto::Orientation_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int PanelProto::kOrientationFieldNumber;
const int PanelProto::kResizeOtherDimensionFieldNumber;
const int PanelProto::kIsMainFieldNumber;
#endif  // !_MSC_VER

PanelProto::PanelProto()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void PanelProto::InitAsDefaultInstance() {
}

PanelProto::PanelProto(const PanelProto& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void PanelProto::SharedCtor() {
  _cached_size_ = 0;
  orientation_ = 0;
  resize_other_dimension_ = true;
  is_main_ = false;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

PanelProto::~PanelProto() {
  SharedDtor();
}

void PanelProto::SharedDtor() {
  if (this != default_instance_) {
  }
}

void PanelProto::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* PanelProto::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return PanelProto_descriptor_;
}

const PanelProto& PanelProto::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fgui_2fproto_2fPanel_2eproto();
  return *default_instance_;
}

PanelProto* PanelProto::default_instance_ = NULL;

PanelProto* PanelProto::New() const {
  return new PanelProto;
}

void PanelProto::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    orientation_ = 0;
    resize_other_dimension_ = true;
    is_main_ = false;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool PanelProto::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .rec.gui.PanelProto.Orientation orientation = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::rec::gui::PanelProto_Orientation_IsValid(value)) {
            set_orientation(static_cast< ::rec::gui::PanelProto_Orientation >(value));
          } else {
            mutable_unknown_fields()->AddVarint(1, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_resize_other_dimension;
        break;
      }

      // optional bool resize_other_dimension = 3 [default = true];
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_resize_other_dimension:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &resize_other_dimension_)));
          set_has_resize_other_dimension();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_is_main;
        break;
      }

      // optional bool is_main = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_is_main:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &is_main_)));
          set_has_is_main();
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

void PanelProto::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .rec.gui.PanelProto.Orientation orientation = 1;
  if (has_orientation()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->orientation(), output);
  }

  // optional bool resize_other_dimension = 3 [default = true];
  if (has_resize_other_dimension()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(3, this->resize_other_dimension(), output);
  }

  // optional bool is_main = 4;
  if (has_is_main()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(4, this->is_main(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* PanelProto::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .rec.gui.PanelProto.Orientation orientation = 1;
  if (has_orientation()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->orientation(), target);
  }

  // optional bool resize_other_dimension = 3 [default = true];
  if (has_resize_other_dimension()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(3, this->resize_other_dimension(), target);
  }

  // optional bool is_main = 4;
  if (has_is_main()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(4, this->is_main(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int PanelProto::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .rec.gui.PanelProto.Orientation orientation = 1;
    if (has_orientation()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->orientation());
    }

    // optional bool resize_other_dimension = 3 [default = true];
    if (has_resize_other_dimension()) {
      total_size += 1 + 1;
    }

    // optional bool is_main = 4;
    if (has_is_main()) {
      total_size += 1 + 1;
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

void PanelProto::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const PanelProto* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const PanelProto*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void PanelProto::MergeFrom(const PanelProto& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_orientation()) {
      set_orientation(from.orientation());
    }
    if (from.has_resize_other_dimension()) {
      set_resize_other_dimension(from.resize_other_dimension());
    }
    if (from.has_is_main()) {
      set_is_main(from.is_main());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void PanelProto::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void PanelProto::CopyFrom(const PanelProto& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PanelProto::IsInitialized() const {

  return true;
}

void PanelProto::Swap(PanelProto* other) {
  if (other != this) {
    std::swap(orientation_, other->orientation_);
    std::swap(resize_other_dimension_, other->resize_other_dimension_);
    std::swap(is_main_, other->is_main_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata PanelProto::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = PanelProto_descriptor_;
  metadata.reflection = PanelProto_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace gui
}  // namespace rec

// @@protoc_insertion_point(global_scope)
