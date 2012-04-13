// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/util/SystemStats.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace rec {
namespace util {

namespace {

const ::google::protobuf::Descriptor* SystemStats_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  SystemStats_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2futil_2fSystemStats_2eproto() {
  protobuf_AddDesc_rec_2futil_2fSystemStats_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/util/SystemStats.proto");
  GOOGLE_CHECK(file != NULL);
  SystemStats_descriptor_ = file->message_type(0);
  static const int SystemStats_offsets_[16] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SystemStats, juce_version_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SystemStats, operating_system_type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SystemStats, operating_system_name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SystemStats, is_operating_system_64_bit_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SystemStats, osx_minor_version_number_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SystemStats, logon_name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SystemStats, full_user_name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SystemStats, computer_name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SystemStats, num_cpus_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SystemStats, cpu_speed_in_megahertz_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SystemStats, cpu_vendor_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SystemStats, has_mmx_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SystemStats, has_sse_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SystemStats, has_sse2_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SystemStats, has_3dnow_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SystemStats, memory_size_in_megabytes_),
  };
  SystemStats_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      SystemStats_descriptor_,
      SystemStats::default_instance_,
      SystemStats_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SystemStats, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SystemStats, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(SystemStats));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2futil_2fSystemStats_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    SystemStats_descriptor_, &SystemStats::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2futil_2fSystemStats_2eproto() {
  delete SystemStats::default_instance_;
  delete SystemStats_reflection_;
}

void protobuf_AddDesc_rec_2futil_2fSystemStats_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\032rec/util/SystemStats.proto\022\010rec.util\"\231"
    "\003\n\013SystemStats\022\024\n\014juce_version\030\001 \001(\t\022\035\n\025"
    "operating_system_type\030\002 \001(\r\022\035\n\025operating"
    "_system_name\030\003 \001(\t\022\"\n\032is_operating_syste"
    "m_64_bit\030\004 \001(\010\022 \n\030osx_minor_version_numb"
    "er\030\005 \001(\r\022\022\n\nlogon_name\030\006 \001(\t\022\026\n\016full_use"
    "r_name\030\007 \001(\t\022\025\n\rcomputer_name\030\010 \001(\t\022\020\n\010n"
    "um_cpus\030\t \001(\r\022\036\n\026cpu_speed_in_megahertz\030"
    "\n \001(\r\022\022\n\ncpu_vendor\030\013 \001(\t\022\017\n\007has_mmx\030\014 \001"
    "(\010\022\017\n\007has_sse\030\r \001(\010\022\020\n\010has_sse2\030\016 \001(\010\022\021\n"
    "\thas_3dnow\030\017 \001(\010\022 \n\030memory_size_in_megab"
    "ytes\030\020 \001(\r", 450);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/util/SystemStats.proto", &protobuf_RegisterTypes);
  SystemStats::default_instance_ = new SystemStats();
  SystemStats::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2futil_2fSystemStats_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2futil_2fSystemStats_2eproto {
  StaticDescriptorInitializer_rec_2futil_2fSystemStats_2eproto() {
    protobuf_AddDesc_rec_2futil_2fSystemStats_2eproto();
  }
} static_descriptor_initializer_rec_2futil_2fSystemStats_2eproto_;


// ===================================================================

const ::std::string SystemStats::_default_juce_version_;
const ::std::string SystemStats::_default_operating_system_name_;
const ::std::string SystemStats::_default_logon_name_;
const ::std::string SystemStats::_default_full_user_name_;
const ::std::string SystemStats::_default_computer_name_;
const ::std::string SystemStats::_default_cpu_vendor_;
#ifndef _MSC_VER
const int SystemStats::kJuceVersionFieldNumber;
const int SystemStats::kOperatingSystemTypeFieldNumber;
const int SystemStats::kOperatingSystemNameFieldNumber;
const int SystemStats::kIsOperatingSystem64BitFieldNumber;
const int SystemStats::kOsxMinorVersionNumberFieldNumber;
const int SystemStats::kLogonNameFieldNumber;
const int SystemStats::kFullUserNameFieldNumber;
const int SystemStats::kComputerNameFieldNumber;
const int SystemStats::kNumCpusFieldNumber;
const int SystemStats::kCpuSpeedInMegahertzFieldNumber;
const int SystemStats::kCpuVendorFieldNumber;
const int SystemStats::kHasMmxFieldNumber;
const int SystemStats::kHasSseFieldNumber;
const int SystemStats::kHasSse2FieldNumber;
const int SystemStats::kHas3DnowFieldNumber;
const int SystemStats::kMemorySizeInMegabytesFieldNumber;
#endif  // !_MSC_VER

