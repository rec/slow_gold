// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/gui/Geometry.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/gui/Geometry.pb.h"

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
namespace gui {

namespace {

const ::google::protobuf::Descriptor* Point_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Point_reflection_ = NULL;
const ::google::protobuf::Descriptor* Rectangle_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Rectangle_reflection_ = NULL;
const ::google::protobuf::Descriptor* Line_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Line_reflection_ = NULL;
const ::google::protobuf::Descriptor* Layer_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Layer_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2fgui_2fGeometry_2eproto() {
  protobuf_AddDesc_rec_2fgui_2fGeometry_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/gui/Geometry.proto");
  GOOGLE_CHECK(file != NULL);
  Point_descriptor_ = file->message_type(0);
  static const int Point_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Point, x_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Point, y_),
  };
  Point_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Point_descriptor_,
      Point::default_instance_,
      Point_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Point, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Point, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Point));
  Rectangle_descriptor_ = file->message_type(1);
  static const int Rectangle_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Rectangle, top_left_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Rectangle, dimensions_),
  };
  Rectangle_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Rectangle_descriptor_,
      Rectangle::default_instance_,
      Rectangle_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Rectangle, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Rectangle, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Rectangle));
  Line_descriptor_ = file->message_type(2);
  static const int Line_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Line, bounds_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Line, thickness_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Line, dashing_),
  };
  Line_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Line_descriptor_,
      Line::default_instance_,
      Line_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Line, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Line, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Line));
  Layer_descriptor_ = file->message_type(3);
  static const int Layer_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Layer, bounds_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Layer, zorder_),
  };
  Layer_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Layer_descriptor_,
      Layer::default_instance_,
      Layer_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Layer, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Layer, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Layer));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2fgui_2fGeometry_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Point_descriptor_, &Point::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Rectangle_descriptor_, &Rectangle::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Line_descriptor_, &Line::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Layer_descriptor_, &Layer::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2fgui_2fGeometry_2eproto() {
  delete Point::default_instance_;
  delete Point_reflection_;
  delete Rectangle::default_instance_;
  delete Rectangle_reflection_;
  delete Line::default_instance_;
  delete Line_reflection_;
  delete Layer::default_instance_;
  delete Layer_reflection_;
}

void protobuf_AddDesc_rec_2fgui_2fGeometry_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\026rec/gui/Geometry.proto\022\007rec.gui\"\035\n\005Poi"
    "nt\022\t\n\001x\030\001 \001(\005\022\t\n\001y\030\002 \001(\005\"Q\n\tRectangle\022 \n"
    "\010top_left\030\001 \001(\0132\016.rec.gui.Point\022\"\n\ndimen"
    "sions\030\002 \001(\0132\016.rec.gui.Point\"Q\n\004Line\022\"\n\006b"
    "ounds\030\001 \001(\0132\022.rec.gui.Rectangle\022\024\n\tthick"
    "ness\030\002 \001(\002:\0011\022\017\n\007dashing\030\003 \003(\002\"\?\n\005Layer\022"
    "\"\n\006bounds\030\001 \001(\0132\022.rec.gui.Rectangle\022\022\n\006z"
    "Order\030\002 \001(\005:\002-1", 295);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/gui/Geometry.proto", &protobuf_RegisterTypes);
  Point::default_instance_ = new Point();
  Rectangle::default_instance_ = new Rectangle();
  Line::default_instance_ = new Line();
  Layer::default_instance_ = new Layer();
  Point::default_instance_->InitAsDefaultInstance();
  Rectangle::default_instance_->InitAsDefaultInstance();
  Line::default_instance_->InitAsDefaultInstance();
  Layer::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2fgui_2fGeometry_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2fgui_2fGeometry_2eproto {
  StaticDescriptorInitializer_rec_2fgui_2fGeometry_2eproto() {
    protobuf_AddDesc_rec_2fgui_2fGeometry_2eproto();
  }
} static_descriptor_initializer_rec_2fgui_2fGeometry_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Point::kXFieldNumber;
const int Point::kYFieldNumber;
#endif  // !_MSC_VER

Point::Point()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Point::InitAsDefaultInstance() {
}

Point::Point(const Point& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Point::SharedCtor() {
  _cached_size_ = 0;
  x_ = 0;
  y_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Point::~Point() {
  SharedDtor();
}

void Point::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Point::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Point::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Point_descriptor_;
}

const Point& Point::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fgui_2fGeometry_2eproto();
  return *default_instance_;
}

Point* Point::default_instance_ = NULL;

Point* Point::New() const {
  return new Point;
}

void Point::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    x_ = 0;
    y_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Point::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 x = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &x_)));
          set_has_x();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_y;
        break;
      }

      // optional int32 y = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_y:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &y_)));
          set_has_y();
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

