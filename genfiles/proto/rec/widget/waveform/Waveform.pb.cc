// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/widget/waveform/Waveform.pb.h"
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

const ::google::protobuf::Descriptor* WaveformProto_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  WaveformProto_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* WaveformProto_Layout_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2fwidget_2fwaveform_2fWaveform_2eproto() {
  protobuf_AddDesc_rec_2fwidget_2fwaveform_2fWaveform_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/widget/waveform/Waveform.proto");
  GOOGLE_CHECK(file != NULL);
  WaveformProto_descriptor_ = file->message_type(0);
  static const int WaveformProto_offsets_[15] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WaveformProto, widget_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WaveformProto, cursor_thickness_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WaveformProto, source_samples_per_thumbnail_sample_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WaveformProto, thumbnail_cache_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WaveformProto, cursor_thread_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WaveformProto, tic_height_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WaveformProto, subtic_height_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WaveformProto, use_captions_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WaveformProto, tics_at_bottom_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WaveformProto, selection_frame_in_seconds_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WaveformProto, show_grid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WaveformProto, parallel_waveforms_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WaveformProto, show_names_in_waveform_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WaveformProto, layout_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WaveformProto, show_selection_buttons_),
  };
  WaveformProto_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      WaveformProto_descriptor_,
      WaveformProto::default_instance_,
      WaveformProto_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WaveformProto, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(WaveformProto, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(WaveformProto));
  WaveformProto_Layout_descriptor_ = WaveformProto_descriptor_->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2fwidget_2fwaveform_2fWaveform_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    WaveformProto_descriptor_, &WaveformProto::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2fwidget_2fwaveform_2fWaveform_2eproto() {
  delete WaveformProto::default_instance_;
  delete WaveformProto_reflection_;
}

void protobuf_AddDesc_rec_2fwidget_2fwaveform_2fWaveform_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::rec::gui::protobuf_AddDesc_rec_2fgui_2fColor_2eproto();
  ::rec::gui::protobuf_AddDesc_rec_2fgui_2fFont_2eproto();
  ::rec::widget::protobuf_AddDesc_rec_2fwidget_2fWidget_2eproto();
  ::rec::util::thread::protobuf_AddDesc_rec_2futil_2fthread_2fThread_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\"rec/widget/waveform/Waveform.proto\022\023re"
    "c.widget.waveform\032\023rec/gui/Color.proto\032\022"
    "rec/gui/Font.proto\032\027rec/widget/Widget.pr"
    "oto\032\034rec/util/thread/Thread.proto\"\323\004\n\rWa"
    "veformProto\022\"\n\006widget\030\001 \001(\0132\022.rec.widget"
    ".Widget\022\033\n\020cursor_thickness\030\002 \001(\r:\0011\0220\n#"
    "source_samples_per_thumbnail_sample\030\004 \001("
    "\r:\003512\022\032\n\017thumbnail_cache\030\005 \001(\r:\0015\0229\n\rcu"
    "rsor_thread\030\006 \001(\0132\".rec.util.thread.Thre"
    "adDescription\022\025\n\ntic_height\030\010 \001(\r:\0018\022\030\n\r"
    "subtic_height\030\t \001(\r:\0013\022\032\n\014use_captions\030\n"
    " \001(\010:\004true\022\034\n\016tics_at_bottom\030\013 \001(\010:\004true"
    "\022%\n\032selection_frame_in_seconds\030\014 \001(\001:\0015\022"
    "\027\n\tshow_grid\030\r \001(\010:\004true\022!\n\022parallel_wav"
    "eforms\030\016 \001(\010:\005false\022$\n\026show_names_in_wav"
    "eform\030\017 \001(\010:\004true\0229\n\006layout\030\020 \001(\0162).rec."
    "widget.waveform.WaveformProto.Layout\022$\n\026"
    "show_selection_buttons\030\021 \001(\010:\004true\"#\n\006La"
    "yout\022\013\n\007STACKED\020\001\022\014\n\010PARALLEL\020\002", 751);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/widget/waveform/Waveform.proto", &protobuf_RegisterTypes);
  WaveformProto::default_instance_ = new WaveformProto();
  WaveformProto::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2fwidget_2fwaveform_2fWaveform_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2fwidget_2fwaveform_2fWaveform_2eproto {
  StaticDescriptorInitializer_rec_2fwidget_2fwaveform_2fWaveform_2eproto() {
    protobuf_AddDesc_rec_2fwidget_2fwaveform_2fWaveform_2eproto();
  }
} static_descriptor_initializer_rec_2fwidget_2fwaveform_2fWaveform_2eproto_;


