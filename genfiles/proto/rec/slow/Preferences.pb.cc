// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/slow/Preferences.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace rec {
namespace slow {
namespace proto {

namespace {

const ::google::protobuf::Descriptor* Preferences_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Preferences_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2fslow_2fPreferences_2eproto() {
  protobuf_AddDesc_rec_2fslow_2fPreferences_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/slow/Preferences.proto");
  GOOGLE_CHECK(file != NULL);
  Preferences_descriptor_ = file->message_type(0);
  static const int Preferences_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Preferences, waveform_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Preferences, recent_files_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Preferences, audio_setup_),
  };
  Preferences_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Preferences_descriptor_,
      Preferences::default_instance_,
      Preferences_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Preferences, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Preferences, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Preferences));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2fslow_2fPreferences_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Preferences_descriptor_, &Preferences::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2fslow_2fPreferences_2eproto() {
  delete Preferences::default_instance_;
  delete Preferences_reflection_;
}

void protobuf_AddDesc_rec_2fslow_2fPreferences_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::rec::audio::protobuf_AddDesc_rec_2faudio_2fAudioDeviceSetup_2eproto();
  ::rec::gui::protobuf_AddDesc_rec_2fgui_2fRecentFiles_2eproto();
  ::rec::widget::waveform::protobuf_AddDesc_rec_2fwidget_2fwaveform_2fWaveform_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\032rec/slow/Preferences.proto\022\016rec.slow.p"
    "roto\032 rec/audio/AudioDeviceSetup.proto\032\031"
    "rec/gui/RecentFiles.proto\032\"rec/widget/wa"
    "veform/Waveform.proto\"\246\001\n\013Preferences\0224\n"
    "\010waveform\030\002 \001(\0132\".rec.widget.waveform.Wa"
    "veformProto\022*\n\014recent_files\030\003 \001(\0132\024.rec."
    "gui.RecentFiles\0225\n\013audio_setup\030\004 \001(\0132 .r"
    "ec.audio.AudioDeviceSetupProto", 310);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/slow/Preferences.proto", &protobuf_RegisterTypes);
  Preferences::default_instance_ = new Preferences();
  Preferences::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2fslow_2fPreferences_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2fslow_2fPreferences_2eproto {
  StaticDescriptorInitializer_rec_2fslow_2fPreferences_2eproto() {
    protobuf_AddDesc_rec_2fslow_2fPreferences_2eproto();
  }
} static_descriptor_initializer_rec_2fslow_2fPreferences_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int Preferences::kWaveformFieldNumber;
const int Preferences::kRecentFilesFieldNumber;
const int Preferences::kAudioSetupFieldNumber;
#endif  // !_MSC_VER

Preferences::Preferences()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Preferences::InitAsDefaultInstance() {
  waveform_ = const_cast< ::rec::widget::waveform::WaveformProto*>(&::rec::widget::waveform::WaveformProto::default_instance());
  recent_files_ = const_cast< ::rec::gui::RecentFiles*>(&::rec::gui::RecentFiles::default_instance());
  audio_setup_ = const_cast< ::rec::audio::AudioDeviceSetupProto*>(&::rec::audio::AudioDeviceSetupProto::default_instance());
}

Preferences::Preferences(const Preferences& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Preferences::SharedCtor() {
  _cached_size_ = 0;
  waveform_ = NULL;
  recent_files_ = NULL;
  audio_setup_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Preferences::~Preferences() {
  SharedDtor();
}

void Preferences::SharedDtor() {
  if (this != default_instance_) {
    delete waveform_;
    delete recent_files_;
    delete audio_setup_;
  }
}

void Preferences::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Preferences::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Preferences_descriptor_;
}

const Preferences& Preferences::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fslow_2fPreferences_2eproto();  return *default_instance_;
}

Preferences* Preferences::default_instance_ = NULL;

Preferences* Preferences::New() const {
  return new Preferences;
}

void Preferences::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (_has_bit(0)) {
      if (waveform_ != NULL) waveform_->::rec::widget::waveform::WaveformProto::Clear();
    }
    if (_has_bit(1)) {
      if (recent_files_ != NULL) recent_files_->::rec::gui::RecentFiles::Clear();
    }
    if (_has_bit(2)) {
      if (audio_setup_ != NULL) audio_setup_->::rec::audio::AudioDeviceSetupProto::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Preferences::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .rec.widget.waveform.WaveformProto waveform = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_waveform()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_recent_files;
        break;
      }
      
      // optional .rec.gui.RecentFiles recent_files = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_recent_files:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_recent_files()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_audio_setup;
        break;
      }
      
      // optional .rec.audio.AudioDeviceSetupProto audio_setup = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_audio_setup:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_audio_setup()));
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

void Preferences::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .rec.widget.waveform.WaveformProto waveform = 2;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->waveform(), output);
  }
  
  // optional .rec.gui.RecentFiles recent_files = 3;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->recent_files(), output);
  }
  
  // optional .rec.audio.AudioDeviceSetupProto audio_setup = 4;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4, this->audio_setup(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Preferences::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .rec.widget.waveform.WaveformProto waveform = 2;
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->waveform(), target);
  }
  
  // optional .rec.gui.RecentFiles recent_files = 3;
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->recent_files(), target);
  }
  
  // optional .rec.audio.AudioDeviceSetupProto audio_setup = 4;
  if (_has_bit(2)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        4, this->audio_setup(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Preferences::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .rec.widget.waveform.WaveformProto waveform = 2;
    if (has_waveform()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->waveform());
    }
    
    // optional .rec.gui.RecentFiles recent_files = 3;
    if (has_recent_files()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->recent_files());
    }
    
    // optional .rec.audio.AudioDeviceSetupProto audio_setup = 4;
    if (has_audio_setup()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->audio_setup());
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

void Preferences::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Preferences* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Preferences*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Preferences::MergeFrom(const Preferences& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      mutable_waveform()->::rec::widget::waveform::WaveformProto::MergeFrom(from.waveform());
    }
    if (from._has_bit(1)) {
      mutable_recent_files()->::rec::gui::RecentFiles::MergeFrom(from.recent_files());
    }
    if (from._has_bit(2)) {
      mutable_audio_setup()->::rec::audio::AudioDeviceSetupProto::MergeFrom(from.audio_setup());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Preferences::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Preferences::CopyFrom(const Preferences& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Preferences::IsInitialized() const {
  
  return true;
}

void Preferences::Swap(Preferences* other) {
  if (other != this) {
    std::swap(waveform_, other->waveform_);
    std::swap(recent_files_, other->recent_files_);
    std::swap(audio_setup_, other->audio_setup_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Preferences::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Preferences_descriptor_;
  metadata.reflection = Preferences_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace slow
}  // namespace rec

// @@protoc_insertion_point(global_scope)
