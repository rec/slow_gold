// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/gui/proto/Component.proto

#ifndef PROTOBUF_rec_2fgui_2fproto_2fComponent_2eproto__INCLUDED
#define PROTOBUF_rec_2fgui_2fproto_2fComponent_2eproto__INCLUDED

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
#include "rec/gui/proto/Button.pb.h"
#include "rec/gui/proto/ComboBox.pb.h"
#include "rec/gui/proto/Custom.pb.h"
#include "rec/gui/proto/Font.pb.h"
#include "rec/gui/proto/Help.pb.h"
#include "rec/gui/proto/Label.pb.h"
#include "rec/gui/proto/Resizer.pb.h"
#include "rec/gui/proto/Size.pb.h"
#include "rec/gui/proto/Slider.pb.h"
#include "rec/gui/proto/Text.pb.h"
#include "rec/gui/proto/ToggleButton.pb.h"
#include "rec/gui/Color.pb.h"
// @@protoc_insertion_point(includes)

namespace rec {
namespace gui {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fgui_2fproto_2fComponent_2eproto();
void protobuf_AssignDesc_rec_2fgui_2fproto_2fComponent_2eproto();
void protobuf_ShutdownFile_rec_2fgui_2fproto_2fComponent_2eproto();

class ComponentProto;

// ===================================================================

class ComponentProto : public ::google::protobuf::Message {
 public:
  ComponentProto();
  virtual ~ComponentProto();

  ComponentProto(const ComponentProto& from);

  inline ComponentProto& operator=(const ComponentProto& from) {
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
  static const ComponentProto& default_instance();

  void Swap(ComponentProto* other);

  // implements Message ----------------------------------------------

  ComponentProto* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ComponentProto& from);
  void MergeFrom(const ComponentProto& from);
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

  // optional string name = 1;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 1;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // optional string tooltip = 2;
  inline bool has_tooltip() const;
  inline void clear_tooltip();
  static const int kTooltipFieldNumber = 2;
  inline const ::std::string& tooltip() const;
  inline void set_tooltip(const ::std::string& value);
  inline void set_tooltip(const char* value);
  inline void set_tooltip(const char* value, size_t size);
  inline ::std::string* mutable_tooltip();
  inline ::std::string* release_tooltip();
  inline void set_allocated_tooltip(::std::string* tooltip);

  // optional .rec.gui.Size size = 3;
  inline bool has_size() const;
  inline void clear_size();
  static const int kSizeFieldNumber = 3;
  inline const ::rec::gui::Size& size() const;
  inline ::rec::gui::Size* mutable_size();
  inline ::rec::gui::Size* release_size();
  inline void set_allocated_size(::rec::gui::Size* size);

  // optional .rec.data.AddressProto address = 4;
  inline bool has_address() const;
  inline void clear_address();
  static const int kAddressFieldNumber = 4;
  inline const ::rec::data::AddressProto& address() const;
  inline ::rec::data::AddressProto* mutable_address();
  inline ::rec::data::AddressProto* release_address();
  inline void set_allocated_address(::rec::data::AddressProto* address);

  // repeated .rec.gui.Color color = 5;
  inline int color_size() const;
  inline void clear_color();
  static const int kColorFieldNumber = 5;
  inline const ::rec::gui::Color& color(int index) const;
  inline ::rec::gui::Color* mutable_color(int index);
  inline ::rec::gui::Color* add_color();
  inline const ::google::protobuf::RepeatedPtrField< ::rec::gui::Color >&
      color() const;
  inline ::google::protobuf::RepeatedPtrField< ::rec::gui::Color >*
      mutable_color();

  // optional .rec.gui.FontProto font = 6;
  inline bool has_font() const;
  inline void clear_font();
  static const int kFontFieldNumber = 6;
  inline const ::rec::gui::FontProto& font() const;
  inline ::rec::gui::FontProto* mutable_font();
  inline ::rec::gui::FontProto* release_font();
  inline void set_allocated_font(::rec::gui::FontProto* font);

  // optional string layout = 17;
  inline bool has_layout() const;
  inline void clear_layout();
  static const int kLayoutFieldNumber = 17;
  inline const ::std::string& layout() const;
  inline void set_layout(const ::std::string& value);
  inline void set_layout(const char* value);
  inline void set_layout(const char* value, size_t size);
  inline ::std::string* mutable_layout();
  inline ::std::string* release_layout();
  inline void set_allocated_layout(::std::string* layout);

