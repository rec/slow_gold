#include "rec/widget/waveform/Waveform.h"

#include "rec/gui/audio/CommandBar.h"
#include "rec/gui/audio/ModeSelector.h"
#include "rec/gui/icon/ZoomMode.svg.h"
#include "rec/util/Defaulter.h"
#include "rec/util/FormatTime.h"
#include "rec/util/Math.h"
#include "rec/util/Range.h"
#include "rec/util/STL.h"
#include "rec/util/block/Difference.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/widget/waveform/MouseWheelEvent.h"
#include "rec/widget/waveform/Zoom.h"

using namespace rec::util::block;

namespace rec {
namespace widget {
namespace waveform {

namespace {

static const int GRID_TEXT_WIDTH = 50;
static const int GRID_TEXT_HEIGHT = 9;
static const int GRID_TEXT_PAD = 4;
static const int CURSOR_LABEL_HEIGHT = 20;
static const int MODE_SELECTOR_OFFSET = 5;
static const int COMMAND_BAR_OFFSET = -2;

static const int64 SMALLEST_TIME_SAMPLES = 10000;
static const int ZOOM_CURSOR_X_HOTSPOT = 8;
static const int ZOOM_CURSOR_Y_HOTSPOT = 8;
static const int ZOOM_CURSOR_WIDTH = 24;
static const int ZOOM_CURSOR_HEIGHT = 24;


static juce::Image* getZoomCursor() {
  ptr<juce::Image> img(new juce::Image(juce::Image::RGB, ZOOM_CURSOR_WIDTH,
                                       ZOOM_CURSOR_HEIGHT, false));
  Graphics g(*img);
  ptr<Drawable> drawable(gui::icon::ZoomMode::create());
  drawable->draw(g, 1.0f);
  return img.transfer();
}

Def<CursorProto> timeDesc(
"widget {colors {color: {name: \"red\"}}}\n"
"line {thickness: 2.0}"
);

Def<CursorProto> defaultDesc(
"widget {colors {color: {name: \"yellow\"}}}\n"
"line {thickness: 2.0}"
);

}  // namespace

Waveform::Waveform(MenuBarModel* m, const CursorProto* timeCursor)
    : length_(0),
      thumbnail_(NULL),
      empty_(true),
      isDraggingCursor_(false),
      helpScreenUp_(false),
      zoomCursor_(*ptr<juce::Image>(getZoomCursor()), ZOOM_CURSOR_X_HOTSPOT,
                  ZOOM_CURSOR_Y_HOTSPOT) {
  setName("Waveform");
  setTooltip("This is the waveform window, which shows your current track. "
             "You can drag files from your desktop or your music player here. "
             "If your mouse has a wheel, use it to zoom the waveform."
             "The four mode buttons on the top right control how clicks work. ");

  timeCursor_.reset(new Cursor(*timeCursor, this, 0, 0, true));
  timeCursor_->setTooltip("This is the playback time cursor - it follows the "
                          "current time during playback or you can drag it "
                          "around to set the current playback time.");
  timeCursor_->startListening();
  gui::clear(&dirty_);
}

Waveform::~Waveform() {
  stl::deletePointers(&cursors_);
}

void Waveform::internalRepaint(int x, int y, int width, int height) {
  Lock l(lock_);
  juce::Rectangle<int> r(std::max(x, 0), std::max(y, 0), width, height);
  gui::addInto(r, &dirty_);
  dirty_.setWidth(std::min(getWidth() - dirty_.getX(), dirty_.getWidth()));
  dirty_.setHeight(std::min(getHeight() - dirty_.getY(), dirty_.getHeight()));

  if (width * height)
    Component::internalRepaint(x, y, width, height);
}

void Waveform::startListening() {
  DataListener<LoopPointList>::startListening();
  DataListener<ZoomProto>::startListening();

  GlobalDataListener<Mode>::startListening();
  GlobalDataListener<WaveformProto>::startListening();
}

const CursorProto& Waveform::defaultTimeCursor() {
  return timeDesc.get();
}

void Waveform::paint(Graphics& g) {
  {
    Lock l(lock_);
    if (!helpScreenUp_) {
      juce::Rectangle<int> clip = g.getClipBounds().getIntersection(dirty_);
      bool hasClip = clip.getWidth() * clip.getHeight();
      if (hasClip) {
        g.reduceClipRegion(dirty_);
        gui::clear(&dirty_);
      } else {
        gui::clear(&dirty_);
        return;
      }
    }

    Painter p(desc_.widget(), &g);

    if (empty_) {
      g.setFont(14.0f);
      g.drawFittedText("Drop a file here or double-click to open a new file",
                       0, 0, getWidth(), getHeight(), juce::Justification::centred, 0);
    } else {
      Range<Samples<44100> > range = getTimeRange();
      drawWaveform(p, range);
      drawGrid(g, range);
    }
  }
}

void Waveform::drawWaveform(Painter& p, const Range<Samples<44100> >& range) {
  BlockSet::iterator i = selection_.begin();
  Block r;
  r.first = Samples<44100>(range.begin_);
  r.second = Samples<44100>(range.end_);
  const juce::Rectangle<int>& bounds = getLocalBounds();
  int channels = thumbnail_->getNumChannels();

  while (getSize(r) > 0) {
    for (; i != selection_.end() && i->second <= r.first; ++i);
    bool selected = (i != selection_.end() && r.first >= i->first);
    Block draw = r;
    if (selected)
      draw.second = i->second;

    else if (i != selection_.end())
      draw.second = i->first;

    int x1 = timeToX(Samples<44100>(draw.first));
    int x2 = timeToX(Samples<44100>(draw.second));

    juce::Rectangle<int> b(x1, bounds.getY(), x2 - x1, bounds.getHeight());

    double first = static_cast<double>(draw.first) / 44100.0;
    double second = static_cast<double>(draw.second) / 44100.0;
    if (desc_.parallel_waveforms() ||
        desc_.layout() == WaveformProto::PARALLEL) {
      for (int i = 0; i < channels; ++i) {
        p.setColor(selected ? i + 1 : i + 1 + channels);
        thumbnail_->drawChannel(*p.graphics(), b, first, second, i, 1.0f);
      }
    } else {
      p.setColor(2 + (!selected) * 2);
      thumbnail_->drawChannels(*p.graphics(), b, first, second, 1.0f);
    }
    r.first = draw.second;
  }
}

int Waveform::timeToX(Samples<44100> t) const {
  return static_cast<int>((t - getTimeRange().begin_) * pixelsPerSample());
}

Samples<44100> Waveform::xToTime(int x) const {
  return static_cast<int64>(getTimeRange().begin_.get() + x / pixelsPerSample());
}

double Waveform::pixelsPerSample() const {
  return getWidth() / (1.0 * getTimeRange().size());
}

void Waveform::operator()(const WaveformProto& proto) {
  {
    Lock l(lock_);
    desc_ = proto;
  }
  thread::callAsync(this, &Waveform::layout);
}

void Waveform::operator()(const LoopPointList& loopPoints) {
  BlockSet newSelection = rec::audio::getTimeSelection(loopPoints);
  bool isDraggingCursor;
  BlockSet oldSelection;
  {
    Lock l(lock_);
    oldSelection = selection_;
    selection_ = newSelection;
    length_ = loopPoints.length();
    constrainZoom(&zoom_, length_);
    empty_ = !loopPoints.has_length();
    isDraggingCursor = isDraggingCursor_;
  }

  BlockSet dirty = symmetricDifference(oldSelection, newSelection);
  if (!isDraggingCursor_)
    thread::callAsync(this, &Waveform::adjustCursors, loopPoints, dirty);
  else if (!dirty.empty())
    thread::callAsync(this, &Waveform::repaintBlocks, dirty);
}

void Waveform::adjustCursors(LoopPointList loopPoints, BlockSet dirty) {
  uint size = loopPoints.loop_point_size();
  for (uint i = 0; i < size; ++i) {
    Samples<44100> time = loopPoints.loop_point(i).time();
    Cursor* c;
    if (i < cursors_.size()) {
      c = cursors_[i];
    } else {
      c = new Cursor(*defaultDesc, this, time, i, false);
      c->setTooltip("This is a loop point in your track.  You can drag it "
                    "around on the waveform, or you can click on the label "
                    "above and to the right to edit its name.");
      c->startListening();
      cursors_.push_back(c);
    }
    c->setTime(time);
    c->setSelected(loopPoints.loop_point(i).selected());
    c->setCaption(str(loopPoints.loop_point(i).name()));
  }

  while (cursors_.size() > size) {
    Cursor* c = cursors_.back();
    removeChildComponent(c);
    removeChildComponent(c->getCaption());
    delete c;
    cursors_.pop_back();
  }

  repaintBlocks(dirty);
}

void Waveform::operator()(const ZoomProto& zp) {
  {
    Lock l(lock_);
    zoom_ = zp;
    constrainZoom(&zoom_, length_);
  }

  thread::callAsync(this, &Waveform::layout);
}

static const juce::MouseCursor::StandardCursorType getCursor(const Mode& mode) {
  using juce::MouseCursor;
  switch (mode.click()) {
    case Mode::DRAG:              return MouseCursor::DraggingHandCursor;
    case Mode::DRAW_LOOP_POINTS:  return MouseCursor::IBeamCursor;
    case Mode::SET_TIME:          return MouseCursor::PointingHandCursor;
    case Mode::TOGGLE_SELECTION:  return MouseCursor::CrosshairCursor;
    case Mode::ZOOM_IN:
    case Mode::ZOOM_OUT:          return MouseCursor::UpDownLeftRightResizeCursor;
    default:                      return MouseCursor::NormalCursor;
  }
}

void Waveform::operator()(const Mode& mode) {
  Lock l(lock_);
  if (mode.click() == Mode::ZOOM_IN)
    setMouseCursor(zoomCursor_);
  else
    setMouseCursor(getCursor(mode));
}

void Waveform::layout() {
  {
    Lock l(lock_);
    for (CursorList::iterator i = cursors_.begin(); i != cursors_.end(); ++i)
      (*i)->layout();

    using namespace rec::gui::audio;
    CommandBar* cb = NULL;
    ModeSelector* ms = NULL;
    for (int i = 0; i < getNumChildComponents(); ++i) {
      Component* c = getChildComponent(i);
      if (!cb)
        cb = dynamic_cast<CommandBar*>(c);
      if (!ms)
        ms = dynamic_cast<ModeSelector*>(c);
    }

    if (ms) {
      int dy = MODE_SELECTOR_OFFSET;
      if (desc_.show_times_at_top() == desc_.modes_at_top())
        dy += GRID_TEXT_HEIGHT;
      if (desc_.show_labels_at_top() == desc_.modes_at_top())
        dy += CURSOR_LABEL_HEIGHT;
      int x = desc_.modes_at_left() ? 0 : (getWidth() - ms->getWidth());
      int y = desc_.modes_at_top() ? dy : (getHeight() - ms->getHeight() - dy);
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

      int x = desc_.command_bar_at_left() ? 0 : (getWidth() - cb->getWidth());
      int y = desc_.command_bar_at_top() ? dy : (getHeight() - cb->getHeight()) - dy;
      cb->setTopLeftPosition(x, y);
    } else {
      LOG(DFATAL) << "No command bar";
    }
  }
  repaint();
}

Samples<44100> Waveform::zoomEnd() const {
  Lock l(lock_);
  return zoom_.has_end() ? Samples<44100>(zoom_.end()) : Samples<44100>(length_);
}

Range<Samples<44100> > Waveform::getTimeRange() const {
  Lock l(lock_);
  Range<Samples<44100> > r;
  if (zoom_.zoom_to_selection() && !selection_.empty()) {
    r.begin_ = Samples<44100>(selection_.begin()->first);
    r.end_ = Samples<44100>(selection_.rbegin()->second);
    if (r.end_ == 0)
      r.end_ = zoomEnd();

    r.begin_ = std::max<Samples<44100> >(r.begin_, 0);
    r.end_ = std::min<Samples<44100> >(r.end_, zoomEnd());
  } else {
    r.begin_ = zoom_.begin();
    r.end_= zoomEnd();
  }

  if (r.size() < SMALLEST_TIME_SAMPLES) {
  	Samples<44100> len = SMALLEST_TIME_SAMPLES;
    if (thumbnail_)
     len = static_cast<int64>(thumbnail_->getTotalLength() * 44100);
    r = Range<Samples<44100> >(0, len);
  }

  return r;
}

void Waveform::mouseWheelMove(const MouseEvent& e, float xIncrement, float yIncrement) {
  MouseWheelEvent we;
  we.event_ = &e;
  we.xIncrement_ = xIncrement;
  we.yIncrement_ = yIncrement;
  Broadcaster<const MouseWheelEvent&>::broadcast(we);
}

void Waveform::drawGrid(Graphics& g, const Range<Samples<44100> >& r) {
  Samples<44100> width = r.size();
  if (width < SMALLEST_TIME_SAMPLES) {
    LOG_FIRST_N(ERROR, 4) << "Nothing on screen! " << width;
    return;
  }
  double seconds = pow(10.0, floor(log10(width / 44100.0)));
  double samples = seconds * 44100.0;

  int b = static_cast<int>(ceil(r.begin_ / samples));
  int e = static_cast<int>(r.end_ / samples);
  int diff = e - b;

  if (diff <= 2)
    samples /= 2.0;
  else if (diff > 15)
    samples *= 5.0;

  if (samples > 10.0 * 44100)
    samples *= 1.2;

  b = static_cast<int>(ceil(r.begin_ / samples));
  e = static_cast<int>(floor(r.end_ / samples));

  int h = getHeight();
  int decimals = 0;
  if (samples < 0.01 * 44100.0)
    decimals = 3;
  else if (samples < 0.1 * 44100.0)
    decimals = 2;
  else if (samples < 1 * 44100.0)
    decimals = 1;

  g.setFont(10);

  for (int i = b - 1; i <= e + 1; ++i) {
    Samples<44100> time = static_cast<int64>(i * samples);
    int x = timeToX(time);

    if (desc_.show_grid()) {
      g.setColour(juce::Colours::lightgreen.withAlpha(0.8f));
      g.drawVerticalLine(x, 0, h);
    }

    String s = formatTime(time, length_, false, false, decimals);
    g.setColour(juce::Colours::black);
    g.drawText(s, i ? x - GRID_TEXT_WIDTH / 2 : x - GRID_TEXT_WIDTH / 4,
               desc_.show_times_at_top() ? GRID_TEXT_PAD :
               (h - GRID_TEXT_PAD - GRID_TEXT_HEIGHT),
               GRID_TEXT_WIDTH,
               GRID_TEXT_HEIGHT,
               Justification::centred, true);
  }
}

int Waveform::getCursorX(uint index) const {
  return (index < cursors_.size()) ? cursors_[index]->getX() : getWidth();
}

void Waveform::setCursorText(int index, const String& text) {
  LoopPointList lpl = DataListener<LoopPointList>::getProto();
  DCHECK_GE(index,  0);
  DCHECK_LT(index,  lpl.loop_point_size());
  if (index < 0 || index >= lpl.loop_point_size())
    return;
  lpl.mutable_loop_point(index)->set_name(str(text));
  DataListener<LoopPointList>::setProto(lpl);
}

void Waveform::repaintBlock(Block b) {
  int x1 = timeToX(b.first);
  if (x1 < getWidth()) {
    int x2 = timeToX(b.second);
    if (x2 >= 0) {
      x1 = std::max(0, x1);
      x2 = std::min(x2, getWidth());
      if (x1 < x2 && getHeight())
        repaint(x1, 0, x2 - x1, getHeight());
    }
  }
}

void Waveform::repaintBlocks(const BlockSet& b) {
  for (BlockSet::const_iterator i = b.begin(); i != b.end(); ++i)
    repaintBlock(*i);
}

void Waveform::setIsDraggingCursor(bool d) {
  Lock l(lock_);
  isDraggingCursor_ = d;
}

void Waveform::setSelected(int index, bool selected) {
  LoopPointList lpl = DataListener<LoopPointList>::getProto();
  if (index < 0 || index >= lpl.loop_point_size()) {
    LOG(DFATAL) << "Bad index " << index << ", " << lpl.loop_point_size();
    return;
  }
  lpl.mutable_loop_point(index)->set_selected(selected);
  DataListener<LoopPointList>::setProto(lpl);
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
