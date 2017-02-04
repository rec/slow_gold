#include "rec/slow/callbacks/ExportFile.h"

#include "rec/audio/Audio.h"
#include "rec/audio/OutputSampleRate.h"
#include "rec/audio/AudioSettings.pb.h"
#include "rec/audio/format/Manager.h"
#include "rec/audio/source/Empty.h"
#include "rec/audio/source/Player.h"
#include "rec/audio/stretch/Stretch.h"
#include "rec/audio/stretch/Implementation.h"
#include "rec/audio/util/BufferFiller.h"
#include "rec/audio/util/BufferedReader.h"
#include "rec/base/ArraySize.h"
#include "rec/base/SampleRate.h"
#include "rec/base/Trans.h"
#include "rec/music/CreateMusicFileReader.h"
#include "rec/music/Metadata.h"
#include "rec/slow/CurrentFile.h"
#include "rec/slow/GuiSettings.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/Instance.h"
#include "rec/slow/SlowWindow.h"
#include "rec/util/Math.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/range/Fillable.h"
#include "rec/widget/waveform/Viewport.h"

TRAN(FILE_SAVE_FAILED, "Error During Save.");
TRAN(FILE_SAVE_FAILED_FULL, "There was an error saving your file %s.");
TRAN(FINISHING_LOADING, "Finishing loading audio from disk.");
TRAN(SAVING_FILE, "Saving File %s.");
TRAN(SELECT_SAVE_FILE, "Choose File To Save to");
TRAN(DOWN, "down");
TRAN(UP, "up");

TRAN(TRANSPOSE_ONE, "one semitone %s");
TRAN(TRANSPOSE_MANY, "%s %s semitones");
TRAN(BAD_SUFFIX, "The file extension must be .aiff, .aif, .flac, .ogg, "
                                                  ".wav or .wave.");
TRAN(CANT_OVERWRITE_SELF, "You cannot overwrite the current file.");

namespace rec {
namespace slow {
namespace {

using namespace juce;
using audio::AudioSettings;
using namespace rec::audio::stretch;
using namespace rec::widget::waveform;

const int COPY_UPDATE_SIZE = 2048;
const int COPY_BLOCK_SIZE = 2048;

String removeTrailingZeroes(const String& s) {
    String st = s;
    st = st.trimCharactersAtEnd("0");
    st = st.trimCharactersAtEnd(".");
    return st;
}

File getBaseFile(Instance* instance, const String& suffix,
                                  const GuiSettings& guiSettings,
                                  const AudioSettings& audioSettings) {
    File file;
    if (guiSettings.has_last_directory())
        file = str(guiSettings.last_directory());
    else
        file = File::getSpecialLocation(File::userMusicDirectory);

    String baseName = instance->window_->getName();
    const StretchParameters stretch = instance->player_->stretchy()->
        implementation()->stretch();
    double ts = 100.0 / audio::stretch::timeScale(stretch);

    if (!near(ts, 100.0, 0.05)) {
        int roundTs = static_cast<int>(ts);
        if (near(ts, roundTs, 0.05))
            baseName += String::formatted(" at %d", roundTs);
        else
            baseName += String::formatted(" at %.1f", ts);
    }

    double ps = audio::stretch::pitchSemitones(stretch);
    if (!near(ps, 0.0, 0.005)) {
        const Trans& sign = (ps > 0) ? t_UP : t_DOWN;
        ps = abs(ps);
        String num = removeTrailingZeroes(String::formatted("%.3f", ps));
        baseName += ", ";
        if (num == "1")
            baseName += String::formatted(t_TRANSPOSE_ONE, c_str(sign));
        else
            baseName += String::formatted(t_TRANSPOSE_MANY, c_str(sign), c_str(num));
    }

    baseName = File::createLegalFileName(baseName);
    return file.getChildFile(baseName).withFileExtension(suffix);
}

static const char* SUFFIXES[] = {".aiff", ".flac", ".ogg", ".wav", ".aif", ".wave"};

static bool isLegalSuffix(const String& suffix) {
    for (uint32 i = 0; i < arraysize(SUFFIXES); ++i) {
        if (suffix == SUFFIXES[i])
            return true;
    }
    return false;
}


File getExportFile(Instance* instance, audio::AudioSettings::FileType t) {
    LookAndFeel::getDefaultLookAndFeel().setUsingNativeAlertWindows(true);
    DCHECK(LookAndFeel::getDefaultLookAndFeel().isUsingNativeAlertWindows());

    if (instance->empty())
        return File::nonexistent;

    String suffix = SUFFIXES[t];
    File file;
    GuiSettings settings = data::getProto<GuiSettings>();
    audio::AudioSettings audioSettings = data::getProto<audio::AudioSettings>();

    File startFile(getBaseFile(instance, suffix, settings, audioSettings));
    VirtualFile vf = instance->file();
    File baseFile;
    if (vf.type() != VirtualFile::CD) {
        baseFile = file::toRealFile(vf);
        if (startFile == baseFile) {
            String p = startFile.getFileNameWithoutExtension();
            String s = startFile.getFileExtension();
            startFile = startFile.getParentDirectory().getNonexistentChildFile(p, s);
        }
    }

    while (true) {
        file = slow::browseForFile(t_SELECT_SAVE_FILE, startFile, slow::SAVE_FILE);

        if (file == File::nonexistent)
            return file;
        String newSuffix = file.getFileExtension();
        if (!isLegalSuffix(newSuffix)) {
            if (newSuffix == "" || newSuffix == ".")
                file = file.withFileExtension(suffix);
        }

        String error;
        if (!isLegalSuffix(file.getFileExtension()))
            error = t_BAD_SUFFIX;
        else if (file == baseFile)
            error = t_CANT_OVERWRITE_SELF;
        else
            break;

        AlertWindow::showMessageBox(AlertWindow::InfoIcon, error, error, t_OK);
    }

    settings.set_last_directory(str(file.getParentDirectory()));
    data::setProto(settings);

    return file;
}

class SaveThread : public ThreadWithProgressWindow {
  public:
    SaveThread(const String& name, Instance* i, const File& f, audio::Source* s,
                          const Viewport& viewport)
            : ThreadWithProgressWindow(name, true, true),
                instance_(i), file_(f), source_(s),
                viewport_(viewport),
                length_(viewport.loop_points().length()) {
    }
    virtual ~SaveThread() {}