  // optional string resizer = 7;
  inline bool has_resizer() const;
  inline void clear_resizer();
  static const int kResizerFieldNumber = 7;
  inline const ::std::string& resizer() const;
  inline void set_resizer(const ::std::string& value);
  inline void set_resizer(const char* value);
  inline void set_resizer(const char* value, size_t size);
  inline ::std::string* mutable_resizer();
  inline ::std::string* release_resizer();
  inline void set_allocated_resizer(::std::string* resizer);

  // optional uint32 min_resizer = 18;
  inline bool has_min_resizer() const;
  inline void clear_min_resizer();
  static const int kMinResizerFieldNumber = 18;
  inline ::google::protobuf::uint32 min_resizer() const;
  inline void set_min_resizer(::google::protobuf::uint32 value);

  // optional .rec.gui.ButtonProto button = 8;
  inline bool has_button() const;
  inline void clear_button();
  static const int kButtonFieldNumber = 8;
  inline const ::rec::gui::ButtonProto& button() const;
  inline ::rec::gui::ButtonProto* mutable_button();
  inline ::rec::gui::ButtonProto* release_button();
  inline void set_allocated_button(::rec::gui::ButtonProto* button);

  // optional .rec.gui.ComboBoxProto combo_box = 9;
  inline bool has_combo_box() const;
  inline void clear_combo_box();
  static const int kComboBoxFieldNumber = 9;
  inline const ::rec::gui::ComboBoxProto& combo_box() const;
  inline ::rec::gui::ComboBoxProto* mutable_combo_box();
  inline ::rec::gui::ComboBoxProto* release_combo_box();
  inline void set_allocated_combo_box(::rec::gui::ComboBoxProto* combo_box);

  // optional .rec.gui.CustomProto custom = 10;
  inline bool has_custom() const;
  inline void clear_custom();
  static const int kCustomFieldNumber = 10;
  inline const ::rec::gui::CustomProto& custom() const;
  inline ::rec::gui::CustomProto* mutable_custom();
  inline ::rec::gui::CustomProto* release_custom();
  inline void set_allocated_custom(::rec::gui::CustomProto* custom);

  // optional .rec.gui.HelpProto help = 16;
  inline bool has_help() const;
  inline void clear_help();
  static const int kHelpFieldNumber = 16;
  inline const ::rec::gui::HelpProto& help() const;
  inline ::rec::gui::HelpProto* mutable_help();
  inline ::rec::gui::HelpProto* release_help();
  inline void set_allocated_help(::rec::gui::HelpProto* help);

  // optional .rec.gui.LabelProto label = 11;
  inline bool has_label() const;
  inline void clear_label();
  static const int kLabelFieldNumber = 11;
  inline const ::rec::gui::LabelProto& label() const;
  inline ::rec::gui::LabelProto* mutable_label();
  inline ::rec::gui::LabelProto* release_label();
  inline void set_allocated_label(::rec::gui::LabelProto* label);

  // optional .rec.gui.ResizerProto full_resizer = 12;
  inline bool has_full_resizer() const;
  inline void clear_full_resizer();
  static const int kFullResizerFieldNumber = 12;
  inline const ::rec::gui::ResizerProto& full_resizer() const;
  inline ::rec::gui::ResizerProto* mutable_full_resizer();
  inline ::rec::gui::ResizerProto* release_full_resizer();
  inline void set_allocated_full_resizer(::rec::gui::ResizerProto* full_resizer);

  // optional .rec.gui.SliderProto slider = 13;
  inline bool has_slider() const;
  inline void clear_slider();
  static const int kSliderFieldNumber = 13;
  inline const ::rec::gui::SliderProto& slider() const;
  inline ::rec::gui::SliderProto* mutable_slider();
  inline ::rec::gui::SliderProto* release_slider();
  inline void set_allocated_slider(::rec::gui::SliderProto* slider);

  // optional .rec.gui.TextProto text = 14;
  inline bool has_text() const;
  inline void clear_text();
  static const int kTextFieldNumber = 14;
  inline const ::rec::gui::TextProto& text() const;
  inline ::rec::gui::TextProto* mutable_text();
  inline ::rec::gui::TextProto* release_text();
  inline void set_allocated_text(::rec::gui::TextProto* text);

