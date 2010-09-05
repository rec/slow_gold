// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/components/ThumbnailDescription.pb.h"
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

const ::google::protobuf::Descriptor* ThumbnailDescription_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ThumbnailDescription_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2fcomponents_2fThumbnailDescription_2eproto() {
  protobuf_AddDesc_rec_2fcomponents_2fThumbnailDescription_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/components/ThumbnailDescription.proto");
  GOOGLE_CHECK(file != NULL);
  ThumbnailDescription_descriptor_ = file->message_type(0);
  static const int ThumbnailDescription_offsets_[9] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ThumbnailDescription, background_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ThumbnailDescription, foreground_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ThumbnailDescription, cursor_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ThumbnailDescription, cursor_thickness_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ThumbnailDescription, margin_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ThumbnailDescription, source_samples_per_thumbnail_sample_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ThumbnailDescription, thumbnail_cache_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ThumbnailDescription, cursor_thread_update_period_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ThumbnailDescription, cursor_thread_priority_),
  };
  ThumbnailDescription_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ThumbnailDescription_descriptor_,
      ThumbnailDescription::default_instance_,
      ThumbnailDescription_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ThumbnailDescription, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ThumbnailDescription, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ThumbnailDescription));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2fcomponents_2fThumbnailDescription_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ThumbnailDescription_descriptor_, &ThumbnailDescription::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2fcomponents_2fThumbnailDescription_2eproto() {
  delete ThumbnailDescription::default_instance_;
  delete ThumbnailDescription_reflection_;
}

void protobuf_AddDesc_rec_2fcomponents_2fThumbnailDescription_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::rec::gui::protobuf_AddDesc_rec_2fcomponents_2fColor_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n)rec/components/ThumbnailDescription.pr"
    "oto\022\007rec.gui\032\032rec/components/Color.proto"
    "\"\310\002\n\024ThumbnailDescription\022\"\n\nbackground\030"
    "\001 \001(\0132\016.rec.gui.Color\022\"\n\nforeground\030\002 \001("
    "\0132\016.rec.gui.Color\022\036\n\006cursor\030\003 \001(\0132\016.rec."
    "gui.Color\022\033\n\020cursor_thickness\030\004 \001(\r:\0011\022\021"
    "\n\006margin\030\005 \001(\r:\0012\0220\n#source_samples_per_"
    "thumbnail_sample\030\006 \001(\r:\003512\022\032\n\017thumbnail"
    "_cache\030\007 \001(\r:\0015\022\'\n\033cursor_thread_update_"
    "period\030\010 \001(\r:\00240\022!\n\026cursor_thread_priori"
    "ty\030\t \001(\r:\0014", 411);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/components/ThumbnailDescription.proto", &protobuf_RegisterTypes);
  ThumbnailDescription::default_instance_ = new ThumbnailDescription();
  ThumbnailDescription::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2fcomponents_2fThumbnailDescription_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2fcomponents_2fThumbnailDescription_2eproto {
  StaticDescriptorInitializer_rec_2fcomponents_2fThumbnailDescription_2eproto() {
    protobuf_AddDesc_rec_2fcomponents_2fThumbnailDescription_2eproto();
  }
} static_descriptor_initializer_rec_2fcomponents_2fThumbnailDescription_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int ThumbnailDescription::kBackgroundFieldNumber;
const int ThumbnailDescription::kForegroundFieldNumber;
const int ThumbnailDescription::kCursorFieldNumber;
const int ThumbnailDescription::kCursorThicknessFieldNumber;
const int ThumbnailDescription::kMarginFieldNumber;
const int ThumbnailDescription::kSourceSamplesPerThumbnailSampleFieldNumber;
const int ThumbnailDescription::kThumbnailCacheFieldNumber;
const int ThumbnailDescription::kCursorThreadUpdatePeriodFieldNumber;
const int ThumbnailDescription::kCursorThreadPriorityFieldNumber;
#endif  // !_MSC_VER

ThumbnailDescription::ThumbnailDescription()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void ThumbnailDescription::InitAsDefaultInstance() {
  background_ = const_cast< ::rec::gui::Color*>(&::rec::gui::Color::default_instance());
  foreground_ = const_cast< ::rec::gui::Color*>(&::rec::gui::Color::default_instance());
  cursor_ = const_cast< ::rec::gui::Color*>(&::rec::gui::Color::default_instance());
}