    virtual void run() {
        const Fillable& buffer = *instance_->bufferFiller_->reader();

        setProgress(0.0);
        setStatusMessage(t_FINISHING_LOADING);
        while (!(threadShouldExit() || buffer.isFull())) {
            setProgress(buffer.filledPercent());
            Thread::sleep(100);
        }
        if (writeFile())
            setFile();
    }

    bool writeFile() {
        std::unique_ptr<AudioFormatWriter> writer(audio::format::createWriter(file_));
        if (!writer) {
            LOG(DFATAL) << "Couldn't create AudioFormatWriter for " << str(file_);
            return false;
        }

        setProgress(0.0);
        source_->prepareToPlay(COPY_BLOCK_SIZE, audio::getOutputSampleRate());
        String name = file_.getFileName();
        setStatusMessage(String::formatted(t_SAVING_FILE, c_str(name)));

        for (SampleTime toCopy = length_;
                  !threadShouldExit() && toCopy > 0; toCopy -= COPY_UPDATE_SIZE) {
            if (writer->writeFromAudioSource(*source_,
                                                                                std::min(COPY_UPDATE_SIZE, toCopy.toInt()),
                                                                                COPY_BLOCK_SIZE)) {
                setProgress(1.0 - toCopy / (1.0 * length_));
            } else {
                writer.reset();
                file_.deleteFile();
                String error = String::formatted(t_FILE_SAVE_FAILED_FULL,
                                                                                  c_str(file_.getFileName()));
                AlertWindow::showMessageBox(AlertWindow::InfoIcon, t_FILE_SAVE_FAILED,
                                                                        error, t_OK);
                return false;
            }
        }
        return true;
    }

    void setFile() {
        const VirtualFile vf = instance_->currentFile_.get()->file();
        const VirtualFile newVf = file::toVirtualFile(file_);
        data::setProto(data::getProto<music::Metadata>(vf), newVf, data::CANT_UNDO);
        data::setProto(viewport_, newVf, data::CANT_UNDO);
        instance_->currentFile_->setFile(file_);
    }

  private:
    Instance* const instance_;
    const File file_;
    std::unique_ptr<audio::Source> source_;
    const Viewport viewport_;
    const SampleTime length_;

    DISALLOW_COPY_ASSIGN_AND_LEAKS(SaveThread)
};


Viewport getViewport(Instance* instance, bool useSelection,
                                          SampleTime len) {
    Viewport original = data::getProto<Viewport>(instance->currentFile_->file());
    Viewport viewport;
    if (useSelection) {
        SampleTime start = 0;
        const LoopPointList& lpl = original.loop_points();
        uint32 size = lpl.loop_point_size();
        for (uint32 i = 0; i < size; ++i) {
            const LoopPoint& loop = lpl.loop_point(i);
            if (loop.selected()) {
                if (!start)
                    *viewport.mutable_zoom() = original.zoom();
                LoopPoint* newLoop = viewport.mutable_loop_points()->add_loop_point();
                newLoop->set_selected(true);
                newLoop->set_time(start);
                newLoop->set_name(loop.name());
                if (i < (size - 1))
                    start += (lpl.loop_point(i + 1).time() - loop.time());
                else
                    start = len;
            }
        }
    }

    if (!viewport.loop_points().loop_point_size())
        viewport = original;

    viewport.mutable_loop_points()->set_length(len);
    viewport.mutable_zoom()->set_begin(0);
    viewport.mutable_zoom()->set_end(len);
    return viewport;
}

void doExportFile(Instance* instance, bool useSelection) {
    using namespace juce;
    std::unique_ptr<audio::Source> s(instance->makeSource());
    s.reset(instance->player_->makeSourceCopy(s.release(), useSelection));

    SampleTime len = useSelection ?
        instance->player_->getSelectionLength() : SampleTime(s->getTotalLength());

    SampleTime minSize = SampleTime(audio::MINIMUM_FILE_SIZE,
                                                                    instance->getSourceSampleRate());
    if (len <= minSize) {
        // TODO: this code duplicates code in CreateMusicFileReader.
        String e = String::formatted(t_FILE_TOO_SMALL_FULL, "save");
        AlertWindow::showMessageBox(AlertWindow::InfoIcon, t_FILE_TOO_SMALL,
                                                                e, t_OK);
        return;
    }

    AudioSettings::FileType t = data::getProto<AudioSettings>().
        file_type_for_save();
    File file = getExportFile(instance, t);
    if (file != File::nonexistent) {
        String name = String::formatted(t_SAVING_FILE, c_str(file.getFileName()));
        Viewport viewport = getViewport(instance, useSelection, len);
        SaveThread(name, instance, file, s.release(), viewport).runThread();
    }
}

}  // namespace


void exportFile() {
    doExportFile(getInstance(), false);
}

void exportFileSelection() {
    doExportFile(getInstance(), true);
}

}  // namespace slow
}  // namespace rec
