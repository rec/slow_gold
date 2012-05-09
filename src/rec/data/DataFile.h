#ifndef __REC_DATA_DATAFILE__
#define __REC_DATA_DATAFILE__

#include "rec/util/Listener.h"

namespace rec {
namespace data {

typedef const VirtualFile* DataFile;

typedef Listener<DataFile> DataFileListener;
typedef Broadcaster<DataFile> DataFileBroadcaster;


}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATAFILE__
