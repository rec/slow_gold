// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/slow/app/AppLayout.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace rec {
namespace slow {

namespace {

const ::google::protobuf::Descriptor* AppLayout_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  AppLayout_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2fslow_2fapp_2fAppLayout_2eproto() {
  protobuf_AddDesc_rec_2fslow_2fapp_2fAppLayout_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/slow/app/AppLayout.proto");
  GOOGLE_CHECK(file != NULL);
  AppLayout_descriptor_ = file->message_type(0);
  static const int AppLayout_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AppLayout, bounds_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AppLayout, directory_height_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AppLayout, loops_width_),
  };
  AppLayout_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      AppLayout_descriptor_,
      AppLayout::default_instance_,
      AppLayout_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AppLayout, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AppLayout, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(AppLayout));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2fslow_2fapp_2fAppLayout_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    AppLayout_descriptor_, &AppLayout::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2fslow_2fapp_2fAppLayout_2eproto() {
  delete AppLayout::default_instance_;
  delete AppLayout_reflection_;
}

void protobuf_AddDesc_rec_2fslow_2fapp_2fAppLayout_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::rec::gui::protobuf_AddDesc_rec_2fgui_2fGeometry_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\034rec/slow/app/AppLayout.proto\022\010rec.slow"
    "\032\026rec/gui/Geometry.proto\"^\n\tAppLayout\022\"\n"
    "\006bounds\030\001 \001(\0132\022.rec.gui.Rectangle\022\030\n\020dir"
    "ectory_height\030\002 \001(\r\022\023\n\013loops_width\030\003 \001(\r", 160);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/slow/app/AppLayout.proto", &protobuf_RegisterTypes);
  AppLayout::default_instance_ = new AppLayout();
  AppLayout::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2fslow_2fapp_2fAppLayout_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2fslow_2fapp_2fAppLayout_2eproto {
  StaticDescriptorInitializer_rec_2fslow_2fapp_2fAppLayout_2eproto() {
    protobuf_AddDesc_rec_2fslow_2fapp_2fAppLayout_2eproto();
  }
} static_descriptor_initializer_rec_2fslow_2fapp_2fAppLayout_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int AppLayout::kBoundsFieldNumber;
const int AppLayout::kDirectoryHeightFieldNumber;
const int AppLayout::kLoopsWidthFieldNumber;
#endif  // !_MSC_VER

AppLayout::AppLayout()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void AppLayout::InitAsDefaultInstance() {
  bounds_ = const_cast< ::rec::gui::Rectangle*>(&::rec::gui::Rectangle::default_instance());
}

AppLayout::AppLayout(const AppLayout& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void AppLayout::SharedCtor() {
  _cached_size_ = 0;
  bounds_ = NULL;
  directory_height_ = 0u;
  loops_width_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

AppLayout::~AppLayout() {
  SharedDtor();
}

void AppLayout::SharedDtor() {
  if (this != default_instance_) {
    delete bounds_;
  }
}

void AppLayout::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* AppLayout::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return AppLayout_descriptor_;
}

const AppLayout& AppLayout::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fslow_2fapp_2fAppLayout_2eproto();  return *default_instance_;
}

AppLayout* AppLayout::default_instance_ = NULL;

AppLayout* AppLayout::New() const {
  return new AppLayout;
}

void AppLayout::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (_has_bit(0)) {
      if (bounds_ != NULL) bounds_->::rec::gui::Rectangle::Clear();
    }
    directory_height_ = 0u;
    loops_width_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool AppLayout::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .rec.gui.Rectangle bounds = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_bounds()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_directory_height;
        break;
      }
      
      // optional uint32 directory_height = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_directory_height:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &directory_height_)));
          _set_bit(1);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_loops_width;
        break;
      }
      
      // optional uint32 loops_width = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_loops_width:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &loops_width_)));
          _set_bit(2);
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

void AppLayout::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .rec.gui.Rectangle bounds = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->bounds(), output);
  }
  
  // optional uint32 directory_height = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->directory_height(), output);
  }
  
  // optional uint32 loops_width = 3;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->loops_width(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* AppLayout::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .rec.gui.Rectangle bounds = 1;
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->bounds(), target);
  }
  
  // optional uint32 directory_height = 2;
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->directory_height(), target);
  }
  
  // optional uint32 loops_width = 3;
  if (_has_bit(2)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->loops_width(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int AppLayout::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .rec.gui.Rectangle bounds = 1;
    if (has_bounds()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->bounds());
    }
    
    // optional uint32 directory_height = 2;
    if (has_directory_height()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->directory_height());
    }
    
    // optional uint32 loops_width = 3;
    if (has_loops_width()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->loops_width());
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

void AppLayout::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const AppLayout* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const AppLayout*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void AppLayout::MergeFrom(const AppLayout& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      mutable_bounds()->::rec::gui::Rectangle::MergeFrom(from.bounds());
    }
    if (from._has_bit(1)) {
      set_directory_height(from.directory_height());
    }
    if (from._has_bit(2)) {
      set_loops_width(from.loops_width());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void AppLayout::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AppLayout::CopyFrom(const AppLayout& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AppLayout::IsInitialized() const {
  
  return true;
}

void AppLayout::Swap(AppLayout* other) {
  if (other != this) {
    std::swap(bounds_, other->bounds_);
    std::swap(directory_height_, other->directory_height_);
    std::swap(loops_width_, other->loops_width_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata AppLayout::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = AppLayout_descriptor_;
  metadata.reflection = AppLayout_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace slow
}  // namespace rec

// @@protoc_insertion_point(global_scope)
