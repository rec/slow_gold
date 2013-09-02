// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/app/Menu.proto

#ifndef PROTOBUF_rec_2fapp_2fMenu_2eproto__INCLUDED
#define PROTOBUF_rec_2fapp_2fMenu_2eproto__INCLUDED

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
#include "rec/command/Command.pb.h"
// @@protoc_insertion_point(includes)

namespace rec {
namespace app {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fapp_2fMenu_2eproto();
void protobuf_AssignDesc_rec_2fapp_2fMenu_2eproto();
void protobuf_ShutdownFile_rec_2fapp_2fMenu_2eproto();

class MenuEntry;
class Menu;
class Menus;
class MenuBar;
class MenuCollection;

// ===================================================================

class MenuEntry : public ::google::protobuf::Message {
 public:
  MenuEntry();
  virtual ~MenuEntry();

  MenuEntry(const MenuEntry& from);

  inline MenuEntry& operator=(const MenuEntry& from) {
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
  static const MenuEntry& default_instance();

  void Swap(MenuEntry* other);

  // implements Message ----------------------------------------------

  MenuEntry* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MenuEntry& from);
  void MergeFrom(const MenuEntry& from);
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

  // optional uint32 command = 1;
  inline bool has_command() const;
  inline void clear_command();
  static const int kCommandFieldNumber = 1;
  inline ::google::protobuf::uint32 command() const;
  inline void set_command(::google::protobuf::uint32 value);

  // optional string submenu = 2;
  inline bool has_submenu() const;
  inline void clear_submenu();
  static const int kSubmenuFieldNumber = 2;
  inline const ::std::string& submenu() const;
  inline void set_submenu(const ::std::string& value);
  inline void set_submenu(const char* value);
  inline void set_submenu(const char* value, size_t size);
  inline ::std::string* mutable_submenu();
  inline ::std::string* release_submenu();
  inline void set_allocated_submenu(::std::string* submenu);

  // optional bool is_recent_files_menu = 3;
  inline bool has_is_recent_files_menu() const;
  inline void clear_is_recent_files_menu();
  static const int kIsRecentFilesMenuFieldNumber = 3;
  inline bool is_recent_files_menu() const;
  inline void set_is_recent_files_menu(bool value);

  // optional string callout_function = 4;
  inline bool has_callout_function() const;
  inline void clear_callout_function();
  static const int kCalloutFunctionFieldNumber = 4;
  inline const ::std::string& callout_function() const;
  inline void set_callout_function(const ::std::string& value);
  inline void set_callout_function(const char* value);
  inline void set_callout_function(const char* value, size_t size);
  inline ::std::string* mutable_callout_function();
  inline ::std::string* release_callout_function();
  inline void set_allocated_callout_function(::std::string* callout_function);

  // @@protoc_insertion_point(class_scope:rec.app.MenuEntry)
 private:
  inline void set_has_command();
  inline void clear_has_command();
  inline void set_has_submenu();
  inline void clear_has_submenu();
  inline void set_has_is_recent_files_menu();
  inline void clear_has_is_recent_files_menu();
  inline void set_has_callout_function();
  inline void clear_has_callout_function();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* submenu_;
  ::google::protobuf::uint32 command_;
  bool is_recent_files_menu_;
  ::std::string* callout_function_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];

  friend void  protobuf_AddDesc_rec_2fapp_2fMenu_2eproto();
  friend void protobuf_AssignDesc_rec_2fapp_2fMenu_2eproto();
  friend void protobuf_ShutdownFile_rec_2fapp_2fMenu_2eproto();

  void InitAsDefaultInstance();
  static MenuEntry* default_instance_;
};
// -------------------------------------------------------------------

class Menu : public ::google::protobuf::Message {
 public:
  Menu();
  virtual ~Menu();

  Menu(const Menu& from);

  inline Menu& operator=(const Menu& from) {
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
  static const Menu& default_instance();

  void Swap(Menu* other);

  // implements Message ----------------------------------------------

  Menu* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Menu& from);
  void MergeFrom(const Menu& from);
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

  // optional .rec.command.Description description = 1;
  inline bool has_description() const;
  inline void clear_description();
  static const int kDescriptionFieldNumber = 1;
  inline const ::rec::command::Description& description() const;
  inline ::rec::command::Description* mutable_description();
  inline ::rec::command::Description* release_description();
  inline void set_allocated_description(::rec::command::Description* description);

