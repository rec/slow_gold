// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ThumbnailDescription.proto

#ifndef PROTOBUF_ThumbnailDescription_2eproto__INCLUDED
#define PROTOBUF_ThumbnailDescription_2eproto__INCLUDED

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
#include "Color.pb.h"
// @@protoc_insertion_point(includes)

namespace rec {
namespace gui {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ThumbnailDescription_2eproto();
void protobuf_AssignDesc_ThumbnailDescription_2eproto();
void protobuf_ShutdownFile_ThumbnailDescription_2eproto();

class ThumbnailDescription;

// ===================================================================

class ThumbnailDescription : public ::google::protobuf::Message {
 public:
  ThumbnailDescription();
  virtual ~ThumbnailDescription();
  
  ThumbnailDescription(const ThumbnailDescription& from);
  
  inline ThumbnailDescription& operator=(const ThumbnailDescription& from) {
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
  static const ThumbnailDescription& default_instance();
  
  void Swap(ThumbnailDescription* other);
  
  // implements Message ----------------------------------------------
  
  ThumbnailDescription* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ThumbnailDescription& from);
  void MergeFrom(const ThumbnailDescription& from);
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
  
  // required .rec.gui.Color background = 1;
  inline bool has_background() const;
  inline void clear_background();
  static const int kBackgroundFieldNumber = 1;
  inline const ::rec::gui::Color& background() const;
  inline ::rec::gui::Color* mutable_background();
  
  // required .rec.gui.Color foreground = 2;
  inline bool has_foreground() const;
  inline void clear_foreground();
  static const int kForegroundFieldNumber = 2;
  inline const ::rec::gui::Color& foreground() const;
  inline ::rec::gui::Color* mutable_foreground();
  
  // required .rec.gui.Color cursor = 3;
  inline bool has_cursor() const;
  inline void clear_cursor();
  static const int kCursorFieldNumber = 3;
  inline const ::rec::gui::Color& cursor() const;
  inline ::rec::gui::Color* mutable_cursor();
  
  // optional uint32 cursor_thickness = 4 [default = 1];
  inline bool has_cursor_thickness() const;
  inline void clear_cursor_thickness();
  static const int kCursorThicknessFieldNumber = 4;
  inline ::google::protobuf::uint32 cursor_thickness() const;
  inline void set_cursor_thickness(::google::protobuf::uint32 value);
  
  // optional uint32 margin = 5 [default = 2];
  inline bool has_margin() const;
  inline void clear_margin();
  static const int kMarginFieldNumber = 5;
  inline ::google::protobuf::uint32 margin() const;
  inline void set_margin(::google::protobuf::uint32 value);
  
  // optional uint32 source_samples_per_thumbnail_sample = 6 [default = 512];
  inline bool has_source_samples_per_thumbnail_sample() const;
  inline void clear_source_samples_per_thumbnail_sample();
  static const int kSourceSamplesPerThumbnailSampleFieldNumber = 6;
  inline ::google::protobuf::uint32 source_samples_per_thumbnail_sample() const;
  inline void set_source_samples_per_thumbnail_sample(::google::protobuf::uint32 value);
  
