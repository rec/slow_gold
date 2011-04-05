// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/audio/source/Runny.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace rec {
namespace audio {
namespace source {

namespace {

const ::google::protobuf::Descriptor* RunnyProto_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  RunnyProto_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2faudio_2fsource_2fRunny_2eproto() {
  protobuf_AddDesc_rec_2faudio_2fsource_2fRunny_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/audio/source/Runny.proto");
  GOOGLE_CHECK(file != NULL);
  RunnyProto_descriptor_ = file->message_type(0);
  static const int RunnyProto_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RunnyProto, buffer_size_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RunnyProto, chunk_size_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RunnyProto, thread_),
  };
  RunnyProto_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      RunnyProto_descriptor_,
      RunnyProto::default_instance_,
      RunnyProto_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RunnyProto, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RunnyProto, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(RunnyProto));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2faudio_2fsource_2fRunny_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    RunnyProto_descriptor_, &RunnyProto::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2faudio_2fsource_2fRunny_2eproto() {
  delete RunnyProto::default_instance_;
  delete RunnyProto_reflection_;
}

void protobuf_AddDesc_rec_2faudio_2fsource_2fRunny_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::rec::util::thread::protobuf_AddDesc_rec_2futil_2fthread_2fThread_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\034rec/audio/source/Runny.proto\022\020rec.audi"
    "o.source\032\034rec/util/thread/Thread.proto\"w"
    "\n\nRunnyProto\022\033\n\013buffer_size\030\001 \001(\r:\00651200"
    "0\022\030\n\nchunk_size\030\002 \001(\r:\0041024\0222\n\006thread\030\003 "
    "\001(\0132\".rec.util.thread.ThreadDescription", 199);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/audio/source/Runny.proto", &protobuf_RegisterTypes);
  RunnyProto::default_instance_ = new RunnyProto();
  RunnyProto::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2faudio_2fsource_2fRunny_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2faudio_2fsource_2fRunny_2eproto {
  StaticDescriptorInitializer_rec_2faudio_2fsource_2fRunny_2eproto() {
    protobuf_AddDesc_rec_2faudio_2fsource_2fRunny_2eproto();
  }
} static_descriptor_initializer_rec_2faudio_2fsource_2fRunny_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int RunnyProto::kBufferSizeFieldNumber;
const int RunnyProto::kChunkSizeFieldNumber;
const int RunnyProto::kThreadFieldNumber;
#endif  // !_MSC_VER

RunnyProto::RunnyProto()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void RunnyProto::InitAsDefaultInstance() {
  thread_ = const_cast< ::rec::util::thread::ThreadDescription*>(&::rec::util::thread::ThreadDescription::default_instance());
}

RunnyProto::RunnyProto(const RunnyProto& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void RunnyProto::SharedCtor() {
  _cached_size_ = 0;
  buffer_size_ = 512000u;
  chunk_size_ = 1024u;
  thread_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

RunnyProto::~RunnyProto() {
  SharedDtor();
}

void RunnyProto::SharedDtor() {
  if (this != default_instance_) {
    delete thread_;
  }
}

void RunnyProto::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* RunnyProto::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return RunnyProto_descriptor_;
}

const RunnyProto& RunnyProto::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2faudio_2fsource_2fRunny_2eproto();  return *default_instance_;
}

RunnyProto* RunnyProto::default_instance_ = NULL;

RunnyProto* RunnyProto::New() const {
  return new RunnyProto;
}

void RunnyProto::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    buffer_size_ = 512000u;
    chunk_size_ = 1024u;
    if (_has_bit(2)) {
      if (thread_ != NULL) thread_->::rec::util::thread::ThreadDescription::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool RunnyProto::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 buffer_size = 1 [default = 512000];
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &buffer_size_)));
          _set_bit(0);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_chunk_size;
        break;
      }
      
      // optional uint32 chunk_size = 2 [default = 1024];
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_chunk_size:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &chunk_size_)));
          _set_bit(1);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_thread;
        break;
      }
      
      // optional .rec.util.thread.ThreadDescription thread = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_thread:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_thread()));
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

void RunnyProto::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional uint32 buffer_size = 1 [default = 512000];
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->buffer_size(), output);
  }
  
  // optional uint32 chunk_size = 2 [default = 1024];
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->chunk_size(), output);
  }
  
  // optional .rec.util.thread.ThreadDescription thread = 3;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->thread(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* RunnyProto::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional uint32 buffer_size = 1 [default = 512000];
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->buffer_size(), target);
  }
  
  // optional uint32 chunk_size = 2 [default = 1024];
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->chunk_size(), target);
  }
  
  // optional .rec.util.thread.ThreadDescription thread = 3;
  if (_has_bit(2)) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->thread(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int RunnyProto::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint32 buffer_size = 1 [default = 512000];
    if (has_buffer_size()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->buffer_size());
    }
    
    // optional uint32 chunk_size = 2 [default = 1024];
    if (has_chunk_size()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->chunk_size());
    }
    
    // optional .rec.util.thread.ThreadDescription thread = 3;
    if (has_thread()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->thread());
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

void RunnyProto::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const RunnyProto* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const RunnyProto*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void RunnyProto::MergeFrom(const RunnyProto& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_buffer_size(from.buffer_size());
    }
    if (from._has_bit(1)) {
      set_chunk_size(from.chunk_size());
    }
    if (from._has_bit(2)) {
      mutable_thread()->::rec::util::thread::ThreadDescription::MergeFrom(from.thread());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void RunnyProto::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void RunnyProto::CopyFrom(const RunnyProto& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool RunnyProto::IsInitialized() const {
  
  return true;
}

void RunnyProto::Swap(RunnyProto* other) {
  if (other != this) {
    std::swap(buffer_size_, other->buffer_size_);
    std::swap(chunk_size_, other->chunk_size_);
    std::swap(thread_, other->thread_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata RunnyProto::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = RunnyProto_descriptor_;
  metadata.reflection = RunnyProto_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace source
}  // namespace audio
}  // namespace rec

// @@protoc_insertion_point(global_scope)
