// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rec/data/proto/TestData.proto

#ifndef PROTOBUF_rec_2fdata_2fproto_2fTestData_2eproto__INCLUDED
#define PROTOBUF_rec_2fdata_2fproto_2fTestData_2eproto__INCLUDED

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
namespace proto {
namespace test {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rec_2fdata_2fproto_2fTestData_2eproto();
void protobuf_AssignDesc_rec_2fdata_2fproto_2fTestData_2eproto();
void protobuf_ShutdownFile_rec_2fdata_2fproto_2fTestData_2eproto();

class TestData1;
class TestData2;
class TestData3;

// ===================================================================

class TestData1 : public ::google::protobuf::Message {
 public:
  TestData1();
  virtual ~TestData1();
  
  TestData1(const TestData1& from);
  
  inline TestData1& operator=(const TestData1& from) {
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
  static const TestData1& default_instance();
  
  void Swap(TestData1* other);
  
  // implements Message ----------------------------------------------
  
  TestData1* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TestData1& from);
  void MergeFrom(const TestData1& from);
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
  
  // repeated uint32 test = 1;
  inline int test_size() const;
  inline void clear_test();
  static const int kTestFieldNumber = 1;
  inline ::google::protobuf::uint32 test(int index) const;
  inline void set_test(int index, ::google::protobuf::uint32 value);
  inline void add_test(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      test() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_test();
  
  // optional string test_string = 2;
  inline bool has_test_string() const;
  inline void clear_test_string();
  static const int kTestStringFieldNumber = 2;
  inline const ::std::string& test_string() const;
  inline void set_test_string(const ::std::string& value);
  inline void set_test_string(const char* value);
  inline void set_test_string(const char* value, size_t size);
  inline ::std::string* mutable_test_string();
  
  // @@protoc_insertion_point(class_scope:rec.proto.test.TestData1)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > test_;
  ::std::string* test_string_;
  static const ::std::string _default_test_string_;
  friend void  protobuf_AddDesc_rec_2fdata_2fproto_2fTestData_2eproto();
  friend void protobuf_AssignDesc_rec_2fdata_2fproto_2fTestData_2eproto();
  friend void protobuf_ShutdownFile_rec_2fdata_2fproto_2fTestData_2eproto();
  
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
  static TestData1* default_instance_;
};
// -------------------------------------------------------------------

class TestData2 : public ::google::protobuf::Message {
 public:
  TestData2();
  virtual ~TestData2();
  
  TestData2(const TestData2& from);
  
  inline TestData2& operator=(const TestData2& from) {
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
  static const TestData2& default_instance();
  
  void Swap(TestData2* other);
  
  // implements Message ----------------------------------------------
  
  TestData2* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TestData2& from);
  void MergeFrom(const TestData2& from);
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
  
  // repeated .rec.proto.test.TestData1 test1 = 5;
  inline int test1_size() const;
  inline void clear_test1();
  static const int kTest1FieldNumber = 5;
  inline const ::rec::proto::test::TestData1& test1(int index) const;
  inline ::rec::proto::test::TestData1* mutable_test1(int index);
  inline ::rec::proto::test::TestData1* add_test1();
  inline const ::google::protobuf::RepeatedPtrField< ::rec::proto::test::TestData1 >&
      test1() const;
  inline ::google::protobuf::RepeatedPtrField< ::rec::proto::test::TestData1 >*
      mutable_test1();
  
  // optional uint32 test_uint = 6;
  inline bool has_test_uint() const;
  inline void clear_test_uint();
  static const int kTestUintFieldNumber = 6;
  inline ::google::protobuf::uint32 test_uint() const;
  inline void set_test_uint(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:rec.proto.test.TestData2)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::google::protobuf::RepeatedPtrField< ::rec::proto::test::TestData1 > test1_;
  ::google::protobuf::uint32 test_uint_;
  friend void  protobuf_AddDesc_rec_2fdata_2fproto_2fTestData_2eproto();
  friend void protobuf_AssignDesc_rec_2fdata_2fproto_2fTestData_2eproto();
  friend void protobuf_ShutdownFile_rec_2fdata_2fproto_2fTestData_2eproto();
  
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
  static TestData2* default_instance_;
};
// -------------------------------------------------------------------

class TestData3 : public ::google::protobuf::Message {
 public:
  TestData3();
  virtual ~TestData3();
  
  TestData3(const TestData3& from);
  
  inline TestData3& operator=(const TestData3& from) {
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
  static const TestData3& default_instance();
  
  void Swap(TestData3* other);
  
  // implements Message ----------------------------------------------
  
  TestData3* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TestData3& from);
  void MergeFrom(const TestData3& from);
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
  
  // optional double test_double = 7;
  inline bool has_test_double() const;
  inline void clear_test_double();
  static const int kTestDoubleFieldNumber = 7;
  inline double test_double() const;
  inline void set_test_double(double value);
  
