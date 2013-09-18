// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/gui/proto/Component.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/gui/proto/Component.pb.h"

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

const ::google::protobuf::Descriptor* ComponentProto_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ComponentProto_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2fgui_2fproto_2fComponent_2eproto() {
  protobuf_AddDesc_rec_2fgui_2fproto_2fComponent_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/gui/proto/Component.proto");
  GOOGLE_CHECK(file != NULL);
  ComponentProto_descriptor_ = file->message_type(0);
  static const int ComponentProto_offsets_[11] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ComponentProto, name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ComponentProto, preferred_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ComponentProto, min_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ComponentProto, max_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ComponentProto, color_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ComponentProto, button_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ComponentProto, combo_box_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ComponentProto, label_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ComponentProto, resizer_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ComponentProto, slider_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ComponentProto, toggle_button_),
  };
  ComponentProto_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ComponentProto_descriptor_,
      ComponentProto::default_instance_,
      ComponentProto_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ComponentProto, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ComponentProto, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ComponentProto));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2fgui_2fproto_2fComponent_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ComponentProto_descriptor_, &ComponentProto::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2fgui_2fproto_2fComponent_2eproto() {
  delete ComponentProto::default_instance_;
  delete ComponentProto_reflection_;
}

void protobuf_AddDesc_rec_2fgui_2fproto_2fComponent_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::rec::gui::protobuf_AddDesc_rec_2fgui_2fproto_2fButton_2eproto();
  ::rec::gui::protobuf_AddDesc_rec_2fgui_2fproto_2fComboBox_2eproto();
  ::rec::gui::protobuf_AddDesc_rec_2fgui_2fproto_2fLabel_2eproto();
  ::rec::gui::protobuf_AddDesc_rec_2fgui_2fproto_2fResizer_2eproto();
  ::rec::gui::protobuf_AddDesc_rec_2fgui_2fproto_2fSlider_2eproto();
  ::rec::gui::protobuf_AddDesc_rec_2fgui_2fproto_2fToggleButton_2eproto();
  ::rec::gui::protobuf_AddDesc_rec_2fgui_2fColor_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\035rec/gui/proto/Component.proto\022\007rec.gui"
    "\032\032rec/gui/proto/Button.proto\032\034rec/gui/pr"
    "oto/ComboBox.proto\032\031rec/gui/proto/Label."
    "proto\032\033rec/gui/proto/Resizer.proto\032\032rec/"
    "gui/proto/Slider.proto\032 rec/gui/proto/To"
    "ggleButton.proto\032\023rec/gui/Color.proto\"\340\002"
    "\n\016ComponentProto\022\014\n\004name\030\001 \001(\t\022\021\n\tprefer"
    "red\030\002 \001(\t\022\013\n\003min\030\003 \001(\t\022\013\n\003max\030\004 \001(\t\022\035\n\005c"
    "olor\030\005 \003(\0132\016.rec.gui.Color\022$\n\006button\030\006 \001"
    "(\0132\024.rec.gui.ButtonProto\022)\n\tcombo_box\030\007 "
    "\001(\0132\026.rec.gui.ComboBoxProto\022\"\n\005label\030\010 \001"
    "(\0132\023.rec.gui.LabelProto\022&\n\007resizer\030\t \001(\013"
    "2\025.rec.gui.ResizerProto\022$\n\006slider\030\n \001(\0132"
    "\024.rec.gui.SliderProto\0221\n\rtoggle_button\030\013"
    " \001(\0132\032.rec.gui.ToggleButtonProto", 592);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/gui/proto/Component.proto", &protobuf_RegisterTypes);
  ComponentProto::default_instance_ = new ComponentProto();
  ComponentProto::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2fgui_2fproto_2fComponent_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2fgui_2fproto_2fComponent_2eproto {
  StaticDescriptorInitializer_rec_2fgui_2fproto_2fComponent_2eproto() {
    protobuf_AddDesc_rec_2fgui_2fproto_2fComponent_2eproto();
  }
} static_descriptor_initializer_rec_2fgui_2fproto_2fComponent_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int ComponentProto::kNameFieldNumber;
const int ComponentProto::kPreferredFieldNumber;
const int ComponentProto::kMinFieldNumber;
const int ComponentProto::kMaxFieldNumber;
const int ComponentProto::kColorFieldNumber;
const int ComponentProto::kButtonFieldNumber;
const int ComponentProto::kComboBoxFieldNumber;
const int ComponentProto::kLabelFieldNumber;
const int ComponentProto::kResizerFieldNumber;
const int ComponentProto::kSliderFieldNumber;
const int ComponentProto::kToggleButtonFieldNumber;
#endif  // !_MSC_VER

