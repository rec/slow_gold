#include <algorithm>

#include "rec/util/file/VirtualFile.h"
#include "rec/app/Files.h"
#include "rec/base/Arraysize.h"
#include "rec/util/proto/Reverse.h"
#include "rec/util/file/FileType.h"
#include "rec/util/file/Util.h"

using namespace juce;
using namespace google;

namespace rec {
namespace util {
namespace file {

namespace {

#if JUCE_WINDOWS
String removeColon(const String& p) {
    return p.endsWithChar(':') ? p.dropLastCharacters(1) : p;
}
#endif

bool readVolumeName(const File& f, VirtualFile* vf, bool failOnError) {
    auto last = vf->path_size() - 1;
    auto& root = vf->path(last);

#if JUCE_WINDOWS
    auto s = f.getFileName();
    if (!s.length()) {
        if (failOnError)
            LOG(DFATAL) << "Empty " << vf->ShortDebugString();
        return false;
    }
    vf->set_volume_name(str(removeColon(s)));

#elif JUCE_MAC
    DCHECK(!f.getFileName().length());
    if (last && root == "Volumes") {
        vf->set_volume_name(vf->path(last - 1));
        vf->mutable_path()->RemoveLast();
        vf->mutable_path()->RemoveLast();
    }
#endif
    return true;
}

static File getRoot(const VirtualFile& vf) {
    auto type = vf.type();
    if (type != VirtualFile::VOLUME)
        return getFileTypeDirectory(type);
    auto volume = str(vf.volume_name());

#if JUCE_WINDOWS
    return File(volume + ":\\");
#elif JUCE_MAC
    return File("/" + (volume.length() ? ("Volumes/" + volume) : String::empty));
#endif
}

}  // namespace

const File getShadowDirectory(const VirtualFile& vf) {
    auto name = str(VirtualFile::Type_Name(vf.type())).toLowerCase();
    auto f = app::getAppFile(name);
    if (vf.volume_name().size())
        f = f.getChildFile(str(vf.volume_name()));

    auto len = f.getFullPathName().length();
    for (int i = 0; i < vf.path_size(); ++i)
        len += (vf.path(i).size() + 1);  // Include one for the path separator.

    // Skip path entries until we're short enough.
    int i = 0;
    static int MAX_LEN = static_cast<int>(MAX_SHADOW_DIRECTORY_LENGTH);
    for (; len > MAX_LEN && i < vf.path_size(); ++i)
        len -= (vf.path(i).size() + 1);

    for (; i < vf.path_size(); ++i)
        f = f.getChildFile(str(vf.path(i)));

    return f;
}

const VirtualFile toVirtualFile(const File& file, bool useSpecial,
                                bool failOnError) {
    auto type = useSpecial ? getFileType(file) : VirtualFile::VOLUME;
    auto isAbsolutePath = (type == VirtualFile::VOLUME);
    auto parent = isAbsolutePath ? File() : getFileTypeDirectory(type);

    VirtualFile vf;
    vf.set_type(type);

    auto f = file;
    for (auto g = f; f != parent && f != (g = g.getParentDirectory()); f = g)
        vf.add_path(str(f.getFileName()));

    if (isAbsolutePath) {
        if (not readVolumeName(f, &vf, failOnError))
            return {};
    }

    reverseProto(vf.mutable_path());
    return vf;
}

const File toRealFile(const VirtualFile& vf) {
    File f = getRoot(vf);
    for (int i = 0; i < vf.path_size(); ++i)
        f = f.getChildFile(str(vf.path(i)));

    return f;
}

}  // namespace file
}  // namespace util
}  // namespace rec
