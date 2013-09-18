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
#include "rec/gui/proto/Button.pb.h"
#include "rec/gui/proto/ComboBox.pb.h"
#include "rec/gui/proto/Label.pb.h"
#include "rec/gui/proto/Resizer.pb.h"
#include "rec/gui/proto/Slider.pb.h"
#include "rec/gui/proto/ToggleButton.pb.h"
// @@protoc_insertion_point(includes)

namespace rec {
namespace gui {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fgui_2fproto_2fComponent_2eproto();
void protobuf_AssignDesc_rec_2fgui_2fproto_2fComponent_2eproto();
void protobuf_ShutdownFile_rec_2fgui_2fproto_2fComponent_2eproto();

class ComponentProto;
class ComponentProtos;

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

  // optional string preferred = 2;
  inline bool has_preferred() const;
  inline void clear_preferred();
  static const int kPreferredFieldNumber = 2;
  inline const ::std::string& preferred() const;
  inline void set_preferred(const ::std::string& value);
  inline void set_preferred(const char* value);
  inline void set_preferred(const char* value, size_t size);
  inline ::std::string* mutable_preferred();
  inline ::std::string* release_preferred();
  inline void set_allocated_preferred(::std::string* preferred);

  // optional string min = 3;
  inline bool has_min() const;
  inline void clear_min();
  static const int kMinFieldNumber = 3;
  inline const ::std::string& min() const;
  inline void set_min(const ::std::string& value);
  inline void set_min(const char* value);
  inline void set_min(const char* value, size_t size);
  inline ::std::string* mutable_min();
  inline ::std::string* release_min();
  inline void set_allocated_min(::std::string* min);

  // optional string max = 4;
  inline bool has_max() const;
  inline void clear_max();
  static const int kMaxFieldNumber = 4;
  inline const ::std::string& max() const;
  inline void set_max(const ::std::string& value);
  inline void set_max(const char* value);
  inline void set_max(const char* value, size_t size);
  inline ::std::string* mutable_max();
  inline ::std::string* release_max();
  inline void set_allocated_max(::std::string* max);

  // optional .rec.gui.ButtonProto button = 5;
  inline bool has_button() const;
  inline void clear_button();
  static const int kButtonFieldNumber = 5;
  inline const ::rec::gui::ButtonProto& button() const;
  inline ::rec::gui::ButtonProto* mutable_button();
  inline ::rec::gui::ButtonProto* release_button();
  inline void set_allocated_button(::rec::gui::ButtonProto* button);

  // optional .rec.gui.ComboBoxProto combo_box = 6;
  inline bool has_combo_box() const;
  inline void clear_combo_box();
  static const int kComboBoxFieldNumber = 6;
  inline const ::rec::gui::ComboBoxProto& combo_box() const;
  inline ::rec::gui::ComboBoxProto* mutable_combo_box();
  inline ::rec::gui::ComboBoxProto* release_combo_box();
  inline void set_allocated_combo_box(::rec::gui::ComboBoxProto* combo_box);

  // optional .rec.gui.LabelProto label = 7;
  inline bool has_label() const;
  inline void clear_label();
  static const int kLabelFieldNumber = 7;
  inline const ::rec::gui::LabelProto& label() const;
  inline ::rec::gui::LabelProto* mutable_label();
  inline ::rec::gui::LabelProto* release_label();
  inline void set_allocated_label(::rec::gui::LabelProto* label);

  // optional .rec.gui.ResizerProto resizer = 9;
  inline bool has_resizer() const;
  inline void clear_resizer();
  static const int kResizerFieldNumber = 9;
  inline const ::rec::gui::ResizerProto& resizer() const;
  inline ::rec::gui::ResizerProto* mutable_resizer();
  inline ::rec::gui::ResizerProto* release_resizer();
  inline void set_allocated_resizer(::rec::gui::ResizerProto* resizer);

  // optional .rec.gui.SliderProto slider = 10;
  inline bool has_slider() const;
  inline void clear_slider();
  static const int kSliderFieldNumber = 10;
  inline const ::rec::gui::SliderProto& slider() const;
  inline ::rec::gui::SliderProto* mutable_slider();
  inline ::rec::gui::SliderProto* release_slider();
  inline void set_allocated_slider(::rec::gui::SliderProto* slider);