ThumbnailDescription::ThumbnailDescription(const ThumbnailDescription& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void ThumbnailDescription::SharedCtor() {
  _cached_size_ = 0;
  background_ = NULL;
  foreground_ = NULL;
  cursor_ = NULL;
  cursor_thickness_ = 1u;
  margin_ = 2u;
  source_samples_per_thumbnail_sample_ = 512u;
  thumbnail_cache_ = 5u;
  cursor_thread_update_period_ = 40u;
  cursor_thread_priority_ = 4u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ThumbnailDescription::~ThumbnailDescription() {
  SharedDtor();
}

void ThumbnailDescription::SharedDtor() {
  if (this != default_instance_) {
    delete background_;
    delete foreground_;
    delete cursor_;
  }
}

void ThumbnailDescription::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ThumbnailDescription::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ThumbnailDescription_descriptor_;
}

const ThumbnailDescription& ThumbnailDescription::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fcomponents_2fThumbnailDescription_2eproto();  return *default_instance_;
}

ThumbnailDescription* ThumbnailDescription::default_instance_ = NULL;

ThumbnailDescription* ThumbnailDescription::New() const {
  return new ThumbnailDescription;
}

void ThumbnailDescription::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (_has_bit(0)) {
      if (background_ != NULL) background_->::rec::gui::Color::Clear();
    }
    if (_has_bit(1)) {
      if (foreground_ != NULL) foreground_->::rec::gui::Color::Clear();
    }
    if (_has_bit(2)) {
      if (cursor_ != NULL) cursor_->::rec::gui::Color::Clear();
    }
    cursor_thickness_ = 1u;
    margin_ = 2u;
    source_samples_per_thumbnail_sample_ = 512u;
    thumbnail_cache_ = 5u;
    cursor_thread_update_period_ = 40u;
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    cursor_thread_priority_ = 4u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ThumbnailDescription::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .rec.gui.Color background = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_background()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_foreground;
        break;
      }
      
      // optional .rec.gui.Color foreground = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_foreground:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_foreground()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_cursor;
        break;
      }
      
      // optional .rec.gui.Color cursor = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_cursor:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_cursor()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_cursor_thickness;
        break;
      }
      
      // optional uint32 cursor_thickness = 4 [default = 1];
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_cursor_thickness:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &cursor_thickness_)));
          _set_bit(3);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_margin;
        break;
      }
      
      // optional uint32 margin = 5 [default = 2];
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_margin:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &margin_)));
          _set_bit(4);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(48)) goto parse_source_samples_per_thumbnail_sample;
        break;
      }
      
      // optional uint32 source_samples_per_thumbnail_sample = 6 [default = 512];
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_source_samples_per_thumbnail_sample:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &source_samples_per_thumbnail_sample_)));
          _set_bit(5);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(56)) goto parse_thumbnail_cache;
        break;
      }
      
      // optional uint32 thumbnail_cache = 7 [default = 5];
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_thumbnail_cache:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &thumbnail_cache_)));
          _set_bit(6);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(64)) goto parse_cursor_thread_update_period;
        break;
      }
      
      // optional uint32 cursor_thread_update_period = 8 [default = 40];
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_cursor_thread_update_period:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &cursor_thread_update_period_)));
          _set_bit(7);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(72)) goto parse_cursor_thread_priority;
        break;
      }
      
      // optional uint32 cursor_thread_priority = 9 [default = 4];
      case 9: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_cursor_thread_priority:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &cursor_thread_priority_)));
          _set_bit(8);
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

