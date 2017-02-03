#pragma once

#include <set>

#include "rec/app/LanguageListener.h"
#include "rec/base/SampleTime.h"
#include "rec/data/DataListener.h"
#include "rec/util/Disableable.h"
#include "rec/gui/DropTarget.h"
#include "rec/util/Listener.h"
#include "rec/util/Loading.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/Mode.pb.h"
#include "rec/util/StateListener.h"
#include "rec/util/range/Range.h"
#include "rec/widget/waveform/Cursor.pb.h"
#include "rec/widget/waveform/Viewport.pb.h"
#include "rec/widget/waveform/Waveform.pb.h"
#include "rec/widget/waveform/Zoom.pb.h"

namespace rec {
namespace widget {
namespace waveform {

class Cursor;
class CursorProto;
class WaveformPainter;
class WaveformModel;

struct MouseWheelEvent;
struct TimeAndMouseEvent;

typedef vector<Cursor*> CursorList;

// This handles waveform display of a juce::AudioThumbnail.
class Waveform : public Component,
                                  public Disableable,
                                  public SettableTooltipClient,
                                  public DataListener<Viewport>,
                                  public app::LanguageListener,
                                  public DataListener<Mode>,
                                  public DataListener<WaveformProto>,
                                  public StateListener<Loading>,
                                  public StateListener<const SampleRange&>,
                                  public Broadcaster<const MouseWheelEvent&>,
                                  public Broadcaster<const TimeAndMouseEvent&> {
  public:
    Waveform();
    virtual ~Waveform();
    void init();

    void mouseDoubleClick(const MouseEvent&) override;

    static const CursorProto& defaultTimeCursor();

    void setAudioThumbnail(juce::AudioThumbnail*);
    void resized() override;

    void paint(Graphics&) override;
    void operator()(const Mode&) override;
    void operator()(const WaveformProto&) override;
    void operator()(const Viewport& vp) override;
    void operator()(const SampleRange& range) override {
        repaintRange(range);
    }
    void operator()(Loading) override;

    void languageChanged() override;

    Cursor* timeCursor() { return timeCursor_; }

    const CursorList& getCursors() const { return cursors_; }
    CursorList* getCursorsMutable() { return &cursors_; }

    void mouseWheelMove(const MouseEvent& e, const juce::MouseWheelDetails&) override;
    CriticalSection* lock() { return &lock_;}
    int getCursorX(uint index) const;
    void setCursorText(int index, const String& text);
    void setIsDraggingCursor(bool d);
    bool isDraggingCursor() const;
    void repaintRange(const SampleRange&);
    void repaintRanges(const SampleRangeVector&);

    void adjustCursors(const LoopPointList& loopPoints,
                                          const SampleRangeVector& dirty);
    void setSelected(int index, bool selected);
    const WaveformModel& model() { return *model_; }
    void setLoading(bool loading);
    void setSampleRate(SampleRate);

    virtual void childrenChanged() override {
        // TODO.
    }

  private:
    void layout();
    void viewportChanged();

    void doClick(const juce::MouseEvent& e, int clickCount);
    void cursorDragged(int index, int x);

    CriticalSection lock_;
    juce::AudioThumbnail* thumbnail_;
    std::unique_ptr<WaveformModel> model_;
    std::unique_ptr<WaveformPainter> painter_;

    CursorList cursors_;
    Cursor* timeCursor_;

    juce::MouseCursor zoomCursor_;
    Loading loading_;

    DISALLOW_COPY_ASSIGN_AND_LEAKS(Waveform);

    friend class Cursor;
    friend class WaveformPainter;
};

typedef gui::DropTarget<Waveform> DropWaveform;

}  // namespace waveform
}  // namespace widget
}  // namespace rec
