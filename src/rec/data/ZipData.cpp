#include "rec/data/ZipData.h"

#include "rec/app/Files.h"
#include "rec/data/DataOps.h"
#include "rec/util/SystemStats.h"

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

File zipFileName(const String& name) {
  return File::getSpecialLocation(File::userDesktopDirectory).getChildFile(name);
}

void addFiles(const File& root, Builder* builder, int cmp = COMPRESSION_LEVEL) {
  int toFind = File::findFilesAndDirectories + File::ignoreHiddenFiles;
  DirectoryIterator it(root, true, "*", toFind);

  for (bool isDir; it.next(&isDir, NULL, NULL, NULL, NULL, NULL); ) {
    File f = it.getFile();
    if (!isDir && mustZip(f)) {
      builder->addFile(f, cmp, f.getRelativePathFrom(root));
    }
  }
}

File writeZipFile(const Builder& builder, const String& name) {
  File f = zipFileName(name);
  FileOutputStream output(f);
  if (builder.writeToStream(output, NULL))
    return f;

  LOG(ERROR) << "Couldn't write to " << str(f);
  return File::nonexistent;
}

File writeZipFile(const Builder& builder, const File& file) {
  File f = file.withFileExtension(".zip");
  FileOutputStream output(f);
  return builder.writeToStream(output, NULL) ? f : File::nonexistent;
}

}  // namespace

File zipData(const String& name) {
  return zipData(zipFileName(name));
}

File zipData(const File& file) {
  data::setGlobal(getSystemStats(), CANT_UNDO);
  Thread::sleep(1000);  // TODO: hack!

  Builder builder;
  addFiles(app::getAppDirectory(), &builder);
  return writeZipFile(builder, file);
}

bool unzipData(const File& file) {
  return ZipFile(file).uncompressTo(app::getAppDirectory(), true);
}

}  // namespace data
}  // namespace rec
