// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/widget/tree/VirtualFile.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace rec {
namespace widget {
namespace tree {

namespace {

const ::google::protobuf::Descriptor* Volume_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Volume_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* Volume_Type_descriptor_ = NULL;
const ::google::protobuf::Descriptor* VolumeFile_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  VolumeFile_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2fwidget_2ftree_2fVirtualFile_2eproto() {
  protobuf_AddDesc_rec_2fwidget_2ftree_2fVirtualFile_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/widget/tree/VirtualFile.proto");
  GOOGLE_CHECK(file != NULL);
  Volume_descriptor_ = file->message_type(0);
  static const int Volume_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Volume, type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Volume, name_),
  };
  Volume_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Volume_descriptor_,
      Volume::default_instance_,
      Volume_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Volume, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Volume, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Volume));
  Volume_Type_descriptor_ = Volume_descriptor_->enum_type(0);
  VolumeFile_descriptor_ = file->message_type(1);
  static const int VolumeFile_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(VolumeFile, volume_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(VolumeFile, path_),
  };
  VolumeFile_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      VolumeFile_descriptor_,
      VolumeFile::default_instance_,
      VolumeFile_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(VolumeFile, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(VolumeFile, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(VolumeFile));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2fwidget_2ftree_2fVirtualFile_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Volume_descriptor_, &Volume::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    VolumeFile_descriptor_, &VolumeFile::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2fwidget_2ftree_2fVirtualFile_2eproto() {
  delete Volume::default_instance_;
  delete Volume_reflection_;
  delete VolumeFile::default_instance_;
  delete VolumeFile_reflection_;
}

void protobuf_AddDesc_rec_2fwidget_2ftree_2fVirtualFile_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::rec::widget::protobuf_AddDesc_rec_2fwidget_2fWidget_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n!rec/widget/tree/VirtualFile.proto\022\017rec"
    ".widget.tree\032\027rec/widget/Widget.proto\"i\n"
    "\006Volume\022*\n\004type\030\001 \001(\0162\034.rec.widget.tree."
    "Volume.Type\022\014\n\004name\030\002 \003(\t\"%\n\004Type\022\006\n\002CD\020"
    "\001\022\t\n\005MUSIC\020\002\022\n\n\006VOLUME\020\003\"C\n\nVolumeFile\022\'"
    "\n\006volume\030\001 \001(\0132\027.rec.widget.tree.Volume\022"
    "\014\n\004path\030\002 \003(\t", 253);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/widget/tree/VirtualFile.proto", &protobuf_RegisterTypes);
  Volume::default_instance_ = new Volume();
  VolumeFile::default_instance_ = new VolumeFile();
  Volume::default_instance_->InitAsDefaultInstance();
  VolumeFile::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2fwidget_2ftree_2fVirtualFile_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2fwidget_2ftree_2fVirtualFile_2eproto {
  StaticDescriptorInitializer_rec_2fwidget_2ftree_2fVirtualFile_2eproto() {
    protobuf_AddDesc_rec_2fwidget_2ftree_2fVirtualFile_2eproto();
  }
} static_descriptor_initializer_rec_2fwidget_2ftree_2fVirtualFile_2eproto_;


// ===================================================================