  // optional .rec.gui.ToggleButtonProto toggle_button = 15;
  inline bool has_toggle_button() const;
  inline void clear_toggle_button();
  static const int kToggleButtonFieldNumber = 15;
  inline const ::rec::gui::ToggleButtonProto& toggle_button() const;
  inline ::rec::gui::ToggleButtonProto* mutable_toggle_button();
  inline ::rec::gui::ToggleButtonProto* release_toggle_button();
  inline void set_allocated_toggle_button(::rec::gui::ToggleButtonProto* toggle_button);

  // @@protoc_insertion_point(class_scope:rec.gui.ComponentProto)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_tooltip();
  inline void clear_has_tooltip();
  inline void set_has_size();
  inline void clear_has_size();
  inline void set_has_address();
  inline void clear_has_address();
  inline void set_has_font();
  inline void clear_has_font();
  inline void set_has_layout();
  inline void clear_has_layout();
  inline void set_has_resizer();
  inline void clear_has_resizer();
  inline void set_has_min_resizer();
  inline void clear_has_min_resizer();
  inline void set_has_button();
  inline void clear_has_button();
  inline void set_has_combo_box();
  inline void clear_has_combo_box();
  inline void set_has_custom();
  inline void clear_has_custom();
  inline void set_has_help();
  inline void clear_has_help();
  inline void set_has_label();
  inline void clear_has_label();
  inline void set_has_full_resizer();
  inline void clear_has_full_resizer();
  inline void set_has_slider();
  inline void clear_has_slider();
  inline void set_has_text();
  inline void clear_has_text();
  inline void set_has_toggle_button();
  inline void clear_has_toggle_button();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* name_;
  ::std::string* tooltip_;
  ::rec::gui::Size* size_;
  ::rec::data::AddressProto* address_;
  ::google::protobuf::RepeatedPtrField< ::rec::gui::Color > color_;
  ::rec::gui::FontProto* font_;
  ::std::string* layout_;
  ::std::string* resizer_;
  ::rec::gui::ButtonProto* button_;
  ::rec::gui::ComboBoxProto* combo_box_;
  ::rec::gui::CustomProto* custom_;
  ::rec::gui::HelpProto* help_;
  ::rec::gui::LabelProto* label_;
  ::rec::gui::ResizerProto* full_resizer_;
  ::rec::gui::SliderProto* slider_;
  ::rec::gui::TextProto* text_;
  ::rec::gui::ToggleButtonProto* toggle_button_;
  ::google::protobuf::uint32 min_resizer_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(18 + 31) / 32];

  friend void  protobuf_AddDesc_rec_2fgui_2fproto_2fComponent_2eproto();
  friend void protobuf_AssignDesc_rec_2fgui_2fproto_2fComponent_2eproto();
  friend void protobuf_ShutdownFile_rec_2fgui_2fproto_2fComponent_2eproto();

