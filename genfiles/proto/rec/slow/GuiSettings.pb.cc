// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rec/slow/GuiSettings.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace rec {
namespace slow {

namespace {

const ::google::protobuf::Descriptor* GuiSettings_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  GuiSettings_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* GuiSettings_FileType_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_rec_2fslow_2fGuiSettings_2eproto() {
  protobuf_AddDesc_rec_2fslow_2fGuiSettings_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "rec/slow/GuiSettings.proto");
  GOOGLE_CHECK(file != NULL);
  GuiSettings_descriptor_ = file->message_type(0);
  static const int GuiSettings_offsets_[10] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GuiSettings, follow_cursor_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GuiSettings, drop_adds_to_browser_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GuiSettings, show_tooltips_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GuiSettings, show_help_pane_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GuiSettings, advanced_menus_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GuiSettings, show_about_on_startup_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GuiSettings, auto_check_for_updates_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GuiSettings, use_tree_view_in_file_dialogs_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GuiSettings, last_directory_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GuiSettings, file_type_for_save_),
  };
  GuiSettings_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      GuiSettings_descriptor_,
      GuiSettings::default_instance_,
      GuiSettings_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GuiSettings, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GuiSettings, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(GuiSettings));
  GuiSettings_FileType_descriptor_ = GuiSettings_descriptor_->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_rec_2fslow_2fGuiSettings_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    GuiSettings_descriptor_, &GuiSettings::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_rec_2fslow_2fGuiSettings_2eproto() {
  delete GuiSettings::default_instance_;
  delete GuiSettings_reflection_;
}

void protobuf_AddDesc_rec_2fslow_2fGuiSettings_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\032rec/slow/GuiSettings.proto\022\010rec.slow\"\272"
    "\003\n\013GuiSettings\022\033\n\rfollow_cursor\030\001 \001(\010:\004t"
    "rue\022\"\n\024drop_adds_to_browser\030\002 \001(\010:\004true\022"
    "\034\n\rshow_tooltips\030\003 \001(\010:\005false\022\034\n\016show_he"
    "lp_pane\030\004 \001(\010:\004true\022\035\n\016advanced_menus\030\005 "
    "\001(\010:\005false\022#\n\025show_about_on_startup\030\006 \001("
    "\010:\004true\022%\n\026auto_check_for_updates\030\007 \001(\010:"
    "\005false\022,\n\035use_tree_view_in_file_dialogs\030"
    "\010 \001(\010:\005false\022\026\n\016last_directory\030\t \001(\t\022@\n\022"
    "file_type_for_save\030\n \001(\0162\036.rec.slow.GuiS"
    "ettings.FileType:\004AIFF\";\n\010FileType\022\010\n\004AI"
    "FF\020\000\022\010\n\004FLAC\020\001\022\007\n\003OGG\020\002\022\007\n\003WAV\020\003\022\t\n\005COUN"
    "T\020\004", 483);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rec/slow/GuiSettings.proto", &protobuf_RegisterTypes);
  GuiSettings::default_instance_ = new GuiSettings();
  GuiSettings::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rec_2fslow_2fGuiSettings_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_rec_2fslow_2fGuiSettings_2eproto {
  StaticDescriptorInitializer_rec_2fslow_2fGuiSettings_2eproto() {
    protobuf_AddDesc_rec_2fslow_2fGuiSettings_2eproto();
  }
} static_descriptor_initializer_rec_2fslow_2fGuiSettings_2eproto_;


// ===================================================================