SystemStats::SystemStats()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void SystemStats::InitAsDefaultInstance() {
}

SystemStats::SystemStats(const SystemStats& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void SystemStats::SharedCtor() {
  _cached_size_ = 0;
  juce_version_ = const_cast< ::std::string*>(&_default_juce_version_);
  operating_system_type_ = 0u;
  operating_system_name_ = const_cast< ::std::string*>(&_default_operating_system_name_);
  is_operating_system_64_bit_ = false;
  osx_minor_version_number_ = 0u;
  logon_name_ = const_cast< ::std::string*>(&_default_logon_name_);
  full_user_name_ = const_cast< ::std::string*>(&_default_full_user_name_);
  computer_name_ = const_cast< ::std::string*>(&_default_computer_name_);
  num_cpus_ = 0u;
  cpu_speed_in_megahertz_ = 0u;
  cpu_vendor_ = const_cast< ::std::string*>(&_default_cpu_vendor_);
  has_mmx_ = false;
  has_sse_ = false;
  has_sse2_ = false;
  has_3dnow_ = false;
  memory_size_in_megabytes_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

SystemStats::~SystemStats() {
  SharedDtor();
}

void SystemStats::SharedDtor() {
  if (juce_version_ != &_default_juce_version_) {
    delete juce_version_;
  }
  if (operating_system_name_ != &_default_operating_system_name_) {
    delete operating_system_name_;
  }
  if (logon_name_ != &_default_logon_name_) {
    delete logon_name_;
  }
  if (full_user_name_ != &_default_full_user_name_) {
    delete full_user_name_;
  }
  if (computer_name_ != &_default_computer_name_) {
    delete computer_name_;
  }
  if (cpu_vendor_ != &_default_cpu_vendor_) {
    delete cpu_vendor_;
  }
  if (this != default_instance_) {
  }
}

void SystemStats::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* SystemStats::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return SystemStats_descriptor_;
}

const SystemStats& SystemStats::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2futil_2fSystemStats_2eproto();  return *default_instance_;
}

SystemStats* SystemStats::default_instance_ = NULL;

SystemStats* SystemStats::New() const {
  return new SystemStats;
}

