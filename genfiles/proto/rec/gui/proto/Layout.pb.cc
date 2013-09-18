// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/gui/proto/Layout.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/gui/proto/Layout.pb.h"

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

const ::google::protobuf::Descriptor* Layout_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Layout_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* Layout_Orientation_descriptor_ = NULL;
const ::google::protobuf::Descriptor* Layouts_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Layouts_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2fgui_2fproto_2fLayout_2eproto() {
  protobuf_AddDesc_rec_2fgui_2fproto_2fLayout_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/gui/proto/Layout.proto");
  GOOGLE_CHECK(file != NULL);
  Layout_descriptor_ = file->message_type(0);
  static const int Layout_offsets_[9] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Layout, name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Layout, orientation_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Layout, resize_other_dimension_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Layout, is_main_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Layout, padding_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Layout, preferred_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Layout, min_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Layout, max_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Layout, component_),
  };
  Layout_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Layout_descriptor_,
      Layout::default_instance_,
      Layout_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Layout, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Layout, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Layout));
  Layout_Orientation_descriptor_ = Layout_descriptor_->enum_type(0);
  Layouts_descriptor_ = file->message_type(1);
  static const int Layouts_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Layouts, layout_),
  };
  Layouts_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Layouts_descriptor_,
      Layouts::default_instance_,
      Layouts_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Layouts, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Layouts, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Layouts));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2fgui_2fproto_2fLayout_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Layout_descriptor_, &Layout::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Layouts_descriptor_, &Layouts::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2fgui_2fproto_2fLayout_2eproto() {
  delete Layout::default_instance_;
  delete Layout_reflection_;
  delete Layouts::default_instance_;
  delete Layouts_reflection_;
}

void protobuf_AddDesc_rec_2fgui_2fproto_2fLayout_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::rec::gui::protobuf_AddDesc_rec_2fgui_2fproto_2fComponent_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\032rec/gui/proto/Layout.proto\022\007rec.gui\032\035r"
    "ec/gui/proto/Component.proto\"\226\002\n\006Layout\022"
    "\014\n\004name\030\001 \001(\t\0220\n\013orientation\030\002 \001(\0162\033.rec"
    ".gui.Layout.Orientation\022$\n\026resize_other_"
    "dimension\030\003 \001(\010:\004true\022\017\n\007is_main\030\004 \001(\010\022\017"
    "\n\007padding\030\005 \001(\010\022\021\n\tpreferred\030\006 \001(\t\022\013\n\003mi"
    "n\030\007 \001(\t\022\013\n\003max\030\010 \001(\t\022*\n\tcomponent\030\t \003(\0132"
    "\027.rec.gui.ComponentProto\"+\n\013Orientation\022"
    "\016\n\nHORIZONTAL\020\000\022\014\n\010VERTICAL\020\001\"*\n\007Layouts"
    "\022\037\n\006layout\030\001 \003(\0132\017.rec.gui.Layout", 393);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/gui/proto/Layout.proto", &protobuf_RegisterTypes);
  Layout::default_instance_ = new Layout();
  Layouts::default_instance_ = new Layouts();
  Layout::default_instance_->InitAsDefaultInstance();
  Layouts::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2fgui_2fproto_2fLayout_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2fgui_2fproto_2fLayout_2eproto {
  StaticDescriptorInitializer_rec_2fgui_2fproto_2fLayout_2eproto() {
    protobuf_AddDesc_rec_2fgui_2fproto_2fLayout_2eproto();
  }
} static_descriptor_initializer_rec_2fgui_2fproto_2fLayout_2eproto_;

// ===================================================================

const ::google::protobuf::EnumDescriptor* Layout_Orientation_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Layout_Orientation_descriptor_;
}
bool Layout_Orientation_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const Layout_Orientation Layout::HORIZONTAL;
const Layout_Orientation Layout::VERTICAL;
const Layout_Orientation Layout::Orientation_MIN;
const Layout_Orientation Layout::Orientation_MAX;
const int Layout::Orientation_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int Layout::kNameFieldNumber;
const int Layout::kOrientationFieldNumber;
const int Layout::kResizeOtherDimensionFieldNumber;
const int Layout::kIsMainFieldNumber;
const int Layout::kPaddingFieldNumber;
const int Layout::kPreferredFieldNumber;
const int Layout::kMinFieldNumber;
const int Layout::kMaxFieldNumber;
const int Layout::kComponentFieldNumber;
#endif  // !_MSC_VER

