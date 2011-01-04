// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/util/cd/Album.proto

#ifndef PROTOBUF_rec_2futil_2fcd_2fAlbum_2eproto__INCLUDED
#define PROTOBUF_rec_2futil_2fcd_2fAlbum_2eproto__INCLUDED

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
// @@protoc_insertion_point(includes)

namespace rec {
namespace util {
namespace cd {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2futil_2fcd_2fAlbum_2eproto();
void protobuf_AssignDesc_rec_2futil_2fcd_2fAlbum_2eproto();
void protobuf_ShutdownFile_rec_2futil_2fcd_2fAlbum_2eproto();

class Metadata;
class Album;
class AlbumList;

// ===================================================================

class Metadata : public ::google::protobuf::Message {
 public:
  Metadata();
  virtual ~Metadata();
  
  Metadata(const Metadata& from);
  
  inline Metadata& operator=(const Metadata& from) {
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
  static const Metadata& default_instance();
  
  void Swap(Metadata* other);
  
  // implements Message ----------------------------------------------
  
  Metadata* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Metadata& from);
  void MergeFrom(const Metadata& from);
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
  
  // optional string discid = 1;
  inline bool has_discid() const;
  inline void clear_discid();
  static const int kDiscidFieldNumber = 1;
  inline const ::std::string& discid() const;
  inline void set_discid(const ::std::string& value);
  inline void set_discid(const char* value);
  inline void set_discid(const char* value, size_t size);
  inline ::std::string* mutable_discid();
  
  // optional string year = 2;
  inline bool has_year() const;
  inline void clear_year();
  static const int kYearFieldNumber = 2;
  inline const ::std::string& year() const;
  inline void set_year(const ::std::string& value);
  inline void set_year(const char* value);
  inline void set_year(const char* value, size_t size);
  inline ::std::string* mutable_year();
  
  // optional string genre = 3;
  inline bool has_genre() const;
  inline void clear_genre();
  static const int kGenreFieldNumber = 3;
  inline const ::std::string& genre() const;
  inline void set_genre(const ::std::string& value);
  inline void set_genre(const char* value);
  inline void set_genre(const char* value, size_t size);
  inline ::std::string* mutable_genre();
  
  // optional string track_title = 4;
  inline bool has_track_title() const;
  inline void clear_track_title();
  static const int kTrackTitleFieldNumber = 4;
  inline const ::std::string& track_title() const;
  inline void set_track_title(const ::std::string& value);
  inline void set_track_title(const char* value);
  inline void set_track_title(const char* value, size_t size);
  inline ::std::string* mutable_track_title();
  
  // optional string album_title = 5;
  inline bool has_album_title() const;
  inline void clear_album_title();
  static const int kAlbumTitleFieldNumber = 5;
  inline const ::std::string& album_title() const;
  inline void set_album_title(const ::std::string& value);
  inline void set_album_title(const char* value);
  inline void set_album_title(const char* value, size_t size);
  inline ::std::string* mutable_album_title();
  
  // optional string artist = 6;
  inline bool has_artist() const;
  inline void clear_artist();
  static const int kArtistFieldNumber = 6;
  inline const ::std::string& artist() const;
  inline void set_artist(const ::std::string& value);
  inline void set_artist(const char* value);
  inline void set_artist(const char* value, size_t size);
  inline ::std::string* mutable_artist();
  
  // optional string track_number = 7;
  inline bool has_track_number() const;
  inline void clear_track_number();
  static const int kTrackNumberFieldNumber = 7;
  inline const ::std::string& track_number() const;
  inline void set_track_number(const ::std::string& value);
  inline void set_track_number(const char* value);
  inline void set_track_number(const char* value, size_t size);
  inline ::std::string* mutable_track_number();
  
  // @@protoc_insertion_point(class_scope:rec.util.cd.Metadata)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::std::string* discid_;
  static const ::std::string _default_discid_;
  ::std::string* year_;
  static const ::std::string _default_year_;
  ::std::string* genre_;
  static const ::std::string _default_genre_;
  ::std::string* track_title_;
  static const ::std::string _default_track_title_;
  ::std::string* album_title_;
  static const ::std::string _default_album_title_;
  ::std::string* artist_;
  static const ::std::string _default_artist_;
  ::std::string* track_number_;
  static const ::std::string _default_track_number_;
  friend void  protobuf_AddDesc_rec_2futil_2fcd_2fAlbum_2eproto();
  friend void protobuf_AssignDesc_rec_2futil_2fcd_2fAlbum_2eproto();
  friend void protobuf_ShutdownFile_rec_2futil_2fcd_2fAlbum_2eproto();
  
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
  static Metadata* default_instance_;
};
// -------------------------------------------------------------------

class Album : public ::google::protobuf::Message {
 public:
  Album();
  virtual ~Album();
  