void Point::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional int32 x = 1;
  if (has_x()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->x(), output);
  }

  // optional int32 y = 2;
  if (has_y()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->y(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Point::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional int32 x = 1;
  if (has_x()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->x(), target);
  }

  // optional int32 y = 2;
  if (has_y()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->y(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Point::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional int32 x = 1;
    if (has_x()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->x());
    }

    // optional int32 y = 2;
    if (has_y()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->y());
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

void Point::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Point* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Point*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Point::MergeFrom(const Point& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_x()) {
      set_x(from.x());
    }
    if (from.has_y()) {
      set_y(from.y());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Point::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Point::CopyFrom(const Point& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Point::IsInitialized() const {

  return true;
}

void Point::Swap(Point* other) {
  if (other != this) {
    std::swap(x_, other->x_);
    std::swap(y_, other->y_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Point::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Point_descriptor_;
  metadata.reflection = Point_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Rectangle::kTopLeftFieldNumber;
const int Rectangle::kDimensionsFieldNumber;
#endif  // !_MSC_VER

Rectangle::Rectangle()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Rectangle::InitAsDefaultInstance() {
  top_left_ = const_cast< ::rec::gui::Point*>(&::rec::gui::Point::default_instance());
  dimensions_ = const_cast< ::rec::gui::Point*>(&::rec::gui::Point::default_instance());
}

Rectangle::Rectangle(const Rectangle& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Rectangle::SharedCtor() {
  _cached_size_ = 0;
  top_left_ = NULL;
  dimensions_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Rectangle::~Rectangle() {
  SharedDtor();
}

void Rectangle::SharedDtor() {
  if (this != default_instance_) {
    delete top_left_;
    delete dimensions_;
  }
}

void Rectangle::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Rectangle::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Rectangle_descriptor_;
}

const Rectangle& Rectangle::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fgui_2fGeometry_2eproto();
  return *default_instance_;
}

Rectangle* Rectangle::default_instance_ = NULL;

Rectangle* Rectangle::New() const {
  return new Rectangle;
}

void Rectangle::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_top_left()) {
      if (top_left_ != NULL) top_left_->::rec::gui::Point::Clear();
    }
    if (has_dimensions()) {
      if (dimensions_ != NULL) dimensions_->::rec::gui::Point::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Rectangle::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .rec.gui.Point top_left = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_top_left()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_dimensions;
        break;
      }

      // optional .rec.gui.Point dimensions = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_dimensions:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_dimensions()));
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

void Rectangle::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .rec.gui.Point top_left = 1;
  if (has_top_left()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->top_left(), output);
  }

  // optional .rec.gui.Point dimensions = 2;
  if (has_dimensions()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->dimensions(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Rectangle::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .rec.gui.Point top_left = 1;
  if (has_top_left()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->top_left(), target);
  }

  // optional .rec.gui.Point dimensions = 2;
  if (has_dimensions()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->dimensions(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Rectangle::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .rec.gui.Point top_left = 1;
    if (has_top_left()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->top_left());
    }

    // optional .rec.gui.Point dimensions = 2;
    if (has_dimensions()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->dimensions());
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

void Rectangle::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Rectangle* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Rectangle*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Rectangle::MergeFrom(const Rectangle& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_top_left()) {
      mutable_top_left()->::rec::gui::Point::MergeFrom(from.top_left());
    }
    if (from.has_dimensions()) {
      mutable_dimensions()->::rec::gui::Point::MergeFrom(from.dimensions());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Rectangle::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Rectangle::CopyFrom(const Rectangle& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Rectangle::IsInitialized() const {

  return true;
}

void Rectangle::Swap(Rectangle* other) {
  if (other != this) {
    std::swap(top_left_, other->top_left_);
    std::swap(dimensions_, other->dimensions_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Rectangle::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Rectangle_descriptor_;
  metadata.reflection = Rectangle_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Line::kBoundsFieldNumber;
const int Line::kThicknessFieldNumber;
const int Line::kDashingFieldNumber;
#endif  // !_MSC_VER

Line::Line()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Line::InitAsDefaultInstance() {
  bounds_ = const_cast< ::rec::gui::Rectangle*>(&::rec::gui::Rectangle::default_instance());
}

Line::Line(const Line& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Line::SharedCtor() {
  _cached_size_ = 0;
  bounds_ = NULL;
  thickness_ = 1;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Line::~Line() {
  SharedDtor();
}

void Line::SharedDtor() {
  if (this != default_instance_) {
    delete bounds_;
  }
}

void Line::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Line::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Line_descriptor_;
}

const Line& Line::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fgui_2fGeometry_2eproto();
  return *default_instance_;
}

Line* Line::default_instance_ = NULL;

Line* Line::New() const {
  return new Line;
}

void Line::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_bounds()) {
      if (bounds_ != NULL) bounds_->::rec::gui::Rectangle::Clear();
    }
    thickness_ = 1;
  }
  dashing_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Line::MergePartialFromCodedStream(
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
        if (input->ExpectTag(21)) goto parse_thickness;
        break;
      }

      // optional float thickness = 2 [default = 1];
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_thickness:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &thickness_)));
          set_has_thickness();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(29)) goto parse_dashing;
        break;
      }

      // repeated float dashing = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_dashing:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 1, 29, input, this->mutable_dashing())));
        } else if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag)
                   == ::google::protobuf::internal::WireFormatLite::
                      WIRETYPE_LENGTH_DELIMITED) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, this->mutable_dashing())));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(29)) goto parse_dashing;
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

