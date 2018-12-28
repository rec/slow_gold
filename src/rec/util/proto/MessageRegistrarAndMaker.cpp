#include <unordered_map>

#include <google/protobuf/message.h>

#include "rec/util/file/VirtualFile.h"
#include "rec/util/proto/MessageRegistrarAndMaker.h"
#include "rec/util/proto/Proto.h"

using namespace rec::data;

namespace rec {
namespace util {

namespace {

struct Entry {
    Entry(const Message& m, bool c, AddressProto::Scope scope)
            : copyFrom_(c), scope_(scope) {
        message_.reset(m.New());
    }

    std::unique_ptr<Message> makeMessage() const {
        std::unique_ptr<Message> m(message_->New());
        if (copyFrom_)
            m->CopyFrom(*message_);
        return m;
    }

    std::unique_ptr<Message> message_;
    bool copyFrom_;
    AddressProto::Scope scope_;
};

}  // namespace


struct MessageRegistrarAndMaker::Impl {
    std::unordered_map<string, std::unique_ptr<Entry>> registry_;
};

MessageRegistrarAndMaker::MessageRegistrarAndMaker() : impl_(new Impl) {}
MessageRegistrarAndMaker::~MessageRegistrarAndMaker() {}

void MessageRegistrarAndMaker::registerInstance(
        const Message& m, bool copy, AddressProto::Scope scope) {
    const string& typeName = m.GetTypeName();
    DCHECK_LT(typeName.size(), file::MAX_FILENANE_LENGTH);
    if (impl_->registry_.count(typeName)) {
        LOG(DFATAL) << "Tried to register the same type twice: " << typeName;
        return;
    }
    impl_->registry_[typeName] = std::make_unique<Entry>(m, copy, scope);
}

std::unique_ptr<Message> MessageRegistrarAndMaker::makeMessage(const string& tn) const {
    try {
        return impl_->registry_.at(tn)->makeMessage();
    } catch (std::out_of_range&) {
        LOG(DFATAL) << "Couldn't find data type " << tn;
        return std::unique_ptr<Message>();
    }
}

AddressProto::Scope MessageRegistrarAndMaker::getScope(const string& tn) const {
    try {
        return impl_->registry_.at(tn)->scope_;
    } catch (std::out_of_range&) {
        LOG(DFATAL) << "Couldn't find data type " << tn;
        return AddressProto::FILE_SCOPE;
    }
}

}  // namespace util
}  // namespace rec
