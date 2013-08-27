// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/gui/TableColumn.proto

#ifndef PROTOBUF_rec_2fgui_2fTableColumn_2eproto__INCLUDED
#define PROTOBUF_rec_2fgui_2fTableColumn_2eproto__INCLUDED

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
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
#include "rec/data/proto/Address.pb.h"
// @@protoc_insertion_point(includes)

namespace rec {
namespace gui {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fgui_2fTableColumn_2eproto();
void protobuf_AssignDesc_rec_2fgui_2fTableColumn_2eproto();
void protobuf_ShutdownFile_rec_2fgui_2fTableColumn_2eproto();

class TableColumn;
class TableColumnList;

enum TableColumn_Properties {
  TableColumn_Properties_VISIBLE = 1,
  TableColumn_Properties_RESIZABLE = 2,
  TableColumn_Properties_DRAGGABLE = 4,
  TableColumn_Properties_APPEARS_ON_COLUMN_MENU = 8,
  TableColumn_Properties_SORTABLE = 16,
  TableColumn_Properties_SORTED_FORWARDS = 32,
  TableColumn_Properties_SORTED_BACKWARDS = 64,
  TableColumn_Properties_EDITABLE = 128,
  TableColumn_Properties_DEFAULT = 143,
  TableColumn_Properties_DEFAULT_NOT_EDITABLE = 15
};
bool TableColumn_Properties_IsValid(int value);
const TableColumn_Properties TableColumn_Properties_Properties_MIN = TableColumn_Properties_VISIBLE;
const TableColumn_Properties TableColumn_Properties_Properties_MAX = TableColumn_Properties_DEFAULT;
const int TableColumn_Properties_Properties_ARRAYSIZE = TableColumn_Properties_Properties_MAX + 1;

const ::google::protobuf::EnumDescriptor* TableColumn_Properties_descriptor();
inline const ::std::string& TableColumn_Properties_Name(TableColumn_Properties value) {
  return ::google::protobuf::internal::NameOfEnum(
    TableColumn_Properties_descriptor(), value);
}
inline bool TableColumn_Properties_Parse(
    const ::std::string& name, TableColumn_Properties* value) {
  return ::google::protobuf::internal::ParseNamedEnum<TableColumn_Properties>(
    TableColumn_Properties_descriptor(), name, value);
}
enum TableColumn_Type {
  TableColumn_Type_STRING = 1,
  TableColumn_Type_TIME = 2,
  TableColumn_Type_UINT32 = 3,
  TableColumn_Type_DOUBLE = 4
};
bool TableColumn_Type_IsValid(int value);
const TableColumn_Type TableColumn_Type_Type_MIN = TableColumn_Type_STRING;
const TableColumn_Type TableColumn_Type_Type_MAX = TableColumn_Type_DOUBLE;
const int TableColumn_Type_Type_ARRAYSIZE = TableColumn_Type_Type_MAX + 1;

const ::google::protobuf::EnumDescriptor* TableColumn_Type_descriptor();
inline const ::std::string& TableColumn_Type_Name(TableColumn_Type value) {
  return ::google::protobuf::internal::NameOfEnum(
    TableColumn_Type_descriptor(), value);
}
inline bool TableColumn_Type_Parse(
    const ::std::string& name, TableColumn_Type* value) {
  return ::google::protobuf::internal::ParseNamedEnum<TableColumn_Type>(
    TableColumn_Type_descriptor(), name, value);
}
// ===================================================================

class TableColumn : public ::google::protobuf::Message {
 public:
  TableColumn();
  virtual ~TableColumn();

  TableColumn(const TableColumn& from);

  inline TableColumn& operator=(const TableColumn& from) {
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
  static const TableColumn& default_instance();

  void Swap(TableColumn* other);

  // implements Message ----------------------------------------------

  TableColumn* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TableColumn& from);
  void MergeFrom(const TableColumn& from);
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