void Line::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .rec.gui.Rectangle bounds = 1;
  if (has_bounds()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->bounds(), output);
  }

  // optional float thickness = 2 [default = 1];
  if (has_thickness()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(2, this->thickness(), output);
  }

  // repeated float dashing = 3;
  for (int i = 0; i < this->dashing_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(
      3, this->dashing(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Line::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .rec.gui.Rectangle bounds = 1;
  if (has_bounds()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->bounds(), target);
  }

  // optional float thickness = 2 [default = 1];
  if (has_thickness()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(2, this->thickness(), target);
  }

  // repeated float dashing = 3;
  for (int i = 0; i < this->dashing_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteFloatToArray(3, this->dashing(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Line::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .rec.gui.Rectangle bounds = 1;
    if (has_bounds()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->bounds());
    }

    // optional float thickness = 2 [default = 1];
    if (has_thickness()) {
      total_size += 1 + 4;
    }

  }
  // repeated float dashing = 3;
  {
    int data_size = 0;
    data_size = 4 * this->dashing_size();
    total_size += 1 * this->dashing_size() + data_size;
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

void Line::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Line* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Line*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Line::MergeFrom(const Line& from) {
  GOOGLE_CHECK_NE(&from, this);
  dashing_.MergeFrom(from.dashing_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_bounds()) {
      mutable_bounds()->::rec::gui::Rectangle::MergeFrom(from.bounds());
    }
    if (from.has_thickness()) {
      set_thickness(from.thickness());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Line::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Line::CopyFrom(const Line& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Line::IsInitialized() const {

  return true;
}

void Line::Swap(Line* other) {
  if (other != this) {
    std::swap(bounds_, other->bounds_);
    std::swap(thickness_, other->thickness_);
    dashing_.Swap(&other->dashing_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Line::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Line_descriptor_;
  metadata.reflection = Line_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Layer::kBoundsFieldNumber;
const int Layer::kZOrderFieldNumber;
#endif  // !_MSC_VER

Layer::Layer()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Layer::InitAsDefaultInstance() {
  bounds_ = const_cast< ::rec::gui::Rectangle*>(&::rec::gui::Rectangle::default_instance());
}

Layer::Layer(const Layer& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Layer::SharedCtor() {
  _cached_size_ = 0;
  bounds_ = NULL;
  zorder_ = -1;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Layer::~Layer() {
  SharedDtor();
}

void Layer::SharedDtor() {
  if (this != default_instance_) {
    delete bounds_;
  }
}

void Layer::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Layer::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Layer_descriptor_;
}

const Layer& Layer::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fgui_2fGeometry_2eproto();
  return *default_instance_;
}

Layer* Layer::default_instance_ = NULL;

Layer* Layer::New() const {
  return new Layer;
}

void Layer::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_bounds()) {
      if (bounds_ != NULL) bounds_->::rec::gui::Rectangle::Clear();
    }
    zorder_ = -1;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Layer::MergePartialFromCodedStream(
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
        if (input->ExpectTag(16)) goto parse_zOrder;
        break;
      }

      // optional int32 zOrder = 2 [default = -1];
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_zOrder:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &zorder_)));
          set_has_zorder();
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

void Layer::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .rec.gui.Rectangle bounds = 1;
  if (has_bounds()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->bounds(), output);
  }

  // optional int32 zOrder = 2 [default = -1];
  if (has_zorder()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->zorder(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Layer::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .rec.gui.Rectangle bounds = 1;
  if (has_bounds()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->bounds(), target);
  }

  // optional int32 zOrder = 2 [default = -1];
  if (has_zorder()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->zorder(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Layer::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .rec.gui.Rectangle bounds = 1;
    if (has_bounds()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->bounds());
    }

    // optional int32 zOrder = 2 [default = -1];
    if (has_zorder()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->zorder());
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

void Layer::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Layer* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Layer*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Layer::MergeFrom(const Layer& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_bounds()) {
      mutable_bounds()->::rec::gui::Rectangle::MergeFrom(from.bounds());
    }
    if (from.has_zorder()) {
      set_zorder(from.zorder());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Layer::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Layer::CopyFrom(const Layer& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Layer::IsInitialized() const {

  return true;
}

void Layer::Swap(Layer* other) {
  if (other != this) {
    std::swap(bounds_, other->bounds_);
    std::swap(zorder_, other->zorder_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Layer::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Layer_descriptor_;
  metadata.reflection = Layer_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace gui
}  // namespace rec

// @@protoc_insertion_point(global_scope)
