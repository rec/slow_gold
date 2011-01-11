// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/gui/TableColumn.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace rec {
namespace gui {

namespace {

const ::google::protobuf::Descriptor* TableColumn_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TableColumn_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* TableColumn_Properties_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* TableColumn_Type_descriptor_ = NULL;
const ::google::protobuf::Descriptor* TableColumnList_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TableColumnList_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2fgui_2fTableColumn_2eproto() {
  protobuf_AddDesc_rec_2fgui_2fTableColumn_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/gui/TableColumn.proto");
  GOOGLE_CHECK(file != NULL);
  TableColumn_descriptor_ = file->message_type(0);
  static const int TableColumn_offsets_[7] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TableColumn, name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TableColumn, width_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TableColumn, minimum_width_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TableColumn, maximum_width_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TableColumn, property_flags_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TableColumn, address_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TableColumn, type_),
  };
  TableColumn_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TableColumn_descriptor_,
      TableColumn::default_instance_,
      TableColumn_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TableColumn, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TableColumn, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TableColumn));
  TableColumn_Properties_descriptor_ = TableColumn_descriptor_->enum_type(0);
  TableColumn_Type_descriptor_ = TableColumn_descriptor_->enum_type(1);
  TableColumnList_descriptor_ = file->message_type(1);
  static const int TableColumnList_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TableColumnList, column_),
  };
  TableColumnList_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TableColumnList_descriptor_,
      TableColumnList::default_instance_,
      TableColumnList_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TableColumnList, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TableColumnList, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TableColumnList));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2fgui_2fTableColumn_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TableColumn_descriptor_, &TableColumn::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TableColumnList_descriptor_, &TableColumnList::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2fgui_2fTableColumn_2eproto() {
  delete TableColumn::default_instance_;
  delete TableColumn_reflection_;
  delete TableColumnList::default_instance_;
  delete TableColumnList_reflection_;
}

void protobuf_AddDesc_rec_2fgui_2fTableColumn_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::rec::proto::protobuf_AddDesc_rec_2fdata_2fproto_2fAddress_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\031rec/gui/TableColumn.proto\022\007rec.gui\032\034re"
    "c/data/proto/Address.proto\"\272\003\n\013TableColu"
    "mn\022\014\n\004name\030\007 \001(\t\022\r\n\005width\030\001 \001(\r\022\025\n\rminim"
    "um_width\030\002 \001(\r\022\025\n\rmaximum_width\030\003 \001(\r\022@\n"
    "\016property_flags\030\004 \001(\0162\037.rec.gui.TableCol"
    "umn.Properties:\007DEFAULT\022#\n\007address\030\005 \001(\013"
    "2\022.rec.proto.Address\022\'\n\004type\030\006 \001(\0162\031.rec"
    ".gui.TableColumn.Type\"\231\001\n\nProperties\022\013\n\007"
    "VISIBLE\020\001\022\r\n\tRESIZABLE\020\002\022\r\n\tDRAGGABLE\020\004\022"
    "\032\n\026APPEARS_ON_COLUMN_MENU\020\010\022\014\n\010SORTABLE\020"
    "\020\022\023\n\017SORTED_FORWARDS\020 \022\024\n\020SORTED_BACKWAR"
    "DS\020@\022\013\n\007DEFAULT\020\037\"4\n\004Type\022\n\n\006STRING\020\001\022\010\n"
    "\004TIME\020\002\022\n\n\006UINT32\020\003\022\n\n\006DOUBLE\020\004\"7\n\017Table"
    "ColumnList\022$\n\006column\030\001 \003(\0132\024.rec.gui.Tab"
    "leColumn", 568);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/gui/TableColumn.proto", &protobuf_RegisterTypes);
  TableColumn::default_instance_ = new TableColumn();
  TableColumnList::default_instance_ = new TableColumnList();
  TableColumn::default_instance_->InitAsDefaultInstance();
  TableColumnList::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2fgui_2fTableColumn_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2fgui_2fTableColumn_2eproto {
  StaticDescriptorInitializer_rec_2fgui_2fTableColumn_2eproto() {
    protobuf_AddDesc_rec_2fgui_2fTableColumn_2eproto();
  }
} static_descriptor_initializer_rec_2fgui_2fTableColumn_2eproto_;


// ===================================================================

