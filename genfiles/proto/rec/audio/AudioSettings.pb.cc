// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/audio/AudioSettings.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/audio/AudioSettings.pb.h"

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
namespace audio {

namespace {

const ::google::protobuf::Descriptor* AudioSettings_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  AudioSettings_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* AudioSettings_FileType_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2faudio_2fAudioSettings_2eproto() {
  protobuf_AddDesc_rec_2faudio_2fAudioSettings_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/audio/AudioSettings.proto");
  GOOGLE_CHECK(file != NULL);
  AudioSettings_descriptor_ = file->message_type(0);
  static const int AudioSettings_offsets_[6] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AudioSettings, master_tune_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AudioSettings, file_type_for_save_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AudioSettings, volume_nudge_db_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AudioSettings, speed_nudge_percent_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AudioSettings, time_nudge_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AudioSettings, autoplay_),
  };
  AudioSettings_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      AudioSettings_descriptor_,
      AudioSettings::default_instance_,
      AudioSettings_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AudioSettings, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AudioSettings, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(AudioSettings));
  AudioSettings_FileType_descriptor_ = AudioSettings_descriptor_->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2faudio_2fAudioSettings_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    AudioSettings_descriptor_, &AudioSettings::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2faudio_2fAudioSettings_2eproto() {
  delete AudioSettings::default_instance_;
  delete AudioSettings_reflection_;
}

void protobuf_AddDesc_rec_2faudio_2fAudioSettings_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\035rec/audio/AudioSettings.proto\022\trec.aud"
    "io\"\222\002\n\rAudioSettings\022\023\n\013master_tune\030\001 \001("
    "\001\022B\n\022file_type_for_save\030\002 \001(\0162!.rec.audi"
    "o.AudioSettings.FileType:\003WAV\022\032\n\017volume_"
    "nudge_db\030\003 \001(\001:\0011\022\037\n\023speed_nudge_percent"
    "\030\004 \001(\001:\00210\022\026\n\ntime_nudge\030\005 \001(\001:\00210\022\026\n\010au"
    "toplay\030\006 \001(\010:\004true\";\n\010FileType\022\010\n\004AIFF\020\000"
    "\022\010\n\004FLAC\020\001\022\007\n\003OGG\020\002\022\007\n\003WAV\020\003\022\t\n\005COUNT\020\004", 319);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/audio/AudioSettings.proto", &protobuf_RegisterTypes);
  AudioSettings::default_instance_ = new AudioSettings();
  AudioSettings::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2faudio_2fAudioSettings_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2faudio_2fAudioSettings_2eproto {
  StaticDescriptorInitializer_rec_2faudio_2fAudioSettings_2eproto() {
    protobuf_AddDesc_rec_2faudio_2fAudioSettings_2eproto();
  }
} static_descriptor_initializer_rec_2faudio_2fAudioSettings_2eproto_;

// ===================================================================

const ::google::protobuf::EnumDescriptor* AudioSettings_FileType_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return AudioSettings_FileType_descriptor_;
}
bool AudioSettings_FileType_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const AudioSettings_FileType AudioSettings::AIFF;
const AudioSettings_FileType AudioSettings::FLAC;
const AudioSettings_FileType AudioSettings::OGG;
const AudioSettings_FileType AudioSettings::WAV;
const AudioSettings_FileType AudioSettings::COUNT;
const AudioSettings_FileType AudioSettings::FileType_MIN;
const AudioSettings_FileType AudioSettings::FileType_MAX;
const int AudioSettings::FileType_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int AudioSettings::kMasterTuneFieldNumber;
const int AudioSettings::kFileTypeForSaveFieldNumber;
const int AudioSettings::kVolumeNudgeDbFieldNumber;
const int AudioSettings::kSpeedNudgePercentFieldNumber;
const int AudioSettings::kTimeNudgeFieldNumber;
const int AudioSettings::kAutoplayFieldNumber;
#endif  // !_MSC_VER

AudioSettings::AudioSettings()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void AudioSettings::InitAsDefaultInstance() {
}

AudioSettings::AudioSettings(const AudioSettings& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void AudioSettings::SharedCtor() {
  _cached_size_ = 0;
  master_tune_ = 0;
  file_type_for_save_ = 3;
  volume_nudge_db_ = 1;
  speed_nudge_percent_ = 10;
  time_nudge_ = 10;
  autoplay_ = true;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

AudioSettings::~AudioSettings() {
  SharedDtor();
}

void AudioSettings::SharedDtor() {
  if (this != default_instance_) {
  }
}

void AudioSettings::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* AudioSettings::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return AudioSettings_descriptor_;
}

const AudioSettings& AudioSettings::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2faudio_2fAudioSettings_2eproto();
  return *default_instance_;
}

AudioSettings* AudioSettings::default_instance_ = NULL;

AudioSettings* AudioSettings::New() const {
  return new AudioSettings;
}

