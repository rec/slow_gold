#include "rec/widget/waveform/WaveformModel.h"

#include "rec/data/proto/Equals.h"
#include "rec/gui/audio/CommandBar.h"
#include "rec/gui/audio/ModeSelector.h"
#include "rec/util/block/Difference.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/widget/waveform/Zoom.h"

namespace rec {
namespace widget {
namespace waveform {

using namespace rec::util::block;

namespace {

// Skin

const int64 SMALLEST_TIME_SAMPLES = 10000;  // ALSO!
const int GRID_TEXT_HEIGHT = 9;  // ALSO IN WaveformPainter!
const int MODE_SELECTOR_OFFSET = 5;
const int COMMAND_BAR_OFFSET = -2;
const int CURSOR_LABEL_HEIGHT = 20;

}  // namespace

Range<Samples<44100> > WaveformModel::getTimeRange() const {
  const Zoom& zoom = viewport_.zoom();
  Range<Samples<44100> > r;
  if (zoom.zoom_to_selection() && !selection_.empty()) {
    r.begin_ = Samples<44100>(selection_.begin()->first);
    r.end_ = Samples<44100>(selection_.rbegin()->second);
    if (r.end_ == 0)
      r.end_ = zoomEnd();

    r.begin_ = std::max<Samples<44100> >(r.begin_, 0);
    r.end_ = std::min<Samples<44100> >(r.end_, zoomEnd());
  } else {
    r.begin_ = zoom.begin();
    r.end_= zoomEnd();
  }

  if (r.size() < SMALLEST_TIME_SAMPLES)
    r = Range<Samples<44100> >(0, viewport_.loop_points().length());

  if (r.size() < SMALLEST_TIME_SAMPLES)
    r.end_ = SMALLEST_TIME_SAMPLES;

  return r;
}

int WaveformModel::timeToX(Samples<44100> t) const {
  return static_cast<int>((t - getTimeRange().begin_) * pixelsPerSample());
}

Samples<44100> WaveformModel::xToTime(int x) const {
  return static_cast<int64>(getTimeRange().begin_.get() + x / pixelsPerSample());
}

double WaveformModel::pixelsPerSample() const {
  return width_ / (1.0 * getTimeRange().size());
}

Samples<44100> WaveformModel::zoomEnd() const {
  const Zoom& zoom = viewport_.zoom();
  // DCHECK(zoom.has_end());  // TODO
  return zoom.has_end() ? Samples<44100>(zoom.end()) : Samples<44100>(length());
}

bool WaveformModel::setViewport(const Viewport& vp) {
  bool changed = !data::equals(vp.zoom(), viewport_.zoom());
  viewport_ = vp;
  BlockSet newSelection = rec::audio::getTimeSelection(vp.loop_points());
  dirty_ = symmetricDifference(selection_, newSelection);

  selection_ = newSelection;
  int64 len = length();
  if (len)
    constrainZoom(viewport_.mutable_zoom(), len);
  return changed;
}

void WaveformModel::layout(Component* waveform) {
  using namespace rec::gui::audio;

  CommandBar* cb = NULL;
  ModeSelector* ms = NULL;
  int w = waveform->getWidth(), h = waveform->getHeight();

  for (int i = 0; i < waveform->getNumChildComponents(); ++i) {
    Component* c = waveform->getChildComponent(i);
    if (Cursor* cursor = dynamic_cast<Cursor*>(c)) {
      cursor->layout();
    } else {
      if (!cb)
        cb = dynamic_cast<CommandBar*>(c);
      if (!ms)
        ms = dynamic_cast<ModeSelector*>(c);
    }
  }

  if (ms) {
    int dy = MODE_SELECTOR_OFFSET;
    if (desc_.show_times_at_top() == desc_.modes_at_top())
      dy += GRID_TEXT_HEIGHT;
    if (desc_.show_labels_at_top() == desc_.modes_at_top())
      dy += CURSOR_LABEL_HEIGHT;
    int x = desc_.modes_at_left() ? 0 : (w - ms->getWidth());
    int y = desc_.modes_at_top() ? dy : (h - ms->getHeight() - dy);
    ms->setTopLeftPosition(x, y);
  } else {
    LOG(DFATAL) << "No mode selector";
  }

  if (cb) {
    int dy = COMMAND_BAR_OFFSET;
    if (desc_.show_times_at_top() == desc_.command_bar_at_top())
      dy += GRID_TEXT_HEIGHT;
    if (desc_.show_labels_at_top() == desc_.command_bar_at_top())
      dy += CURSOR_LABEL_HEIGHT;
    if (ms && desc_.modes_at_top() == desc_.command_bar_at_top() &&
        desc_.modes_at_left() == desc_.command_bar_at_left()) {
      dy += (ms->getHeight() + MODE_SELECTOR_OFFSET);
    }

    int x = desc_.command_bar_at_left() ? 0 : (w - cb->getWidth());
    int y = desc_.command_bar_at_top() ? dy : (h - cb->getHeight()) - dy;
    cb->setTopLeftPosition(x, y);
  } else {
    LOG(DFATAL) << "No command bar";
  }
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
