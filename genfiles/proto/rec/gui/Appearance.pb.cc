// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/gui/Appearance.pb.h"
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

const ::google::protobuf::Descriptor* Appearance_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Appearance_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2fgui_2fAppearance_2eproto() {
  protobuf_AddDesc_rec_2fgui_2fAppearance_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/gui/Appearance.proto");
  GOOGLE_CHECK(file != NULL);
  Appearance_descriptor_ = file->message_type(0);
  static const int Appearance_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Appearance, colors_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Appearance, thumbnail_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Appearance, time_),
  };
  Appearance_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Appearance_descriptor_,
      Appearance::default_instance_,
      Appearance_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Appearance, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Appearance, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Appearance));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2fgui_2fAppearance_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Appearance_descriptor_, &Appearance::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2fgui_2fAppearance_2eproto() {
  delete Appearance::default_instance_;
  delete Appearance_reflection_;
}

void protobuf_AddDesc_rec_2fgui_2fAppearance_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::rec::gui::protobuf_AddDesc_rec_2fgui_2fColor_2eproto();
  ::rec::widget::protobuf_AddDesc_rec_2fwidget_2fAudioThumbnail_2eproto();
  ::rec::widget::time::protobuf_AddDesc_rec_2fwidget_2fTime_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\030rec/gui/Appearance.proto\022\007rec.gui\032\023rec"
    "/gui/Color.proto\032\037rec/widget/AudioThumbn"
    "ail.proto\032\025rec/widget/Time.proto\"\205\001\n\nApp"
    "earance\022\037\n\006colors\030\001 \001(\0132\017.rec.gui.Colors"
    "\0221\n\tthumbnail\030\002 \001(\0132\036.rec.widget.AudioTh"
    "umbnailDesc\022#\n\004time\030\003 \001(\0132\025.rec.widget.t"
    "ime.Time", 248);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/gui/Appearance.proto", &protobuf_RegisterTypes);
  Appearance::default_instance_ = new Appearance();
  Appearance::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2fgui_2fAppearance_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2fgui_2fAppearance_2eproto {
  StaticDescriptorInitializer_rec_2fgui_2fAppearance_2eproto() {
    protobuf_AddDesc_rec_2fgui_2fAppearance_2eproto();
  }
} static_descriptor_initializer_rec_2fgui_2fAppearance_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int Appearance::kColorsFieldNumber;
const int Appearance::kThumbnailFieldNumber;
const int Appearance::kTimeFieldNumber;
#endif  // !_MSC_VER

Appearance::Appearance()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Appearance::InitAsDefaultInstance() {
  colors_ = const_cast< ::rec::gui::Colors*>(&::rec::gui::Colors::default_instance());
  thumbnail_ = const_cast< ::rec::widget::AudioThumbnailDesc*>(&::rec::widget::AudioThumbnailDesc::default_instance());
  time_ = const_cast< ::rec::widget::time::Time*>(&::rec::widget::time::Time::default_instance());
}

Appearance::Appearance(const Appearance& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Appearance::SharedCtor() {
  _cached_size_ = 0;
  colors_ = NULL;
  thumbnail_ = NULL;
  time_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Appearance::~Appearance() {
  SharedDtor();
}

void Appearance::SharedDtor() {
  if (this != default_instance_) {
    delete colors_;
    delete thumbnail_;
    delete time_;
  }
}

void Appearance::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Appearance::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Appearance_descriptor_;
}

const Appearance& Appearance::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fgui_2fAppearance_2eproto();  return *default_instance_;
}

Appearance* Appearance::default_instance_ = NULL;

Appearance* Appearance::New() const {
  return new Appearance;
}

void Appearance::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (_has_bit(0)) {
      if (colors_ != NULL) colors_->::rec::gui::Colors::Clear();
    }
    if (_has_bit(1)) {
      if (thumbnail_ != NULL) thumbnail_->::rec::widget::AudioThumbnailDesc::Clear();
    }
    if (_has_bit(2)) {
      if (time_ != NULL) time_->::rec::widget::time::Time::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Appearance::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .rec.gui.Colors colors = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_colors()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_thumbnail;
        break;
      }
      
      // optional .rec.widget.AudioThumbnailDesc thumbnail = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_thumbnail:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_thumbnail()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_time;
        break;
      }
      
      // optional .rec.widget.time.Time time = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_time:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_time()));
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

void Appearance::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .rec.gui.Colors colors = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->colors(), output);
  }
  
  // optional .rec.widget.AudioThumbnailDesc thumbnail = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->thumbnail(), output);
  }
  
  // optional .rec.widget.time.Time time = 3;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->time(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Appearance::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .rec.gui.Colors colors = 1;
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->colors(), target);
  }
  
  // optional .rec.widget.AudioThumbnailDesc thumbnail = 2;
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->thumbnail(), target);
  }
  
  // optional .rec.widget.time.Time time = 3;
  if (_has_bit(2)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->time(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Appearance::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .rec.gui.Colors colors = 1;
    if (has_colors()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->colors());
    }
    
    // optional .rec.widget.AudioThumbnailDesc thumbnail = 2;
    if (has_thumbnail()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->thumbnail());
    }
    
    // optional .rec.widget.time.Time time = 3;
    if (has_time()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->time());
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

void Appearance::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Appearance* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Appearance*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Appearance::MergeFrom(const Appearance& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      mutable_colors()->::rec::gui::Colors::MergeFrom(from.colors());
    }
    if (from._has_bit(1)) {
      mutable_thumbnail()->::rec::widget::AudioThumbnailDesc::MergeFrom(from.thumbnail());
    }
    if (from._has_bit(2)) {
      mutable_time()->::rec::widget::time::Time::MergeFrom(from.time());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Appearance::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Appearance::CopyFrom(const Appearance& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Appearance::IsInitialized() const {
  
  return true;
}

void Appearance::Swap(Appearance* other) {
  if (other != this) {
    std::swap(colors_, other->colors_);
    std::swap(thumbnail_, other->thumbnail_);
    std::swap(time_, other->time_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Appearance::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Appearance_descriptor_;
  metadata.reflection = Appearance_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace gui
}  // namespace rec

// @@protoc_insertion_point(global_scope)
