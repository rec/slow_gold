// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/base/Trans.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace rec {

namespace {

const ::google::protobuf::Descriptor* TranslatedString_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TranslatedString_reflection_ = NULL;
const ::google::protobuf::Descriptor* TranslatedStrings_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TranslatedStrings_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2fbase_2fTrans_2eproto() {
  protobuf_AddDesc_rec_2fbase_2fTrans_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/base/Trans.proto");
  GOOGLE_CHECK(file != NULL);
  TranslatedString_descriptor_ = file->message_type(0);
  static const int TranslatedString_offsets_[6] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TranslatedString, original_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TranslatedString, translation_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TranslatedString, hint_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TranslatedString, file_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TranslatedString, line_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TranslatedString, index_),
  };
  TranslatedString_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TranslatedString_descriptor_,
      TranslatedString::default_instance_,
      TranslatedString_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TranslatedString, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TranslatedString, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TranslatedString));
  TranslatedStrings_descriptor_ = file->message_type(1);
  static const int TranslatedStrings_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TranslatedStrings, str_),
  };
  TranslatedStrings_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TranslatedStrings_descriptor_,
      TranslatedStrings::default_instance_,
      TranslatedStrings_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TranslatedStrings, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TranslatedStrings, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TranslatedStrings));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2fbase_2fTrans_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TranslatedString_descriptor_, &TranslatedString::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TranslatedStrings_descriptor_, &TranslatedStrings::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2fbase_2fTrans_2eproto() {
  delete TranslatedString::default_instance_;
  delete TranslatedString_reflection_;
  delete TranslatedStrings::default_instance_;
  delete TranslatedStrings_reflection_;
}

void protobuf_AddDesc_rec_2fbase_2fTrans_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\024rec/base/Trans.proto\022\003rec\"r\n\020Translate"
    "dString\022\020\n\010original\030\001 \001(\t\022\023\n\013translation"
    "\030\002 \001(\t\022\014\n\004hint\030\003 \001(\t\022\014\n\004file\030\004 \001(\t\022\014\n\004li"
    "ne\030\005 \001(\r\022\r\n\005index\030\006 \001(\r\"7\n\021TranslatedStr"
    "ings\022\"\n\003str\030\001 \003(\0132\025.rec.TranslatedString", 200);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/base/Trans.proto", &protobuf_RegisterTypes);
  TranslatedString::default_instance_ = new TranslatedString();
  TranslatedStrings::default_instance_ = new TranslatedStrings();
  TranslatedString::default_instance_->InitAsDefaultInstance();
  TranslatedStrings::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2fbase_2fTrans_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2fbase_2fTrans_2eproto {
  StaticDescriptorInitializer_rec_2fbase_2fTrans_2eproto() {
    protobuf_AddDesc_rec_2fbase_2fTrans_2eproto();
  }
} static_descriptor_initializer_rec_2fbase_2fTrans_2eproto_;


// ===================================================================

const ::std::string TranslatedString::_default_original_;
const ::std::string TranslatedString::_default_translation_;
const ::std::string TranslatedString::_default_hint_;
const ::std::string TranslatedString::_default_file_;
#ifndef _MSC_VER
const int TranslatedString::kOriginalFieldNumber;
const int TranslatedString::kTranslationFieldNumber;
const int TranslatedString::kHintFieldNumber;
const int TranslatedString::kFileFieldNumber;
const int TranslatedString::kLineFieldNumber;
const int TranslatedString::kIndexFieldNumber;
#endif  // !_MSC_VER

TranslatedString::TranslatedString()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void TranslatedString::InitAsDefaultInstance() {
}

TranslatedString::TranslatedString(const TranslatedString& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void TranslatedString::SharedCtor() {
  _cached_size_ = 0;
  original_ = const_cast< ::std::string*>(&_default_original_);
  translation_ = const_cast< ::std::string*>(&_default_translation_);
  hint_ = const_cast< ::std::string*>(&_default_hint_);
  file_ = const_cast< ::std::string*>(&_default_file_);
  line_ = 0u;
  index_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TranslatedString::~TranslatedString() {
  SharedDtor();
}

void TranslatedString::SharedDtor() {
  if (original_ != &_default_original_) {
    delete original_;
  }
  if (translation_ != &_default_translation_) {
    delete translation_;
  }
  if (hint_ != &_default_hint_) {
    delete hint_;
  }
  if (file_ != &_default_file_) {
    delete file_;
  }
  if (this != default_instance_) {
  }
}

void TranslatedString::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TranslatedString::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TranslatedString_descriptor_;
}

const TranslatedString& TranslatedString::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fbase_2fTrans_2eproto();  return *default_instance_;
}

TranslatedString* TranslatedString::default_instance_ = NULL;

TranslatedString* TranslatedString::New() const {
  return new TranslatedString;
}

void TranslatedString::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (_has_bit(0)) {
      if (original_ != &_default_original_) {
        original_->clear();
      }
    }
    if (_has_bit(1)) {
      if (translation_ != &_default_translation_) {
        translation_->clear();
      }
    }
    if (_has_bit(2)) {
      if (hint_ != &_default_hint_) {
        hint_->clear();
      }
    }
    if (_has_bit(3)) {
      if (file_ != &_default_file_) {
        file_->clear();
      }
    }
    line_ = 0u;
    index_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TranslatedString::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string original = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_original()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->original().data(), this->original().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_translation;
        break;
      }
      
      // optional string translation = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_translation:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_translation()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->translation().data(), this->translation().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_hint;
        break;
      }
      
      // optional string hint = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_hint:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_hint()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->hint().data(), this->hint().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_file;
        break;
      }
      
      // optional string file = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_file:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_file()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->file().data(), this->file().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_line;
        break;
      }
      
      // optional uint32 line = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_line:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &line_)));
          _set_bit(4);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(48)) goto parse_index;
        break;
      }
      
      // optional uint32 index = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_index:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &index_)));
          _set_bit(5);
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