const ::google::protobuf::EnumDescriptor* GuiSettings_FileType_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return GuiSettings_FileType_descriptor_;
}
bool GuiSettings_FileType_IsValid(int value) {
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
const GuiSettings_FileType GuiSettings::AIFF;
const GuiSettings_FileType GuiSettings::FLAC;
const GuiSettings_FileType GuiSettings::OGG;
const GuiSettings_FileType GuiSettings::WAV;
const GuiSettings_FileType GuiSettings::COUNT;
const GuiSettings_FileType GuiSettings::FileType_MIN;
const GuiSettings_FileType GuiSettings::FileType_MAX;
const int GuiSettings::FileType_ARRAYSIZE;
#endif  // _MSC_VER
const ::std::string GuiSettings::_default_last_directory_;
#ifndef _MSC_VER
const int GuiSettings::kFollowCursorFieldNumber;
const int GuiSettings::kDropAddsToBrowserFieldNumber;
const int GuiSettings::kShowTooltipsFieldNumber;
const int GuiSettings::kShowHelpPaneFieldNumber;
const int GuiSettings::kAdvancedMenusFieldNumber;
const int GuiSettings::kShowAboutOnStartupFieldNumber;
const int GuiSettings::kAutoCheckForUpdatesFieldNumber;
const int GuiSettings::kUseTreeViewInFileDialogsFieldNumber;
const int GuiSettings::kLastDirectoryFieldNumber;
const int GuiSettings::kFileTypeForSaveFieldNumber;
#endif  // !_MSC_VER

GuiSettings::GuiSettings()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void GuiSettings::InitAsDefaultInstance() {
}

GuiSettings::GuiSettings(const GuiSettings& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void GuiSettings::SharedCtor() {
  _cached_size_ = 0;
  follow_cursor_ = true;
  drop_adds_to_browser_ = true;
  show_tooltips_ = false;
  show_help_pane_ = true;
  advanced_menus_ = false;
  show_about_on_startup_ = true;
  auto_check_for_updates_ = false;
  use_tree_view_in_file_dialogs_ = false;
  last_directory_ = const_cast< ::std::string*>(&_default_last_directory_);
  file_type_for_save_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

GuiSettings::~GuiSettings() {
  SharedDtor();
}

void GuiSettings::SharedDtor() {
  if (last_directory_ != &_default_last_directory_) {
    delete last_directory_;
  }
  if (this != default_instance_) {
  }
}

void GuiSettings::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* GuiSettings::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return GuiSettings_descriptor_;
}

const GuiSettings& GuiSettings::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_rec_2fslow_2fGuiSettings_2eproto();  return *default_instance_;
}

GuiSettings* GuiSettings::default_instance_ = NULL;

GuiSettings* GuiSettings::New() const {
  return new GuiSettings;
}

void GuiSettings::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    follow_cursor_ = true;
    drop_adds_to_browser_ = true;
    show_tooltips_ = false;
    show_help_pane_ = true;
    advanced_menus_ = false;
    show_about_on_startup_ = true;
    auto_check_for_updates_ = false;
    use_tree_view_in_file_dialogs_ = false;
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (_has_bit(8)) {
      if (last_directory_ != &_default_last_directory_) {
        last_directory_->clear();
      }
    }
    file_type_for_save_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool GuiSettings::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional bool follow_cursor = 1 [default = true];
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &follow_cursor_)));
          _set_bit(0);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_drop_adds_to_browser;
        break;
      }
      
      // optional bool drop_adds_to_browser = 2 [default = true];
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_drop_adds_to_browser:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &drop_adds_to_browser_)));
          _set_bit(1);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_show_tooltips;
        break;
      }
      
      // optional bool show_tooltips = 3 [default = false];
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_show_tooltips:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &show_tooltips_)));
          _set_bit(2);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_show_help_pane;
        break;
      }
      
      // optional bool show_help_pane = 4 [default = true];
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_show_help_pane:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &show_help_pane_)));
          _set_bit(3);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_advanced_menus;
        break;
      }
      
      // optional bool advanced_menus = 5 [default = false];
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_advanced_menus:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &advanced_menus_)));
          _set_bit(4);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(48)) goto parse_show_about_on_startup;
        break;
      }
      
      // optional bool show_about_on_startup = 6 [default = true];
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_show_about_on_startup:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &show_about_on_startup_)));
          _set_bit(5);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(56)) goto parse_auto_check_for_updates;
        break;
      }
      
      // optional bool auto_check_for_updates = 7 [default = false];
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_auto_check_for_updates:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &auto_check_for_updates_)));
          _set_bit(6);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(64)) goto parse_use_tree_view_in_file_dialogs;
        break;
      }
      
      // optional bool use_tree_view_in_file_dialogs = 8 [default = false];
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_use_tree_view_in_file_dialogs:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &use_tree_view_in_file_dialogs_)));
          _set_bit(7);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(74)) goto parse_last_directory;
        break;
      }
      
      // optional string last_directory = 9;
      case 9: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_last_directory:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_last_directory()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->last_directory().data(), this->last_directory().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(80)) goto parse_file_type_for_save;
        break;
      }
      
      // optional .rec.slow.GuiSettings.FileType file_type_for_save = 10 [default = AIFF];
      case 10: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_file_type_for_save:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::rec::slow::GuiSettings_FileType_IsValid(value)) {
            set_file_type_for_save(static_cast< ::rec::slow::GuiSettings_FileType >(value));
          } else {
            mutable_unknown_fields()->AddVarint(10, value);
          }
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

