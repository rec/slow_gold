// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/gui/Appearance.proto

#ifndef PROTOBUF_rec_2fgui_2fAppearance_2eproto__INCLUDED
#define PROTOBUF_rec_2fgui_2fAppearance_2eproto__INCLUDED

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
#include "rec/gui/Color.pb.h"
#include "rec/widget/status/Time.pb.h"
// @@protoc_insertion_point(includes)

namespace rec {
namespace gui {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fgui_2fAppearance_2eproto();
void protobuf_AssignDesc_rec_2fgui_2fAppearance_2eproto();
void protobuf_ShutdownFile_rec_2fgui_2fAppearance_2eproto();

class Appearance;

// ===================================================================

class Appearance : public ::google::protobuf::Message {
 public:
  Appearance();
  virtual ~Appearance();
  
  Appearance(const Appearance& from);
  
  inline Appearance& operator=(const Appearance& from) {
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
  static const Appearance& default_instance();
  
  void Swap(Appearance* other);
  
  // implements Message ----------------------------------------------
  
  Appearance* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Appearance& from);
  void MergeFrom(const Appearance& from);
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
  
  // optional .rec.gui.Colors colors = 1;
  inline bool has_colors() const;
  inline void clear_colors();
  static const int kColorsFieldNumber = 1;
  inline const ::rec::gui::Colors& colors() const;
  inline ::rec::gui::Colors* mutable_colors();
  
  // optional .rec.widget.status.time.Time time = 3;
  inline bool has_time() const;
  inline void clear_time();
  static const int kTimeFieldNumber = 3;
  inline const ::rec::widget::status::time::Time& time() const;
  inline ::rec::widget::status::time::Time* mutable_time();
  
  // @@protoc_insertion_point(class_scope:rec.gui.Appearance)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::rec::gui::Colors* colors_;
  ::rec::widget::status::time::Time* time_;
  friend void  protobuf_AddDesc_rec_2fgui_2fAppearance_2eproto();
  friend void protobuf_AssignDesc_rec_2fgui_2fAppearance_2eproto();
  friend void protobuf_ShutdownFile_rec_2fgui_2fAppearance_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
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
  static Appearance* default_instance_;
};
// ===================================================================


// ===================================================================

// Appearance

// optional .rec.gui.Colors colors = 1;
inline bool Appearance::has_colors() const {
  return _has_bit(0);
}
inline void Appearance::clear_colors() {
  if (colors_ != NULL) colors_->::rec::gui::Colors::Clear();
  _clear_bit(0);
}
inline const ::rec::gui::Colors& Appearance::colors() const {
  return colors_ != NULL ? *colors_ : *default_instance_->colors_;
}
inline ::rec::gui::Colors* Appearance::mutable_colors() {
  _set_bit(0);
  if (colors_ == NULL) colors_ = new ::rec::gui::Colors;
  return colors_;
}

// optional .rec.widget.status.time.Time time = 3;
inline bool Appearance::has_time() const {
  return _has_bit(1);
}
inline void Appearance::clear_time() {
  if (time_ != NULL) time_->::rec::widget::status::time::Time::Clear();
  _clear_bit(1);
}
inline const ::rec::widget::status::time::Time& Appearance::time() const {
  return time_ != NULL ? *time_ : *default_instance_->time_;
}
inline ::rec::widget::status::time::Time* Appearance::mutable_time() {
  _set_bit(1);
  if (time_ == NULL) time_ = new ::rec::widget::status::time::Time;
  return time_;
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

#endif  // PROTOBUF_rec_2fgui_2fAppearance_2eproto__INCLUDED