void TranslatedString::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional string original = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->original().data(), this->original().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->original(), output);
  }
  
  // optional string translation = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->translation().data(), this->translation().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->translation(), output);
  }
  
  // optional string hint = 3;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->hint().data(), this->hint().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->hint(), output);
  }
  
  // optional string file = 4;
  if (_has_bit(3)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->file().data(), this->file().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      4, this->file(), output);
  }
  
  // optional uint32 line = 5;
  if (_has_bit(4)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(5, this->line(), output);
  }
  
  // optional uint32 index = 6;
  if (_has_bit(5)) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(6, this->index(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* TranslatedString::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional string original = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->original().data(), this->original().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->original(), target);
  }
  
  // optional string translation = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->translation().data(), this->translation().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->translation(), target);
  }
  
  // optional string hint = 3;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->hint().data(), this->hint().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->hint(), target);
  }
  
  // optional string file = 4;
  if (_has_bit(3)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->file().data(), this->file().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->file(), target);
  }
  
  // optional uint32 line = 5;
  if (_has_bit(4)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(5, this->line(), target);
  }
  
  // optional uint32 index = 6;
  if (_has_bit(5)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(6, this->index(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int TranslatedString::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string original = 1;
    if (has_original()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->original());
    }
    
    // optional string translation = 2;
    if (has_translation()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->translation());
    }
    
    // optional string hint = 3;
    if (has_hint()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->hint());
    }
    
    // optional string file = 4;
    if (has_file()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->file());
    }
    
    // optional uint32 line = 5;
    if (has_line()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->line());
    }
    
    // optional uint32 index = 6;
    if (has_index()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->index());
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

void TranslatedString::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TranslatedString* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TranslatedString*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TranslatedString::MergeFrom(const TranslatedString& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_original(from.original());
    }
    if (from._has_bit(1)) {
      set_translation(from.translation());
    }
    if (from._has_bit(2)) {
      set_hint(from.hint());
    }
    if (from._has_bit(3)) {
      set_file(from.file());
    }
    if (from._has_bit(4)) {
      set_line(from.line());
    }
    if (from._has_bit(5)) {
      set_index(from.index());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TranslatedString::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TranslatedString::CopyFrom(const TranslatedString& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TranslatedString::IsInitialized() const {
  
  return true;
}

void TranslatedString::Swap(TranslatedString* other) {
  if (other != this) {
    std::swap(original_, other->original_);
    std::swap(translation_, other->translation_);
    std::swap(hint_, other->hint_);
    std::swap(file_, other->file_);
    std::swap(line_, other->line_);
    std::swap(index_, other->index_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TranslatedString::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TranslatedString_descriptor_;
  metadata.reflection = TranslatedString_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int TranslatedStrings::kStrFieldNumber;
#endif  // !_MSC_VER

TranslatedStrings::TranslatedStrings()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void TranslatedStrings::InitAsDefaultInstance() {
}

TranslatedStrings::TranslatedStrings(const TranslatedStrings& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void TranslatedStrings::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TranslatedStrings::~TranslatedStrings() {
  SharedDtor();
}

void TranslatedStrings::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TranslatedStrings::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TranslatedStrings::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TranslatedStrings_descriptor_;
}

const TranslatedStrings& TranslatedStrings::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fbase_2fTrans_2eproto();  return *default_instance_;
}

TranslatedStrings* TranslatedStrings::default_instance_ = NULL;

TranslatedStrings* TranslatedStrings::New() const {
  return new TranslatedStrings;
}

void TranslatedStrings::Clear() {
  str_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TranslatedStrings::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .rec.TranslatedString str = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_str:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_str()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_str;
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

void TranslatedStrings::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .rec.TranslatedString str = 1;
  for (int i = 0; i < this->str_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->str(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* TranslatedStrings::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .rec.TranslatedString str = 1;
  for (int i = 0; i < this->str_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->str(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int TranslatedStrings::ByteSize() const {
  int total_size = 0;
  
  // repeated .rec.TranslatedString str = 1;
  total_size += 1 * this->str_size();
  for (int i = 0; i < this->str_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->str(i));
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

void TranslatedStrings::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TranslatedStrings* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TranslatedStrings*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TranslatedStrings::MergeFrom(const TranslatedStrings& from) {
  GOOGLE_CHECK_NE(&from, this);
  str_.MergeFrom(from.str_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TranslatedStrings::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TranslatedStrings::CopyFrom(const TranslatedStrings& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TranslatedStrings::IsInitialized() const {
  
  return true;
}

void TranslatedStrings::Swap(TranslatedStrings* other) {
  if (other != this) {
    str_.Swap(&other->str_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TranslatedStrings::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TranslatedStrings_descriptor_;
  metadata.reflection = TranslatedStrings_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace rec

// @@protoc_insertion_point(global_scope)