// ===================================================================

const ::google::protobuf::EnumDescriptor* WaveformProto_Layout_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return WaveformProto_Layout_descriptor_;
}
bool WaveformProto_Layout_IsValid(int value) {
  switch(value) {
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const WaveformProto_Layout WaveformProto::STACKED;
const WaveformProto_Layout WaveformProto::PARALLEL;
const WaveformProto_Layout WaveformProto::Layout_MIN;
const WaveformProto_Layout WaveformProto::Layout_MAX;
const int WaveformProto::Layout_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int WaveformProto::kWidgetFieldNumber;
const int WaveformProto::kCursorThicknessFieldNumber;
const int WaveformProto::kSourceSamplesPerThumbnailSampleFieldNumber;
const int WaveformProto::kThumbnailCacheFieldNumber;
const int WaveformProto::kCursorThreadFieldNumber;
const int WaveformProto::kTicHeightFieldNumber;
const int WaveformProto::kSubticHeightFieldNumber;
const int WaveformProto::kUseCaptionsFieldNumber;
const int WaveformProto::kTicsAtBottomFieldNumber;
const int WaveformProto::kSelectionFrameInSecondsFieldNumber;
const int WaveformProto::kShowGridFieldNumber;
const int WaveformProto::kParallelWaveformsFieldNumber;
const int WaveformProto::kShowNamesInWaveformFieldNumber;
const int WaveformProto::kLayoutFieldNumber;
const int WaveformProto::kShowSelectionButtonsFieldNumber;
#endif  // !_MSC_VER

WaveformProto::WaveformProto()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void WaveformProto::InitAsDefaultInstance() {
  widget_ = const_cast< ::rec::widget::Widget*>(&::rec::widget::Widget::default_instance());
  cursor_thread_ = const_cast< ::rec::util::thread::ThreadDescription*>(&::rec::util::thread::ThreadDescription::default_instance());
}

WaveformProto::WaveformProto(const WaveformProto& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void WaveformProto::SharedCtor() {
  _cached_size_ = 0;
  widget_ = NULL;
  cursor_thickness_ = 1u;
  source_samples_per_thumbnail_sample_ = 512u;
  thumbnail_cache_ = 5u;
  cursor_thread_ = NULL;
  tic_height_ = 8u;
  subtic_height_ = 3u;
  use_captions_ = true;
  tics_at_bottom_ = true;
  selection_frame_in_seconds_ = 5;
  show_grid_ = true;
  parallel_waveforms_ = false;
  show_names_in_waveform_ = true;
  layout_ = 1;
  show_selection_buttons_ = true;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

WaveformProto::~WaveformProto() {
  SharedDtor();
}

void WaveformProto::SharedDtor() {
  if (this != default_instance_) {
    delete widget_;
    delete cursor_thread_;
  }
}

void WaveformProto::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* WaveformProto::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return WaveformProto_descriptor_;
}

const WaveformProto& WaveformProto::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fwidget_2fwaveform_2fWaveform_2eproto();  return *default_instance_;
}

WaveformProto* WaveformProto::default_instance_ = NULL;

WaveformProto* WaveformProto::New() const {
  return new WaveformProto;
}

void WaveformProto::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (_has_bit(0)) {
      if (widget_ != NULL) widget_->::rec::widget::Widget::Clear();
    }
    cursor_thickness_ = 1u;
    source_samples_per_thumbnail_sample_ = 512u;
    thumbnail_cache_ = 5u;
    if (_has_bit(4)) {
      if (cursor_thread_ != NULL) cursor_thread_->::rec::util::thread::ThreadDescription::Clear();
    }
    tic_height_ = 8u;
    subtic_height_ = 3u;
    use_captions_ = true;
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    tics_at_bottom_ = true;
    selection_frame_in_seconds_ = 5;
    show_grid_ = true;
    parallel_waveforms_ = false;
    show_names_in_waveform_ = true;
    layout_ = 1;
    show_selection_buttons_ = true;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool WaveformProto::MergePartialFromCodedStream(
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
        if (input->ExpectTag(16)) goto parse_cursor_thickness;
        break;
      }
      
      // optional uint32 cursor_thickness = 2 [default = 1];
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_cursor_thickness:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &cursor_thickness_)));
          _set_bit(1);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_source_samples_per_thumbnail_sample;
        break;
      }
      
      // optional uint32 source_samples_per_thumbnail_sample = 4 [default = 512];
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_source_samples_per_thumbnail_sample:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &source_samples_per_thumbnail_sample_)));
          _set_bit(2);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_thumbnail_cache;
        break;
      }
      
      // optional uint32 thumbnail_cache = 5 [default = 5];
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_thumbnail_cache:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &thumbnail_cache_)));
          _set_bit(3);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(50)) goto parse_cursor_thread;
        break;
      }
      
      // optional .rec.util.thread.ThreadDescription cursor_thread = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_cursor_thread:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_cursor_thread()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(64)) goto parse_tic_height;
        break;
      }
      
      // optional uint32 tic_height = 8 [default = 8];
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_tic_height:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &tic_height_)));
          _set_bit(5);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(72)) goto parse_subtic_height;
        break;
      }
      
      // optional uint32 subtic_height = 9 [default = 3];
      case 9: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_subtic_height:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &subtic_height_)));
          _set_bit(6);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(80)) goto parse_use_captions;
        break;
      }
      
      // optional bool use_captions = 10 [default = true];
      case 10: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_use_captions:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &use_captions_)));
          _set_bit(7);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(88)) goto parse_tics_at_bottom;
        break;
      }
      
      // optional bool tics_at_bottom = 11 [default = true];
      case 11: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_tics_at_bottom:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &tics_at_bottom_)));
          _set_bit(8);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(97)) goto parse_selection_frame_in_seconds;
        break;
      }
      
      // optional double selection_frame_in_seconds = 12 [default = 5];
      case 12: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_selection_frame_in_seconds:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &selection_frame_in_seconds_)));
          _set_bit(9);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(104)) goto parse_show_grid;
        break;
      }
      
      // optional bool show_grid = 13 [default = true];
      case 13: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_show_grid:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &show_grid_)));
          _set_bit(10);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(112)) goto parse_parallel_waveforms;
        break;
      }
      
      // optional bool parallel_waveforms = 14 [default = false];
      case 14: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_parallel_waveforms:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &parallel_waveforms_)));
          _set_bit(11);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(120)) goto parse_show_names_in_waveform;
        break;
      }
      
      // optional bool show_names_in_waveform = 15 [default = true];
      case 15: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_show_names_in_waveform:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &show_names_in_waveform_)));
          _set_bit(12);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(128)) goto parse_layout;
        break;
      }
      
      // optional .rec.widget.waveform.WaveformProto.Layout layout = 16;
      case 16: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_layout:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::rec::widget::waveform::WaveformProto_Layout_IsValid(value)) {
            set_layout(static_cast< ::rec::widget::waveform::WaveformProto_Layout >(value));
          } else {
            mutable_unknown_fields()->AddVarint(16, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(136)) goto parse_show_selection_buttons;
        break;
      }
      
      // optional bool show_selection_buttons = 17 [default = true];
      case 17: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_show_selection_buttons:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &show_selection_buttons_)));
          _set_bit(14);
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