void GuiSettings::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional bool follow_cursor = 1 [default = true];
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(1, this->follow_cursor(), output);
  }
  
  // optional bool drop_adds_to_browser = 2 [default = true];
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(2, this->drop_adds_to_browser(), output);
  }
  
  // optional bool show_tooltips = 3 [default = false];
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(3, this->show_tooltips(), output);
  }
  
  // optional bool show_help_pane = 4 [default = true];
  if (_has_bit(3)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(4, this->show_help_pane(), output);
  }
  
  // optional bool advanced_menus = 5 [default = false];
  if (_has_bit(4)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(5, this->advanced_menus(), output);
  }
  
  // optional bool show_about_on_startup = 6 [default = true];
  if (_has_bit(5)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(6, this->show_about_on_startup(), output);
  }
  
  // optional bool auto_check_for_updates = 7 [default = false];
  if (_has_bit(6)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(7, this->auto_check_for_updates(), output);
  }
  
  // optional bool use_tree_view_in_file_dialogs = 8 [default = false];
  if (_has_bit(7)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(8, this->use_tree_view_in_file_dialogs(), output);
  }
  
  // optional string last_directory = 9;
  if (_has_bit(8)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->last_directory().data(), this->last_directory().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      9, this->last_directory(), output);
  }
  
  // optional .rec.slow.GuiSettings.FileType file_type_for_save = 10 [default = AIFF];
  if (_has_bit(9)) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      10, this->file_type_for_save(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* GuiSettings::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional bool follow_cursor = 1 [default = true];
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(1, this->follow_cursor(), target);
  }
  
  // optional bool drop_adds_to_browser = 2 [default = true];
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(2, this->drop_adds_to_browser(), target);
  }
  
  // optional bool show_tooltips = 3 [default = false];
  if (_has_bit(2)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(3, this->show_tooltips(), target);
  }
  
  // optional bool show_help_pane = 4 [default = true];
  if (_has_bit(3)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(4, this->show_help_pane(), target);
  }
  
  // optional bool advanced_menus = 5 [default = false];
  if (_has_bit(4)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(5, this->advanced_menus(), target);
  }
  
  // optional bool show_about_on_startup = 6 [default = true];
  if (_has_bit(5)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(6, this->show_about_on_startup(), target);
  }
  
  // optional bool auto_check_for_updates = 7 [default = false];
  if (_has_bit(6)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(7, this->auto_check_for_updates(), target);
  }
  
  // optional bool use_tree_view_in_file_dialogs = 8 [default = false];
  if (_has_bit(7)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(8, this->use_tree_view_in_file_dialogs(), target);
  }
  
  // optional string last_directory = 9;
  if (_has_bit(8)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->last_directory().data(), this->last_directory().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        9, this->last_directory(), target);
  }
  
  // optional .rec.slow.GuiSettings.FileType file_type_for_save = 10 [default = AIFF];
  if (_has_bit(9)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      10, this->file_type_for_save(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int GuiSettings::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional bool follow_cursor = 1 [default = true];
    if (has_follow_cursor()) {
      total_size += 1 + 1;
    }
    
    // optional bool drop_adds_to_browser = 2 [default = true];
    if (has_drop_adds_to_browser()) {
      total_size += 1 + 1;
    }
    
    // optional bool show_tooltips = 3 [default = false];
    if (has_show_tooltips()) {
      total_size += 1 + 1;
    }
    
    // optional bool show_help_pane = 4 [default = true];
    if (has_show_help_pane()) {
      total_size += 1 + 1;
    }
    
    // optional bool advanced_menus = 5 [default = false];
    if (has_advanced_menus()) {
      total_size += 1 + 1;
    }
    
    // optional bool show_about_on_startup = 6 [default = true];
    if (has_show_about_on_startup()) {
      total_size += 1 + 1;
    }
    
    // optional bool auto_check_for_updates = 7 [default = false];
    if (has_auto_check_for_updates()) {
      total_size += 1 + 1;
    }
    
    // optional bool use_tree_view_in_file_dialogs = 8 [default = false];
    if (has_use_tree_view_in_file_dialogs()) {
      total_size += 1 + 1;
    }
    
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // optional string last_directory = 9;
    if (has_last_directory()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->last_directory());
    }
    
    // optional .rec.slow.GuiSettings.FileType file_type_for_save = 10 [default = AIFF];
    if (has_file_type_for_save()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->file_type_for_save());
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

void GuiSettings::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const GuiSettings* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const GuiSettings*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void GuiSettings::MergeFrom(const GuiSettings& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_follow_cursor(from.follow_cursor());
    }
    if (from._has_bit(1)) {
      set_drop_adds_to_browser(from.drop_adds_to_browser());
    }
    if (from._has_bit(2)) {
      set_show_tooltips(from.show_tooltips());
    }
    if (from._has_bit(3)) {
      set_show_help_pane(from.show_help_pane());
    }
    if (from._has_bit(4)) {
      set_advanced_menus(from.advanced_menus());
    }
    if (from._has_bit(5)) {
      set_show_about_on_startup(from.show_about_on_startup());
    }
    if (from._has_bit(6)) {
      set_auto_check_for_updates(from.auto_check_for_updates());
    }
    if (from._has_bit(7)) {
      set_use_tree_view_in_file_dialogs(from.use_tree_view_in_file_dialogs());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from._has_bit(8)) {
      set_last_directory(from.last_directory());
    }
    if (from._has_bit(9)) {
      set_file_type_for_save(from.file_type_for_save());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void GuiSettings::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void GuiSettings::CopyFrom(const GuiSettings& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GuiSettings::IsInitialized() const {
  
  return true;
}

void GuiSettings::Swap(GuiSettings* other) {
  if (other != this) {
    std::swap(follow_cursor_, other->follow_cursor_);
    std::swap(drop_adds_to_browser_, other->drop_adds_to_browser_);
    std::swap(show_tooltips_, other->show_tooltips_);
    std::swap(show_help_pane_, other->show_help_pane_);
    std::swap(advanced_menus_, other->advanced_menus_);
    std::swap(show_about_on_startup_, other->show_about_on_startup_);
    std::swap(auto_check_for_updates_, other->auto_check_for_updates_);
    std::swap(use_tree_view_in_file_dialogs_, other->use_tree_view_in_file_dialogs_);
    std::swap(last_directory_, other->last_directory_);
    std::swap(file_type_for_save_, other->file_type_for_save_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata GuiSettings::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = GuiSettings_descriptor_;
  metadata.reflection = GuiSettings_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace slow
}  // namespace rec

// @@protoc_insertion_point(global_scope)