void SystemStats::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (_has_bit(0)) {
      if (juce_version_ != &_default_juce_version_) {
        juce_version_->clear();
      }
    }
    operating_system_type_ = 0u;
    if (_has_bit(2)) {
      if (operating_system_name_ != &_default_operating_system_name_) {
        operating_system_name_->clear();
      }
    }
    is_operating_system_64_bit_ = false;
    osx_minor_version_number_ = 0u;
    if (_has_bit(5)) {
      if (logon_name_ != &_default_logon_name_) {
        logon_name_->clear();
      }
    }
    if (_has_bit(6)) {
      if (full_user_name_ != &_default_full_user_name_) {
        full_user_name_->clear();
      }
    }
    if (_has_bit(7)) {
      if (computer_name_ != &_default_computer_name_) {
        computer_name_->clear();
      }
    }
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    num_cpus_ = 0u;
    cpu_speed_in_megahertz_ = 0u;
    if (_has_bit(10)) {
      if (cpu_vendor_ != &_default_cpu_vendor_) {
        cpu_vendor_->clear();
      }
    }
    has_mmx_ = false;
    has_sse_ = false;
    has_sse2_ = false;
    has_3dnow_ = false;
    memory_size_in_megabytes_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool SystemStats::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string juce_version = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_juce_version()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->juce_version().data(), this->juce_version().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_operating_system_type;
        break;
      }
      
      // optional uint32 operating_system_type = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_operating_system_type:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &operating_system_type_)));
          _set_bit(1);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_operating_system_name;
        break;
      }
      
      // optional string operating_system_name = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_operating_system_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_operating_system_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->operating_system_name().data(), this->operating_system_name().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_is_operating_system_64_bit;
        break;
      }
      
      // optional bool is_operating_system_64_bit = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_is_operating_system_64_bit:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &is_operating_system_64_bit_)));
          _set_bit(3);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_osx_minor_version_number;
        break;
      }
      
      // optional uint32 osx_minor_version_number = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_osx_minor_version_number:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &osx_minor_version_number_)));
          _set_bit(4);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(50)) goto parse_logon_name;
        break;
      }
      
      // optional string logon_name = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_logon_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_logon_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->logon_name().data(), this->logon_name().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(58)) goto parse_full_user_name;
        break;
      }
      
      // optional string full_user_name = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_full_user_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_full_user_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->full_user_name().data(), this->full_user_name().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(66)) goto parse_computer_name;
        break;
      }
      
      // optional string computer_name = 8;
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_computer_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_computer_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->computer_name().data(), this->computer_name().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(72)) goto parse_num_cpus;
        break;
      }
      
      // optional uint32 num_cpus = 9;
      case 9: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_num_cpus:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &num_cpus_)));
          _set_bit(8);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(80)) goto parse_cpu_speed_in_megahertz;
        break;
      }
      
      // optional uint32 cpu_speed_in_megahertz = 10;
      case 10: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_cpu_speed_in_megahertz:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &cpu_speed_in_megahertz_)));
          _set_bit(9);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(90)) goto parse_cpu_vendor;
        break;
      }
      
      // optional string cpu_vendor = 11;
      case 11: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_cpu_vendor:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_cpu_vendor()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->cpu_vendor().data(), this->cpu_vendor().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(96)) goto parse_has_mmx;
        break;
      }
      
      // optional bool has_mmx = 12;
      case 12: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_has_mmx:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &has_mmx_)));
          _set_bit(11);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(104)) goto parse_has_sse;
        break;
      }
      
      // optional bool has_sse = 13;
      case 13: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_has_sse:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &has_sse_)));
          _set_bit(12);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(112)) goto parse_has_sse2;
        break;
      }
      
      // optional bool has_sse2 = 14;
      case 14: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_has_sse2:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &has_sse2_)));
          _set_bit(13);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(120)) goto parse_has_3dnow;
        break;
      }
      
      // optional bool has_3dnow = 15;
      case 15: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_has_3dnow:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &has_3dnow_)));
          _set_bit(14);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(128)) goto parse_memory_size_in_megabytes;
        break;
      }
      
      // optional uint32 memory_size_in_megabytes = 16;
      case 16: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_memory_size_in_megabytes:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &memory_size_in_megabytes_)));
          _set_bit(15);
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

