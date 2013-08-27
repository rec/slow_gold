// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/command/Access.proto

#ifndef PROTOBUF_rec_2fcommand_2fAccess_2eproto__INCLUDED
#define PROTOBUF_rec_2fcommand_2fAccess_2eproto__INCLUDED

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
// @@protoc_insertion_point(includes)

namespace rec {
namespace command {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fcommand_2fAccess_2eproto();
void protobuf_AssignDesc_rec_2fcommand_2fAccess_2eproto();
void protobuf_ShutdownFile_rec_2fcommand_2fAccess_2eproto();

class Global;
class Input;
class Output;
class Access;

// ===================================================================

class Global : public ::google::protobuf::Message {
 public:
  Global();
  virtual ~Global();

  Global(const Global& from);

  inline Global& operator=(const Global& from) {
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
  static const Global& default_instance();

  void Swap(Global* other);

  // implements Message ----------------------------------------------

  Global* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Global& from);
  void MergeFrom(const Global& from);
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

  // optional string language = 1 [default = "en"];
  inline bool has_language() const;
  inline void clear_language();
  static const int kLanguageFieldNumber = 1;
  inline const ::std::string& language() const;
  inline void set_language(const ::std::string& value);
  inline void set_language(const char* value);
  inline void set_language(const char* value, size_t size);
  inline ::std::string* mutable_language();
  inline ::std::string* release_language();
  inline void set_allocated_language(::std::string* language);

  // optional string locale = 2;
  inline bool has_locale() const;
  inline void clear_locale();
  static const int kLocaleFieldNumber = 2;
  inline const ::std::string& locale() const;
  inline void set_locale(const ::std::string& value);
  inline void set_locale(const char* value);
  inline void set_locale(const char* value, size_t size);
  inline ::std::string* mutable_locale();
  inline ::std::string* release_locale();
  inline void set_allocated_locale(::std::string* locale);

  // @@protoc_insertion_point(class_scope:rec.command.Global)
 private:
  inline void set_has_language();
  inline void clear_has_language();
  inline void set_has_locale();
  inline void clear_has_locale();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* language_;
  static ::std::string* _default_language_;
  ::std::string* locale_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_rec_2fcommand_2fAccess_2eproto();
  friend void protobuf_AssignDesc_rec_2fcommand_2fAccess_2eproto();
  friend void protobuf_ShutdownFile_rec_2fcommand_2fAccess_2eproto();

  void InitAsDefaultInstance();
  static Global* default_instance_;
};
// -------------------------------------------------------------------

class Input : public ::google::protobuf::Message {
 public:
  Input();
  virtual ~Input();

  Input(const Input& from);

  inline Input& operator=(const Input& from) {
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
  static const Input& default_instance();

  void Swap(Input* other);

  // implements Message ----------------------------------------------

  Input* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Input& from);
  void MergeFrom(const Input& from);
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

  // @@protoc_insertion_point(class_scope:rec.command.Input)
 private:
  inline void set_has_name();
  inline void clear_has_name();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* name_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_rec_2fcommand_2fAccess_2eproto();
  friend void protobuf_AssignDesc_rec_2fcommand_2fAccess_2eproto();
  friend void protobuf_ShutdownFile_rec_2fcommand_2fAccess_2eproto();

  void InitAsDefaultInstance();
  static Input* default_instance_;
};
// -------------------------------------------------------------------

class Output : public ::google::protobuf::Message {
 public:
  Output();
  virtual ~Output();

  Output(const Output& from);

  inline Output& operator=(const Output& from) {
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
  static const Output& default_instance();

  void Swap(Output* other);

  // implements Message ----------------------------------------------

  Output* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Output& from);
  void MergeFrom(const Output& from);
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

  // @@protoc_insertion_point(class_scope:rec.command.Output)
 private:
  inline void set_has_name();
  inline void clear_has_name();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* name_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_rec_2fcommand_2fAccess_2eproto();
  friend void protobuf_AssignDesc_rec_2fcommand_2fAccess_2eproto();
  friend void protobuf_ShutdownFile_rec_2fcommand_2fAccess_2eproto();