  // optional uint32 thumbnail_cache = 7 [default = 5];
  inline bool has_thumbnail_cache() const;
  inline void clear_thumbnail_cache();
  static const int kThumbnailCacheFieldNumber = 7;
  inline ::google::protobuf::uint32 thumbnail_cache() const;
  inline void set_thumbnail_cache(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:rec.gui.ThumbnailDescription)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::rec::gui::Color* background_;
  ::rec::gui::Color* foreground_;
  ::rec::gui::Color* cursor_;
  ::google::protobuf::uint32 cursor_thickness_;
  ::google::protobuf::uint32 margin_;
  ::google::protobuf::uint32 source_samples_per_thumbnail_sample_;
  ::google::protobuf::uint32 thumbnail_cache_;
  friend void  protobuf_AddDesc_ThumbnailDescription_2eproto();
  friend void protobuf_AssignDesc_ThumbnailDescription_2eproto();
  friend void protobuf_ShutdownFile_ThumbnailDescription_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(7 + 31) / 32];
  
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
  static ThumbnailDescription* default_instance_;
};
// ===================================================================


// ===================================================================

// ThumbnailDescription

// required .rec.gui.Color background = 1;
inline bool ThumbnailDescription::has_background() const {
  return _has_bit(0);
}
inline void ThumbnailDescription::clear_background() {
  if (background_ != NULL) background_->::rec::gui::Color::Clear();
  _clear_bit(0);
}
inline const ::rec::gui::Color& ThumbnailDescription::background() const {
  return background_ != NULL ? *background_ : *default_instance_->background_;
}
inline ::rec::gui::Color* ThumbnailDescription::mutable_background() {
  _set_bit(0);
  if (background_ == NULL) background_ = new ::rec::gui::Color;
  return background_;
}

// required .rec.gui.Color foreground = 2;
inline bool ThumbnailDescription::has_foreground() const {
  return _has_bit(1);
}
inline void ThumbnailDescription::clear_foreground() {
  if (foreground_ != NULL) foreground_->::rec::gui::Color::Clear();
  _clear_bit(1);
}
inline const ::rec::gui::Color& ThumbnailDescription::foreground() const {
  return foreground_ != NULL ? *foreground_ : *default_instance_->foreground_;
}
inline ::rec::gui::Color* ThumbnailDescription::mutable_foreground() {
  _set_bit(1);
  if (foreground_ == NULL) foreground_ = new ::rec::gui::Color;
  return foreground_;
}

// required .rec.gui.Color cursor = 3;
inline bool ThumbnailDescription::has_cursor() const {
  return _has_bit(2);
}
inline void ThumbnailDescription::clear_cursor() {
  if (cursor_ != NULL) cursor_->::rec::gui::Color::Clear();
  _clear_bit(2);
}
inline const ::rec::gui::Color& ThumbnailDescription::cursor() const {
  return cursor_ != NULL ? *cursor_ : *default_instance_->cursor_;
}
inline ::rec::gui::Color* ThumbnailDescription::mutable_cursor() {
  _set_bit(2);
  if (cursor_ == NULL) cursor_ = new ::rec::gui::Color;
  return cursor_;
}

// optional uint32 cursor_thickness = 4 [default = 1];
inline bool ThumbnailDescription::has_cursor_thickness() const {
  return _has_bit(3);
}
inline void ThumbnailDescription::clear_cursor_thickness() {
  cursor_thickness_ = 1u;
  _clear_bit(3);
}
inline ::google::protobuf::uint32 ThumbnailDescription::cursor_thickness() const {
  return cursor_thickness_;
}
inline void ThumbnailDescription::set_cursor_thickness(::google::protobuf::uint32 value) {
  _set_bit(3);
  cursor_thickness_ = value;
}

// optional uint32 margin = 5 [default = 2];
inline bool ThumbnailDescription::has_margin() const {
  return _has_bit(4);
}
inline void ThumbnailDescription::clear_margin() {
  margin_ = 2u;
  _clear_bit(4);
}
inline ::google::protobuf::uint32 ThumbnailDescription::margin() const {
  return margin_;
}
inline void ThumbnailDescription::set_margin(::google::protobuf::uint32 value) {
  _set_bit(4);
  margin_ = value;
}

// optional uint32 source_samples_per_thumbnail_sample = 6 [default = 512];
inline bool ThumbnailDescription::has_source_samples_per_thumbnail_sample() const {
  return _has_bit(5);
}
inline void ThumbnailDescription::clear_source_samples_per_thumbnail_sample() {
  source_samples_per_thumbnail_sample_ = 512u;
  _clear_bit(5);
}
inline ::google::protobuf::uint32 ThumbnailDescription::source_samples_per_thumbnail_sample() const {
  return source_samples_per_thumbnail_sample_;
}
inline void ThumbnailDescription::set_source_samples_per_thumbnail_sample(::google::protobuf::uint32 value) {
  _set_bit(5);
  source_samples_per_thumbnail_sample_ = value;
}

// optional uint32 thumbnail_cache = 7 [default = 5];
inline bool ThumbnailDescription::has_thumbnail_cache() const {
  return _has_bit(6);
}
inline void ThumbnailDescription::clear_thumbnail_cache() {
  thumbnail_cache_ = 5u;
  _clear_bit(6);
}
inline ::google::protobuf::uint32 ThumbnailDescription::thumbnail_cache() const {
  return thumbnail_cache_;
}
inline void ThumbnailDescription::set_thumbnail_cache(::google::protobuf::uint32 value) {
  _set_bit(6);
  thumbnail_cache_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace gui
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ThumbnailDescription_2eproto__INCLUDED