  typedef TableColumn_Properties Properties;
  static const Properties VISIBLE = TableColumn_Properties_VISIBLE;
  static const Properties RESIZABLE = TableColumn_Properties_RESIZABLE;
  static const Properties DRAGGABLE = TableColumn_Properties_DRAGGABLE;
  static const Properties APPEARS_ON_COLUMN_MENU = TableColumn_Properties_APPEARS_ON_COLUMN_MENU;
  static const Properties SORTABLE = TableColumn_Properties_SORTABLE;
  static const Properties SORTED_FORWARDS = TableColumn_Properties_SORTED_FORWARDS;
  static const Properties SORTED_BACKWARDS = TableColumn_Properties_SORTED_BACKWARDS;
  static const Properties EDITABLE = TableColumn_Properties_EDITABLE;
  static const Properties DEFAULT = TableColumn_Properties_DEFAULT;
  static const Properties DEFAULT_NOT_EDITABLE = TableColumn_Properties_DEFAULT_NOT_EDITABLE;
  static inline bool Properties_IsValid(int value) {
    return TableColumn_Properties_IsValid(value);
  }
  static const Properties Properties_MIN =
    TableColumn_Properties_Properties_MIN;
  static const Properties Properties_MAX =
    TableColumn_Properties_Properties_MAX;
  static const int Properties_ARRAYSIZE =
    TableColumn_Properties_Properties_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Properties_descriptor() {
    return TableColumn_Properties_descriptor();
  }
  static inline const ::std::string& Properties_Name(Properties value) {
    return TableColumn_Properties_Name(value);
  }
  static inline bool Properties_Parse(const ::std::string& name,
      Properties* value) {
    return TableColumn_Properties_Parse(name, value);
  }

  typedef TableColumn_Type Type;
  static const Type STRING = TableColumn_Type_STRING;
  static const Type TIME = TableColumn_Type_TIME;
  static const Type UINT32 = TableColumn_Type_UINT32;
  static const Type DOUBLE = TableColumn_Type_DOUBLE;
  static inline bool Type_IsValid(int value) {
    return TableColumn_Type_IsValid(value);
  }
  static const Type Type_MIN =
    TableColumn_Type_Type_MIN;
  static const Type Type_MAX =
    TableColumn_Type_Type_MAX;
  static const int Type_ARRAYSIZE =
    TableColumn_Type_Type_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Type_descriptor() {
    return TableColumn_Type_descriptor();
  }
  static inline const ::std::string& Type_Name(Type value) {
    return TableColumn_Type_Name(value);
  }
  static inline bool Type_Parse(const ::std::string& name,
      Type* value) {
    return TableColumn_Type_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // optional string name = 7;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 7;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // optional uint32 width = 1 [default = 60];
  inline bool has_width() const;
  inline void clear_width();
  static const int kWidthFieldNumber = 1;
  inline ::google::protobuf::uint32 width() const;
  inline void set_width(::google::protobuf::uint32 value);

  // optional uint32 minimum_width = 2 [default = 60];
  inline bool has_minimum_width() const;
  inline void clear_minimum_width();
  static const int kMinimumWidthFieldNumber = 2;
  inline ::google::protobuf::uint32 minimum_width() const;
  inline void set_minimum_width(::google::protobuf::uint32 value);

  // optional int32 maximum_width = 3 [default = -1];
  inline bool has_maximum_width() const;
  inline void clear_maximum_width();
  static const int kMaximumWidthFieldNumber = 3;
  inline ::google::protobuf::int32 maximum_width() const;
  inline void set_maximum_width(::google::protobuf::int32 value);

  // optional .rec.gui.TableColumn.Properties property_flags = 4 [default = DEFAULT];
  inline bool has_property_flags() const;
  inline void clear_property_flags();
  static const int kPropertyFlagsFieldNumber = 4;
  inline ::rec::gui::TableColumn_Properties property_flags() const;
  inline void set_property_flags(::rec::gui::TableColumn_Properties value);

  // optional .rec.data.AddressProto address = 5;
  inline bool has_address() const;
  inline void clear_address();
  static const int kAddressFieldNumber = 5;
  inline const ::rec::data::AddressProto& address() const;
  inline ::rec::data::AddressProto* mutable_address();
  inline ::rec::data::AddressProto* release_address();
  inline void set_allocated_address(::rec::data::AddressProto* address);

  // optional .rec.gui.TableColumn.Type type = 6;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 6;
  inline ::rec::gui::TableColumn_Type type() const;
  inline void set_type(::rec::gui::TableColumn_Type value);

  // @@protoc_insertion_point(class_scope:rec.gui.TableColumn)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_width();
  inline void clear_has_width();
  inline void set_has_minimum_width();
  inline void clear_has_minimum_width();
  inline void set_has_maximum_width();
  inline void clear_has_maximum_width();
  inline void set_has_property_flags();
  inline void clear_has_property_flags();
  inline void set_has_address();
  inline void clear_has_address();
  inline void set_has_type();
  inline void clear_has_type();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* name_;
  ::google::protobuf::uint32 width_;
  ::google::protobuf::uint32 minimum_width_;
  ::google::protobuf::int32 maximum_width_;
  int property_flags_;
  ::rec::data::AddressProto* address_;
  int type_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(7 + 31) / 32];