ComponentProto::ComponentProto()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void ComponentProto::InitAsDefaultInstance() {
  button_ = const_cast< ::rec::gui::ButtonProto*>(&::rec::gui::ButtonProto::default_instance());
  combo_box_ = const_cast< ::rec::gui::ComboBoxProto*>(&::rec::gui::ComboBoxProto::default_instance());
  label_ = const_cast< ::rec::gui::LabelProto*>(&::rec::gui::LabelProto::default_instance());
  resizer_ = const_cast< ::rec::gui::ResizerProto*>(&::rec::gui::ResizerProto::default_instance());
  slider_ = const_cast< ::rec::gui::SliderProto*>(&::rec::gui::SliderProto::default_instance());
  toggle_button_ = const_cast< ::rec::gui::ToggleButtonProto*>(&::rec::gui::ToggleButtonProto::default_instance());
}

ComponentProto::ComponentProto(const ComponentProto& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void ComponentProto::SharedCtor() {
  _cached_size_ = 0;
  name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  preferred_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  min_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  max_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  button_ = NULL;
  combo_box_ = NULL;
  label_ = NULL;
  resizer_ = NULL;
  slider_ = NULL;
  toggle_button_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ComponentProto::~ComponentProto() {
  SharedDtor();
}

void ComponentProto::SharedDtor() {
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
    delete button_;
    delete combo_box_;
    delete label_;
    delete resizer_;
    delete slider_;
    delete toggle_button_;
  }
}

void ComponentProto::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ComponentProto::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ComponentProto_descriptor_;
}

const ComponentProto& ComponentProto::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fgui_2fproto_2fComponent_2eproto();
  return *default_instance_;
}

ComponentProto* ComponentProto::default_instance_ = NULL;

ComponentProto* ComponentProto::New() const {
  return new ComponentProto;
}

void ComponentProto::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_name()) {
      if (name_ != &::google::protobuf::internal::kEmptyString) {
        name_->clear();
      }
    }
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
    if (has_button()) {
      if (button_ != NULL) button_->::rec::gui::ButtonProto::Clear();
    }
    if (has_combo_box()) {
      if (combo_box_ != NULL) combo_box_->::rec::gui::ComboBoxProto::Clear();
    }
    if (has_label()) {
      if (label_ != NULL) label_->::rec::gui::LabelProto::Clear();
    }
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (has_resizer()) {
      if (resizer_ != NULL) resizer_->::rec::gui::ResizerProto::Clear();
    }
    if (has_slider()) {
      if (slider_ != NULL) slider_->::rec::gui::SliderProto::Clear();
    }
    if (has_toggle_button()) {
      if (toggle_button_ != NULL) toggle_button_->::rec::gui::ToggleButtonProto::Clear();
    }
  }
  color_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ComponentProto::MergePartialFromCodedStream(
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
        if (input->ExpectTag(18)) goto parse_preferred;
        break;
      }

      // optional string preferred = 2;
      case 2: {
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
        if (input->ExpectTag(26)) goto parse_min;
        break;
      }

      // optional string min = 3;
      case 3: {
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
        if (input->ExpectTag(34)) goto parse_max;
        break;
      }

      // optional string max = 4;
      case 4: {
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
        if (input->ExpectTag(42)) goto parse_color;
        break;
      }

      // repeated .rec.gui.Color color = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_color:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_color()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(42)) goto parse_color;
        if (input->ExpectTag(50)) goto parse_button;
        break;
      }

      // optional .rec.gui.ButtonProto button = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_button:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_button()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(58)) goto parse_combo_box;
        break;
      }

      // optional .rec.gui.ComboBoxProto combo_box = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_combo_box:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_combo_box()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(66)) goto parse_label;
        break;
      }

      // optional .rec.gui.LabelProto label = 8;
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_label:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_label()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(74)) goto parse_resizer;
        break;
      }

      // optional .rec.gui.ResizerProto resizer = 9;
      case 9: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_resizer:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_resizer()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(82)) goto parse_slider;
        break;
      }

      // optional .rec.gui.SliderProto slider = 10;
      case 10: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_slider:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_slider()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(90)) goto parse_toggle_button;
        break;
      }

      // optional .rec.gui.ToggleButtonProto toggle_button = 11;
      case 11: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_toggle_button:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_toggle_button()));
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

