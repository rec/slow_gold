// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/widget/waveform/Cursor.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace rec {
namespace widget {
namespace waveform {

namespace {

const ::google::protobuf::Descriptor* CursorProto_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  CursorProto_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* CursorProto_Type_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2fwidget_2fwaveform_2fCursor_2eproto() {
  protobuf_AddDesc_rec_2fwidget_2fwaveform_2fCursor_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/widget/waveform/Cursor.proto");
  GOOGLE_CHECK(file != NULL);
  CursorProto_descriptor_ = file->message_type(0);
  static const int CursorProto_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CursorProto, widget_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CursorProto, type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CursorProto, line_),
  };
  CursorProto_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      CursorProto_descriptor_,
      CursorProto::default_instance_,
      CursorProto_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CursorProto, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CursorProto, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(CursorProto));
  CursorProto_Type_descriptor_ = CursorProto_descriptor_->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2fwidget_2fwaveform_2fCursor_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    CursorProto_descriptor_, &CursorProto::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2fwidget_2fwaveform_2fCursor_2eproto() {
  delete CursorProto::default_instance_;
  delete CursorProto_reflection_;
}

void protobuf_AddDesc_rec_2fwidget_2fwaveform_2fCursor_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::rec::widget::protobuf_AddDesc_rec_2fwidget_2fWidget_2eproto();
  ::rec::gui::protobuf_AddDesc_rec_2fgui_2fGeometry_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n rec/widget/waveform/Cursor.proto\022\023rec."
    "widget.waveform\032\027rec/widget/Widget.proto"
    "\032\026rec/gui/Geometry.proto\"\312\001\n\013CursorProto"
    "\022\"\n\006widget\030\001 \001(\0132\022.rec.widget.Widget\0223\n\004"
    "type\030\002 \001(\0162%.rec.widget.waveform.CursorP"
    "roto.Type\022\033\n\004line\030\003 \001(\0132\r.rec.gui.Line\"E"
    "\n\004Type\022\010\n\004NONE\020\000\022\025\n\021PLAYBACK_POSITION\020\001\022"
    "\016\n\nLOOP_START\020\002\022\014\n\010LOOP_END\020\003", 309);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/widget/waveform/Cursor.proto", &protobuf_RegisterTypes);
  CursorProto::default_instance_ = new CursorProto();
  CursorProto::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2fwidget_2fwaveform_2fCursor_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2fwidget_2fwaveform_2fCursor_2eproto {
  StaticDescriptorInitializer_rec_2fwidget_2fwaveform_2fCursor_2eproto() {
    protobuf_AddDesc_rec_2fwidget_2fwaveform_2fCursor_2eproto();
  }
} static_descriptor_initializer_rec_2fwidget_2fwaveform_2fCursor_2eproto_;


// ===================================================================

const ::google::protobuf::EnumDescriptor* CursorProto_Type_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return CursorProto_Type_descriptor_;
}
bool CursorProto_Type_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const CursorProto_Type CursorProto::NONE;
const CursorProto_Type CursorProto::PLAYBACK_POSITION;
const CursorProto_Type CursorProto::LOOP_START;
const CursorProto_Type CursorProto::LOOP_END;
const CursorProto_Type CursorProto::Type_MIN;
const CursorProto_Type CursorProto::Type_MAX;
const int CursorProto::Type_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int CursorProto::kWidgetFieldNumber;
const int CursorProto::kTypeFieldNumber;
const int CursorProto::kLineFieldNumber;
#endif  // !_MSC_VER

CursorProto::CursorProto()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void CursorProto::InitAsDefaultInstance() {
  widget_ = const_cast< ::rec::widget::Widget*>(&::rec::widget::Widget::default_instance());
  line_ = const_cast< ::rec::gui::Line*>(&::rec::gui::Line::default_instance());
}

CursorProto::CursorProto(const CursorProto& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void CursorProto::SharedCtor() {
  _cached_size_ = 0;
  widget_ = NULL;
  type_ = 0;
  line_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

CursorProto::~CursorProto() {
  SharedDtor();
}

void CursorProto::SharedDtor() {
  if (this != default_instance_) {
    delete widget_;
    delete line_;
  }
}

void CursorProto::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* CursorProto::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return CursorProto_descriptor_;
}

const CursorProto& CursorProto::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fwidget_2fwaveform_2fCursor_2eproto();  return *default_instance_;
}

CursorProto* CursorProto::default_instance_ = NULL;

CursorProto* CursorProto::New() const {
  return new CursorProto;
}

void CursorProto::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (_has_bit(0)) {
      if (widget_ != NULL) widget_->::rec::widget::Widget::Clear();
    }
    type_ = 0;
    if (_has_bit(2)) {
      if (line_ != NULL) line_->::rec::gui::Line::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool CursorProto::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .rec.widget.Widget widget = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_widget()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_type;
        break;
      }
      
      // optional .rec.widget.waveform.CursorProto.Type type = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_type:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::rec::widget::waveform::CursorProto_Type_IsValid(value)) {
            set_type(static_cast< ::rec::widget::waveform::CursorProto_Type >(value));
          } else {
            mutable_unknown_fields()->AddVarint(2, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_line;
        break;
      }
      
      // optional .rec.gui.Line line = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_line:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_line()));
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

void CursorProto::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .rec.widget.Widget widget = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->widget(), output);
  }
  
  // optional .rec.widget.waveform.CursorProto.Type type = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      2, this->type(), output);
  }
  
  // optional .rec.gui.Line line = 3;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->line(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* CursorProto::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .rec.widget.Widget widget = 1;
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->widget(), target);
  }
  
  // optional .rec.widget.waveform.CursorProto.Type type = 2;
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      2, this->type(), target);
  }
  
  // optional .rec.gui.Line line = 3;
  if (_has_bit(2)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->line(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int CursorProto::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .rec.widget.Widget widget = 1;
    if (has_widget()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->widget());
    }
    
    // optional .rec.widget.waveform.CursorProto.Type type = 2;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->type());
    }
    
    // optional .rec.gui.Line line = 3;
    if (has_line()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->line());
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

void CursorProto::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const CursorProto* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const CursorProto*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void CursorProto::MergeFrom(const CursorProto& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      mutable_widget()->::rec::widget::Widget::MergeFrom(from.widget());
    }
    if (from._has_bit(1)) {
      set_type(from.type());
    }
    if (from._has_bit(2)) {
      mutable_line()->::rec::gui::Line::MergeFrom(from.line());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void CursorProto::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void CursorProto::CopyFrom(const CursorProto& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CursorProto::IsInitialized() const {
  
  return true;
}

void CursorProto::Swap(CursorProto* other) {
  if (other != this) {
    std::swap(widget_, other->widget_);
    std::swap(type_, other->type_);
    std::swap(line_, other->line_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata CursorProto::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = CursorProto_descriptor_;
  metadata.reflection = CursorProto_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace waveform
}  // namespace widget
}  // namespace rec

// @@protoc_insertion_point(global_scope)
