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

enum GuiSettings_FileType {
  GuiSettings_FileType_AIFF = 0,
  GuiSettings_FileType_FLAC = 1,
  GuiSettings_FileType_OGG = 2,
  GuiSettings_FileType_WAV = 3,
  GuiSettings_FileType_COUNT = 4
};
bool GuiSettings_FileType_IsValid(int value);
const GuiSettings_FileType GuiSettings_FileType_FileType_MIN = GuiSettings_FileType_AIFF;
const GuiSettings_FileType GuiSettings_FileType_FileType_MAX = GuiSettings_FileType_COUNT;
const int GuiSettings_FileType_FileType_ARRAYSIZE = GuiSettings_FileType_FileType_MAX + 1;

const ::google::protobuf::EnumDescriptor* GuiSettings_FileType_descriptor();
inline const ::std::string& GuiSettings_FileType_Name(GuiSettings_FileType value) {
  return ::google::protobuf::internal::NameOfEnum(
    GuiSettings_FileType_descriptor(), value);
}
inline bool GuiSettings_FileType_Parse(
    const ::std::string& name, GuiSettings_FileType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<GuiSettings_FileType>(
    GuiSettings_FileType_descriptor(), name, value);
}
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
  
  typedef GuiSettings_FileType FileType;
  static const FileType AIFF = GuiSettings_FileType_AIFF;
  static const FileType FLAC = GuiSettings_FileType_FLAC;
  static const FileType OGG = GuiSettings_FileType_OGG;
  static const FileType WAV = GuiSettings_FileType_WAV;
  static const FileType COUNT = GuiSettings_FileType_COUNT;
  static inline bool FileType_IsValid(int value) {
    return GuiSettings_FileType_IsValid(value);
  }
  static const FileType FileType_MIN =
    GuiSettings_FileType_FileType_MIN;
  static const FileType FileType_MAX =
    GuiSettings_FileType_FileType_MAX;
  static const int FileType_ARRAYSIZE =
    GuiSettings_FileType_FileType_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  FileType_descriptor() {
    return GuiSettings_FileType_descriptor();
  }
  static inline const ::std::string& FileType_Name(FileType value) {
    return GuiSettings_FileType_Name(value);
  }
  static inline bool FileType_Parse(const ::std::string& name,
      FileType* value) {
    return GuiSettings_FileType_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // optional bool advanced_menus = 1 [default = false];
  inline bool has_advanced_menus() const;
  inline void clear_advanced_menus();
  static const int kAdvancedMenusFieldNumber = 1;
  inline bool advanced_menus() const;
  inline void set_advanced_menus(bool value);
  
  // optional bool auto_check_for_updates = 2 [default = false];
  inline bool has_auto_check_for_updates() const;
  inline void clear_auto_check_for_updates();
  static const int kAutoCheckForUpdatesFieldNumber = 2;
  inline bool auto_check_for_updates() const;
  inline void set_auto_check_for_updates(bool value);
  
  // optional bool drop_adds_to_browser = 3 [default = true];
  inline bool has_drop_adds_to_browser() const;
  inline void clear_drop_adds_to_browser();
  static const int kDropAddsToBrowserFieldNumber = 3;
  inline bool drop_adds_to_browser() const;
  inline void set_drop_adds_to_browser(bool value);
  
  // optional bool follow_cursor = 4 [default = true];
  inline bool has_follow_cursor() const;
  inline void clear_follow_cursor();
  static const int kFollowCursorFieldNumber = 4;
  inline bool follow_cursor() const;
  inline void set_follow_cursor(bool value);
  
  // optional bool show_about_on_startup = 5 [default = true];
  inline bool has_show_about_on_startup() const;
  inline void clear_show_about_on_startup();
  static const int kShowAboutOnStartupFieldNumber = 5;
  inline bool show_about_on_startup() const;
  inline void set_show_about_on_startup(bool value);
  
  // optional bool show_help_pane = 6 [default = true];
  inline bool has_show_help_pane() const;
  inline void clear_show_help_pane();
  static const int kShowHelpPaneFieldNumber = 6;
  inline bool show_help_pane() const;
  inline void set_show_help_pane(bool value);
  
  // optional bool show_master_tune = 7 [default = false];
  inline bool has_show_master_tune() const;
  inline void clear_show_master_tune();
  static const int kShowMasterTuneFieldNumber = 7;
  inline bool show_master_tune() const;
  inline void set_show_master_tune(bool value);
  
  // optional bool show_tooltips = 8 [default = false];
  inline bool has_show_tooltips() const;
  inline void clear_show_tooltips();
  static const int kShowTooltipsFieldNumber = 8;
  inline bool show_tooltips() const;
  inline void set_show_tooltips(bool value);
  
  // optional bool use_tree_view_in_file_dialogs = 9 [default = false];
  inline bool has_use_tree_view_in_file_dialogs() const;
  inline void clear_use_tree_view_in_file_dialogs();
  static const int kUseTreeViewInFileDialogsFieldNumber = 9;
  inline bool use_tree_view_in_file_dialogs() const;
  inline void set_use_tree_view_in_file_dialogs(bool value);
  
  // optional string last_directory = 10;
  inline bool has_last_directory() const;
  inline void clear_last_directory();
  static const int kLastDirectoryFieldNumber = 10;
  inline const ::std::string& last_directory() const;
  inline void set_last_directory(const ::std::string& value);
  inline void set_last_directory(const char* value);
  inline void set_last_directory(const char* value, size_t size);
  inline ::std::string* mutable_last_directory();
  
  // optional .rec.slow.GuiSettings.FileType file_type_for_save = 11 [default = AIFF];
  inline bool has_file_type_for_save() const;
  inline void clear_file_type_for_save();
  static const int kFileTypeForSaveFieldNumber = 11;
  inline ::rec::slow::GuiSettings_FileType file_type_for_save() const;
  inline void set_file_type_for_save(::rec::slow::GuiSettings_FileType value);
  
  // @@protoc_insertion_point(class_scope:rec.slow.GuiSettings)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  bool advanced_menus_;
  bool auto_check_for_updates_;
  bool drop_adds_to_browser_;
  bool follow_cursor_;
  bool show_about_on_startup_;
  bool show_help_pane_;
  bool show_master_tune_;
  bool show_tooltips_;
  bool use_tree_view_in_file_dialogs_;
  ::std::string* last_directory_;
  static const ::std::string _default_last_directory_;
  int file_type_for_save_;
  friend void  protobuf_AddDesc_rec_2fslow_2fGuiSettings_2eproto();
  friend void protobuf_AssignDesc_rec_2fslow_2fGuiSettings_2eproto();
  friend void protobuf_ShutdownFile_rec_2fslow_2fGuiSettings_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(11 + 31) / 32];
  
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