  // optional .rec.gui.ToggleButtonProto toggle_button = 11;
  inline bool has_toggle_button() const;
  inline void clear_toggle_button();
  static const int kToggleButtonFieldNumber = 11;
  inline const ::rec::gui::ToggleButtonProto& toggle_button() const;
  inline ::rec::gui::ToggleButtonProto* mutable_toggle_button();
  inline ::rec::gui::ToggleButtonProto* release_toggle_button();
  inline void set_allocated_toggle_button(::rec::gui::ToggleButtonProto* toggle_button);

  // @@protoc_insertion_point(class_scope:rec.gui.ComponentProto)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_preferred();
  inline void clear_has_preferred();
  inline void set_has_min();
  inline void clear_has_min();
  inline void set_has_max();
  inline void clear_has_max();
  inline void set_has_button();
  inline void clear_has_button();
  inline void set_has_combo_box();
  inline void clear_has_combo_box();
  inline void set_has_label();
  inline void clear_has_label();
  inline void set_has_resizer();
  inline void clear_has_resizer();
  inline void set_has_slider();
  inline void clear_has_slider();
  inline void set_has_toggle_button();
  inline void clear_has_toggle_button();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* name_;
  ::std::string* preferred_;
  ::std::string* min_;
  ::std::string* max_;
  ::rec::gui::ButtonProto* button_;
  ::rec::gui::ComboBoxProto* combo_box_;
  ::rec::gui::LabelProto* label_;
  ::rec::gui::ResizerProto* resizer_;
  ::rec::gui::SliderProto* slider_;
  ::rec::gui::ToggleButtonProto* toggle_button_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(10 + 31) / 32];

  friend void  protobuf_AddDesc_rec_2fgui_2fproto_2fComponent_2eproto();
  friend void protobuf_AssignDesc_rec_2fgui_2fproto_2fComponent_2eproto();
  friend void protobuf_ShutdownFile_rec_2fgui_2fproto_2fComponent_2eproto();

  void InitAsDefaultInstance();
  static ComponentProto* default_instance_;
};
// -------------------------------------------------------------------

class ComponentProtos : public ::google::protobuf::Message {
 public:
  ComponentProtos();
  virtual ~ComponentProtos();

  ComponentProtos(const ComponentProtos& from);

  inline ComponentProtos& operator=(const ComponentProtos& from) {
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
  static const ComponentProtos& default_instance();

  void Swap(ComponentProtos* other);

  // implements Message ----------------------------------------------

  ComponentProtos* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ComponentProtos& from);
  void MergeFrom(const ComponentProtos& from);
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

  // repeated .rec.gui.ComponentProto component = 1;
  inline int component_size() const;
  inline void clear_component();
  static const int kComponentFieldNumber = 1;
  inline const ::rec::gui::ComponentProto& component(int index) const;
  inline ::rec::gui::ComponentProto* mutable_component(int index);
  inline ::rec::gui::ComponentProto* add_component();
  inline const ::google::protobuf::RepeatedPtrField< ::rec::gui::ComponentProto >&
      component() const;
  inline ::google::protobuf::RepeatedPtrField< ::rec::gui::ComponentProto >*
      mutable_component();

  // @@protoc_insertion_point(class_scope:rec.gui.ComponentProtos)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::rec::gui::ComponentProto > component_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_rec_2fgui_2fproto_2fComponent_2eproto();
  friend void protobuf_AssignDesc_rec_2fgui_2fproto_2fComponent_2eproto();
  friend void protobuf_ShutdownFile_rec_2fgui_2fproto_2fComponent_2eproto();

