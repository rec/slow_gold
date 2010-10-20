// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/widget/tree/Node.proto

#ifndef PROTOBUF_rec_2fwidget_2ftree_2fNode_2eproto__INCLUDED
#define PROTOBUF_rec_2fwidget_2ftree_2fNode_2eproto__INCLUDED

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
#include "rec/widget/Widget.pb.h"
// @@protoc_insertion_point(includes)

namespace rec {
namespace widget {
namespace tree {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fwidget_2ftree_2fNode_2eproto();
void protobuf_AssignDesc_rec_2fwidget_2ftree_2fNode_2eproto();
void protobuf_ShutdownFile_rec_2fwidget_2ftree_2fNode_2eproto();

class NodeDesc;

// ===================================================================

class NodeDesc : public ::google::protobuf::Message {
 public:
  NodeDesc();
  virtual ~NodeDesc();
  
  NodeDesc(const NodeDesc& from);
  
  inline NodeDesc& operator=(const NodeDesc& from) {
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
  static const NodeDesc& default_instance();
  
  void Swap(NodeDesc* other);
  
  // implements Message ----------------------------------------------
  
  NodeDesc* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const NodeDesc& from);
  void MergeFrom(const NodeDesc& from);
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
  
  // optional .rec.widget.Widget widget = 1;
  inline bool has_widget() const;
  inline void clear_widget();
  static const int kWidgetFieldNumber = 1;
  inline const ::rec::widget::Widget& widget() const;
  inline ::rec::widget::Widget* mutable_widget();
  
  // optional uint32 max_branch = 2 [default = 16];
  inline bool has_max_branch() const;
  inline void clear_max_branch();
  static const int kMaxBranchFieldNumber = 2;
  inline ::google::protobuf::uint32 max_branch() const;
  inline void set_max_branch(::google::protobuf::uint32 value);
  
  // optional string icon = 3;
  inline bool has_icon() const;
  inline void clear_icon();
  static const int kIconFieldNumber = 3;
  inline const ::std::string& icon() const;
  inline void set_icon(const ::std::string& value);
  inline void set_icon(const char* value);
  inline void set_icon(const char* value, size_t size);
  inline ::std::string* mutable_icon();
  
  // @@protoc_insertion_point(class_scope:rec.widget.tree.NodeDesc)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::rec::widget::Widget* widget_;
  ::google::protobuf::uint32 max_branch_;
  ::std::string* icon_;
  static const ::std::string _default_icon_;
  friend void  protobuf_AddDesc_rec_2fwidget_2ftree_2fNode_2eproto();
  friend void protobuf_AssignDesc_rec_2fwidget_2ftree_2fNode_2eproto();
  friend void protobuf_ShutdownFile_rec_2fwidget_2ftree_2fNode_2eproto();
  
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
  static NodeDesc* default_instance_;
};
// ===================================================================


// ===================================================================

// NodeDesc

// optional .rec.widget.Widget widget = 1;
inline bool NodeDesc::has_widget() const {
  return _has_bit(0);
}
inline void NodeDesc::clear_widget() {
  if (widget_ != NULL) widget_->::rec::widget::Widget::Clear();
  _clear_bit(0);
}
inline const ::rec::widget::Widget& NodeDesc::widget() const {
  return widget_ != NULL ? *widget_ : *default_instance_->widget_;
}
inline ::rec::widget::Widget* NodeDesc::mutable_widget() {
  _set_bit(0);
  if (widget_ == NULL) widget_ = new ::rec::widget::Widget;
  return widget_;
}

// optional uint32 max_branch = 2 [default = 16];
inline bool NodeDesc::has_max_branch() const {
  return _has_bit(1);
}
inline void NodeDesc::clear_max_branch() {
  max_branch_ = 16u;
  _clear_bit(1);
}
inline ::google::protobuf::uint32 NodeDesc::max_branch() const {
  return max_branch_;
}
inline void NodeDesc::set_max_branch(::google::protobuf::uint32 value) {
  _set_bit(1);
  max_branch_ = value;
}

// optional string icon = 3;
inline bool NodeDesc::has_icon() const {
  return _has_bit(2);
}
inline void NodeDesc::clear_icon() {
  if (icon_ != &_default_icon_) {
    icon_->clear();
  }
  _clear_bit(2);
}
inline const ::std::string& NodeDesc::icon() const {
  return *icon_;
}
inline void NodeDesc::set_icon(const ::std::string& value) {
  _set_bit(2);
  if (icon_ == &_default_icon_) {
    icon_ = new ::std::string;
  }
  icon_->assign(value);
}
inline void NodeDesc::set_icon(const char* value) {
  _set_bit(2);
  if (icon_ == &_default_icon_) {
    icon_ = new ::std::string;
  }
  icon_->assign(value);
}
inline void NodeDesc::set_icon(const char* value, size_t size) {
  _set_bit(2);
  if (icon_ == &_default_icon_) {
    icon_ = new ::std::string;
  }
  icon_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* NodeDesc::mutable_icon() {
  _set_bit(2);
  if (icon_ == &_default_icon_) {
    icon_ = new ::std::string;
  }
  return icon_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace tree
}  // namespace widget
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2fwidget_2ftree_2fNode_2eproto__INCLUDED
