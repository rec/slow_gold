// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/slow/GuiSettings.proto

#ifndef PROTOBUF_rec_2fslow_2fGuiSettings_2eproto__INCLUDED
#define PROTOBUF_rec_2fslow_2fGuiSettings_2eproto__INCLUDED

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
namespace slow {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fslow_2fGuiSettings_2eproto();
void protobuf_AssignDesc_rec_2fslow_2fGuiSettings_2eproto();
void protobuf_ShutdownFile_rec_2fslow_2fGuiSettings_2eproto();

class GuiSettings;

// ===================================================================

class GuiSettings : public ::google::protobuf::Message {
 public:
  GuiSettings();
  virtual ~GuiSettings();
  
  GuiSettings(const GuiSettings& from);
  
  inline GuiSettings& operator=(const GuiSettings& from) {
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
  static const GuiSettings& default_instance();
  
  void Swap(GuiSettings* other);
  
  // implements Message ----------------------------------------------
  
  GuiSettings* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GuiSettings& from);
  void MergeFrom(const GuiSettings& from);
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
  
  // optional bool follow_cursor = 1 [default = true];
  inline bool has_follow_cursor() const;
  inline void clear_follow_cursor();
  static const int kFollowCursorFieldNumber = 1;
  inline bool follow_cursor() const;
  inline void set_follow_cursor(bool value);
  
  // optional bool drop_adds_to_browser = 2 [default = true];
  inline bool has_drop_adds_to_browser() const;
  inline void clear_drop_adds_to_browser();
  static const int kDropAddsToBrowserFieldNumber = 2;
  inline bool drop_adds_to_browser() const;
  inline void set_drop_adds_to_browser(bool value);
  
  // optional bool show_tooltips = 3 [default = false];
  inline bool has_show_tooltips() const;
  inline void clear_show_tooltips();
  static const int kShowTooltipsFieldNumber = 3;
  inline bool show_tooltips() const;
  inline void set_show_tooltips(bool value);
  
  // optional bool show_help_pane = 4 [default = true];
  inline bool has_show_help_pane() const;
  inline void clear_show_help_pane();
  static const int kShowHelpPaneFieldNumber = 4;
  inline bool show_help_pane() const;
  inline void set_show_help_pane(bool value);
  
  // optional bool advanced_menus = 5 [default = false];
  inline bool has_advanced_menus() const;
  inline void clear_advanced_menus();
  static const int kAdvancedMenusFieldNumber = 5;
  inline bool advanced_menus() const;
  inline void set_advanced_menus(bool value);
  
  // optional bool show_about_on_startup = 6 [default = true];
  inline bool has_show_about_on_startup() const;
  inline void clear_show_about_on_startup();
  static const int kShowAboutOnStartupFieldNumber = 6;
  inline bool show_about_on_startup() const;
  inline void set_show_about_on_startup(bool value);
  
  // @@protoc_insertion_point(class_scope:rec.slow.GuiSettings)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  bool follow_cursor_;
  bool drop_adds_to_browser_;
  bool show_tooltips_;
  bool show_help_pane_;
  bool advanced_menus_;
  bool show_about_on_startup_;
  friend void  protobuf_AddDesc_rec_2fslow_2fGuiSettings_2eproto();
  friend void protobuf_AssignDesc_rec_2fslow_2fGuiSettings_2eproto();
  friend void protobuf_ShutdownFile_rec_2fslow_2fGuiSettings_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(6 + 31) / 32];
  
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
  static GuiSettings* default_instance_;
};
// ===================================================================


// ===================================================================

// GuiSettings

// optional bool follow_cursor = 1 [default = true];
inline bool GuiSettings::has_follow_cursor() const {
  return _has_bit(0);
}
inline void GuiSettings::clear_follow_cursor() {
  follow_cursor_ = true;
  _clear_bit(0);
}
inline bool GuiSettings::follow_cursor() const {
  return follow_cursor_;
}
inline void GuiSettings::set_follow_cursor(bool value) {
  _set_bit(0);
  follow_cursor_ = value;
}

// optional bool drop_adds_to_browser = 2 [default = true];
inline bool GuiSettings::has_drop_adds_to_browser() const {
  return _has_bit(1);
}
inline void GuiSettings::clear_drop_adds_to_browser() {
  drop_adds_to_browser_ = true;
  _clear_bit(1);
}
inline bool GuiSettings::drop_adds_to_browser() const {
  return drop_adds_to_browser_;
}
inline void GuiSettings::set_drop_adds_to_browser(bool value) {
  _set_bit(1);
  drop_adds_to_browser_ = value;
}

// optional bool show_tooltips = 3 [default = false];
inline bool GuiSettings::has_show_tooltips() const {
  return _has_bit(2);
}
inline void GuiSettings::clear_show_tooltips() {
  show_tooltips_ = false;
  _clear_bit(2);
}
inline bool GuiSettings::show_tooltips() const {
  return show_tooltips_;
}
inline void GuiSettings::set_show_tooltips(bool value) {
  _set_bit(2);
  show_tooltips_ = value;
}

// optional bool show_help_pane = 4 [default = true];
inline bool GuiSettings::has_show_help_pane() const {
  return _has_bit(3);
}
inline void GuiSettings::clear_show_help_pane() {
  show_help_pane_ = true;
  _clear_bit(3);
}
inline bool GuiSettings::show_help_pane() const {
  return show_help_pane_;
}
inline void GuiSettings::set_show_help_pane(bool value) {
  _set_bit(3);
  show_help_pane_ = value;
}

// optional bool advanced_menus = 5 [default = false];
inline bool GuiSettings::has_advanced_menus() const {
  return _has_bit(4);
}
inline void GuiSettings::clear_advanced_menus() {
  advanced_menus_ = false;
  _clear_bit(4);
}
inline bool GuiSettings::advanced_menus() const {
  return advanced_menus_;
}
inline void GuiSettings::set_advanced_menus(bool value) {
  _set_bit(4);
  advanced_menus_ = value;
}

// optional bool show_about_on_startup = 6 [default = true];
inline bool GuiSettings::has_show_about_on_startup() const {
  return _has_bit(5);
}
inline void GuiSettings::clear_show_about_on_startup() {
  show_about_on_startup_ = true;
  _clear_bit(5);
}
inline bool GuiSettings::show_about_on_startup() const {
  return show_about_on_startup_;
}
inline void GuiSettings::set_show_about_on_startup(bool value) {
  _set_bit(5);
  show_about_on_startup_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace slow
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2fslow_2fGuiSettings_2eproto__INCLUDED