void ThumbnailDescription::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .rec.gui.Color background = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->background(), output);
  }
  
  // optional .rec.gui.Color foreground = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->foreground(), output);
  }
  
  // optional .rec.gui.Color cursor = 3;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->cursor(), output);
  }
  
  // optional uint32 cursor_thickness = 4 [default = 1];
  if (_has_bit(3)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->cursor_thickness(), output);
  }
  
  // optional uint32 margin = 5 [default = 2];
  if (_has_bit(4)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(5, this->margin(), output);
  }
  
  // optional uint32 source_samples_per_thumbnail_sample = 6 [default = 512];
  if (_has_bit(5)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(6, this->source_samples_per_thumbnail_sample(), output);
  }
  
  // optional uint32 thumbnail_cache = 7 [default = 5];
  if (_has_bit(6)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(7, this->thumbnail_cache(), output);
  }
  
  // optional uint32 cursor_thread_update_period = 8 [default = 40];
  if (_has_bit(7)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(8, this->cursor_thread_update_period(), output);
  }
  
  // optional uint32 cursor_thread_priority = 9 [default = 4];
  if (_has_bit(8)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(9, this->cursor_thread_priority(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* ThumbnailDescription::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .rec.gui.Color background = 1;
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->background(), target);
  }
  
  // optional .rec.gui.Color foreground = 2;
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->foreground(), target);
  }
  
  // optional .rec.gui.Color cursor = 3;
  if (_has_bit(2)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->cursor(), target);
  }
  
  // optional uint32 cursor_thickness = 4 [default = 1];
  if (_has_bit(3)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->cursor_thickness(), target);
  }
  
  // optional uint32 margin = 5 [default = 2];
  if (_has_bit(4)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(5, this->margin(), target);
  }
  
  // optional uint32 source_samples_per_thumbnail_sample = 6 [default = 512];
  if (_has_bit(5)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(6, this->source_samples_per_thumbnail_sample(), target);
  }
  
  // optional uint32 thumbnail_cache = 7 [default = 5];
  if (_has_bit(6)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(7, this->thumbnail_cache(), target);
  }
  
  // optional uint32 cursor_thread_update_period = 8 [default = 40];
  if (_has_bit(7)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(8, this->cursor_thread_update_period(), target);
  }
  
  // optional uint32 cursor_thread_priority = 9 [default = 4];
  if (_has_bit(8)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(9, this->cursor_thread_priority(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int ThumbnailDescription::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .rec.gui.Color background = 1;
    if (has_background()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->background());
    }
    
    // optional .rec.gui.Color foreground = 2;
    if (has_foreground()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->foreground());
    }
    
    // optional .rec.gui.Color cursor = 3;
    if (has_cursor()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->cursor());
    }
    
    // optional uint32 cursor_thickness = 4 [default = 1];
    if (has_cursor_thickness()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->cursor_thickness());
    }
    
    // optional uint32 margin = 5 [default = 2];
    if (has_margin()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->margin());
    }
    
    // optional uint32 source_samples_per_thumbnail_sample = 6 [default = 512];
    if (has_source_samples_per_thumbnail_sample()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->source_samples_per_thumbnail_sample());
    }
    
    // optional uint32 thumbnail_cache = 7 [default = 5];
    if (has_thumbnail_cache()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->thumbnail_cache());
    }
    
    // optional uint32 cursor_thread_update_period = 8 [default = 40];
    if (has_cursor_thread_update_period()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->cursor_thread_update_period());
    }
    
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // optional uint32 cursor_thread_priority = 9 [default = 4];
    if (has_cursor_thread_priority()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->cursor_thread_priority());
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

void ThumbnailDescription::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ThumbnailDescription* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ThumbnailDescription*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ThumbnailDescription::MergeFrom(const ThumbnailDescription& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      mutable_background()->::rec::gui::Color::MergeFrom(from.background());
    }
    if (from._has_bit(1)) {
      mutable_foreground()->::rec::gui::Color::MergeFrom(from.foreground());
    }
    if (from._has_bit(2)) {
      mutable_cursor()->::rec::gui::Color::MergeFrom(from.cursor());
    }
    if (from._has_bit(3)) {
      set_cursor_thickness(from.cursor_thickness());
    }
    if (from._has_bit(4)) {
      set_margin(from.margin());
    }
    if (from._has_bit(5)) {
      set_source_samples_per_thumbnail_sample(from.source_samples_per_thumbnail_sample());
    }
    if (from._has_bit(6)) {
      set_thumbnail_cache(from.thumbnail_cache());
    }
    if (from._has_bit(7)) {
      set_cursor_thread_update_period(from.cursor_thread_update_period());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from._has_bit(8)) {
      set_cursor_thread_priority(from.cursor_thread_priority());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ThumbnailDescription::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ThumbnailDescription::CopyFrom(const ThumbnailDescription& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ThumbnailDescription::IsInitialized() const {
  
  return true;
}

void ThumbnailDescription::Swap(ThumbnailDescription* other) {
  if (other != this) {
    std::swap(background_, other->background_);
    std::swap(foreground_, other->foreground_);
    std::swap(cursor_, other->cursor_);
    std::swap(cursor_thickness_, other->cursor_thickness_);
    std::swap(margin_, other->margin_);
    std::swap(source_samples_per_thumbnail_sample_, other->source_samples_per_thumbnail_sample_);
    std::swap(thumbnail_cache_, other->thumbnail_cache_);
    std::swap(cursor_thread_update_period_, other->cursor_thread_update_period_);
    std::swap(cursor_thread_priority_, other->cursor_thread_priority_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ThumbnailDescription::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ThumbnailDescription_descriptor_;
  metadata.reflection = ThumbnailDescription_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace gui
}  // namespace rec

// @@protoc_insertion_point(global_scope)