  void InitAsDefaultInstance();
  static Output* default_instance_;
};
// -------------------------------------------------------------------

class Access : public ::google::protobuf::Message {
 public:
  Access();
  virtual ~Access();

  Access(const Access& from);

  inline Access& operator=(const Access& from) {
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
  static const Access& default_instance();

  void Swap(Access* other);

  // implements Message ----------------------------------------------

  Access* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Access& from);
  void MergeFrom(const Access& from);
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

  // optional .rec.command.Global global = 1;
  inline bool has_global() const;
  inline void clear_global();
  static const int kGlobalFieldNumber = 1;
  inline const ::rec::command::Global& global() const;
  inline ::rec::command::Global* mutable_global();
  inline ::rec::command::Global* release_global();
  inline void set_allocated_global(::rec::command::Global* global);

  // repeated .rec.command.Input input = 2;
  inline int input_size() const;
  inline void clear_input();
  static const int kInputFieldNumber = 2;
  inline const ::rec::command::Input& input(int index) const;
  inline ::rec::command::Input* mutable_input(int index);
  inline ::rec::command::Input* add_input();
  inline const ::google::protobuf::RepeatedPtrField< ::rec::command::Input >&
      input() const;
  inline ::google::protobuf::RepeatedPtrField< ::rec::command::Input >*
      mutable_input();

  // repeated .rec.command.Output output = 3;
  inline int output_size() const;
  inline void clear_output();
  static const int kOutputFieldNumber = 3;
  inline const ::rec::command::Output& output(int index) const;
  inline ::rec::command::Output* mutable_output(int index);
  inline ::rec::command::Output* add_output();
  inline const ::google::protobuf::RepeatedPtrField< ::rec::command::Output >&
      output() const;
  inline ::google::protobuf::RepeatedPtrField< ::rec::command::Output >*
      mutable_output();

  // @@protoc_insertion_point(class_scope:rec.command.Access)
 private:
  inline void set_has_global();
  inline void clear_has_global();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::rec::command::Global* global_;
  ::google::protobuf::RepeatedPtrField< ::rec::command::Input > input_;
  ::google::protobuf::RepeatedPtrField< ::rec::command::Output > output_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_rec_2fcommand_2fAccess_2eproto();
  friend void protobuf_AssignDesc_rec_2fcommand_2fAccess_2eproto();
  friend void protobuf_ShutdownFile_rec_2fcommand_2fAccess_2eproto();

