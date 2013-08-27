// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/widget/waveform/Viewport.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/widget/waveform/Viewport.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace rec {
namespace widget {
namespace waveform {

namespace {

const ::google::protobuf::Descriptor* Viewport_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Viewport_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2fwidget_2fwaveform_2fViewport_2eproto() {
  protobuf_AddDesc_rec_2fwidget_2fwaveform_2fViewport_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/widget/waveform/Viewport.proto");
  GOOGLE_CHECK(file != NULL);
  Viewport_descriptor_ = file->message_type(0);
  static const int Viewport_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Viewport, loop_points_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Viewport, zoom_),
  };
  Viewport_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Viewport_descriptor_,
      Viewport::default_instance_,
      Viewport_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Viewport, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Viewport, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Viewport));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2fwidget_2fwaveform_2fViewport_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Viewport_descriptor_, &Viewport::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2fwidget_2fwaveform_2fViewport_2eproto() {
  delete Viewport::default_instance_;
  delete Viewport_reflection_;
}

void protobuf_AddDesc_rec_2fwidget_2fwaveform_2fViewport_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::rec::util::protobuf_AddDesc_rec_2futil_2fLoopPoint_2eproto();
  ::rec::widget::waveform::protobuf_AddDesc_rec_2fwidget_2fwaveform_2fZoom_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\"rec/widget/waveform/Viewport.proto\022\023re"
    "c.widget.waveform\032\030rec/util/LoopPoint.pr"
    "oto\032\036rec/widget/waveform/Zoom.proto\"a\n\010V"
    "iewport\022,\n\013loop_points\030\001 \001(\0132\027.rec.util."
    "LoopPointList\022\'\n\004zoom\030\002 \001(\0132\031.rec.widget"
    ".waveform.Zoom", 214);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/widget/waveform/Viewport.proto", &protobuf_RegisterTypes);
  Viewport::default_instance_ = new Viewport();
  Viewport::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2fwidget_2fwaveform_2fViewport_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2fwidget_2fwaveform_2fViewport_2eproto {
  StaticDescriptorInitializer_rec_2fwidget_2fwaveform_2fViewport_2eproto() {
    protobuf_AddDesc_rec_2fwidget_2fwaveform_2fViewport_2eproto();
  }
} static_descriptor_initializer_rec_2fwidget_2fwaveform_2fViewport_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Viewport::kLoopPointsFieldNumber;
const int Viewport::kZoomFieldNumber;
#endif  // !_MSC_VER

Viewport::Viewport()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Viewport::InitAsDefaultInstance() {
  loop_points_ = const_cast< ::rec::util::LoopPointList*>(&::rec::util::LoopPointList::default_instance());
  zoom_ = const_cast< ::rec::widget::waveform::Zoom*>(&::rec::widget::waveform::Zoom::default_instance());
}

Viewport::Viewport(const Viewport& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Viewport::SharedCtor() {
  _cached_size_ = 0;
  loop_points_ = NULL;
  zoom_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Viewport::~Viewport() {
  SharedDtor();
}

void Viewport::SharedDtor() {
  if (this != default_instance_) {
    delete loop_points_;
    delete zoom_;
  }
}

void Viewport::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Viewport::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Viewport_descriptor_;
}

const Viewport& Viewport::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fwidget_2fwaveform_2fViewport_2eproto();
  return *default_instance_;
}

Viewport* Viewport::default_instance_ = NULL;

Viewport* Viewport::New() const {
  return new Viewport;
}

void Viewport::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_loop_points()) {
      if (loop_points_ != NULL) loop_points_->::rec::util::LoopPointList::Clear();
    }
    if (has_zoom()) {
      if (zoom_ != NULL) zoom_->::rec::widget::waveform::Zoom::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Viewport::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .rec.util.LoopPointList loop_points = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_loop_points()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_zoom;
        break;
      }

      // optional .rec.widget.waveform.Zoom zoom = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_zoom:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_zoom()));
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

void Viewport::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .rec.util.LoopPointList loop_points = 1;
  if (has_loop_points()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->loop_points(), output);
  }

  // optional .rec.widget.waveform.Zoom zoom = 2;
  if (has_zoom()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->zoom(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Viewport::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .rec.util.LoopPointList loop_points = 1;
  if (has_loop_points()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->loop_points(), target);
  }

  // optional .rec.widget.waveform.Zoom zoom = 2;
  if (has_zoom()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->zoom(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Viewport::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .rec.util.LoopPointList loop_points = 1;
    if (has_loop_points()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->loop_points());
    }

    // optional .rec.widget.waveform.Zoom zoom = 2;
    if (has_zoom()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->zoom());
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

void Viewport::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Viewport* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Viewport*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Viewport::MergeFrom(const Viewport& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_loop_points()) {
      mutable_loop_points()->::rec::util::LoopPointList::MergeFrom(from.loop_points());
    }
    if (from.has_zoom()) {
      mutable_zoom()->::rec::widget::waveform::Zoom::MergeFrom(from.zoom());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Viewport::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Viewport::CopyFrom(const Viewport& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Viewport::IsInitialized() const {

  return true;
}

void Viewport::Swap(Viewport* other) {
  if (other != this) {
    std::swap(loop_points_, other->loop_points_);
    std::swap(zoom_, other->zoom_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Viewport::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Viewport_descriptor_;
  metadata.reflection = Viewport_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace waveform
}  // namespace widget
}  // namespace rec

// @@protoc_insertion_point(global_scope)