void AudioSettings::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    master_tune_ = 0;
    file_type_for_save_ = 3;
    volume_nudge_db_ = 1;
    speed_nudge_percent_ = 10;
    time_nudge_ = 10;
    autoplay_ = true;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool AudioSettings::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional double master_tune = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &master_tune_)));
          set_has_master_tune();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_file_type_for_save;
        break;
      }

      // optional .rec.audio.AudioSettings.FileType file_type_for_save = 2 [default = WAV];
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_file_type_for_save:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::rec::audio::AudioSettings_FileType_IsValid(value)) {
            set_file_type_for_save(static_cast< ::rec::audio::AudioSettings_FileType >(value));
          } else {
            mutable_unknown_fields()->AddVarint(2, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(25)) goto parse_volume_nudge_db;
        break;
      }

      // optional double volume_nudge_db = 3 [default = 1];
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_volume_nudge_db:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &volume_nudge_db_)));
          set_has_volume_nudge_db();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(33)) goto parse_speed_nudge_percent;
        break;
      }

      // optional double speed_nudge_percent = 4 [default = 10];
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_speed_nudge_percent:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &speed_nudge_percent_)));
          set_has_speed_nudge_percent();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(41)) goto parse_time_nudge;
        break;
      }

      // optional double time_nudge = 5 [default = 10];
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_time_nudge:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &time_nudge_)));
          set_has_time_nudge();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(48)) goto parse_autoplay;
        break;
      }

      // optional bool autoplay = 6 [default = true];
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_autoplay:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &autoplay_)));
          set_has_autoplay();
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

void AudioSettings::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional double master_tune = 1;
  if (has_master_tune()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(1, this->master_tune(), output);
  }

  // optional .rec.audio.AudioSettings.FileType file_type_for_save = 2 [default = WAV];
  if (has_file_type_for_save()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      2, this->file_type_for_save(), output);
  }

  // optional double volume_nudge_db = 3 [default = 1];
  if (has_volume_nudge_db()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(3, this->volume_nudge_db(), output);
  }

  // optional double speed_nudge_percent = 4 [default = 10];
  if (has_speed_nudge_percent()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(4, this->speed_nudge_percent(), output);
  }

  // optional double time_nudge = 5 [default = 10];
  if (has_time_nudge()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(5, this->time_nudge(), output);
  }

  // optional bool autoplay = 6 [default = true];
  if (has_autoplay()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(6, this->autoplay(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* AudioSettings::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional double master_tune = 1;
  if (has_master_tune()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(1, this->master_tune(), target);
  }

  // optional .rec.audio.AudioSettings.FileType file_type_for_save = 2 [default = WAV];
  if (has_file_type_for_save()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      2, this->file_type_for_save(), target);
  }

  // optional double volume_nudge_db = 3 [default = 1];
  if (has_volume_nudge_db()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(3, this->volume_nudge_db(), target);
  }

  // optional double speed_nudge_percent = 4 [default = 10];
  if (has_speed_nudge_percent()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(4, this->speed_nudge_percent(), target);
  }

  // optional double time_nudge = 5 [default = 10];
  if (has_time_nudge()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(5, this->time_nudge(), target);
  }

  // optional bool autoplay = 6 [default = true];
  if (has_autoplay()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(6, this->autoplay(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int AudioSettings::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional double master_tune = 1;
    if (has_master_tune()) {
      total_size += 1 + 8;
    }

    // optional .rec.audio.AudioSettings.FileType file_type_for_save = 2 [default = WAV];
    if (has_file_type_for_save()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->file_type_for_save());
    }

    // optional double volume_nudge_db = 3 [default = 1];
    if (has_volume_nudge_db()) {
      total_size += 1 + 8;
    }

    // optional double speed_nudge_percent = 4 [default = 10];
    if (has_speed_nudge_percent()) {
      total_size += 1 + 8;
    }

    // optional double time_nudge = 5 [default = 10];
    if (has_time_nudge()) {
      total_size += 1 + 8;
    }

    // optional bool autoplay = 6 [default = true];
    if (has_autoplay()) {
      total_size += 1 + 1;
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

void AudioSettings::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const AudioSettings* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const AudioSettings*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void AudioSettings::MergeFrom(const AudioSettings& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_master_tune()) {
      set_master_tune(from.master_tune());
    }
    if (from.has_file_type_for_save()) {
      set_file_type_for_save(from.file_type_for_save());
    }
    if (from.has_volume_nudge_db()) {
      set_volume_nudge_db(from.volume_nudge_db());
    }
    if (from.has_speed_nudge_percent()) {
      set_speed_nudge_percent(from.speed_nudge_percent());
    }
    if (from.has_time_nudge()) {
      set_time_nudge(from.time_nudge());
    }
    if (from.has_autoplay()) {
      set_autoplay(from.autoplay());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void AudioSettings::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AudioSettings::CopyFrom(const AudioSettings& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AudioSettings::IsInitialized() const {

  return true;
}

void AudioSettings::Swap(AudioSettings* other) {
  if (other != this) {
    std::swap(master_tune_, other->master_tune_);
    std::swap(file_type_for_save_, other->file_type_for_save_);
    std::swap(volume_nudge_db_, other->volume_nudge_db_);
    std::swap(speed_nudge_percent_, other->speed_nudge_percent_);
    std::swap(time_nudge_, other->time_nudge_);
    std::swap(autoplay_, other->autoplay_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata AudioSettings::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = AudioSettings_descriptor_;
  metadata.reflection = AudioSettings_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace audio
}  // namespace rec

// @@protoc_insertion_point(global_scope)
