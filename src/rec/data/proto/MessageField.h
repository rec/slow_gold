#pragma once

#include "rec/base/base.h"

namespace google {
namespace protobuf {

class FieldDescriptor;

}  // namespace protobuf
}  // namespace google

using google::protobuf::FieldDescriptor;

namespace rec {
namespace data {

class Operation;
class ValueProto;

struct MessageField {
    enum Type {
        INDEXED = 0,
        REPEATED = 1,
        SINGLE = 2,
        TYPE_COUNT = 3,
    };

    Message* message_;
    const FieldDescriptor* field_;

    int32 index_;
    Type type_;
    int32 repeatCount_;
    string error_;

    JUCE_LEAK_DETECTOR(MessageField);
};

bool hasValue(const MessageField& mf);
int getSize(const MessageField& mf);

}  // namespace data
}  // namespace rec