Layout::Layout()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Layout::InitAsDefaultInstance() {
}

Layout::Layout(const Layout& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Layout::SharedCtor() {
  _cached_size_ = 0;
  name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  orientation_ = 0;
  resize_other_dimension_ = true;
  is_main_ = false;
  padding_ = false;
  preferred_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  min_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  max_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Layout::~Layout() {
  SharedDtor();
}

void Layout::SharedDtor() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    delete name_;
  }
  if (preferred_ != &::google::protobuf::internal::kEmptyString) {
    delete preferred_;
  }
  if (min_ != &::google::protobuf::internal::kEmptyString) {
    delete min_;
  }
  if (max_ != &::google::protobuf::internal::kEmptyString) {
    delete max_;
  }
  if (this != default_instance_) {
  }
}

void Layout::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Layout::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Layout_descriptor_;
}

const Layout& Layout::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fgui_2fproto_2fLayout_2eproto();
  return *default_instance_;
}

Layout* Layout::default_instance_ = NULL;

Layout* Layout::New() const {
  return new Layout;
}

void Layout::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_name()) {
      if (name_ != &::google::protobuf::internal::kEmptyString) {
        name_->clear();
      }
    }
    orientation_ = 0;
    resize_other_dimension_ = true;
    is_main_ = false;
    padding_ = false;
    if (has_preferred()) {
      if (preferred_ != &::google::protobuf::internal::kEmptyString) {
        preferred_->clear();
      }
    }
    if (has_min()) {
      if (min_ != &::google::protobuf::internal::kEmptyString) {
        min_->clear();
      }
    }
    if (has_max()) {
      if (max_ != &::google::protobuf::internal::kEmptyString) {
        max_->clear();
      }
    }
  }
  component_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Layout::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string name = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_orientation;
        break;
      }

      // optional .rec.gui.Layout.Orientation orientation = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_orientation:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::rec::gui::Layout_Orientation_IsValid(value)) {
            set_orientation(static_cast< ::rec::gui::Layout_Orientation >(value));
          } else {
            mutable_unknown_fields()->AddVarint(2, value);
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
        if (input->ExpectTag(40)) goto parse_padding;
        break;
      }

      // optional bool padding = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_padding:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &padding_)));
          set_has_padding();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(50)) goto parse_preferred;
        break;
      }

      // optional string preferred = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_preferred:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_preferred()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->preferred().data(), this->preferred().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(58)) goto parse_min;
        break;
      }

      // optional string min = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_min:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_min()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->min().data(), this->min().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(66)) goto parse_max;
        break;
      }

      // optional string max = 8;
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_max:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_max()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->max().data(), this->max().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(74)) goto parse_component;
        break;
      }

      // repeated .rec.gui.ComponentProto component = 9;
      case 9: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_component:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_component()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(74)) goto parse_component;
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

void Layout::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional string name = 1;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->name(), output);
  }

  // optional .rec.gui.Layout.Orientation orientation = 2;
  if (has_orientation()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      2, this->orientation(), output);
  }

  // optional bool resize_other_dimension = 3 [default = true];
  if (has_resize_other_dimension()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(3, this->resize_other_dimension(), output);
  }

  // optional bool is_main = 4;
  if (has_is_main()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(4, this->is_main(), output);
  }

  // optional bool padding = 5;
  if (has_padding()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(5, this->padding(), output);
  }

  // optional string preferred = 6;
  if (has_preferred()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->preferred().data(), this->preferred().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      6, this->preferred(), output);
  }

  // optional string min = 7;
  if (has_min()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->min().data(), this->min().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      7, this->min(), output);
  }

  // optional string max = 8;
  if (has_max()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->max().data(), this->max().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      8, this->max(), output);
  }

  // repeated .rec.gui.ComponentProto component = 9;
  for (int i = 0; i < this->component_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      9, this->component(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Layout::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional string name = 1;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->name(), target);
  }

  // optional .rec.gui.Layout.Orientation orientation = 2;
  if (has_orientation()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      2, this->orientation(), target);
  }

  // optional bool resize_other_dimension = 3 [default = true];
  if (has_resize_other_dimension()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(3, this->resize_other_dimension(), target);
  }

  // optional bool is_main = 4;
  if (has_is_main()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(4, this->is_main(), target);
  }

  // optional bool padding = 5;
  if (has_padding()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(5, this->padding(), target);
  }

  // optional string preferred = 6;
  if (has_preferred()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->preferred().data(), this->preferred().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        6, this->preferred(), target);
  }

  // optional string min = 7;
  if (has_min()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->min().data(), this->min().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        7, this->min(), target);
  }

  // optional string max = 8;
  if (has_max()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->max().data(), this->max().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        8, this->max(), target);
  }

  // repeated .rec.gui.ComponentProto component = 9;
  for (int i = 0; i < this->component_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        9, this->component(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Layout::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string name = 1;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->name());
    }

    // optional .rec.gui.Layout.Orientation orientation = 2;
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

    // optional bool padding = 5;
    if (has_padding()) {
      total_size += 1 + 1;
    }

    // optional string preferred = 6;
    if (has_preferred()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->preferred());
    }

    // optional string min = 7;
    if (has_min()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->min());
    }

    // optional string max = 8;
    if (has_max()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->max());
    }

  }
  // repeated .rec.gui.ComponentProto component = 9;
  total_size += 1 * this->component_size();
  for (int i = 0; i < this->component_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->component(i));
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

