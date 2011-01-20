// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/gui/LoopPoint.pb.h"
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

const ::google::protobuf::Descriptor* LoopPoint_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  LoopPoint_reflection_ = NULL;
const ::google::protobuf::Descriptor* LoopPointList_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  LoopPointList_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2fgui_2fLoopPoint_2eproto() {
  protobuf_AddDesc_rec_2fgui_2fLoopPoint_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/gui/LoopPoint.proto");
  GOOGLE_CHECK(file != NULL);
  LoopPoint_descriptor_ = file->message_type(0);
  static const int LoopPoint_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LoopPoint, time_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LoopPoint, name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LoopPoint, notes_),
  };
  LoopPoint_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      LoopPoint_descriptor_,
      LoopPoint::default_instance_,
      LoopPoint_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LoopPoint, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LoopPoint, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(LoopPoint));
  LoopPointList_descriptor_ = file->message_type(1);
  static const int LoopPointList_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LoopPointList, loop_point_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LoopPointList, selected_),
  };
  LoopPointList_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      LoopPointList_descriptor_,
      LoopPointList::default_instance_,
      LoopPointList_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LoopPointList, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LoopPointList, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(LoopPointList));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2fgui_2fLoopPoint_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    LoopPoint_descriptor_, &LoopPoint::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    LoopPointList_descriptor_, &LoopPointList::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2fgui_2fLoopPoint_2eproto() {
  delete LoopPoint::default_instance_;
  delete LoopPoint_reflection_;
  delete LoopPointList::default_instance_;
  delete LoopPointList_reflection_;
}

void protobuf_AddDesc_rec_2fgui_2fLoopPoint_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\027rec/gui/LoopPoint.proto\022\007rec.gui\"6\n\tLo"
    "opPoint\022\014\n\004time\030\001 \001(\001\022\014\n\004name\030\002 \001(\t\022\r\n\005n"
    "otes\030\003 \001(\t\"I\n\rLoopPointList\022&\n\nloop_poin"
    "t\030\001 \003(\0132\022.rec.gui.LoopPoint\022\020\n\010selected\030"
    "\002 \003(\010", 165);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/gui/LoopPoint.proto", &protobuf_RegisterTypes);
  LoopPoint::default_instance_ = new LoopPoint();
  LoopPointList::default_instance_ = new LoopPointList();
  LoopPoint::default_instance_->InitAsDefaultInstance();
  LoopPointList::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2fgui_2fLoopPoint_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2fgui_2fLoopPoint_2eproto {
  StaticDescriptorInitializer_rec_2fgui_2fLoopPoint_2eproto() {
    protobuf_AddDesc_rec_2fgui_2fLoopPoint_2eproto();
  }
} static_descriptor_initializer_rec_2fgui_2fLoopPoint_2eproto_;


// ===================================================================

const ::std::string LoopPoint::_default_name_;
const ::std::string LoopPoint::_default_notes_;
#ifndef _MSC_VER
const int LoopPoint::kTimeFieldNumber;
const int LoopPoint::kNameFieldNumber;
const int LoopPoint::kNotesFieldNumber;
#endif  // !_MSC_VER

LoopPoint::LoopPoint()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void LoopPoint::InitAsDefaultInstance() {
}

LoopPoint::LoopPoint(const LoopPoint& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void LoopPoint::SharedCtor() {
  _cached_size_ = 0;
  time_ = 0;
  name_ = const_cast< ::std::string*>(&_default_name_);
  notes_ = const_cast< ::std::string*>(&_default_notes_);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

LoopPoint::~LoopPoint() {
  SharedDtor();
}

void LoopPoint::SharedDtor() {
  if (name_ != &_default_name_) {
    delete name_;
  }
  if (notes_ != &_default_notes_) {
    delete notes_;
  }
  if (this != default_instance_) {
  }
}

void LoopPoint::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* LoopPoint::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return LoopPoint_descriptor_;
}

const LoopPoint& LoopPoint::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fgui_2fLoopPoint_2eproto();  return *default_instance_;
}

LoopPoint* LoopPoint::default_instance_ = NULL;

LoopPoint* LoopPoint::New() const {
  return new LoopPoint;
}

void LoopPoint::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    time_ = 0;
    if (_has_bit(1)) {
      if (name_ != &_default_name_) {
        name_->clear();
      }
    }
    if (_has_bit(2)) {
      if (notes_ != &_default_notes_) {
        notes_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool LoopPoint::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional double time = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &time_)));
          _set_bit(0);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_name;
        break;
      }
      
      // optional string name = 2;
      case 2: {
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
        if (input->ExpectTag(26)) goto parse_notes;
        break;
      }
      
      // optional string notes = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_notes:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_notes()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->notes().data(), this->notes().length(),
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

