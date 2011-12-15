#include "rec/data/DataMap.h"

#if 0

#include "rec/data/Data.h"
#include "rec/data/MessageMaker.h"
#include "rec/util/file/VirtualFile.pbh"
#include "rec/util/Stl.h"

namespace rec {
namespace data {

DataMap* getDataMap();
MessageMaker* getMessageMaker();

namespace {

DataMapImpl* getDataMapImpl() {
  static DataMapImpl map;
  return *map;
}

}  // namespace

MessageMaker* getMessageMaker() {
  return &getDataMapImpl()->messageMaker_;
}

DataMap* getDataMap() {
  static DataMapImpl map;
  return *map;
}

}  // namespace data
}  // namespace rec

#endif