void SystemStats::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional string juce_version = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->juce_version().data(), this->juce_version().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->juce_version(), output);
  }
  
  // optional uint32 operating_system_type = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->operating_system_type(), output);
  }
  
  // optional string operating_system_name = 3;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->operating_system_name().data(), this->operating_system_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->operating_system_name(), output);
  }
  
  // optional bool is_operating_system_64_bit = 4;
  if (_has_bit(3)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(4, this->is_operating_system_64_bit(), output);
  }
  
  // optional uint32 osx_minor_version_number = 5;
  if (_has_bit(4)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(5, this->osx_minor_version_number(), output);
  }
  
  // optional string logon_name = 6;
  if (_has_bit(5)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->logon_name().data(), this->logon_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      6, this->logon_name(), output);
  }
  
  // optional string full_user_name = 7;
  if (_has_bit(6)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->full_user_name().data(), this->full_user_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      7, this->full_user_name(), output);
  }
  
  // optional string computer_name = 8;
  if (_has_bit(7)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->computer_name().data(), this->computer_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      8, this->computer_name(), output);
  }
  
  // optional uint32 num_cpus = 9;
  if (_has_bit(8)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(9, this->num_cpus(), output);
  }
  
  // optional uint32 cpu_speed_in_megahertz = 10;
  if (_has_bit(9)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(10, this->cpu_speed_in_megahertz(), output);
  }
  
  // optional string cpu_vendor = 11;
  if (_has_bit(10)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->cpu_vendor().data(), this->cpu_vendor().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      11, this->cpu_vendor(), output);
  }
  
  // optional bool has_mmx = 12;
  if (_has_bit(11)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(12, this->has_mmx(), output);
  }
  
  // optional bool has_sse = 13;
  if (_has_bit(12)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(13, this->has_sse(), output);
  }
  
  // optional bool has_sse2 = 14;
  if (_has_bit(13)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(14, this->has_sse2(), output);
  }
  
  // optional bool has_3dnow = 15;
  if (_has_bit(14)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(15, this->has_3dnow(), output);
  }
  
  // optional uint32 memory_size_in_megabytes = 16;
  if (_has_bit(15)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(16, this->memory_size_in_megabytes(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* SystemStats::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional string juce_version = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->juce_version().data(), this->juce_version().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->juce_version(), target);
  }
  
  // optional uint32 operating_system_type = 2;
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->operating_system_type(), target);
  }
  
  // optional string operating_system_name = 3;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->operating_system_name().data(), this->operating_system_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->operating_system_name(), target);
  }
  
  // optional bool is_operating_system_64_bit = 4;
  if (_has_bit(3)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(4, this->is_operating_system_64_bit(), target);
  }
  
  // optional uint32 osx_minor_version_number = 5;
  if (_has_bit(4)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(5, this->osx_minor_version_number(), target);
  }
  
  // optional string logon_name = 6;
  if (_has_bit(5)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->logon_name().data(), this->logon_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        6, this->logon_name(), target);
  }
  
  // optional string full_user_name = 7;
  if (_has_bit(6)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->full_user_name().data(), this->full_user_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        7, this->full_user_name(), target);
  }
  
  // optional string computer_name = 8;
  if (_has_bit(7)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->computer_name().data(), this->computer_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        8, this->computer_name(), target);
  }
  
  // optional uint32 num_cpus = 9;
  if (_has_bit(8)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(9, this->num_cpus(), target);
  }
  
  // optional uint32 cpu_speed_in_megahertz = 10;
  if (_has_bit(9)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(10, this->cpu_speed_in_megahertz(), target);
  }
  
  // optional string cpu_vendor = 11;
  if (_has_bit(10)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->cpu_vendor().data(), this->cpu_vendor().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        11, this->cpu_vendor(), target);
  }
  
  // optional bool has_mmx = 12;
  if (_has_bit(11)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(12, this->has_mmx(), target);
  }
  
  // optional bool has_sse = 13;
  if (_has_bit(12)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(13, this->has_sse(), target);
  }
  
  // optional bool has_sse2 = 14;
  if (_has_bit(13)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(14, this->has_sse2(), target);
  }
  
  // optional bool has_3dnow = 15;
  if (_has_bit(14)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(15, this->has_3dnow(), target);
  }
  
  // optional uint32 memory_size_in_megabytes = 16;
  if (_has_bit(15)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(16, this->memory_size_in_megabytes(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int SystemStats::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string juce_version = 1;
    if (has_juce_version()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->juce_version());
    }
    
    // optional uint32 operating_system_type = 2;
    if (has_operating_system_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->operating_system_type());
    }
    
    // optional string operating_system_name = 3;
    if (has_operating_system_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->operating_system_name());
    }
    
    // optional bool is_operating_system_64_bit = 4;
    if (has_is_operating_system_64_bit()) {
      total_size += 1 + 1;
    }
    
    // optional uint32 osx_minor_version_number = 5;
    if (has_osx_minor_version_number()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->osx_minor_version_number());
    }
    
    // optional string logon_name = 6;
    if (has_logon_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->logon_name());
    }
    
    // optional string full_user_name = 7;
    if (has_full_user_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->full_user_name());
    }
    
    // optional string computer_name = 8;
    if (has_computer_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->computer_name());
    }
    
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // optional uint32 num_cpus = 9;
    if (has_num_cpus()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->num_cpus());
    }
    
    // optional uint32 cpu_speed_in_megahertz = 10;
    if (has_cpu_speed_in_megahertz()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->cpu_speed_in_megahertz());
    }
    
    // optional string cpu_vendor = 11;
    if (has_cpu_vendor()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->cpu_vendor());
    }
    
    // optional bool has_mmx = 12;
    if (has_has_mmx()) {
      total_size += 1 + 1;
    }
    
    // optional bool has_sse = 13;
    if (has_has_sse()) {
      total_size += 1 + 1;
    }
    
    // optional bool has_sse2 = 14;
    if (has_has_sse2()) {
      total_size += 1 + 1;
    }
    
    // optional bool has_3dnow = 15;
    if (has_has_3dnow()) {
      total_size += 1 + 1;
    }
    
    // optional uint32 memory_size_in_megabytes = 16;
    if (has_memory_size_in_megabytes()) {
      total_size += 2 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->memory_size_in_megabytes());
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