const ::google::protobuf::EnumDescriptor* TableColumn_Properties_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TableColumn_Properties_descriptor_;
}
bool TableColumn_Properties_IsValid(int value) {
  switch(value) {
    case 1:
    case 2:
    case 4:
    case 8:
    case 16:
    case 31:
    case 32:
    case 64:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const TableColumn_Properties TableColumn::VISIBLE;
const TableColumn_Properties TableColumn::RESIZABLE;
const TableColumn_Properties TableColumn::DRAGGABLE;
const TableColumn_Properties TableColumn::APPEARS_ON_COLUMN_MENU;
const TableColumn_Properties TableColumn::SORTABLE;
const TableColumn_Properties TableColumn::SORTED_FORWARDS;
const TableColumn_Properties TableColumn::SORTED_BACKWARDS;
const TableColumn_Properties TableColumn::DEFAULT;
const TableColumn_Properties TableColumn::Properties_MIN;
const TableColumn_Properties TableColumn::Properties_MAX;
const int TableColumn::Properties_ARRAYSIZE;
#endif  // _MSC_VER
const ::google::protobuf::EnumDescriptor* TableColumn_Type_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TableColumn_Type_descriptor_;
}
bool TableColumn_Type_IsValid(int value) {
  switch(value) {
    case 1:
    case 2:
    case 3:
    case 4:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const TableColumn_Type TableColumn::STRING;
const TableColumn_Type TableColumn::TIME;
const TableColumn_Type TableColumn::UINT32;
const TableColumn_Type TableColumn::DOUBLE;
const TableColumn_Type TableColumn::Type_MIN;
const TableColumn_Type TableColumn::Type_MAX;
const int TableColumn::Type_ARRAYSIZE;
#endif  // _MSC_VER
const ::std::string TableColumn::_default_name_;
#ifndef _MSC_VER
const int TableColumn::kNameFieldNumber;
const int TableColumn::kWidthFieldNumber;
const int TableColumn::kMinimumWidthFieldNumber;
const int TableColumn::kMaximumWidthFieldNumber;
const int TableColumn::kPropertyFlagsFieldNumber;
const int TableColumn::kAddressFieldNumber;
const int TableColumn::kTypeFieldNumber;
#endif  // !_MSC_VER

TableColumn::TableColumn()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void TableColumn::InitAsDefaultInstance() {
  address_ = const_cast< ::rec::proto::Address*>(&::rec::proto::Address::default_instance());
}

TableColumn::TableColumn(const TableColumn& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void TableColumn::SharedCtor() {
  _cached_size_ = 0;
  name_ = const_cast< ::std::string*>(&_default_name_);
  width_ = 0u;
  minimum_width_ = 0u;
  maximum_width_ = 0u;
  property_flags_ = 31;
  address_ = NULL;
  type_ = 1;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TableColumn::~TableColumn() {
  SharedDtor();
}

void TableColumn::SharedDtor() {
  if (name_ != &_default_name_) {
    delete name_;
  }
  if (this != default_instance_) {
    delete address_;
  }
}

void TableColumn::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TableColumn::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TableColumn_descriptor_;
}

const TableColumn& TableColumn::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fgui_2fTableColumn_2eproto();  return *default_instance_;
}

TableColumn* TableColumn::default_instance_ = NULL;

TableColumn* TableColumn::New() const {
  return new TableColumn;
}

void TableColumn::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (_has_bit(0)) {
      if (name_ != &_default_name_) {
        name_->clear();
      }
    }
    width_ = 0u;
    minimum_width_ = 0u;
    maximum_width_ = 0u;
    property_flags_ = 31;
    if (_has_bit(5)) {
      if (address_ != NULL) address_->::rec::proto::Address::Clear();
    }
    type_ = 1;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TableColumn::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 width = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &width_)));
          _set_bit(1);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_minimum_width;
        break;
      }
      
      // optional uint32 minimum_width = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_minimum_width:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &minimum_width_)));
          _set_bit(2);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_maximum_width;
        break;
      }
      
      // optional uint32 maximum_width = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_maximum_width:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &maximum_width_)));
          _set_bit(3);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_property_flags;
        break;
      }
      
      // optional .rec.gui.TableColumn.Properties property_flags = 4 [default = DEFAULT];
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_property_flags:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::rec::gui::TableColumn_Properties_IsValid(value)) {
            set_property_flags(static_cast< ::rec::gui::TableColumn_Properties >(value));
          } else {
            mutable_unknown_fields()->AddVarint(4, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(42)) goto parse_address;
        break;
      }
      
      // optional .rec.proto.Address address = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_address:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_address()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(48)) goto parse_type;
        break;
      }
      
      // optional .rec.gui.TableColumn.Type type = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_type:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::rec::gui::TableColumn_Type_IsValid(value)) {
            set_type(static_cast< ::rec::gui::TableColumn_Type >(value));
          } else {
            mutable_unknown_fields()->AddVarint(6, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(58)) goto parse_name;
        break;
      }
      
      // optional string name = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
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