  friend void  protobuf_AddDesc_rec_2fgui_2fTableColumn_2eproto();
  friend void protobuf_AssignDesc_rec_2fgui_2fTableColumn_2eproto();
  friend void protobuf_ShutdownFile_rec_2fgui_2fTableColumn_2eproto();

  void InitAsDefaultInstance();
  static TableColumn* default_instance_;
};
// -------------------------------------------------------------------

class TableColumnList : public ::google::protobuf::Message {
 public:
  TableColumnList();
  virtual ~TableColumnList();

  TableColumnList(const TableColumnList& from);

  inline TableColumnList& operator=(const TableColumnList& from) {
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
  static const TableColumnList& default_instance();

  void Swap(TableColumnList* other);

  // implements Message ----------------------------------------------

  TableColumnList* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TableColumnList& from);
  void MergeFrom(const TableColumnList& from);
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

  // repeated .rec.gui.TableColumn column = 1;
  inline int column_size() const;
  inline void clear_column();
  static const int kColumnFieldNumber = 1;
  inline const ::rec::gui::TableColumn& column(int index) const;
  inline ::rec::gui::TableColumn* mutable_column(int index);
  inline ::rec::gui::TableColumn* add_column();
  inline const ::google::protobuf::RepeatedPtrField< ::rec::gui::TableColumn >&
      column() const;
  inline ::google::protobuf::RepeatedPtrField< ::rec::gui::TableColumn >*
      mutable_column();

  // @@protoc_insertion_point(class_scope:rec.gui.TableColumnList)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::rec::gui::TableColumn > column_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_rec_2fgui_2fTableColumn_2eproto();
  friend void protobuf_AssignDesc_rec_2fgui_2fTableColumn_2eproto();
  friend void protobuf_ShutdownFile_rec_2fgui_2fTableColumn_2eproto();

