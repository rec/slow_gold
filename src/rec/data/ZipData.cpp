#include "rec/data/ZipData.h"
#include "rec/app/Files.h"

namespace rec {
namespace data {

using namespace juce;
typedef ZipFile::Builder Builder;

namespace {

const int COMPRESSION_LEVEL = 5;
const String TIME_FILE_FORMAT = "%Y%m%d-%H%M%S.zip";

bool mustZip(const File& f) {
  String ext = f.getFileExtension();
  return !(ext == ".stream" || ext == ".zip" || ext == ".gz");
}

File zipFileName() {
  return File::getSpecialLocation(File::userDesktopDirectory).
    getChildFile(Time::getCurrentTime().formatted(TIME_FILE_FORMAT));
}

}  // namespace

File zipData() {
  Builder builder;

  DirectoryIterator it(app::getAppDirectory(), true);
  bool isDirectory;
  while (it.next(&isDirectory, NULL, NULL, NULL, NULL, NULL)) {
    if (!isDirectory && mustZip(it.getFile()))
      builder.addFile(it.getFile(), COMPRESSION_LEVEL);
  }

  File f = zipFileName();
  FileOutputStream output(f);
  if (builder.writeToStream(output))
    return f;

  LOG(ERROR) << "Couldn't write to " << str(f);
  return File::nonexistent;
}

}  // namespace data
}  // namespace rec