  // repeated .rec.app.MenuEntry entry = 2;
  inline int entry_size() const;
  inline void clear_entry();
  static const int kEntryFieldNumber = 2;
  inline const ::rec::app::MenuEntry& entry(int index) const;
  inline ::rec::app::MenuEntry* mutable_entry(int index);
  inline ::rec::app::MenuEntry* add_entry();
  inline const ::google::protobuf::RepeatedPtrField< ::rec::app::MenuEntry >&
      entry() const;
  inline ::google::protobuf::RepeatedPtrField< ::rec::app::MenuEntry >*
      mutable_entry();

  // @@protoc_insertion_point(class_scope:rec.app.Menu)
 private:
  inline void set_has_description();
  inline void clear_has_description();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::rec::command::Description* description_;
  ::google::protobuf::RepeatedPtrField< ::rec::app::MenuEntry > entry_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_rec_2fapp_2fMenu_2eproto();
  friend void protobuf_AssignDesc_rec_2fapp_2fMenu_2eproto();
  friend void protobuf_ShutdownFile_rec_2fapp_2fMenu_2eproto();

  void InitAsDefaultInstance();
  static Menu* default_instance_;
};
// -------------------------------------------------------------------

class Menus : public ::google::protobuf::Message {
 public:
  Menus();
  virtual ~Menus();

  Menus(const Menus& from);

  inline Menus& operator=(const Menus& from) {
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
  static const Menus& default_instance();

  void Swap(Menus* other);

  // implements Message ----------------------------------------------

  Menus* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Menus& from);
  void MergeFrom(const Menus& from);
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

  // repeated .rec.app.Menu menu = 1;
  inline int menu_size() const;
  inline void clear_menu();
  static const int kMenuFieldNumber = 1;
  inline const ::rec::app::Menu& menu(int index) const;
  inline ::rec::app::Menu* mutable_menu(int index);
  inline ::rec::app::Menu* add_menu();
  inline const ::google::protobuf::RepeatedPtrField< ::rec::app::Menu >&
      menu() const;
  inline ::google::protobuf::RepeatedPtrField< ::rec::app::Menu >*
      mutable_menu();

  // @@protoc_insertion_point(class_scope:rec.app.Menus)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::rec::app::Menu > menu_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_rec_2fapp_2fMenu_2eproto();
  friend void protobuf_AssignDesc_rec_2fapp_2fMenu_2eproto();
  friend void protobuf_ShutdownFile_rec_2fapp_2fMenu_2eproto();

  void InitAsDefaultInstance();
  static Menus* default_instance_;
};
// -------------------------------------------------------------------

class MenuBar : public ::google::protobuf::Message {
 public:
  MenuBar();
  virtual ~MenuBar();

  MenuBar(const MenuBar& from);

  inline MenuBar& operator=(const MenuBar& from) {
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
  static const MenuBar& default_instance();

  void Swap(MenuBar* other);

  // implements Message ----------------------------------------------

  MenuBar* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MenuBar& from);
  void MergeFrom(const MenuBar& from);
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

  // optional .rec.command.Description description = 1;
  inline bool has_description() const;
  inline void clear_description();
  static const int kDescriptionFieldNumber = 1;
  inline const ::rec::command::Description& description() const;
  inline ::rec::command::Description* mutable_description();
  inline ::rec::command::Description* release_description();
  inline void set_allocated_description(::rec::command::Description* description);

  // repeated string menu = 2;
  inline int menu_size() const;
  inline void clear_menu();
  static const int kMenuFieldNumber = 2;
  inline const ::std::string& menu(int index) const;
  inline ::std::string* mutable_menu(int index);
  inline void set_menu(int index, const ::std::string& value);
  inline void set_menu(int index, const char* value);
  inline void set_menu(int index, const char* value, size_t size);
  inline ::std::string* add_menu();
  inline void add_menu(const ::std::string& value);
  inline void add_menu(const char* value);
  inline void add_menu(const char* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& menu() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_menu();

  // @@protoc_insertion_point(class_scope:rec.app.MenuBar)
 private:
  inline void set_has_description();
  inline void clear_has_description();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::rec::command::Description* description_;
  ::google::protobuf::RepeatedPtrField< ::std::string> menu_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_rec_2fapp_2fMenu_2eproto();
  friend void protobuf_AssignDesc_rec_2fapp_2fMenu_2eproto();
  friend void protobuf_ShutdownFile_rec_2fapp_2fMenu_2eproto();

  void InitAsDefaultInstance();
  static MenuBar* default_instance_;
};
// -------------------------------------------------------------------

class MenuCollection : public ::google::protobuf::Message {
 public:
  MenuCollection();
  virtual ~MenuCollection();