  Album(const Album& from);
  
  inline Album& operator=(const Album& from) {
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
  static const Album& default_instance();
  
  void Swap(Album* other);
  
  // implements Message ----------------------------------------------
  
  Album* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Album& from);
  void MergeFrom(const Album& from);
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
  
  // optional .rec.util.cd.Metadata album = 1;
  inline bool has_album() const;
  inline void clear_album();
  static const int kAlbumFieldNumber = 1;
  inline const ::rec::util::cd::Metadata& album() const;
  inline ::rec::util::cd::Metadata* mutable_album();
  
  // repeated .rec.util.cd.Metadata track = 2;
  inline int track_size() const;
  inline void clear_track();
  static const int kTrackFieldNumber = 2;
  inline const ::rec::util::cd::Metadata& track(int index) const;
  inline ::rec::util::cd::Metadata* mutable_track(int index);
  inline ::rec::util::cd::Metadata* add_track();
  inline const ::google::protobuf::RepeatedPtrField< ::rec::util::cd::Metadata >&
      track() const;
  inline ::google::protobuf::RepeatedPtrField< ::rec::util::cd::Metadata >*
      mutable_track();
  
  // @@protoc_insertion_point(class_scope:rec.util.cd.Album)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::rec::util::cd::Metadata* album_;
  ::google::protobuf::RepeatedPtrField< ::rec::util::cd::Metadata > track_;
  friend void  protobuf_AddDesc_rec_2futil_2fcd_2fAlbum_2eproto();
  friend void protobuf_AssignDesc_rec_2futil_2fcd_2fAlbum_2eproto();
  friend void protobuf_ShutdownFile_rec_2futil_2fcd_2fAlbum_2eproto();
  
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
  static Album* default_instance_;
};
// -------------------------------------------------------------------

class AlbumList : public ::google::protobuf::Message {
 public:
  AlbumList();
  virtual ~AlbumList();
  
  AlbumList(const AlbumList& from);
  
  inline AlbumList& operator=(const AlbumList& from) {
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
  static const AlbumList& default_instance();
  
  void Swap(AlbumList* other);
  
  // implements Message ----------------------------------------------
  
  AlbumList* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AlbumList& from);
  void MergeFrom(const AlbumList& from);
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
  
  // repeated .rec.util.cd.Album album = 1;
  inline int album_size() const;
  inline void clear_album();
  static const int kAlbumFieldNumber = 1;
  inline const ::rec::util::cd::Album& album(int index) const;
  inline ::rec::util::cd::Album* mutable_album(int index);
  inline ::rec::util::cd::Album* add_album();
  inline const ::google::protobuf::RepeatedPtrField< ::rec::util::cd::Album >&
      album() const;
  inline ::google::protobuf::RepeatedPtrField< ::rec::util::cd::Album >*
      mutable_album();
  