// optional bool advanced_menus = 1 [default = false];
inline bool GuiSettings::has_advanced_menus() const {
  return _has_bit(0);
}
inline void GuiSettings::clear_advanced_menus() {
  advanced_menus_ = false;
  _clear_bit(0);
}
inline bool GuiSettings::advanced_menus() const {
  return advanced_menus_;
}
inline void GuiSettings::set_advanced_menus(bool value) {
  _set_bit(0);
  advanced_menus_ = value;
}

// optional bool auto_check_for_updates = 2 [default = false];
inline bool GuiSettings::has_auto_check_for_updates() const {
  return _has_bit(1);
}
inline void GuiSettings::clear_auto_check_for_updates() {
  auto_check_for_updates_ = false;
  _clear_bit(1);
}
inline bool GuiSettings::auto_check_for_updates() const {
  return auto_check_for_updates_;
}
inline void GuiSettings::set_auto_check_for_updates(bool value) {
  _set_bit(1);
  auto_check_for_updates_ = value;
}

// optional bool drop_adds_to_browser = 3 [default = true];
inline bool GuiSettings::has_drop_adds_to_browser() const {
  return _has_bit(2);
}
inline void GuiSettings::clear_drop_adds_to_browser() {
  drop_adds_to_browser_ = true;
  _clear_bit(2);
}
inline bool GuiSettings::drop_adds_to_browser() const {
  return drop_adds_to_browser_;
}
inline void GuiSettings::set_drop_adds_to_browser(bool value) {
  _set_bit(2);
  drop_adds_to_browser_ = value;
}

// optional bool follow_cursor = 4 [default = true];
inline bool GuiSettings::has_follow_cursor() const {
  return _has_bit(3);
}
inline void GuiSettings::clear_follow_cursor() {
  follow_cursor_ = true;
  _clear_bit(3);
}
inline bool GuiSettings::follow_cursor() const {
  return follow_cursor_;
}
inline void GuiSettings::set_follow_cursor(bool value) {
  _set_bit(3);
  follow_cursor_ = value;
}

// optional bool show_about_on_startup = 5 [default = true];
inline bool GuiSettings::has_show_about_on_startup() const {
  return _has_bit(4);
}
inline void GuiSettings::clear_show_about_on_startup() {
  show_about_on_startup_ = true;
  _clear_bit(4);
}
inline bool GuiSettings::show_about_on_startup() const {
  return show_about_on_startup_;
}
inline void GuiSettings::set_show_about_on_startup(bool value) {
  _set_bit(4);
  show_about_on_startup_ = value;
}