  void InitAsDefaultInstance();
  static ComponentProto* default_instance_;
};
// ===================================================================


// ===================================================================

// ComponentProto

// optional string name = 1;
inline bool ComponentProto::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ComponentProto::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ComponentProto::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ComponentProto::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& ComponentProto::name() const {
  return *name_;
}
inline void ComponentProto::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void ComponentProto::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void ComponentProto::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* ComponentProto::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* ComponentProto::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void ComponentProto::set_allocated_name(::std::string* name) {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    delete name_;
  }
  if (name) {
    set_has_name();
    name_ = name;
  } else {
    clear_has_name();
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional string tooltip = 2;
inline bool ComponentProto::has_tooltip() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ComponentProto::set_has_tooltip() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ComponentProto::clear_has_tooltip() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ComponentProto::clear_tooltip() {
  if (tooltip_ != &::google::protobuf::internal::kEmptyString) {
    tooltip_->clear();
  }
  clear_has_tooltip();
}
inline const ::std::string& ComponentProto::tooltip() const {
  return *tooltip_;
}
inline void ComponentProto::set_tooltip(const ::std::string& value) {
  set_has_tooltip();
  if (tooltip_ == &::google::protobuf::internal::kEmptyString) {
    tooltip_ = new ::std::string;
  }
  tooltip_->assign(value);
}
inline void ComponentProto::set_tooltip(const char* value) {
  set_has_tooltip();
  if (tooltip_ == &::google::protobuf::internal::kEmptyString) {
    tooltip_ = new ::std::string;
  }
  tooltip_->assign(value);
}
inline void ComponentProto::set_tooltip(const char* value, size_t size) {
  set_has_tooltip();
  if (tooltip_ == &::google::protobuf::internal::kEmptyString) {
    tooltip_ = new ::std::string;
  }
  tooltip_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* ComponentProto::mutable_tooltip() {
  set_has_tooltip();
  if (tooltip_ == &::google::protobuf::internal::kEmptyString) {
    tooltip_ = new ::std::string;
  }
  return tooltip_;
}
inline ::std::string* ComponentProto::release_tooltip() {
  clear_has_tooltip();
  if (tooltip_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = tooltip_;
    tooltip_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void ComponentProto::set_allocated_tooltip(::std::string* tooltip) {
  if (tooltip_ != &::google::protobuf::internal::kEmptyString) {
    delete tooltip_;
  }
  if (tooltip) {
    set_has_tooltip();
    tooltip_ = tooltip;
  } else {
    clear_has_tooltip();
    tooltip_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional .rec.gui.Size size = 3;
inline bool ComponentProto::has_size() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ComponentProto::set_has_size() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ComponentProto::clear_has_size() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ComponentProto::clear_size() {
  if (size_ != NULL) size_->::rec::gui::Size::Clear();
  clear_has_size();
}
inline const ::rec::gui::Size& ComponentProto::size() const {
  return size_ != NULL ? *size_ : *default_instance_->size_;
}
inline ::rec::gui::Size* ComponentProto::mutable_size() {
  set_has_size();
  if (size_ == NULL) size_ = new ::rec::gui::Size;
  return size_;
}
inline ::rec::gui::Size* ComponentProto::release_size() {
  clear_has_size();
  ::rec::gui::Size* temp = size_;
  size_ = NULL;
  return temp;
}
inline void ComponentProto::set_allocated_size(::rec::gui::Size* size) {
  delete size_;
  size_ = size;
  if (size) {
    set_has_size();
  } else {
    clear_has_size();
  }
}

// optional .rec.data.AddressProto address = 4;
inline bool ComponentProto::has_address() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ComponentProto::set_has_address() {
  _has_bits_[0] |= 0x00000008u;
}
inline void ComponentProto::clear_has_address() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void ComponentProto::clear_address() {
  if (address_ != NULL) address_->::rec::data::AddressProto::Clear();
  clear_has_address();
}
inline const ::rec::data::AddressProto& ComponentProto::address() const {
  return address_ != NULL ? *address_ : *default_instance_->address_;
}
inline ::rec::data::AddressProto* ComponentProto::mutable_address() {
  set_has_address();
  if (address_ == NULL) address_ = new ::rec::data::AddressProto;
  return address_;
}
inline ::rec::data::AddressProto* ComponentProto::release_address() {
  clear_has_address();
  ::rec::data::AddressProto* temp = address_;
  address_ = NULL;
  return temp;
}
inline void ComponentProto::set_allocated_address(::rec::data::AddressProto* address) {
  delete address_;
  address_ = address;
  if (address) {
    set_has_address();
  } else {
    clear_has_address();
  }
}

// repeated .rec.gui.Color color = 5;
inline int ComponentProto::color_size() const {
  return color_.size();
}
inline void ComponentProto::clear_color() {
  color_.Clear();
}
inline const ::rec::gui::Color& ComponentProto::color(int index) const {
  return color_.Get(index);
}
inline ::rec::gui::Color* ComponentProto::mutable_color(int index) {
  return color_.Mutable(index);
}
inline ::rec::gui::Color* ComponentProto::add_color() {
  return color_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::rec::gui::Color >&
ComponentProto::color() const {
  return color_;
}
inline ::google::protobuf::RepeatedPtrField< ::rec::gui::Color >*
ComponentProto::mutable_color() {
  return &color_;
}

// optional .rec.gui.FontProto font = 6;
inline bool ComponentProto::has_font() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void ComponentProto::set_has_font() {
  _has_bits_[0] |= 0x00000020u;
}
inline void ComponentProto::clear_has_font() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void ComponentProto::clear_font() {
  if (font_ != NULL) font_->::rec::gui::FontProto::Clear();
  clear_has_font();
}
inline const ::rec::gui::FontProto& ComponentProto::font() const {
  return font_ != NULL ? *font_ : *default_instance_->font_;
}
inline ::rec::gui::FontProto* ComponentProto::mutable_font() {
  set_has_font();
  if (font_ == NULL) font_ = new ::rec::gui::FontProto;
  return font_;
}
inline ::rec::gui::FontProto* ComponentProto::release_font() {
  clear_has_font();
  ::rec::gui::FontProto* temp = font_;
  font_ = NULL;
  return temp;
}
inline void ComponentProto::set_allocated_font(::rec::gui::FontProto* font) {
  delete font_;
  font_ = font;
  if (font) {
    set_has_font();
  } else {
    clear_has_font();
  }
}

// optional string layout = 17;
inline bool ComponentProto::has_layout() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void ComponentProto::set_has_layout() {
  _has_bits_[0] |= 0x00000040u;
}
inline void ComponentProto::clear_has_layout() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void ComponentProto::clear_layout() {
  if (layout_ != &::google::protobuf::internal::kEmptyString) {
    layout_->clear();
  }
  clear_has_layout();
}
inline const ::std::string& ComponentProto::layout() const {
  return *layout_;
}
inline void ComponentProto::set_layout(const ::std::string& value) {
  set_has_layout();
  if (layout_ == &::google::protobuf::internal::kEmptyString) {
    layout_ = new ::std::string;
  }
  layout_->assign(value);
}
inline void ComponentProto::set_layout(const char* value) {
  set_has_layout();
  if (layout_ == &::google::protobuf::internal::kEmptyString) {
    layout_ = new ::std::string;
  }
  layout_->assign(value);
}
inline void ComponentProto::set_layout(const char* value, size_t size) {
  set_has_layout();
  if (layout_ == &::google::protobuf::internal::kEmptyString) {
    layout_ = new ::std::string;
  }
  layout_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* ComponentProto::mutable_layout() {
  set_has_layout();
  if (layout_ == &::google::protobuf::internal::kEmptyString) {
    layout_ = new ::std::string;
  }
  return layout_;
}
inline ::std::string* ComponentProto::release_layout() {
  clear_has_layout();
  if (layout_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = layout_;
    layout_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void ComponentProto::set_allocated_layout(::std::string* layout) {
  if (layout_ != &::google::protobuf::internal::kEmptyString) {
    delete layout_;
  }
  if (layout) {
    set_has_layout();
    layout_ = layout;
  } else {
    clear_has_layout();
    layout_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional string resizer = 7;
inline bool ComponentProto::has_resizer() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void ComponentProto::set_has_resizer() {
  _has_bits_[0] |= 0x00000080u;
}
inline void ComponentProto::clear_has_resizer() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void ComponentProto::clear_resizer() {
  if (resizer_ != &::google::protobuf::internal::kEmptyString) {
    resizer_->clear();
  }
  clear_has_resizer();
}
inline const ::std::string& ComponentProto::resizer() const {
  return *resizer_;
}
inline void ComponentProto::set_resizer(const ::std::string& value) {
  set_has_resizer();
  if (resizer_ == &::google::protobuf::internal::kEmptyString) {
    resizer_ = new ::std::string;
  }
  resizer_->assign(value);
}
inline void ComponentProto::set_resizer(const char* value) {
  set_has_resizer();
  if (resizer_ == &::google::protobuf::internal::kEmptyString) {
    resizer_ = new ::std::string;
  }
  resizer_->assign(value);
}
inline void ComponentProto::set_resizer(const char* value, size_t size) {
  set_has_resizer();
  if (resizer_ == &::google::protobuf::internal::kEmptyString) {
    resizer_ = new ::std::string;
  }
  resizer_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* ComponentProto::mutable_resizer() {
  set_has_resizer();
  if (resizer_ == &::google::protobuf::internal::kEmptyString) {
    resizer_ = new ::std::string;
  }
  return resizer_;
}
inline ::std::string* ComponentProto::release_resizer() {
  clear_has_resizer();
  if (resizer_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = resizer_;
    resizer_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void ComponentProto::set_allocated_resizer(::std::string* resizer) {
  if (resizer_ != &::google::protobuf::internal::kEmptyString) {
    delete resizer_;
  }
  if (resizer) {
    set_has_resizer();
    resizer_ = resizer;
  } else {
    clear_has_resizer();
    resizer_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional uint32 min_resizer = 18;
inline bool ComponentProto::has_min_resizer() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void ComponentProto::set_has_min_resizer() {
  _has_bits_[0] |= 0x00000100u;
}
inline void ComponentProto::clear_has_min_resizer() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void ComponentProto::clear_min_resizer() {
  min_resizer_ = 0u;
  clear_has_min_resizer();
}
inline ::google::protobuf::uint32 ComponentProto::min_resizer() const {
  return min_resizer_;
}
inline void ComponentProto::set_min_resizer(::google::protobuf::uint32 value) {
  set_has_min_resizer();
  min_resizer_ = value;
}

// optional .rec.gui.ButtonProto button = 8;
inline bool ComponentProto::has_button() const {
  return (_has_bits_[0] & 0x00000200u) != 0;
}
inline void ComponentProto::set_has_button() {
  _has_bits_[0] |= 0x00000200u;
}
inline void ComponentProto::clear_has_button() {
  _has_bits_[0] &= ~0x00000200u;
}
inline void ComponentProto::clear_button() {
  if (button_ != NULL) button_->::rec::gui::ButtonProto::Clear();
  clear_has_button();
}
inline const ::rec::gui::ButtonProto& ComponentProto::button() const {
  return button_ != NULL ? *button_ : *default_instance_->button_;
}
inline ::rec::gui::ButtonProto* ComponentProto::mutable_button() {
  set_has_button();
  if (button_ == NULL) button_ = new ::rec::gui::ButtonProto;
  return button_;
}
inline ::rec::gui::ButtonProto* ComponentProto::release_button() {
  clear_has_button();
  ::rec::gui::ButtonProto* temp = button_;
  button_ = NULL;
  return temp;
}
inline void ComponentProto::set_allocated_button(::rec::gui::ButtonProto* button) {
  delete button_;
  button_ = button;
  if (button) {
    set_has_button();
  } else {
    clear_has_button();
  }
}

// optional .rec.gui.ComboBoxProto combo_box = 9;
inline bool ComponentProto::has_combo_box() const {
  return (_has_bits_[0] & 0x00000400u) != 0;
}
inline void ComponentProto::set_has_combo_box() {
  _has_bits_[0] |= 0x00000400u;
}
inline void ComponentProto::clear_has_combo_box() {
  _has_bits_[0] &= ~0x00000400u;
}
inline void ComponentProto::clear_combo_box() {
  if (combo_box_ != NULL) combo_box_->::rec::gui::ComboBoxProto::Clear();
  clear_has_combo_box();
}
inline const ::rec::gui::ComboBoxProto& ComponentProto::combo_box() const {
  return combo_box_ != NULL ? *combo_box_ : *default_instance_->combo_box_;
}
inline ::rec::gui::ComboBoxProto* ComponentProto::mutable_combo_box() {
  set_has_combo_box();
  if (combo_box_ == NULL) combo_box_ = new ::rec::gui::ComboBoxProto;
  return combo_box_;
}
inline ::rec::gui::ComboBoxProto* ComponentProto::release_combo_box() {
  clear_has_combo_box();
  ::rec::gui::ComboBoxProto* temp = combo_box_;
  combo_box_ = NULL;
  return temp;
}
inline void ComponentProto::set_allocated_combo_box(::rec::gui::ComboBoxProto* combo_box) {
  delete combo_box_;
  combo_box_ = combo_box;
  if (combo_box) {
    set_has_combo_box();
  } else {
    clear_has_combo_box();
  }
}

// optional .rec.gui.CustomProto custom = 10;
inline bool ComponentProto::has_custom() const {
  return (_has_bits_[0] & 0x00000800u) != 0;
}
inline void ComponentProto::set_has_custom() {
  _has_bits_[0] |= 0x00000800u;
}
inline void ComponentProto::clear_has_custom() {
  _has_bits_[0] &= ~0x00000800u;
}
inline void ComponentProto::clear_custom() {
  if (custom_ != NULL) custom_->::rec::gui::CustomProto::Clear();
  clear_has_custom();
}
inline const ::rec::gui::CustomProto& ComponentProto::custom() const {
  return custom_ != NULL ? *custom_ : *default_instance_->custom_;
}
inline ::rec::gui::CustomProto* ComponentProto::mutable_custom() {
  set_has_custom();
  if (custom_ == NULL) custom_ = new ::rec::gui::CustomProto;
  return custom_;
}
inline ::rec::gui::CustomProto* ComponentProto::release_custom() {
  clear_has_custom();
  ::rec::gui::CustomProto* temp = custom_;
  custom_ = NULL;
  return temp;
}
inline void ComponentProto::set_allocated_custom(::rec::gui::CustomProto* custom) {
  delete custom_;
  custom_ = custom;
  if (custom) {
    set_has_custom();
  } else {
    clear_has_custom();
  }
}

// optional .rec.gui.HelpProto help = 16;
inline bool ComponentProto::has_help() const {
  return (_has_bits_[0] & 0x00001000u) != 0;
}
inline void ComponentProto::set_has_help() {
  _has_bits_[0] |= 0x00001000u;
}
inline void ComponentProto::clear_has_help() {
  _has_bits_[0] &= ~0x00001000u;
}
inline void ComponentProto::clear_help() {
  if (help_ != NULL) help_->::rec::gui::HelpProto::Clear();
  clear_has_help();
}
inline const ::rec::gui::HelpProto& ComponentProto::help() const {
  return help_ != NULL ? *help_ : *default_instance_->help_;
}
inline ::rec::gui::HelpProto* ComponentProto::mutable_help() {
  set_has_help();
  if (help_ == NULL) help_ = new ::rec::gui::HelpProto;
  return help_;
}
inline ::rec::gui::HelpProto* ComponentProto::release_help() {
  clear_has_help();
  ::rec::gui::HelpProto* temp = help_;
  help_ = NULL;
  return temp;
}
inline void ComponentProto::set_allocated_help(::rec::gui::HelpProto* help) {
  delete help_;
  help_ = help;
  if (help) {
    set_has_help();
  } else {
    clear_has_help();
  }
}

// optional .rec.gui.LabelProto label = 11;
inline bool ComponentProto::has_label() const {
  return (_has_bits_[0] & 0x00002000u) != 0;
}
inline void ComponentProto::set_has_label() {
  _has_bits_[0] |= 0x00002000u;
}
inline void ComponentProto::clear_has_label() {
  _has_bits_[0] &= ~0x00002000u;
}
inline void ComponentProto::clear_label() {
  if (label_ != NULL) label_->::rec::gui::LabelProto::Clear();
  clear_has_label();
}
inline const ::rec::gui::LabelProto& ComponentProto::label() const {
  return label_ != NULL ? *label_ : *default_instance_->label_;
}
inline ::rec::gui::LabelProto* ComponentProto::mutable_label() {
  set_has_label();
  if (label_ == NULL) label_ = new ::rec::gui::LabelProto;
  return label_;
}
inline ::rec::gui::LabelProto* ComponentProto::release_label() {
  clear_has_label();
  ::rec::gui::LabelProto* temp = label_;
  label_ = NULL;
  return temp;
}
inline void ComponentProto::set_allocated_label(::rec::gui::LabelProto* label) {
  delete label_;
  label_ = label;
  if (label) {
    set_has_label();
  } else {
    clear_has_label();
  }
}

// optional .rec.gui.ResizerProto full_resizer = 12;
inline bool ComponentProto::has_full_resizer() const {
  return (_has_bits_[0] & 0x00004000u) != 0;
}
inline void ComponentProto::set_has_full_resizer() {
  _has_bits_[0] |= 0x00004000u;
}
inline void ComponentProto::clear_has_full_resizer() {
  _has_bits_[0] &= ~0x00004000u;
}
inline void ComponentProto::clear_full_resizer() {
  if (full_resizer_ != NULL) full_resizer_->::rec::gui::ResizerProto::Clear();
  clear_has_full_resizer();
}
inline const ::rec::gui::ResizerProto& ComponentProto::full_resizer() const {
  return full_resizer_ != NULL ? *full_resizer_ : *default_instance_->full_resizer_;
}
inline ::rec::gui::ResizerProto* ComponentProto::mutable_full_resizer() {
  set_has_full_resizer();
  if (full_resizer_ == NULL) full_resizer_ = new ::rec::gui::ResizerProto;
  return full_resizer_;
}
inline ::rec::gui::ResizerProto* ComponentProto::release_full_resizer() {
  clear_has_full_resizer();
  ::rec::gui::ResizerProto* temp = full_resizer_;
  full_resizer_ = NULL;
  return temp;
}
inline void ComponentProto::set_allocated_full_resizer(::rec::gui::ResizerProto* full_resizer) {
  delete full_resizer_;
  full_resizer_ = full_resizer;
  if (full_resizer) {
    set_has_full_resizer();
  } else {
    clear_has_full_resizer();
  }
}

// optional .rec.gui.SliderProto slider = 13;
inline bool ComponentProto::has_slider() const {
  return (_has_bits_[0] & 0x00008000u) != 0;
}
inline void ComponentProto::set_has_slider() {
  _has_bits_[0] |= 0x00008000u;
}
inline void ComponentProto::clear_has_slider() {
  _has_bits_[0] &= ~0x00008000u;
}
inline void ComponentProto::clear_slider() {
  if (slider_ != NULL) slider_->::rec::gui::SliderProto::Clear();
  clear_has_slider();
}
inline const ::rec::gui::SliderProto& ComponentProto::slider() const {
  return slider_ != NULL ? *slider_ : *default_instance_->slider_;
}
inline ::rec::gui::SliderProto* ComponentProto::mutable_slider() {
  set_has_slider();
  if (slider_ == NULL) slider_ = new ::rec::gui::SliderProto;
  return slider_;
}
inline ::rec::gui::SliderProto* ComponentProto::release_slider() {
  clear_has_slider();
  ::rec::gui::SliderProto* temp = slider_;
  slider_ = NULL;
  return temp;
}
inline void ComponentProto::set_allocated_slider(::rec::gui::SliderProto* slider) {
  delete slider_;
  slider_ = slider;
  if (slider) {
    set_has_slider();
  } else {
    clear_has_slider();
  }
}

// optional .rec.gui.TextProto text = 14;
inline bool ComponentProto::has_text() const {
  return (_has_bits_[0] & 0x00010000u) != 0;
}
inline void ComponentProto::set_has_text() {
  _has_bits_[0] |= 0x00010000u;
}
inline void ComponentProto::clear_has_text() {
  _has_bits_[0] &= ~0x00010000u;
}
inline void ComponentProto::clear_text() {
  if (text_ != NULL) text_->::rec::gui::TextProto::Clear();
  clear_has_text();
}
inline const ::rec::gui::TextProto& ComponentProto::text() const {
  return text_ != NULL ? *text_ : *default_instance_->text_;
}
inline ::rec::gui::TextProto* ComponentProto::mutable_text() {
  set_has_text();
  if (text_ == NULL) text_ = new ::rec::gui::TextProto;
  return text_;
}
inline ::rec::gui::TextProto* ComponentProto::release_text() {
  clear_has_text();
  ::rec::gui::TextProto* temp = text_;
  text_ = NULL;
  return temp;
}
inline void ComponentProto::set_allocated_text(::rec::gui::TextProto* text) {
  delete text_;
  text_ = text;
  if (text) {
    set_has_text();
  } else {
    clear_has_text();
  }
}

// optional .rec.gui.ToggleButtonProto toggle_button = 15;
inline bool ComponentProto::has_toggle_button() const {
  return (_has_bits_[0] & 0x00020000u) != 0;
}
inline void ComponentProto::set_has_toggle_button() {
  _has_bits_[0] |= 0x00020000u;
}
inline void ComponentProto::clear_has_toggle_button() {
  _has_bits_[0] &= ~0x00020000u;
}
inline void ComponentProto::clear_toggle_button() {
  if (toggle_button_ != NULL) toggle_button_->::rec::gui::ToggleButtonProto::Clear();
  clear_has_toggle_button();
}
inline const ::rec::gui::ToggleButtonProto& ComponentProto::toggle_button() const {
  return toggle_button_ != NULL ? *toggle_button_ : *default_instance_->toggle_button_;
}
inline ::rec::gui::ToggleButtonProto* ComponentProto::mutable_toggle_button() {
  set_has_toggle_button();
  if (toggle_button_ == NULL) toggle_button_ = new ::rec::gui::ToggleButtonProto;
  return toggle_button_;
}
inline ::rec::gui::ToggleButtonProto* ComponentProto::release_toggle_button() {
  clear_has_toggle_button();
  ::rec::gui::ToggleButtonProto* temp = toggle_button_;
  toggle_button_ = NULL;
  return temp;
}
inline void ComponentProto::set_allocated_toggle_button(::rec::gui::ToggleButtonProto* toggle_button) {
  delete toggle_button_;
  toggle_button_ = toggle_button;
  if (toggle_button) {
    set_has_toggle_button();
  } else {
    clear_has_toggle_button();
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

#endif  // PROTOBUF_rec_2fgui_2fproto_2fComponent_2eproto__INCLUDED