  MenuCollection(const MenuCollection& from);

  inline MenuCollection& operator=(const MenuCollection& from) {
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
  static const MenuCollection& default_instance();

  void Swap(MenuCollection* other);

  // implements Message ----------------------------------------------

  MenuCollection* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MenuCollection& from);
  void MergeFrom(const MenuCollection& from);
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

  // optional .rec.command.Description description = 1;
  inline bool has_description() const;
  inline void clear_description();
  static const int kDescriptionFieldNumber = 1;
  inline const ::rec::command::Description& description() const;
  inline ::rec::command::Description* mutable_description();
  inline ::rec::command::Description* release_description();
  inline void set_allocated_description(::rec::command::Description* description);

  // repeated .rec.app.MenuBar menu_bar = 2;
  inline int menu_bar_size() const;
  inline void clear_menu_bar();
  static const int kMenuBarFieldNumber = 2;
  inline const ::rec::app::MenuBar& menu_bar(int index) const;
  inline ::rec::app::MenuBar* mutable_menu_bar(int index);
  inline ::rec::app::MenuBar* add_menu_bar();
  inline const ::google::protobuf::RepeatedPtrField< ::rec::app::MenuBar >&
      menu_bar() const;
  inline ::google::protobuf::RepeatedPtrField< ::rec::app::MenuBar >*
      mutable_menu_bar();

  // @@protoc_insertion_point(class_scope:rec.app.MenuCollection)
 private:
  inline void set_has_description();
  inline void clear_has_description();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::rec::command::Description* description_;
  ::google::protobuf::RepeatedPtrField< ::rec::app::MenuBar > menu_bar_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_rec_2fapp_2fMenu_2eproto();
  friend void protobuf_AssignDesc_rec_2fapp_2fMenu_2eproto();
  friend void protobuf_ShutdownFile_rec_2fapp_2fMenu_2eproto();