// optional bool show_help_pane = 6 [default = true];
inline bool GuiSettings::has_show_help_pane() const {
  return _has_bit(5);
}
inline void GuiSettings::clear_show_help_pane() {
  show_help_pane_ = true;
  _clear_bit(5);
}
inline bool GuiSettings::show_help_pane() const {
  return show_help_pane_;
}
inline void GuiSettings::set_show_help_pane(bool value) {
  _set_bit(5);
  show_help_pane_ = value;
}

// optional bool show_master_tune = 7 [default = false];
inline bool GuiSettings::has_show_master_tune() const {
  return _has_bit(6);
}
inline void GuiSettings::clear_show_master_tune() {
  show_master_tune_ = false;
  _clear_bit(6);
}
inline bool GuiSettings::show_master_tune() const {
  return show_master_tune_;
}
inline void GuiSettings::set_show_master_tune(bool value) {
  _set_bit(6);
  show_master_tune_ = value;
}

// optional bool show_tooltips = 8 [default = false];
inline bool GuiSettings::has_show_tooltips() const {
  return _has_bit(7);
}
inline void GuiSettings::clear_show_tooltips() {
  show_tooltips_ = false;
  _clear_bit(7);
}
inline bool GuiSettings::show_tooltips() const {
  return show_tooltips_;
}
inline void GuiSettings::set_show_tooltips(bool value) {
  _set_bit(7);
  show_tooltips_ = value;
}

// optional bool use_tree_view_in_file_dialogs = 9 [default = false];
inline bool GuiSettings::has_use_tree_view_in_file_dialogs() const {
  return _has_bit(8);
}
inline void GuiSettings::clear_use_tree_view_in_file_dialogs() {
  use_tree_view_in_file_dialogs_ = false;
  _clear_bit(8);
}
inline bool GuiSettings::use_tree_view_in_file_dialogs() const {
  return use_tree_view_in_file_dialogs_;
}
inline void GuiSettings::set_use_tree_view_in_file_dialogs(bool value) {
  _set_bit(8);
  use_tree_view_in_file_dialogs_ = value;
}

// optional string last_directory = 10;
inline bool GuiSettings::has_last_directory() const {
  return _has_bit(9);
}
inline void GuiSettings::clear_last_directory() {
  if (last_directory_ != &_default_last_directory_) {
    last_directory_->clear();
  }
  _clear_bit(9);
}
inline const ::std::string& GuiSettings::last_directory() const {
  return *last_directory_;
}
inline void GuiSettings::set_last_directory(const ::std::string& value) {
  _set_bit(9);
  if (last_directory_ == &_default_last_directory_) {
    last_directory_ = new ::std::string;
  }
  last_directory_->assign(value);
}
inline void GuiSettings::set_last_directory(const char* value) {
  _set_bit(9);
  if (last_directory_ == &_default_last_directory_) {
    last_directory_ = new ::std::string;
  }
  last_directory_->assign(value);
}
inline void GuiSettings::set_last_directory(const char* value, size_t size) {
  _set_bit(9);
  if (last_directory_ == &_default_last_directory_) {
    last_directory_ = new ::std::string;
  }
  last_directory_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* GuiSettings::mutable_last_directory() {
  _set_bit(9);
  if (last_directory_ == &_default_last_directory_) {
    last_directory_ = new ::std::string;
  }
  return last_directory_;
}

// optional .rec.slow.GuiSettings.FileType file_type_for_save = 11 [default = AIFF];
inline bool GuiSettings::has_file_type_for_save() const {
  return _has_bit(10);
}
inline void GuiSettings::clear_file_type_for_save() {
  file_type_for_save_ = 0;
  _clear_bit(10);
}
inline ::rec::slow::GuiSettings_FileType GuiSettings::file_type_for_save() const {
  return static_cast< ::rec::slow::GuiSettings_FileType >(file_type_for_save_);
}
inline void GuiSettings::set_file_type_for_save(::rec::slow::GuiSettings_FileType value) {
  GOOGLE_DCHECK(::rec::slow::GuiSettings_FileType_IsValid(value));
  _set_bit(10);
  file_type_for_save_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace slow
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::rec::slow::GuiSettings_FileType>() {
  return ::rec::slow::GuiSettings_FileType_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2fslow_2fGuiSettings_2eproto__INCLUDED