void LoopPoint::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional double time = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(1, this->time(), output);
  }
  
  // optional string name = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->name(), output);
  }
  
  // optional string notes = 3;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->notes().data(), this->notes().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->notes(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* LoopPoint::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional double time = 1;
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(1, this->time(), target);
  }
  
  // optional string name = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->name(), target);
  }
  
  // optional string notes = 3;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->notes().data(), this->notes().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->notes(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int LoopPoint::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional double time = 1;
    if (has_time()) {
      total_size += 1 + 8;
    }
    
    // optional string name = 2;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->name());
    }
    
    // optional string notes = 3;
    if (has_notes()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->notes());
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

void LoopPoint::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const LoopPoint* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const LoopPoint*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void LoopPoint::MergeFrom(const LoopPoint& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_time(from.time());
    }
    if (from._has_bit(1)) {
      set_name(from.name());
    }
    if (from._has_bit(2)) {
      set_notes(from.notes());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void LoopPoint::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void LoopPoint::CopyFrom(const LoopPoint& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LoopPoint::IsInitialized() const {
  
  return true;
}

void LoopPoint::Swap(LoopPoint* other) {
  if (other != this) {
    std::swap(time_, other->time_);
    std::swap(name_, other->name_);
    std::swap(notes_, other->notes_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata LoopPoint::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = LoopPoint_descriptor_;
  metadata.reflection = LoopPoint_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int LoopPointList::kLoopPointFieldNumber;
const int LoopPointList::kSelectedFieldNumber;
#endif  // !_MSC_VER

LoopPointList::LoopPointList()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void LoopPointList::InitAsDefaultInstance() {
}

LoopPointList::LoopPointList(const LoopPointList& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void LoopPointList::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

LoopPointList::~LoopPointList() {
  SharedDtor();
}

void LoopPointList::SharedDtor() {
  if (this != default_instance_) {
  }
}

void LoopPointList::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* LoopPointList::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return LoopPointList_descriptor_;
}

const LoopPointList& LoopPointList::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fgui_2fLoopPoint_2eproto();  return *default_instance_;
}

LoopPointList* LoopPointList::default_instance_ = NULL;

LoopPointList* LoopPointList::New() const {
  return new LoopPointList;
}

void LoopPointList::Clear() {
  loop_point_.Clear();
  selected_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool LoopPointList::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .rec.gui.LoopPoint loop_point = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_loop_point:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_loop_point()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_loop_point;
        if (input->ExpectTag(16)) goto parse_selected;
        break;
      }
      
      // repeated bool selected = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_selected:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 1, 16, input, this->mutable_selected())));
        } else if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag)
                   == ::google::protobuf::internal::WireFormatLite::
                      WIRETYPE_LENGTH_DELIMITED) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, this->mutable_selected())));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_selected;
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

void LoopPointList::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .rec.gui.LoopPoint loop_point = 1;
  for (int i = 0; i < this->loop_point_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->loop_point(i), output);
  }
  
  // repeated bool selected = 2;
  for (int i = 0; i < this->selected_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(
      2, this->selected(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* LoopPointList::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .rec.gui.LoopPoint loop_point = 1;
  for (int i = 0; i < this->loop_point_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->loop_point(i), target);
  }
  
  // repeated bool selected = 2;
  for (int i = 0; i < this->selected_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteBoolToArray(2, this->selected(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int LoopPointList::ByteSize() const {
  int total_size = 0;
  
  // repeated .rec.gui.LoopPoint loop_point = 1;
  total_size += 1 * this->loop_point_size();
  for (int i = 0; i < this->loop_point_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->loop_point(i));
  }
  
  // repeated bool selected = 2;
  {
    int data_size = 0;
    data_size = 1 * this->selected_size();
    total_size += 1 * this->selected_size() + data_size;
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

void LoopPointList::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const LoopPointList* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const LoopPointList*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void LoopPointList::MergeFrom(const LoopPointList& from) {
  GOOGLE_CHECK_NE(&from, this);
  loop_point_.MergeFrom(from.loop_point_);
  selected_.MergeFrom(from.selected_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void LoopPointList::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void LoopPointList::CopyFrom(const LoopPointList& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LoopPointList::IsInitialized() const {
  
  return true;
}

void LoopPointList::Swap(LoopPointList* other) {
  if (other != this) {
    loop_point_.Swap(&other->loop_point_);
    selected_.Swap(&other->selected_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata LoopPointList::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = LoopPointList_descriptor_;
  metadata.reflection = LoopPointList_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace gui
}  // namespace rec

// @@protoc_insertion_point(global_scope)