  void InitAsDefaultInstance();
  static ComponentProtos* default_instance_;
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

// optional string preferred = 2;
inline bool ComponentProto::has_preferred() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ComponentProto::set_has_preferred() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ComponentProto::clear_has_preferred() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ComponentProto::clear_preferred() {
  if (preferred_ != &::google::protobuf::internal::kEmptyString) {
    preferred_->clear();
  }
  clear_has_preferred();
}
inline const ::std::string& ComponentProto::preferred() const {
  return *preferred_;
}
inline void ComponentProto::set_preferred(const ::std::string& value) {
  set_has_preferred();
  if (preferred_ == &::google::protobuf::internal::kEmptyString) {
    preferred_ = new ::std::string;
  }
  preferred_->assign(value);
}
inline void ComponentProto::set_preferred(const char* value) {
  set_has_preferred();
  if (preferred_ == &::google::protobuf::internal::kEmptyString) {
    preferred_ = new ::std::string;
  }
  preferred_->assign(value);
}
inline void ComponentProto::set_preferred(const char* value, size_t size) {
  set_has_preferred();
  if (preferred_ == &::google::protobuf::internal::kEmptyString) {
    preferred_ = new ::std::string;
  }
  preferred_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* ComponentProto::mutable_preferred() {
  set_has_preferred();
  if (preferred_ == &::google::protobuf::internal::kEmptyString) {
    preferred_ = new ::std::string;
  }
  return preferred_;
}
inline ::std::string* ComponentProto::release_preferred() {
  clear_has_preferred();
  if (preferred_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = preferred_;
    preferred_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void ComponentProto::set_allocated_preferred(::std::string* preferred) {
  if (preferred_ != &::google::protobuf::internal::kEmptyString) {
    delete preferred_;
  }
  if (preferred) {
    set_has_preferred();
    preferred_ = preferred;
  } else {
    clear_has_preferred();
    preferred_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional string min = 3;
inline bool ComponentProto::has_min() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ComponentProto::set_has_min() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ComponentProto::clear_has_min() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ComponentProto::clear_min() {
  if (min_ != &::google::protobuf::internal::kEmptyString) {
    min_->clear();
  }
  clear_has_min();
}
inline const ::std::string& ComponentProto::min() const {
  return *min_;
}
inline void ComponentProto::set_min(const ::std::string& value) {
  set_has_min();
  if (min_ == &::google::protobuf::internal::kEmptyString) {
    min_ = new ::std::string;
  }
  min_->assign(value);
}
inline void ComponentProto::set_min(const char* value) {
  set_has_min();
  if (min_ == &::google::protobuf::internal::kEmptyString) {
    min_ = new ::std::string;
  }
  min_->assign(value);
}
inline void ComponentProto::set_min(const char* value, size_t size) {
  set_has_min();
  if (min_ == &::google::protobuf::internal::kEmptyString) {
    min_ = new ::std::string;
  }
  min_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* ComponentProto::mutable_min() {
  set_has_min();
  if (min_ == &::google::protobuf::internal::kEmptyString) {
    min_ = new ::std::string;
  }
  return min_;
}
inline ::std::string* ComponentProto::release_min() {
  clear_has_min();
  if (min_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = min_;
    min_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void ComponentProto::set_allocated_min(::std::string* min) {
  if (min_ != &::google::protobuf::internal::kEmptyString) {
    delete min_;
  }
  if (min) {
    set_has_min();
    min_ = min;
  } else {
    clear_has_min();
    min_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional string max = 4;
inline bool ComponentProto::has_max() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ComponentProto::set_has_max() {
  _has_bits_[0] |= 0x00000008u;
}
inline void ComponentProto::clear_has_max() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void ComponentProto::clear_max() {
  if (max_ != &::google::protobuf::internal::kEmptyString) {
    max_->clear();
  }
  clear_has_max();
}
inline const ::std::string& ComponentProto::max() const {
  return *max_;
}
inline void ComponentProto::set_max(const ::std::string& value) {
  set_has_max();
  if (max_ == &::google::protobuf::internal::kEmptyString) {
    max_ = new ::std::string;
  }
  max_->assign(value);
}
inline void ComponentProto::set_max(const char* value) {
  set_has_max();
  if (max_ == &::google::protobuf::internal::kEmptyString) {
    max_ = new ::std::string;
  }
  max_->assign(value);
}
inline void ComponentProto::set_max(const char* value, size_t size) {
  set_has_max();
  if (max_ == &::google::protobuf::internal::kEmptyString) {
    max_ = new ::std::string;
  }
  max_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* ComponentProto::mutable_max() {
  set_has_max();
  if (max_ == &::google::protobuf::internal::kEmptyString) {
    max_ = new ::std::string;
  }
  return max_;
}
inline ::std::string* ComponentProto::release_max() {
  clear_has_max();
  if (max_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = max_;
    max_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void ComponentProto::set_allocated_max(::std::string* max) {
  if (max_ != &::google::protobuf::internal::kEmptyString) {
    delete max_;
  }
  if (max) {
    set_has_max();
    max_ = max;
  } else {
    clear_has_max();
    max_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional .rec.gui.ButtonProto button = 5;
inline bool ComponentProto::has_button() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void ComponentProto::set_has_button() {
  _has_bits_[0] |= 0x00000010u;
}
inline void ComponentProto::clear_has_button() {
  _has_bits_[0] &= ~0x00000010u;
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

// optional .rec.gui.ComboBoxProto combo_box = 6;
inline bool ComponentProto::has_combo_box() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void ComponentProto::set_has_combo_box() {
  _has_bits_[0] |= 0x00000020u;
}
inline void ComponentProto::clear_has_combo_box() {
  _has_bits_[0] &= ~0x00000020u;
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

// optional .rec.gui.LabelProto label = 7;
inline bool ComponentProto::has_label() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void ComponentProto::set_has_label() {
  _has_bits_[0] |= 0x00000040u;
}
inline void ComponentProto::clear_has_label() {
  _has_bits_[0] &= ~0x00000040u;
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

// optional .rec.gui.ResizerProto resizer = 9;
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
  if (resizer_ != NULL) resizer_->::rec::gui::ResizerProto::Clear();
  clear_has_resizer();
}
inline const ::rec::gui::ResizerProto& ComponentProto::resizer() const {
  return resizer_ != NULL ? *resizer_ : *default_instance_->resizer_;
}
inline ::rec::gui::ResizerProto* ComponentProto::mutable_resizer() {
  set_has_resizer();
  if (resizer_ == NULL) resizer_ = new ::rec::gui::ResizerProto;
  return resizer_;
}
inline ::rec::gui::ResizerProto* ComponentProto::release_resizer() {
  clear_has_resizer();
  ::rec::gui::ResizerProto* temp = resizer_;
  resizer_ = NULL;
  return temp;
}
inline void ComponentProto::set_allocated_resizer(::rec::gui::ResizerProto* resizer) {
  delete resizer_;
  resizer_ = resizer;
  if (resizer) {
    set_has_resizer();
  } else {
    clear_has_resizer();
  }
}

// optional .rec.gui.SliderProto slider = 10;
inline bool ComponentProto::has_slider() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void ComponentProto::set_has_slider() {
  _has_bits_[0] |= 0x00000100u;
}
inline void ComponentProto::clear_has_slider() {
  _has_bits_[0] &= ~0x00000100u;
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

// optional .rec.gui.ToggleButtonProto toggle_button = 11;
inline bool ComponentProto::has_toggle_button() const {
  return (_has_bits_[0] & 0x00000200u) != 0;
}
inline void ComponentProto::set_has_toggle_button() {
  _has_bits_[0] |= 0x00000200u;
}
inline void ComponentProto::clear_has_toggle_button() {
  _has_bits_[0] &= ~0x00000200u;
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

// -------------------------------------------------------------------

// ComponentProtos

// repeated .rec.gui.ComponentProto component = 1;
inline int ComponentProtos::component_size() const {
  return component_.size();
}
inline void ComponentProtos::clear_component() {
  component_.Clear();
}
inline const ::rec::gui::ComponentProto& ComponentProtos::component(int index) const {
  return component_.Get(index);
}
inline ::rec::gui::ComponentProto* ComponentProtos::mutable_component(int index) {
  return component_.Mutable(index);
}
inline ::rec::gui::ComponentProto* ComponentProtos::add_component() {
  return component_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::rec::gui::ComponentProto >&
ComponentProtos::component() const {
  return component_;
}
inline ::google::protobuf::RepeatedPtrField< ::rec::gui::ComponentProto >*
ComponentProtos::mutable_component() {
  return &component_;
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