void WaveformProto::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .rec.widget.Widget widget = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->widget(), output);
  }
  
  // optional uint32 cursor_thickness = 2 [default = 1];
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->cursor_thickness(), output);
  }
  
  // optional uint32 source_samples_per_thumbnail_sample = 4 [default = 512];
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->source_samples_per_thumbnail_sample(), output);
  }
  
  // optional uint32 thumbnail_cache = 5 [default = 5];
  if (_has_bit(3)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(5, this->thumbnail_cache(), output);
  }
  
  // optional .rec.util.thread.ThreadDescription cursor_thread = 6;
  if (_has_bit(4)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      6, this->cursor_thread(), output);
  }
  
  // optional uint32 tic_height = 8 [default = 8];
  if (_has_bit(5)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(8, this->tic_height(), output);
  }
  
  // optional uint32 subtic_height = 9 [default = 3];
  if (_has_bit(6)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(9, this->subtic_height(), output);
  }
  
  // optional bool use_captions = 10 [default = true];
  if (_has_bit(7)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(10, this->use_captions(), output);
  }
  
  // optional bool tics_at_bottom = 11 [default = true];
  if (_has_bit(8)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(11, this->tics_at_bottom(), output);
  }
  
  // optional double selection_frame_in_seconds = 12 [default = 5];
  if (_has_bit(9)) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(12, this->selection_frame_in_seconds(), output);
  }
  
  // optional bool show_grid = 13 [default = true];
  if (_has_bit(10)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(13, this->show_grid(), output);
  }
  
  // optional bool parallel_waveforms = 14 [default = false];
  if (_has_bit(11)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(14, this->parallel_waveforms(), output);
  }
  
  // optional bool show_names_in_waveform = 15 [default = true];
  if (_has_bit(12)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(15, this->show_names_in_waveform(), output);
  }
  
  // optional .rec.widget.waveform.WaveformProto.Layout layout = 16;
  if (_has_bit(13)) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      16, this->layout(), output);
  }
  
  // optional bool show_selection_buttons = 17 [default = true];
  if (_has_bit(14)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(17, this->show_selection_buttons(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* WaveformProto::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .rec.widget.Widget widget = 1;
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->widget(), target);
  }
  
  // optional uint32 cursor_thickness = 2 [default = 1];
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->cursor_thickness(), target);
  }
  
  // optional uint32 source_samples_per_thumbnail_sample = 4 [default = 512];
  if (_has_bit(2)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->source_samples_per_thumbnail_sample(), target);
  }
  
  // optional uint32 thumbnail_cache = 5 [default = 5];
  if (_has_bit(3)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(5, this->thumbnail_cache(), target);
  }
  
  // optional .rec.util.thread.ThreadDescription cursor_thread = 6;
  if (_has_bit(4)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        6, this->cursor_thread(), target);
  }
  
  // optional uint32 tic_height = 8 [default = 8];
  if (_has_bit(5)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(8, this->tic_height(), target);
  }
  
  // optional uint32 subtic_height = 9 [default = 3];
  if (_has_bit(6)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(9, this->subtic_height(), target);
  }
  
  // optional bool use_captions = 10 [default = true];
  if (_has_bit(7)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(10, this->use_captions(), target);
  }
  
  // optional bool tics_at_bottom = 11 [default = true];
  if (_has_bit(8)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(11, this->tics_at_bottom(), target);
  }
  
  // optional double selection_frame_in_seconds = 12 [default = 5];
  if (_has_bit(9)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(12, this->selection_frame_in_seconds(), target);
  }
  
  // optional bool show_grid = 13 [default = true];
  if (_has_bit(10)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(13, this->show_grid(), target);
  }
  
  // optional bool parallel_waveforms = 14 [default = false];
  if (_has_bit(11)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(14, this->parallel_waveforms(), target);
  }
  
  // optional bool show_names_in_waveform = 15 [default = true];
  if (_has_bit(12)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(15, this->show_names_in_waveform(), target);
  }
  
  // optional .rec.widget.waveform.WaveformProto.Layout layout = 16;
  if (_has_bit(13)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      16, this->layout(), target);
  }
  
  // optional bool show_selection_buttons = 17 [default = true];
  if (_has_bit(14)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(17, this->show_selection_buttons(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int WaveformProto::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .rec.widget.Widget widget = 1;
    if (has_widget()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->widget());
    }
    
    // optional uint32 cursor_thickness = 2 [default = 1];
    if (has_cursor_thickness()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->cursor_thickness());
    }
    
    // optional uint32 source_samples_per_thumbnail_sample = 4 [default = 512];
    if (has_source_samples_per_thumbnail_sample()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->source_samples_per_thumbnail_sample());
    }
    
    // optional uint32 thumbnail_cache = 5 [default = 5];
    if (has_thumbnail_cache()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->thumbnail_cache());
    }
    
    // optional .rec.util.thread.ThreadDescription cursor_thread = 6;
    if (has_cursor_thread()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->cursor_thread());
    }
    
    // optional uint32 tic_height = 8 [default = 8];
    if (has_tic_height()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->tic_height());
    }
    
    // optional uint32 subtic_height = 9 [default = 3];
    if (has_subtic_height()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->subtic_height());
    }
    
    // optional bool use_captions = 10 [default = true];
    if (has_use_captions()) {
      total_size += 1 + 1;
    }
    
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // optional bool tics_at_bottom = 11 [default = true];
    if (has_tics_at_bottom()) {
      total_size += 1 + 1;
    }
    
    // optional double selection_frame_in_seconds = 12 [default = 5];
    if (has_selection_frame_in_seconds()) {
      total_size += 1 + 8;
    }
    
    // optional bool show_grid = 13 [default = true];
    if (has_show_grid()) {
      total_size += 1 + 1;
    }
    
    // optional bool parallel_waveforms = 14 [default = false];
    if (has_parallel_waveforms()) {
      total_size += 1 + 1;
    }
    
    // optional bool show_names_in_waveform = 15 [default = true];
    if (has_show_names_in_waveform()) {
      total_size += 1 + 1;
    }
    
    // optional .rec.widget.waveform.WaveformProto.Layout layout = 16;
    if (has_layout()) {
      total_size += 2 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->layout());
    }
    
    // optional bool show_selection_buttons = 17 [default = true];
    if (has_show_selection_buttons()) {
      total_size += 2 + 1;
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

void WaveformProto::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const WaveformProto* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const WaveformProto*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void WaveformProto::MergeFrom(const WaveformProto& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      mutable_widget()->::rec::widget::Widget::MergeFrom(from.widget());
    }
    if (from._has_bit(1)) {
      set_cursor_thickness(from.cursor_thickness());
    }
    if (from._has_bit(2)) {
      set_source_samples_per_thumbnail_sample(from.source_samples_per_thumbnail_sample());
    }
    if (from._has_bit(3)) {
      set_thumbnail_cache(from.thumbnail_cache());
    }
    if (from._has_bit(4)) {
      mutable_cursor_thread()->::rec::util::thread::ThreadDescription::MergeFrom(from.cursor_thread());
    }
    if (from._has_bit(5)) {
      set_tic_height(from.tic_height());
    }
    if (from._has_bit(6)) {
      set_subtic_height(from.subtic_height());
    }
    if (from._has_bit(7)) {
      set_use_captions(from.use_captions());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from._has_bit(8)) {
      set_tics_at_bottom(from.tics_at_bottom());
    }
    if (from._has_bit(9)) {
      set_selection_frame_in_seconds(from.selection_frame_in_seconds());
    }
    if (from._has_bit(10)) {
      set_show_grid(from.show_grid());
    }
    if (from._has_bit(11)) {
      set_parallel_waveforms(from.parallel_waveforms());
    }
    if (from._has_bit(12)) {
      set_show_names_in_waveform(from.show_names_in_waveform());
    }
    if (from._has_bit(13)) {
      set_layout(from.layout());
    }
    if (from._has_bit(14)) {
      set_show_selection_buttons(from.show_selection_buttons());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void WaveformProto::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void WaveformProto::CopyFrom(const WaveformProto& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool WaveformProto::IsInitialized() const {
  
  return true;
}

void WaveformProto::Swap(WaveformProto* other) {
  if (other != this) {
    std::swap(widget_, other->widget_);
    std::swap(cursor_thickness_, other->cursor_thickness_);
    std::swap(source_samples_per_thumbnail_sample_, other->source_samples_per_thumbnail_sample_);
    std::swap(thumbnail_cache_, other->thumbnail_cache_);
    std::swap(cursor_thread_, other->cursor_thread_);
    std::swap(tic_height_, other->tic_height_);
    std::swap(subtic_height_, other->subtic_height_);
    std::swap(use_captions_, other->use_captions_);
    std::swap(tics_at_bottom_, other->tics_at_bottom_);
    std::swap(selection_frame_in_seconds_, other->selection_frame_in_seconds_);
    std::swap(show_grid_, other->show_grid_);
    std::swap(parallel_waveforms_, other->parallel_waveforms_);
    std::swap(show_names_in_waveform_, other->show_names_in_waveform_);
    std::swap(layout_, other->layout_);
    std::swap(show_selection_buttons_, other->show_selection_buttons_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata WaveformProto::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = WaveformProto_descriptor_;
  metadata.reflection = WaveformProto_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace waveform
}  // namespace widget
}  // namespace rec

// @@protoc_insertion_point(global_scope)