void TableColumn::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional uint32 width = 1;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->width(), output);
  }
  
  // optional uint32 minimum_width = 2;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->minimum_width(), output);
  }
  
  // optional uint32 maximum_width = 3;
  if (_has_bit(3)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->maximum_width(), output);
  }
  
  // optional .rec.gui.TableColumn.Properties property_flags = 4 [default = DEFAULT];
  if (_has_bit(4)) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      4, this->property_flags(), output);
  }
  
  // optional .rec.proto.Address address = 5;
  if (_has_bit(5)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      5, this->address(), output);
  }
  
  // optional .rec.gui.TableColumn.Type type = 6;
  if (_has_bit(6)) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      6, this->type(), output);
  }
  
  // optional string name = 7;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      7, this->name(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* TableColumn::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional uint32 width = 1;
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->width(), target);
  }
  
  // optional uint32 minimum_width = 2;
  if (_has_bit(2)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->minimum_width(), target);
  }
  
  // optional uint32 maximum_width = 3;
  if (_has_bit(3)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->maximum_width(), target);
  }
  
  // optional .rec.gui.TableColumn.Properties property_flags = 4 [default = DEFAULT];
  if (_has_bit(4)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      4, this->property_flags(), target);
  }
  
  // optional .rec.proto.Address address = 5;
  if (_has_bit(5)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        5, this->address(), target);
  }
  
  // optional .rec.gui.TableColumn.Type type = 6;
  if (_has_bit(6)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      6, this->type(), target);
  }
  
  // optional string name = 7;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        7, this->name(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int TableColumn::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string name = 7;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->name());
    }
    
    // optional uint32 width = 1;
    if (has_width()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->width());
    }
    
    // optional uint32 minimum_width = 2;
    if (has_minimum_width()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->minimum_width());
    }
    
    // optional uint32 maximum_width = 3;
    if (has_maximum_width()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->maximum_width());
    }
    
    // optional .rec.gui.TableColumn.Properties property_flags = 4 [default = DEFAULT];
    if (has_property_flags()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->property_flags());
    }
    
    // optional .rec.proto.Address address = 5;
    if (has_address()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->address());
    }
    
    // optional .rec.gui.TableColumn.Type type = 6;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->type());
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

void TableColumn::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TableColumn* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TableColumn*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TableColumn::MergeFrom(const TableColumn& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_name(from.name());
    }
    if (from._has_bit(1)) {
      set_width(from.width());
    }
    if (from._has_bit(2)) {
      set_minimum_width(from.minimum_width());
    }
    if (from._has_bit(3)) {
      set_maximum_width(from.maximum_width());
    }
    if (from._has_bit(4)) {
      set_property_flags(from.property_flags());
    }
    if (from._has_bit(5)) {
      mutable_address()->::rec::proto::Address::MergeFrom(from.address());
    }
    if (from._has_bit(6)) {
      set_type(from.type());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TableColumn::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TableColumn::CopyFrom(const TableColumn& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TableColumn::IsInitialized() const {
  
  return true;
}

void TableColumn::Swap(TableColumn* other) {
  if (other != this) {
    std::swap(name_, other->name_);
    std::swap(width_, other->width_);
    std::swap(minimum_width_, other->minimum_width_);
    std::swap(maximum_width_, other->maximum_width_);
    std::swap(property_flags_, other->property_flags_);
    std::swap(address_, other->address_);
    std::swap(type_, other->type_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TableColumn::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TableColumn_descriptor_;
  metadata.reflection = TableColumn_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int TableColumnList::kColumnFieldNumber;
#endif  // !_MSC_VER

TableColumnList::TableColumnList()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void TableColumnList::InitAsDefaultInstance() {
}

TableColumnList::TableColumnList(const TableColumnList& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void TableColumnList::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TableColumnList::~TableColumnList() {
  SharedDtor();
}

void TableColumnList::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TableColumnList::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TableColumnList::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TableColumnList_descriptor_;
}

const TableColumnList& TableColumnList::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fgui_2fTableColumn_2eproto();  return *default_instance_;
}

TableColumnList* TableColumnList::default_instance_ = NULL;

TableColumnList* TableColumnList::New() const {
  return new TableColumnList;
}

void TableColumnList::Clear() {
  column_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TableColumnList::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .rec.gui.TableColumn column = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_column:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_column()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_column;
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

void TableColumnList::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .rec.gui.TableColumn column = 1;
  for (int i = 0; i < this->column_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->column(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* TableColumnList::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .rec.gui.TableColumn column = 1;
  for (int i = 0; i < this->column_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->column(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int TableColumnList::ByteSize() const {
  int total_size = 0;
  
  // repeated .rec.gui.TableColumn column = 1;
  total_size += 1 * this->column_size();
  for (int i = 0; i < this->column_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->column(i));
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

void TableColumnList::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TableColumnList* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TableColumnList*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TableColumnList::MergeFrom(const TableColumnList& from) {
  GOOGLE_CHECK_NE(&from, this);
  column_.MergeFrom(from.column_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TableColumnList::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TableColumnList::CopyFrom(const TableColumnList& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TableColumnList::IsInitialized() const {
  
  return true;
}

void TableColumnList::Swap(TableColumnList* other) {
  if (other != this) {
    column_.Swap(&other->column_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TableColumnList::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TableColumnList_descriptor_;
  metadata.reflection = TableColumnList_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace gui
}  // namespace rec

// @@protoc_insertion_point(global_scope)
