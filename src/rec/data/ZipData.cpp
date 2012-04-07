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

void addFiles(const File& root, Builder* builder, int cmp = COMPRESSION_LEVEL) {
  int toFind = File::findFilesAndDirectories + File::ignoreHiddenFiles;
  DirectoryIterator it(root, true, "*", toFind);

  for (bool isDir; it.next(&isDir, NULL, NULL, NULL, NULL, NULL); ) {
    File f = it.getFile();
    if (!isDir && mustZip(f))
      builder->addFile(f, cmp, f.getRelativePathFrom(root));
  }
}

File writeZipFile(const Builder& builder) {
  File f = zipFileName();
  FileOutputStream output(f);
  if (builder.writeToStream(output))
    return f;

  LOG(ERROR) << "Couldn't write to " << str(f);
  return File::nonexistent;
}

}  // namespace

File zipData() {
  Builder builder;
  addFiles(app::getAppDirectory(), &builder);
  return writeZipFile(builder);
}

}  // namespace data
}  // namespace rec