void ComponentProto::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional string name = 1;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->name(), output);
  }

  // optional string preferred = 2;
  if (has_preferred()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->preferred().data(), this->preferred().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->preferred(), output);
  }

  // optional string min = 3;
  if (has_min()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->min().data(), this->min().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->min(), output);
  }

  // optional string max = 4;
  if (has_max()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->max().data(), this->max().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      4, this->max(), output);
  }

  // repeated .rec.gui.Color color = 5;
  for (int i = 0; i < this->color_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      5, this->color(i), output);
  }

  // optional .rec.gui.ButtonProto button = 6;
  if (has_button()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      6, this->button(), output);
  }

  // optional .rec.gui.ComboBoxProto combo_box = 7;
  if (has_combo_box()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      7, this->combo_box(), output);
  }

  // optional .rec.gui.LabelProto label = 8;
  if (has_label()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      8, this->label(), output);
  }

  // optional .rec.gui.ResizerProto resizer = 9;
  if (has_resizer()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      9, this->resizer(), output);
  }

  // optional .rec.gui.SliderProto slider = 10;
  if (has_slider()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      10, this->slider(), output);
  }

  // optional .rec.gui.ToggleButtonProto toggle_button = 11;
  if (has_toggle_button()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      11, this->toggle_button(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* ComponentProto::SerializeWithCachedSizesToArray(
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

  // optional string preferred = 2;
  if (has_preferred()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->preferred().data(), this->preferred().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->preferred(), target);
  }

  // optional string min = 3;
  if (has_min()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->min().data(), this->min().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->min(), target);
  }

  // optional string max = 4;
  if (has_max()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->max().data(), this->max().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->max(), target);
  }

  // repeated .rec.gui.Color color = 5;
  for (int i = 0; i < this->color_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        5, this->color(i), target);
  }

  // optional .rec.gui.ButtonProto button = 6;
  if (has_button()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        6, this->button(), target);
  }

  // optional .rec.gui.ComboBoxProto combo_box = 7;
  if (has_combo_box()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        7, this->combo_box(), target);
  }

  // optional .rec.gui.LabelProto label = 8;
  if (has_label()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        8, this->label(), target);
  }

  // optional .rec.gui.ResizerProto resizer = 9;
  if (has_resizer()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        9, this->resizer(), target);
  }

  // optional .rec.gui.SliderProto slider = 10;
  if (has_slider()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        10, this->slider(), target);
  }

  // optional .rec.gui.ToggleButtonProto toggle_button = 11;
  if (has_toggle_button()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        11, this->toggle_button(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int ComponentProto::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string name = 1;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->name());
    }

    // optional string preferred = 2;
    if (has_preferred()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->preferred());
    }

    // optional string min = 3;
    if (has_min()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->min());
    }

    // optional string max = 4;
    if (has_max()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->max());
    }

    // optional .rec.gui.ButtonProto button = 6;
    if (has_button()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->button());
    }

    // optional .rec.gui.ComboBoxProto combo_box = 7;
    if (has_combo_box()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->combo_box());
    }

    // optional .rec.gui.LabelProto label = 8;
    if (has_label()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->label());
    }

  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // optional .rec.gui.ResizerProto resizer = 9;
    if (has_resizer()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->resizer());
    }

    // optional .rec.gui.SliderProto slider = 10;
    if (has_slider()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->slider());
    }

    // optional .rec.gui.ToggleButtonProto toggle_button = 11;
    if (has_toggle_button()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->toggle_button());
    }

  }
  // repeated .rec.gui.Color color = 5;
  total_size += 1 * this->color_size();
  for (int i = 0; i < this->color_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->color(i));
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

void ComponentProto::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ComponentProto* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ComponentProto*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ComponentProto::MergeFrom(const ComponentProto& from) {
  GOOGLE_CHECK_NE(&from, this);
  color_.MergeFrom(from.color_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_name()) {
      set_name(from.name());
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
    if (from.has_button()) {
      mutable_button()->::rec::gui::ButtonProto::MergeFrom(from.button());
    }
    if (from.has_combo_box()) {
      mutable_combo_box()->::rec::gui::ComboBoxProto::MergeFrom(from.combo_box());
    }
    if (from.has_label()) {
      mutable_label()->::rec::gui::LabelProto::MergeFrom(from.label());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from.has_resizer()) {
      mutable_resizer()->::rec::gui::ResizerProto::MergeFrom(from.resizer());
    }
    if (from.has_slider()) {
      mutable_slider()->::rec::gui::SliderProto::MergeFrom(from.slider());
    }
    if (from.has_toggle_button()) {
      mutable_toggle_button()->::rec::gui::ToggleButtonProto::MergeFrom(from.toggle_button());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ComponentProto::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ComponentProto::CopyFrom(const ComponentProto& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ComponentProto::IsInitialized() const {

  return true;
}

void ComponentProto::Swap(ComponentProto* other) {
  if (other != this) {
    std::swap(name_, other->name_);
    std::swap(preferred_, other->preferred_);
    std::swap(min_, other->min_);
    std::swap(max_, other->max_);
    color_.Swap(&other->color_);
    std::swap(button_, other->button_);
    std::swap(combo_box_, other->combo_box_);
    std::swap(label_, other->label_);
    std::swap(resizer_, other->resizer_);
    std::swap(slider_, other->slider_);
    std::swap(toggle_button_, other->toggle_button_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ComponentProto::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ComponentProto_descriptor_;
  metadata.reflection = ComponentProto_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace gui
}  // namespace rec

// @@protoc_insertion_point(global_scope)