  void InitAsDefaultInstance();
  static MenuCollection* default_instance_;
};
// ===================================================================


// ===================================================================

// MenuEntry

// optional uint32 command = 1;
inline bool MenuEntry::has_command() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MenuEntry::set_has_command() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MenuEntry::clear_has_command() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MenuEntry::clear_command() {
  command_ = 0u;
  clear_has_command();
}
inline ::google::protobuf::uint32 MenuEntry::command() const {
  return command_;
}
inline void MenuEntry::set_command(::google::protobuf::uint32 value) {
  set_has_command();
  command_ = value;
}

// optional string submenu = 2;
inline bool MenuEntry::has_submenu() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MenuEntry::set_has_submenu() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MenuEntry::clear_has_submenu() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MenuEntry::clear_submenu() {
  if (submenu_ != &::google::protobuf::internal::kEmptyString) {
    submenu_->clear();
  }
  clear_has_submenu();
}
inline const ::std::string& MenuEntry::submenu() const {
  return *submenu_;
}
inline void MenuEntry::set_submenu(const ::std::string& value) {
  set_has_submenu();
  if (submenu_ == &::google::protobuf::internal::kEmptyString) {
    submenu_ = new ::std::string;
  }
  submenu_->assign(value);
}
inline void MenuEntry::set_submenu(const char* value) {
  set_has_submenu();
  if (submenu_ == &::google::protobuf::internal::kEmptyString) {
    submenu_ = new ::std::string;
  }
  submenu_->assign(value);
}
inline void MenuEntry::set_submenu(const char* value, size_t size) {
  set_has_submenu();
  if (submenu_ == &::google::protobuf::internal::kEmptyString) {
    submenu_ = new ::std::string;
  }
  submenu_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* MenuEntry::mutable_submenu() {
  set_has_submenu();
  if (submenu_ == &::google::protobuf::internal::kEmptyString) {
    submenu_ = new ::std::string;
  }
  return submenu_;
}
inline ::std::string* MenuEntry::release_submenu() {
  clear_has_submenu();
  if (submenu_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = submenu_;
    submenu_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void MenuEntry::set_allocated_submenu(::std::string* submenu) {
  if (submenu_ != &::google::protobuf::internal::kEmptyString) {
    delete submenu_;
  }
  if (submenu) {
    set_has_submenu();
    submenu_ = submenu;
  } else {
    clear_has_submenu();
    submenu_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional bool is_recent_files_menu = 3;
inline bool MenuEntry::has_is_recent_files_menu() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void MenuEntry::set_has_is_recent_files_menu() {
  _has_bits_[0] |= 0x00000004u;
}
inline void MenuEntry::clear_has_is_recent_files_menu() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void MenuEntry::clear_is_recent_files_menu() {
  is_recent_files_menu_ = false;
  clear_has_is_recent_files_menu();
}
inline bool MenuEntry::is_recent_files_menu() const {
  return is_recent_files_menu_;
}
inline void MenuEntry::set_is_recent_files_menu(bool value) {
  set_has_is_recent_files_menu();
  is_recent_files_menu_ = value;
}

// optional string callout_function = 4;
inline bool MenuEntry::has_callout_function() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void MenuEntry::set_has_callout_function() {
  _has_bits_[0] |= 0x00000008u;
}
inline void MenuEntry::clear_has_callout_function() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void MenuEntry::clear_callout_function() {
  if (callout_function_ != &::google::protobuf::internal::kEmptyString) {
    callout_function_->clear();
  }
  clear_has_callout_function();
}
inline const ::std::string& MenuEntry::callout_function() const {
  return *callout_function_;
}
inline void MenuEntry::set_callout_function(const ::std::string& value) {
  set_has_callout_function();
  if (callout_function_ == &::google::protobuf::internal::kEmptyString) {
    callout_function_ = new ::std::string;
  }
  callout_function_->assign(value);
}
inline void MenuEntry::set_callout_function(const char* value) {
  set_has_callout_function();
  if (callout_function_ == &::google::protobuf::internal::kEmptyString) {
    callout_function_ = new ::std::string;
  }
  callout_function_->assign(value);
}
inline void MenuEntry::set_callout_function(const char* value, size_t size) {
  set_has_callout_function();
  if (callout_function_ == &::google::protobuf::internal::kEmptyString) {
    callout_function_ = new ::std::string;
  }
  callout_function_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* MenuEntry::mutable_callout_function() {
  set_has_callout_function();
  if (callout_function_ == &::google::protobuf::internal::kEmptyString) {
    callout_function_ = new ::std::string;
  }
  return callout_function_;
}
inline ::std::string* MenuEntry::release_callout_function() {
  clear_has_callout_function();
  if (callout_function_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = callout_function_;
    callout_function_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void MenuEntry::set_allocated_callout_function(::std::string* callout_function) {
  if (callout_function_ != &::google::protobuf::internal::kEmptyString) {
    delete callout_function_;
  }
  if (callout_function) {
    set_has_callout_function();
    callout_function_ = callout_function;
  } else {
    clear_has_callout_function();
    callout_function_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// Menu

// optional .rec.command.Description description = 1;
inline bool Menu::has_description() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Menu::set_has_description() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Menu::clear_has_description() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Menu::clear_description() {
  if (description_ != NULL) description_->::rec::command::Description::Clear();
  clear_has_description();
}
inline const ::rec::command::Description& Menu::description() const {
  return description_ != NULL ? *description_ : *default_instance_->description_;
}
inline ::rec::command::Description* Menu::mutable_description() {
  set_has_description();
  if (description_ == NULL) description_ = new ::rec::command::Description;
  return description_;
}
inline ::rec::command::Description* Menu::release_description() {
  clear_has_description();
  ::rec::command::Description* temp = description_;
  description_ = NULL;
  return temp;
}
inline void Menu::set_allocated_description(::rec::command::Description* description) {
  delete description_;
  description_ = description;
  if (description) {
    set_has_description();
  } else {
    clear_has_description();
  }
}

// repeated .rec.app.MenuEntry entry = 2;
inline int Menu::entry_size() const {
  return entry_.size();
}
inline void Menu::clear_entry() {
  entry_.Clear();
}
inline const ::rec::app::MenuEntry& Menu::entry(int index) const {
  return entry_.Get(index);
}
inline ::rec::app::MenuEntry* Menu::mutable_entry(int index) {
  return entry_.Mutable(index);
}
inline ::rec::app::MenuEntry* Menu::add_entry() {
  return entry_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::rec::app::MenuEntry >&
Menu::entry() const {
  return entry_;
}
inline ::google::protobuf::RepeatedPtrField< ::rec::app::MenuEntry >*
Menu::mutable_entry() {
  return &entry_;
}

// -------------------------------------------------------------------

// Menus

// repeated .rec.app.Menu menu = 1;
inline int Menus::menu_size() const {
  return menu_.size();
}
inline void Menus::clear_menu() {
  menu_.Clear();
}
inline const ::rec::app::Menu& Menus::menu(int index) const {
  return menu_.Get(index);
}
inline ::rec::app::Menu* Menus::mutable_menu(int index) {
  return menu_.Mutable(index);
}
inline ::rec::app::Menu* Menus::add_menu() {
  return menu_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::rec::app::Menu >&
Menus::menu() const {
  return menu_;
}
inline ::google::protobuf::RepeatedPtrField< ::rec::app::Menu >*
Menus::mutable_menu() {
  return &menu_;
}

// -------------------------------------------------------------------

// MenuBar

// optional .rec.command.Description description = 1;
inline bool MenuBar::has_description() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MenuBar::set_has_description() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MenuBar::clear_has_description() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MenuBar::clear_description() {
  if (description_ != NULL) description_->::rec::command::Description::Clear();
  clear_has_description();
}
inline const ::rec::command::Description& MenuBar::description() const {
  return description_ != NULL ? *description_ : *default_instance_->description_;
}
inline ::rec::command::Description* MenuBar::mutable_description() {
  set_has_description();
  if (description_ == NULL) description_ = new ::rec::command::Description;
  return description_;
}
inline ::rec::command::Description* MenuBar::release_description() {
  clear_has_description();
  ::rec::command::Description* temp = description_;
  description_ = NULL;
  return temp;
}
inline void MenuBar::set_allocated_description(::rec::command::Description* description) {
  delete description_;
  description_ = description;
  if (description) {
    set_has_description();
  } else {
    clear_has_description();
  }
}

// repeated string menu = 2;
inline int MenuBar::menu_size() const {
  return menu_.size();
}
inline void MenuBar::clear_menu() {
  menu_.Clear();
}
inline const ::std::string& MenuBar::menu(int index) const {
  return menu_.Get(index);
}
inline ::std::string* MenuBar::mutable_menu(int index) {
  return menu_.Mutable(index);
}
inline void MenuBar::set_menu(int index, const ::std::string& value) {
  menu_.Mutable(index)->assign(value);
}
inline void MenuBar::set_menu(int index, const char* value) {
  menu_.Mutable(index)->assign(value);
}
inline void MenuBar::set_menu(int index, const char* value, size_t size) {
  menu_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
}
inline ::std::string* MenuBar::add_menu() {
  return menu_.Add();
}
inline void MenuBar::add_menu(const ::std::string& value) {
  menu_.Add()->assign(value);
}
inline void MenuBar::add_menu(const char* value) {
  menu_.Add()->assign(value);
}
inline void MenuBar::add_menu(const char* value, size_t size) {
  menu_.Add()->assign(reinterpret_cast<const char*>(value), size);
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
MenuBar::menu() const {
  return menu_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
MenuBar::mutable_menu() {
  return &menu_;
}

// -------------------------------------------------------------------

// MenuCollection

// optional .rec.command.Description description = 1;
inline bool MenuCollection::has_description() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MenuCollection::set_has_description() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MenuCollection::clear_has_description() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MenuCollection::clear_description() {
  if (description_ != NULL) description_->::rec::command::Description::Clear();
  clear_has_description();
}
inline const ::rec::command::Description& MenuCollection::description() const {
  return description_ != NULL ? *description_ : *default_instance_->description_;
}
inline ::rec::command::Description* MenuCollection::mutable_description() {
  set_has_description();
  if (description_ == NULL) description_ = new ::rec::command::Description;
  return description_;
}
inline ::rec::command::Description* MenuCollection::release_description() {
  clear_has_description();
  ::rec::command::Description* temp = description_;
  description_ = NULL;
  return temp;
}
inline void MenuCollection::set_allocated_description(::rec::command::Description* description) {
  delete description_;
  description_ = description;
  if (description) {
    set_has_description();
  } else {
    clear_has_description();
  }
}

// repeated .rec.app.MenuBar menu_bar = 2;
inline int MenuCollection::menu_bar_size() const {
  return menu_bar_.size();
}
inline void MenuCollection::clear_menu_bar() {
  menu_bar_.Clear();
}
inline const ::rec::app::MenuBar& MenuCollection::menu_bar(int index) const {
  return menu_bar_.Get(index);
}
inline ::rec::app::MenuBar* MenuCollection::mutable_menu_bar(int index) {
  return menu_bar_.Mutable(index);
}
inline ::rec::app::MenuBar* MenuCollection::add_menu_bar() {
  return menu_bar_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::rec::app::MenuBar >&
MenuCollection::menu_bar() const {
  return menu_bar_;
}
inline ::google::protobuf::RepeatedPtrField< ::rec::app::MenuBar >*
MenuCollection::mutable_menu_bar() {
  return &menu_bar_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace app
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2fapp_2fMenu_2eproto__INCLUDED