  void InitAsDefaultInstance();
  static Access* default_instance_;
};
// ===================================================================


// ===================================================================

// Global

// optional string language = 1 [default = "en"];
inline bool Global::has_language() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Global::set_has_language() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Global::clear_has_language() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Global::clear_language() {
  if (language_ != _default_language_) {
    language_->assign(*_default_language_);
  }
  clear_has_language();
}
inline const ::std::string& Global::language() const {
  return *language_;
}
inline void Global::set_language(const ::std::string& value) {
  set_has_language();
  if (language_ == _default_language_) {
    language_ = new ::std::string;
  }
  language_->assign(value);
}
inline void Global::set_language(const char* value) {
  set_has_language();
  if (language_ == _default_language_) {
    language_ = new ::std::string;
  }
  language_->assign(value);
}
inline void Global::set_language(const char* value, size_t size) {
  set_has_language();
  if (language_ == _default_language_) {
    language_ = new ::std::string;
  }
  language_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Global::mutable_language() {
  set_has_language();
  if (language_ == _default_language_) {
    language_ = new ::std::string(*_default_language_);
  }
  return language_;
}
inline ::std::string* Global::release_language() {
  clear_has_language();
  if (language_ == _default_language_) {
    return NULL;
  } else {
    ::std::string* temp = language_;
    language_ = const_cast< ::std::string*>(_default_language_);
    return temp;
  }
}
inline void Global::set_allocated_language(::std::string* language) {
  if (language_ != _default_language_) {
    delete language_;
  }
  if (language) {
    set_has_language();
    language_ = language;
  } else {
    clear_has_language();
    language_ = const_cast< ::std::string*>(_default_language_);
  }
}

// optional string locale = 2;
inline bool Global::has_locale() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Global::set_has_locale() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Global::clear_has_locale() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Global::clear_locale() {
  if (locale_ != &::google::protobuf::internal::kEmptyString) {
    locale_->clear();
  }
  clear_has_locale();
}
inline const ::std::string& Global::locale() const {
  return *locale_;
}
inline void Global::set_locale(const ::std::string& value) {
  set_has_locale();
  if (locale_ == &::google::protobuf::internal::kEmptyString) {
    locale_ = new ::std::string;
  }
  locale_->assign(value);
}
inline void Global::set_locale(const char* value) {
  set_has_locale();
  if (locale_ == &::google::protobuf::internal::kEmptyString) {
    locale_ = new ::std::string;
  }
  locale_->assign(value);
}
inline void Global::set_locale(const char* value, size_t size) {
  set_has_locale();
  if (locale_ == &::google::protobuf::internal::kEmptyString) {
    locale_ = new ::std::string;
  }
  locale_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Global::mutable_locale() {
  set_has_locale();
  if (locale_ == &::google::protobuf::internal::kEmptyString) {
    locale_ = new ::std::string;
  }
  return locale_;
}
inline ::std::string* Global::release_locale() {
  clear_has_locale();
  if (locale_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = locale_;
    locale_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Global::set_allocated_locale(::std::string* locale) {
  if (locale_ != &::google::protobuf::internal::kEmptyString) {
    delete locale_;
  }
  if (locale) {
    set_has_locale();
    locale_ = locale;
  } else {
    clear_has_locale();
    locale_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// Input

// optional string name = 1;
inline bool Input::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Input::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Input::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Input::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& Input::name() const {
  return *name_;
}
inline void Input::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Input::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Input::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Input::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* Input::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Input::set_allocated_name(::std::string* name) {
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

// -------------------------------------------------------------------

// Output

// optional string name = 1;
inline bool Output::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Output::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Output::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Output::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& Output::name() const {
  return *name_;
}
inline void Output::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Output::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Output::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Output::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* Output::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Output::set_allocated_name(::std::string* name) {
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

// -------------------------------------------------------------------

// Access

// optional .rec.command.Global global = 1;
inline bool Access::has_global() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Access::set_has_global() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Access::clear_has_global() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Access::clear_global() {
  if (global_ != NULL) global_->::rec::command::Global::Clear();
  clear_has_global();
}
inline const ::rec::command::Global& Access::global() const {
  return global_ != NULL ? *global_ : *default_instance_->global_;
}
inline ::rec::command::Global* Access::mutable_global() {
  set_has_global();
  if (global_ == NULL) global_ = new ::rec::command::Global;
  return global_;
}
inline ::rec::command::Global* Access::release_global() {
  clear_has_global();
  ::rec::command::Global* temp = global_;
  global_ = NULL;
  return temp;
}
inline void Access::set_allocated_global(::rec::command::Global* global) {
  delete global_;
  global_ = global;
  if (global) {
    set_has_global();
  } else {
    clear_has_global();
  }
}

// repeated .rec.command.Input input = 2;
inline int Access::input_size() const {
  return input_.size();
}
inline void Access::clear_input() {
  input_.Clear();
}
inline const ::rec::command::Input& Access::input(int index) const {
  return input_.Get(index);
}
inline ::rec::command::Input* Access::mutable_input(int index) {
  return input_.Mutable(index);
}
inline ::rec::command::Input* Access::add_input() {
  return input_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::rec::command::Input >&
Access::input() const {
  return input_;
}
inline ::google::protobuf::RepeatedPtrField< ::rec::command::Input >*
Access::mutable_input() {
  return &input_;
}

// repeated .rec.command.Output output = 3;
inline int Access::output_size() const {
  return output_.size();
}
inline void Access::clear_output() {
  output_.Clear();
}
inline const ::rec::command::Output& Access::output(int index) const {
  return output_.Get(index);
}
inline ::rec::command::Output* Access::mutable_output(int index) {
  return output_.Mutable(index);
}
inline ::rec::command::Output* Access::add_output() {
  return output_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::rec::command::Output >&
Access::output() const {
  return output_;
}
inline ::google::protobuf::RepeatedPtrField< ::rec::command::Output >*
Access::mutable_output() {
  return &output_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace command
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2fcommand_2fAccess_2eproto__INCLUDED