  // optional .rec.proto.test.TestData2 test2 = 8;
  inline bool has_test2() const;
  inline void clear_test2();
  static const int kTest2FieldNumber = 8;
  inline const ::rec::proto::test::TestData2& test2() const;
  inline ::rec::proto::test::TestData2* mutable_test2();
  
  // @@protoc_insertion_point(class_scope:rec.proto.test.TestData3)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  double test_double_;
  ::rec::proto::test::TestData2* test2_;
  friend void  protobuf_AddDesc_rec_2fdata_2fproto_2fTestData_2eproto();
  friend void protobuf_AssignDesc_rec_2fdata_2fproto_2fTestData_2eproto();
  friend void protobuf_ShutdownFile_rec_2fdata_2fproto_2fTestData_2eproto();
  
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
  static TestData3* default_instance_;
};
// ===================================================================


// ===================================================================

// TestData1

// repeated uint32 test = 1;
inline int TestData1::test_size() const {
  return test_.size();
}
inline void TestData1::clear_test() {
  test_.Clear();
}
inline ::google::protobuf::uint32 TestData1::test(int index) const {
  return test_.Get(index);
}
inline void TestData1::set_test(int index, ::google::protobuf::uint32 value) {
  test_.Set(index, value);
}
inline void TestData1::add_test(::google::protobuf::uint32 value) {
  test_.Add(value);
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
TestData1::test() const {
  return test_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
TestData1::mutable_test() {
  return &test_;
}

// optional string test_string = 2;
inline bool TestData1::has_test_string() const {
  return _has_bit(1);
}
inline void TestData1::clear_test_string() {
  if (test_string_ != &_default_test_string_) {
    test_string_->clear();
  }
  _clear_bit(1);
}
inline const ::std::string& TestData1::test_string() const {
  return *test_string_;
}
inline void TestData1::set_test_string(const ::std::string& value) {
  _set_bit(1);
  if (test_string_ == &_default_test_string_) {
    test_string_ = new ::std::string;
  }
  test_string_->assign(value);
}
inline void TestData1::set_test_string(const char* value) {
  _set_bit(1);
  if (test_string_ == &_default_test_string_) {
    test_string_ = new ::std::string;
  }
  test_string_->assign(value);
}
inline void TestData1::set_test_string(const char* value, size_t size) {
  _set_bit(1);
  if (test_string_ == &_default_test_string_) {
    test_string_ = new ::std::string;
  }
  test_string_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* TestData1::mutable_test_string() {
  _set_bit(1);
  if (test_string_ == &_default_test_string_) {
    test_string_ = new ::std::string;
  }
  return test_string_;
}

// -------------------------------------------------------------------

// TestData2

// repeated .rec.proto.test.TestData1 test1 = 5;
inline int TestData2::test1_size() const {
  return test1_.size();
}
inline void TestData2::clear_test1() {
  test1_.Clear();
}
inline const ::rec::proto::test::TestData1& TestData2::test1(int index) const {
  return test1_.Get(index);
}
inline ::rec::proto::test::TestData1* TestData2::mutable_test1(int index) {
  return test1_.Mutable(index);
}
inline ::rec::proto::test::TestData1* TestData2::add_test1() {
  return test1_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::rec::proto::test::TestData1 >&
TestData2::test1() const {
  return test1_;
}
inline ::google::protobuf::RepeatedPtrField< ::rec::proto::test::TestData1 >*
TestData2::mutable_test1() {
  return &test1_;
}

// optional uint32 test_uint = 6;
inline bool TestData2::has_test_uint() const {
  return _has_bit(1);
}
inline void TestData2::clear_test_uint() {
  test_uint_ = 0u;
  _clear_bit(1);
}
inline ::google::protobuf::uint32 TestData2::test_uint() const {
  return test_uint_;
}
inline void TestData2::set_test_uint(::google::protobuf::uint32 value) {
  _set_bit(1);
  test_uint_ = value;
}

// -------------------------------------------------------------------

// TestData3

// optional double test_double = 7;
inline bool TestData3::has_test_double() const {
  return _has_bit(0);
}
inline void TestData3::clear_test_double() {
  test_double_ = 0;
  _clear_bit(0);
}
inline double TestData3::test_double() const {
  return test_double_;
}
inline void TestData3::set_test_double(double value) {
  _set_bit(0);
  test_double_ = value;
}

// optional .rec.proto.test.TestData2 test2 = 8;
inline bool TestData3::has_test2() const {
  return _has_bit(1);
}
inline void TestData3::clear_test2() {
  if (test2_ != NULL) test2_->::rec::proto::test::TestData2::Clear();
  _clear_bit(1);
}
inline const ::rec::proto::test::TestData2& TestData3::test2() const {
  return test2_ != NULL ? *test2_ : *default_instance_->test2_;
}
inline ::rec::proto::test::TestData2* TestData3::mutable_test2() {
  _set_bit(1);
  if (test2_ == NULL) test2_ = new ::rec::proto::test::TestData2;
  return test2_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace test
}  // namespace proto
}  // namespace rec

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rec_2fdata_2fproto_2fTestData_2eproto__INCLUDED