const ::google::protobuf::EnumDescriptor* Volume_Type_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Volume_Type_descriptor_;
}
bool Volume_Type_IsValid(int value) {
  switch(value) {
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const Volume_Type Volume::CD;
const Volume_Type Volume::MUSIC;
const Volume_Type Volume::VOLUME;
const Volume_Type Volume::Type_MIN;
const Volume_Type Volume::Type_MAX;
const int Volume::Type_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int Volume::kTypeFieldNumber;
const int Volume::kNameFieldNumber;
#endif  // !_MSC_VER

Volume::Volume()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Volume::InitAsDefaultInstance() {
}

Volume::Volume(const Volume& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Volume::SharedCtor() {
  _cached_size_ = 0;
  type_ = 1;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Volume::~Volume() {
  SharedDtor();
}

void Volume::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Volume::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Volume::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Volume_descriptor_;
}

const Volume& Volume::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fwidget_2ftree_2fVirtualFile_2eproto();  return *default_instance_;
}

Volume* Volume::default_instance_ = NULL;

Volume* Volume::New() const {
  return new Volume;
}

void Volume::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    type_ = 1;
  }
  name_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Volume::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .rec.widget.tree.Volume.Type type = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::rec::widget::tree::Volume_Type_IsValid(value)) {
            set_type(static_cast< ::rec::widget::tree::Volume_Type >(value));
          } else {
            mutable_unknown_fields()->AddVarint(1, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_name;
        break;
      }
      
      // repeated string name = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->add_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->name(0).data(), this->name(0).length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_name;
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

void Volume::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .rec.widget.tree.Volume.Type type = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->type(), output);
  }
  
  // repeated string name = 2;
  for (int i = 0; i < this->name_size(); i++) {
  ::google::protobuf::internal::WireFormat::VerifyUTF8String(
    this->name(i).data(), this->name(i).length(),
    ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->name(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Volume::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .rec.widget.tree.Volume.Type type = 1;
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->type(), target);
  }
  
  // repeated string name = 2;
  for (int i = 0; i < this->name_size(); i++) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name(i).data(), this->name(i).length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target = ::google::protobuf::internal::WireFormatLite::
      WriteStringToArray(2, this->name(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Volume::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .rec.widget.tree.Volume.Type type = 1;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->type());
    }
    
  }
  // repeated string name = 2;
  total_size += 1 * this->name_size();
  for (int i = 0; i < this->name_size(); i++) {
    total_size += ::google::protobuf::internal::WireFormatLite::StringSize(
      this->name(i));
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

void Volume::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Volume* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Volume*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Volume::MergeFrom(const Volume& from) {
  GOOGLE_CHECK_NE(&from, this);
  name_.MergeFrom(from.name_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_type(from.type());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Volume::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Volume::CopyFrom(const Volume& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Volume::IsInitialized() const {
  
  return true;
}

void Volume::Swap(Volume* other) {
  if (other != this) {
    std::swap(type_, other->type_);
    name_.Swap(&other->name_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Volume::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Volume_descriptor_;
  metadata.reflection = Volume_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int VolumeFile::kVolumeFieldNumber;
const int VolumeFile::kPathFieldNumber;
#endif  // !_MSC_VER

VolumeFile::VolumeFile()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void VolumeFile::InitAsDefaultInstance() {
  volume_ = const_cast< ::rec::widget::tree::Volume*>(&::rec::widget::tree::Volume::default_instance());
}

VolumeFile::VolumeFile(const VolumeFile& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void VolumeFile::SharedCtor() {
  _cached_size_ = 0;
  volume_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

VolumeFile::~VolumeFile() {
  SharedDtor();
}

void VolumeFile::SharedDtor() {
  if (this != default_instance_) {
    delete volume_;
  }
}

void VolumeFile::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* VolumeFile::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return VolumeFile_descriptor_;
}

const VolumeFile& VolumeFile::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fwidget_2ftree_2fVirtualFile_2eproto();  return *default_instance_;
}

VolumeFile* VolumeFile::default_instance_ = NULL;

VolumeFile* VolumeFile::New() const {
  return new VolumeFile;
}

void VolumeFile::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (_has_bit(0)) {
      if (volume_ != NULL) volume_->::rec::widget::tree::Volume::Clear();
    }
  }
  path_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool VolumeFile::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .rec.widget.tree.Volume volume = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_volume()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_path;
        break;
      }
      
      // repeated string path = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_path:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->add_path()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->path(0).data(), this->path(0).length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_path;
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

void VolumeFile::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .rec.widget.tree.Volume volume = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->volume(), output);
  }
  
  // repeated string path = 2;
  for (int i = 0; i < this->path_size(); i++) {
  ::google::protobuf::internal::WireFormat::VerifyUTF8String(
    this->path(i).data(), this->path(i).length(),
    ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->path(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* VolumeFile::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .rec.widget.tree.Volume volume = 1;
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->volume(), target);
  }
  
  // repeated string path = 2;
  for (int i = 0; i < this->path_size(); i++) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->path(i).data(), this->path(i).length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target = ::google::protobuf::internal::WireFormatLite::
      WriteStringToArray(2, this->path(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int VolumeFile::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .rec.widget.tree.Volume volume = 1;
    if (has_volume()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->volume());
    }
    
  }
  // repeated string path = 2;
  total_size += 1 * this->path_size();
  for (int i = 0; i < this->path_size(); i++) {
    total_size += ::google::protobuf::internal::WireFormatLite::StringSize(
      this->path(i));
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

void VolumeFile::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const VolumeFile* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const VolumeFile*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void VolumeFile::MergeFrom(const VolumeFile& from) {
  GOOGLE_CHECK_NE(&from, this);
  path_.MergeFrom(from.path_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      mutable_volume()->::rec::widget::tree::Volume::MergeFrom(from.volume());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void VolumeFile::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void VolumeFile::CopyFrom(const VolumeFile& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool VolumeFile::IsInitialized() const {
  
  return true;
}

void VolumeFile::Swap(VolumeFile* other) {
  if (other != this) {
    std::swap(volume_, other->volume_);
    path_.Swap(&other->path_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata VolumeFile::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = VolumeFile_descriptor_;
  metadata.reflection = VolumeFile_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace tree
}  // namespace widget
}  // namespace rec

// @@protoc_insertion_point(global_scope)
