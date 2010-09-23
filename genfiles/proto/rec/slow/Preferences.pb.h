// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/slow/Preferences.proto

#ifndef PROTOBUF_rec_2fslow_2fPreferences_2eproto__INCLUDED
#define PROTOBUF_rec_2fslow_2fPreferences_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2003000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
#include "rec/gui/ThumbnailDescription.pb.h"
#include "rec/slow/LoopWindow.pb.h"
#include "rec/slow/RecentFiles.pb.h"
// @@protoc_insertion_point(includes)

namespace rec {
namespace slow {
namespace proto {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fslow_2fPreferences_2eproto();
void protobuf_AssignDesc_rec_2fslow_2fPreferences_2eproto();
void protobuf_ShutdownFile_rec_2fslow_2fPreferences_2eproto();

class Preferences;

// ===================================================================

class Preferences : public ::google::protobuf::Message {
 public:
  Preferences();
  virtual ~Preferences();
  
  Preferences(const Preferences& from);
  
  inline Preferences& operator=(const Preferences& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Preferences& default_instance();
  
  void Swap(Preferences* other);
  
  // implements Message ----------------------------------------------
  
  Preferences* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Preferences& from);
  void MergeFrom(const Preferences& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional .rec.slow.proto.LoopWindow loop_window = 1;
  inline bool has_loop_window() const;
  inline void clear_loop_window();
  static const int kLoopWindowFieldNumber = 1;
  inline const ::rec::slow::proto::LoopWindow& loop_window() const;
  inline ::rec::slow::proto::LoopWindow* mutable_loop_window();
  
  // optional .rec.gui.ThumbnailDescription thumbnail = 2;
  inline bool has_thumbnail() const;
  inline void clear_thumbnail();
  static const int kThumbnailFieldNumber = 2;
  inline const ::rec::gui::ThumbnailDescription& thumbnail() const;
  inline ::rec::gui::ThumbnailDescription* mutable_thumbnail();
  
  // optional .rec.slow.RecentFiles recent_files = 3;
  inline bool has_recent_files() const;
  inline void clear_recent_files();
  static const int kRecentFilesFieldNumber = 3;
  inline const ::rec::slow::RecentFiles& recent_files() const;
  inline ::rec::slow::RecentFiles* mutable_recent_files();
  
  // @@protoc_insertion_point(class_scope:rec.slow.proto.Preferences)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::rec::slow::proto::LoopWindow* loop_window_;
  ::rec::gui::ThumbnailDescription* thumbnail_;
  ::rec::slow::RecentFiles* recent_files_;
  friend void  protobuf_AddDesc_rec_2fslow_2fPreferences_2eproto();
  friend void protobuf_AssignDesc_rec_2fslow_2fPreferences_2eproto();
  friend void protobuf_ShutdownFile_rec_2fslow_2fPreferences_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static Preferences* default_instance_;
};
// ===================================================================


// ===================================================================

// Preferences

// optional .rec.slow.proto.LoopWindow loop_window = 1;
inline bool Preferences::has_loop_window() const {
  return _has_bit(0);
}
inline void Preferences::clear_loop_window() {
  if (loop_window_ != NULL) loop_window_->::rec::slow::proto::LoopWindow::Clear();
  _clear_bit(0);
}
inline const ::rec::slow::proto::LoopWindow& Preferences::loop_window() const {
  return loop_window_ != NULL ? *loop_window_ : *default_instance_->loop_window_;
}
inline ::rec::slow::proto::LoopWindow* Preferences::mutable_loop_window() {
  _set_bit(0);
  if (loop_window_ == NULL) loop_window_ = new ::rec::slow::proto::LoopWindow;
  return loop_window_;
}

// optional .rec.gui.ThumbnailDescription thumbnail = 2;
inline bool Preferences::has_thumbnail() const {
  return _has_bit(1);
}
inline void Preferences::clear_thumbnail() {
  if (thumbnail_ != NULL) thumbnail_->::rec::gui::ThumbnailDescription::Clear();
  _clear_bit(1);
}
inline const ::rec::gui::ThumbnailDescription& Preferences::thumbnail() const {
  return thumbnail_ != NULL ? *thumbnail_ : *default_instance_->thumbnail_;
}
inline ::rec::gui::ThumbnailDescription* Preferences::mutable_thumbnail() {
  _set_bit(1);
  if (thumbnail_ == NULL) thumbnail_ = new ::rec::gui::ThumbnailDescription;
  return thumbnail_;
}

// optional .rec.slow.RecentFiles recent_files = 3;
inline bool Preferences::has_recent_files() const {
  return _has_bit(2);
}
inline void Preferences::clear_recent_files() {
  if (recent_files_ != NULL) recent_files_->::rec::slow::RecentFiles::Clear();
  _clear_bit(2);
}
inline const ::rec::slow::RecentFiles& Preferences::recent_files() const {
  return recent_files_ != NULL ? *recent_files_ : *default_instance_->recent_files_;
}
inline ::rec::slow::RecentFiles* Preferences::mutable_recent_files() {
  _set_bit(2);
  if (recent_files_ == NULL) recent_files_ = new ::rec::slow::RecentFiles;
  return recent_files_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace slow
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2fslow_2fPreferences_2eproto__INCLUDED
