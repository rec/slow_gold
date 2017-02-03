#pragma once

#include "rec/base/base.h"

namespace rec {
namespace data {

class Data;

class DataMaker {
 public:
  DataMaker() {}
  virtual ~DataMaker() {}

  virtual Data* makeData(Message*, const File&, bool isEmpty,
                         const string& key) const = 0;
};

}  // namespace data
}  // namespace rec