  // @@protoc_insertion_point(class_scope:rec.util.cd.AlbumList)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::google::protobuf::RepeatedPtrField< ::rec::util::cd::Album > album_;
  friend void  protobuf_AddDesc_rec_2futil_2fcd_2fAlbum_2eproto();
  friend void protobuf_AssignDesc_rec_2futil_2fcd_2fAlbum_2eproto();
  friend void protobuf_ShutdownFile_rec_2futil_2fcd_2fAlbum_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
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
  static AlbumList* default_instance_;
};
// ===================================================================


// ===================================================================

// Metadata

// optional string discid = 1;
inline bool Metadata::has_discid() const {
  return _has_bit(0);
}
inline void Metadata::clear_discid() {
  if (discid_ != &_default_discid_) {
    discid_->clear();
  }
  _clear_bit(0);
}
inline const ::std::string& Metadata::discid() const {
  return *discid_;
}
inline void Metadata::set_discid(const ::std::string& value) {
  _set_bit(0);
  if (discid_ == &_default_discid_) {
    discid_ = new ::std::string;
  }
  discid_->assign(value);
}
inline void Metadata::set_discid(const char* value) {
  _set_bit(0);
  if (discid_ == &_default_discid_) {
    discid_ = new ::std::string;
  }
  discid_->assign(value);
}
inline void Metadata::set_discid(const char* value, size_t size) {
  _set_bit(0);
  if (discid_ == &_default_discid_) {
    discid_ = new ::std::string;
  }
  discid_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Metadata::mutable_discid() {
  _set_bit(0);
  if (discid_ == &_default_discid_) {
    discid_ = new ::std::string;
  }
  return discid_;
}

// optional string year = 2;
inline bool Metadata::has_year() const {
  return _has_bit(1);
}
inline void Metadata::clear_year() {
  if (year_ != &_default_year_) {
    year_->clear();
  }
  _clear_bit(1);
}
inline const ::std::string& Metadata::year() const {
  return *year_;
}
inline void Metadata::set_year(const ::std::string& value) {
  _set_bit(1);
  if (year_ == &_default_year_) {
    year_ = new ::std::string;
  }
  year_->assign(value);
}
inline void Metadata::set_year(const char* value) {
  _set_bit(1);
  if (year_ == &_default_year_) {
    year_ = new ::std::string;
  }
  year_->assign(value);
}
inline void Metadata::set_year(const char* value, size_t size) {
  _set_bit(1);
  if (year_ == &_default_year_) {
    year_ = new ::std::string;
  }
  year_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Metadata::mutable_year() {
  _set_bit(1);
  if (year_ == &_default_year_) {
    year_ = new ::std::string;
  }
  return year_;
}

// optional string genre = 3;
inline bool Metadata::has_genre() const {
  return _has_bit(2);
}
inline void Metadata::clear_genre() {
  if (genre_ != &_default_genre_) {
    genre_->clear();
  }
  _clear_bit(2);
}
inline const ::std::string& Metadata::genre() const {
  return *genre_;
}
inline void Metadata::set_genre(const ::std::string& value) {
  _set_bit(2);
  if (genre_ == &_default_genre_) {
    genre_ = new ::std::string;
  }
  genre_->assign(value);
}
inline void Metadata::set_genre(const char* value) {
  _set_bit(2);
  if (genre_ == &_default_genre_) {
    genre_ = new ::std::string;
  }
  genre_->assign(value);
}
inline void Metadata::set_genre(const char* value, size_t size) {
  _set_bit(2);
  if (genre_ == &_default_genre_) {
    genre_ = new ::std::string;
  }
  genre_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Metadata::mutable_genre() {
  _set_bit(2);
  if (genre_ == &_default_genre_) {
    genre_ = new ::std::string;
  }
  return genre_;
}

// optional string track_title = 4;
inline bool Metadata::has_track_title() const {
  return _has_bit(3);
}
inline void Metadata::clear_track_title() {
  if (track_title_ != &_default_track_title_) {
    track_title_->clear();
  }
  _clear_bit(3);
}
inline const ::std::string& Metadata::track_title() const {
  return *track_title_;
}
inline void Metadata::set_track_title(const ::std::string& value) {
  _set_bit(3);
  if (track_title_ == &_default_track_title_) {
    track_title_ = new ::std::string;
  }
  track_title_->assign(value);
}
inline void Metadata::set_track_title(const char* value) {
  _set_bit(3);
  if (track_title_ == &_default_track_title_) {
    track_title_ = new ::std::string;
  }
  track_title_->assign(value);
}
inline void Metadata::set_track_title(const char* value, size_t size) {
  _set_bit(3);
  if (track_title_ == &_default_track_title_) {
    track_title_ = new ::std::string;
  }
  track_title_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Metadata::mutable_track_title() {
  _set_bit(3);
  if (track_title_ == &_default_track_title_) {
    track_title_ = new ::std::string;
  }
  return track_title_;
}

// optional string album_title = 5;
inline bool Metadata::has_album_title() const {
  return _has_bit(4);
}
inline void Metadata::clear_album_title() {
  if (album_title_ != &_default_album_title_) {
    album_title_->clear();
  }
  _clear_bit(4);
}
inline const ::std::string& Metadata::album_title() const {
  return *album_title_;
}
inline void Metadata::set_album_title(const ::std::string& value) {
  _set_bit(4);
  if (album_title_ == &_default_album_title_) {
    album_title_ = new ::std::string;
  }
  album_title_->assign(value);
}
inline void Metadata::set_album_title(const char* value) {
  _set_bit(4);
  if (album_title_ == &_default_album_title_) {
    album_title_ = new ::std::string;
  }
  album_title_->assign(value);
}
inline void Metadata::set_album_title(const char* value, size_t size) {
  _set_bit(4);
  if (album_title_ == &_default_album_title_) {
    album_title_ = new ::std::string;
  }
  album_title_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Metadata::mutable_album_title() {
  _set_bit(4);
  if (album_title_ == &_default_album_title_) {
    album_title_ = new ::std::string;
  }
  return album_title_;
}

// optional string artist = 6;
inline bool Metadata::has_artist() const {
  return _has_bit(5);
}
inline void Metadata::clear_artist() {
  if (artist_ != &_default_artist_) {
    artist_->clear();
  }
  _clear_bit(5);
}
inline const ::std::string& Metadata::artist() const {
  return *artist_;
}
inline void Metadata::set_artist(const ::std::string& value) {
  _set_bit(5);
  if (artist_ == &_default_artist_) {
    artist_ = new ::std::string;
  }
  artist_->assign(value);
}
inline void Metadata::set_artist(const char* value) {
  _set_bit(5);
  if (artist_ == &_default_artist_) {
    artist_ = new ::std::string;
  }
  artist_->assign(value);
}
inline void Metadata::set_artist(const char* value, size_t size) {
  _set_bit(5);
  if (artist_ == &_default_artist_) {
    artist_ = new ::std::string;
  }
  artist_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Metadata::mutable_artist() {
  _set_bit(5);
  if (artist_ == &_default_artist_) {
    artist_ = new ::std::string;
  }
  return artist_;
}

// optional string track_number = 7;
inline bool Metadata::has_track_number() const {
  return _has_bit(6);
}
inline void Metadata::clear_track_number() {
  if (track_number_ != &_default_track_number_) {
    track_number_->clear();
  }
  _clear_bit(6);
}
inline const ::std::string& Metadata::track_number() const {
  return *track_number_;
}
inline void Metadata::set_track_number(const ::std::string& value) {
  _set_bit(6);
  if (track_number_ == &_default_track_number_) {
    track_number_ = new ::std::string;
  }
  track_number_->assign(value);
}
inline void Metadata::set_track_number(const char* value) {
  _set_bit(6);
  if (track_number_ == &_default_track_number_) {
    track_number_ = new ::std::string;
  }
  track_number_->assign(value);
}
inline void Metadata::set_track_number(const char* value, size_t size) {
  _set_bit(6);
  if (track_number_ == &_default_track_number_) {
    track_number_ = new ::std::string;
  }
  track_number_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Metadata::mutable_track_number() {
  _set_bit(6);
  if (track_number_ == &_default_track_number_) {
    track_number_ = new ::std::string;
  }
  return track_number_;
}

// -------------------------------------------------------------------

// Album

// optional .rec.util.cd.Metadata album = 1;
inline bool Album::has_album() const {
  return _has_bit(0);
}
inline void Album::clear_album() {
  if (album_ != NULL) album_->::rec::util::cd::Metadata::Clear();
  _clear_bit(0);
}
inline const ::rec::util::cd::Metadata& Album::album() const {
  return album_ != NULL ? *album_ : *default_instance_->album_;
}
inline ::rec::util::cd::Metadata* Album::mutable_album() {
  _set_bit(0);
  if (album_ == NULL) album_ = new ::rec::util::cd::Metadata;
  return album_;
}

// repeated .rec.util.cd.Metadata track = 2;
inline int Album::track_size() const {
  return track_.size();
}
inline void Album::clear_track() {
  track_.Clear();
}
inline const ::rec::util::cd::Metadata& Album::track(int index) const {
  return track_.Get(index);
}
inline ::rec::util::cd::Metadata* Album::mutable_track(int index) {
  return track_.Mutable(index);
}
inline ::rec::util::cd::Metadata* Album::add_track() {
  return track_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::rec::util::cd::Metadata >&
Album::track() const {
  return track_;
}
inline ::google::protobuf::RepeatedPtrField< ::rec::util::cd::Metadata >*
Album::mutable_track() {
  return &track_;
}

// -------------------------------------------------------------------

// AlbumList

// repeated .rec.util.cd.Album album = 1;
inline int AlbumList::album_size() const {
  return album_.size();
}
inline void AlbumList::clear_album() {
  album_.Clear();
}
inline const ::rec::util::cd::Album& AlbumList::album(int index) const {
  return album_.Get(index);
}
inline ::rec::util::cd::Album* AlbumList::mutable_album(int index) {
  return album_.Mutable(index);
}
inline ::rec::util::cd::Album* AlbumList::add_album() {
  return album_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::rec::util::cd::Album >&
AlbumList::album() const {
  return album_;
}
inline ::google::protobuf::RepeatedPtrField< ::rec::util::cd::Album >*
AlbumList::mutable_album() {
  return &album_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace cd
}  // namespace util
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2futil_2fcd_2fAlbum_2eproto__INCLUDED