  void InitAsDefaultInstance();
  static TableColumnList* default_instance_;
};
// ===================================================================


// ===================================================================

// TableColumn

// optional string name = 7;
inline bool TableColumn::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TableColumn::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TableColumn::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TableColumn::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& TableColumn::name() const {
  return *name_;
}
inline void TableColumn::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void TableColumn::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void TableColumn::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* TableColumn::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* TableColumn::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void TableColumn::set_allocated_name(::std::string* name) {
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

// optional uint32 width = 1 [default = 60];
inline bool TableColumn::has_width() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TableColumn::set_has_width() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TableColumn::clear_has_width() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TableColumn::clear_width() {
  width_ = 60u;
  clear_has_width();
}
inline ::google::protobuf::uint32 TableColumn::width() const {
  return width_;
}
inline void TableColumn::set_width(::google::protobuf::uint32 value) {
  set_has_width();
  width_ = value;
}

// optional uint32 minimum_width = 2 [default = 60];
inline bool TableColumn::has_minimum_width() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void TableColumn::set_has_minimum_width() {
  _has_bits_[0] |= 0x00000004u;
}
inline void TableColumn::clear_has_minimum_width() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void TableColumn::clear_minimum_width() {
  minimum_width_ = 60u;
  clear_has_minimum_width();
}
inline ::google::protobuf::uint32 TableColumn::minimum_width() const {
  return minimum_width_;
}
inline void TableColumn::set_minimum_width(::google::protobuf::uint32 value) {
  set_has_minimum_width();
  minimum_width_ = value;
}

// optional int32 maximum_width = 3 [default = -1];
inline bool TableColumn::has_maximum_width() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void TableColumn::set_has_maximum_width() {
  _has_bits_[0] |= 0x00000008u;
}
inline void TableColumn::clear_has_maximum_width() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void TableColumn::clear_maximum_width() {
  maximum_width_ = -1;
  clear_has_maximum_width();
}
inline ::google::protobuf::int32 TableColumn::maximum_width() const {
  return maximum_width_;
}
inline void TableColumn::set_maximum_width(::google::protobuf::int32 value) {
  set_has_maximum_width();
  maximum_width_ = value;
}

// optional .rec.gui.TableColumn.Properties property_flags = 4 [default = DEFAULT];
inline bool TableColumn::has_property_flags() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void TableColumn::set_has_property_flags() {
  _has_bits_[0] |= 0x00000010u;
}
inline void TableColumn::clear_has_property_flags() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void TableColumn::clear_property_flags() {
  property_flags_ = 143;
  clear_has_property_flags();
}
inline ::rec::gui::TableColumn_Properties TableColumn::property_flags() const {
  return static_cast< ::rec::gui::TableColumn_Properties >(property_flags_);
}
inline void TableColumn::set_property_flags(::rec::gui::TableColumn_Properties value) {
  assert(::rec::gui::TableColumn_Properties_IsValid(value));
  set_has_property_flags();
  property_flags_ = value;
}

// optional .rec.data.AddressProto address = 5;
inline bool TableColumn::has_address() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void TableColumn::set_has_address() {
  _has_bits_[0] |= 0x00000020u;
}
inline void TableColumn::clear_has_address() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void TableColumn::clear_address() {
  if (address_ != NULL) address_->::rec::data::AddressProto::Clear();
  clear_has_address();
}
inline const ::rec::data::AddressProto& TableColumn::address() const {
  return address_ != NULL ? *address_ : *default_instance_->address_;
}
inline ::rec::data::AddressProto* TableColumn::mutable_address() {
  set_has_address();
  if (address_ == NULL) address_ = new ::rec::data::AddressProto;
  return address_;
}
inline ::rec::data::AddressProto* TableColumn::release_address() {
  clear_has_address();
  ::rec::data::AddressProto* temp = address_;
  address_ = NULL;
  return temp;
}
inline void TableColumn::set_allocated_address(::rec::data::AddressProto* address) {
  delete address_;
  address_ = address;
  if (address) {
    set_has_address();
  } else {
    clear_has_address();
  }
}

// optional .rec.gui.TableColumn.Type type = 6;
inline bool TableColumn::has_type() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void TableColumn::set_has_type() {
  _has_bits_[0] |= 0x00000040u;
}
inline void TableColumn::clear_has_type() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void TableColumn::clear_type() {
  type_ = 1;
  clear_has_type();
}
inline ::rec::gui::TableColumn_Type TableColumn::type() const {
  return static_cast< ::rec::gui::TableColumn_Type >(type_);
}
inline void TableColumn::set_type(::rec::gui::TableColumn_Type value) {
  assert(::rec::gui::TableColumn_Type_IsValid(value));
  set_has_type();
  type_ = value;
}

// -------------------------------------------------------------------

// TableColumnList

// repeated .rec.gui.TableColumn column = 1;
inline int TableColumnList::column_size() const {
  return column_.size();
}
inline void TableColumnList::clear_column() {
  column_.Clear();
}
inline const ::rec::gui::TableColumn& TableColumnList::column(int index) const {
  return column_.Get(index);
}
inline ::rec::gui::TableColumn* TableColumnList::mutable_column(int index) {
  return column_.Mutable(index);
}
inline ::rec::gui::TableColumn* TableColumnList::add_column() {
  return column_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::rec::gui::TableColumn >&
TableColumnList::column() const {
  return column_;
}
inline ::google::protobuf::RepeatedPtrField< ::rec::gui::TableColumn >*
TableColumnList::mutable_column() {
  return &column_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace gui
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::rec::gui::TableColumn_Properties>() {
  return ::rec::gui::TableColumn_Properties_descriptor();
}
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::rec::gui::TableColumn_Type>() {
  return ::rec::gui::TableColumn_Type_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2fgui_2fTableColumn_2eproto__INCLUDED