void Layout::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Layout* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Layout*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Layout::MergeFrom(const Layout& from) {
  GOOGLE_CHECK_NE(&from, this);
  component_.MergeFrom(from.component_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_name()) {
      set_name(from.name());
    }
    if (from.has_orientation()) {
      set_orientation(from.orientation());
    }
    if (from.has_resize_other_dimension()) {
      set_resize_other_dimension(from.resize_other_dimension());
    }
    if (from.has_is_main()) {
      set_is_main(from.is_main());
    }
    if (from.has_padding()) {
      set_padding(from.padding());
    }
    if (from.has_preferred()) {
      set_preferred(from.preferred());
    }
    if (from.has_min()) {
      set_min(from.min());
    }
    if (from.has_max()) {
      set_max(from.max());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Layout::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Layout::CopyFrom(const Layout& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Layout::IsInitialized() const {

  return true;
}

void Layout::Swap(Layout* other) {
  if (other != this) {
    std::swap(name_, other->name_);
    std::swap(orientation_, other->orientation_);
    std::swap(resize_other_dimension_, other->resize_other_dimension_);
    std::swap(is_main_, other->is_main_);
    std::swap(padding_, other->padding_);
    std::swap(preferred_, other->preferred_);
    std::swap(min_, other->min_);
    std::swap(max_, other->max_);
    component_.Swap(&other->component_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Layout::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Layout_descriptor_;
  metadata.reflection = Layout_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Layouts::kLayoutFieldNumber;
#endif  // !_MSC_VER

Layouts::Layouts()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Layouts::InitAsDefaultInstance() {
}

Layouts::Layouts(const Layouts& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Layouts::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Layouts::~Layouts() {
  SharedDtor();
}

void Layouts::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Layouts::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Layouts::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Layouts_descriptor_;
}

const Layouts& Layouts::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fgui_2fproto_2fLayout_2eproto();
  return *default_instance_;
}

Layouts* Layouts::default_instance_ = NULL;

Layouts* Layouts::New() const {
  return new Layouts;
}

void Layouts::Clear() {
  layout_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Layouts::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .rec.gui.Layout layout = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_layout:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_layout()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_layout;
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

void Layouts::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .rec.gui.Layout layout = 1;
  for (int i = 0; i < this->layout_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->layout(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Layouts::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .rec.gui.Layout layout = 1;
  for (int i = 0; i < this->layout_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->layout(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Layouts::ByteSize() const {
  int total_size = 0;

  // repeated .rec.gui.Layout layout = 1;
  total_size += 1 * this->layout_size();
  for (int i = 0; i < this->layout_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->layout(i));
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

void Layouts::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Layouts* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Layouts*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Layouts::MergeFrom(const Layouts& from) {
  GOOGLE_CHECK_NE(&from, this);
  layout_.MergeFrom(from.layout_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Layouts::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Layouts::CopyFrom(const Layouts& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Layouts::IsInitialized() const {

  return true;
}

void Layouts::Swap(Layouts* other) {
  if (other != this) {
    layout_.Swap(&other->layout_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Layouts::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Layouts_descriptor_;
  metadata.reflection = Layouts_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace gui
}  // namespace rec

// @@protoc_insertion_point(global_scope)