void SystemStats::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const SystemStats* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const SystemStats*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void SystemStats::MergeFrom(const SystemStats& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_juce_version(from.juce_version());
    }
    if (from._has_bit(1)) {
      set_operating_system_type(from.operating_system_type());
    }
    if (from._has_bit(2)) {
      set_operating_system_name(from.operating_system_name());
    }
    if (from._has_bit(3)) {
      set_is_operating_system_64_bit(from.is_operating_system_64_bit());
    }
    if (from._has_bit(4)) {
      set_osx_minor_version_number(from.osx_minor_version_number());
    }
    if (from._has_bit(5)) {
      set_logon_name(from.logon_name());
    }
    if (from._has_bit(6)) {
      set_full_user_name(from.full_user_name());
    }
    if (from._has_bit(7)) {
      set_computer_name(from.computer_name());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from._has_bit(8)) {
      set_num_cpus(from.num_cpus());
    }
    if (from._has_bit(9)) {
      set_cpu_speed_in_megahertz(from.cpu_speed_in_megahertz());
    }
    if (from._has_bit(10)) {
      set_cpu_vendor(from.cpu_vendor());
    }
    if (from._has_bit(11)) {
      set_has_mmx(from.has_mmx());
    }
    if (from._has_bit(12)) {
      set_has_sse(from.has_sse());
    }
    if (from._has_bit(13)) {
      set_has_sse2(from.has_sse2());
    }
    if (from._has_bit(14)) {
      set_has_3dnow(from.has_3dnow());
    }
    if (from._has_bit(15)) {
      set_memory_size_in_megabytes(from.memory_size_in_megabytes());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void SystemStats::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SystemStats::CopyFrom(const SystemStats& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SystemStats::IsInitialized() const {
  
  return true;
}

void SystemStats::Swap(SystemStats* other) {
  if (other != this) {
    std::swap(juce_version_, other->juce_version_);
    std::swap(operating_system_type_, other->operating_system_type_);
    std::swap(operating_system_name_, other->operating_system_name_);
    std::swap(is_operating_system_64_bit_, other->is_operating_system_64_bit_);
    std::swap(osx_minor_version_number_, other->osx_minor_version_number_);
    std::swap(logon_name_, other->logon_name_);
    std::swap(full_user_name_, other->full_user_name_);
    std::swap(computer_name_, other->computer_name_);
    std::swap(num_cpus_, other->num_cpus_);
    std::swap(cpu_speed_in_megahertz_, other->cpu_speed_in_megahertz_);
    std::swap(cpu_vendor_, other->cpu_vendor_);
    std::swap(has_mmx_, other->has_mmx_);
    std::swap(has_sse_, other->has_sse_);
    std::swap(has_sse2_, other->has_sse2_);
    std::swap(has_3dnow_, other->has_3dnow_);
    std::swap(memory_size_in_megabytes_, other->memory_size_in_megabytes_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata SystemStats::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = SystemStats_descriptor_;
  metadata.reflection = SystemStats_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace util
}  // namespace rec

// @@protoc_insertion_point(global_scope)