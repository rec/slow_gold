#include "rec/widget/waveform/Waveform.h"

#include "rec/util/Defaulter.h"
#include "rec/util/Range.h"
#include "rec/util/Math.h"
#include "rec/util/FormatTime.h"
#include "rec/util/STL.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/widget/waveform/MouseWheelEvent.h"

namespace rec {
namespace widget {
namespace waveform {

namespace {

static const int64 SMALLEST_TIME_SAMPLES = 10000;

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
    : gui::component::Focusable<Component>(m),
      length_(0),
      thumbnail_(NULL),
      empty_(true),
      isDraggingCursor_(false) {
  setName("Waveform");
  timeCursor_.reset(new Cursor(*timeCursor, this, 0, -1, true));

  setWantsKeyboardFocus(true);
}

Waveform::~Waveform() {
  stl::deletePointers(&cursors_);
}

const CursorProto& Waveform::defaultTimeCursor() {
  return timeDesc.get();
}

void Waveform::paint(Graphics& g) {
  {
    Painter p(desc_.widget(), &g);
    Lock l(lock_);

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
  paintFocus(g);
}

void Waveform::drawWaveform(Painter& p, const Range<Samples<44100> >& range) {
  block::BlockSet::iterator i = selection_.begin();
  block::Block r;
  r.first = Samples<44100>(range.begin_);
  r.second = Samples<44100>(range.end_);
  const juce::Rectangle<int>& bounds = getLocalBounds();
  int channels = thumbnail_->getNumChannels();

  while (block::getSize(r) > 0) {
    for (; i != selection_.end() && i->second <= r.first; ++i);
    bool selected = (i != selection_.end() && r.first >= i->first);
    block::Block draw = r;
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

void Waveform::onDataChange(const WaveformProto& proto) {
  {
    Lock l(lock_);
    desc_ = proto;
  }
  resized();
}

void Waveform::onDataChange(const LoopPointList& loopPoints) {
  bool repaint;
  {
    Lock l(lock_);
    block::BlockSet oldSelection = selection_;
    selection_ = audio::getTimeSelection(loopPoints);
    repaint = (block::compare(selection_, oldSelection) != 0);
    length_ = Samples<44100>(loopPoints.length());
    empty_ = !loopPoints.has_length();
    if (isDraggingCursor_)
      return;
  }

  thread::callAsync(this, &Waveform::adjustCursors, loopPoints, repaint);
}

void Waveform::adjustCursors(const LoopPointList& loopPoints, bool mustRepaint) {
  MessageManagerLock l;
  uint size = loopPoints.loop_point_size();
  for (uint i = 0; i < size; ++i) {
    Samples<44100> time = loopPoints.loop_point(i).time();
    Cursor* c;
    if (i < cursors_.size()) {
      c = cursors_[i];
    } else {
      c = new Cursor(*defaultDesc, this, time, i, false);
      cursors_.push_back(c);
    }
    c->setTime(time);
    c->setCaption(str(loopPoints.loop_point(i).name()));
  }

  while (cursors_.size() > size) {
    delete cursors_.back();
    cursors_.pop_back();
  }

  if (mustRepaint)
    repaint();
}

void Waveform::onDataChange(const ZoomProto& zp) {
  {
    Lock l(lock_);
    zoom_ = zp;
  }

  resized();
}

static const juce::MouseCursor::StandardCursorType getCursor(const Mode& mode) {
  using juce::MouseCursor;
  switch (mode.click()) {
    case Mode::DRAG:              return MouseCursor::DraggingHandCursor;
    case Mode::DRAW_LOOP_POINTS:  return MouseCursor::IBeamCursor;
    case Mode::SET_TIME:          return MouseCursor::CrosshairCursor;
    case Mode::TOGGLE_SELECTION:  return MouseCursor::PointingHandCursor;
    case Mode::ZOOM_IN:
    case Mode::ZOOM_OUT:          return MouseCursor::UpDownLeftRightResizeCursor;
    default:                      return MouseCursor::NormalCursor;
  }
}

void Waveform::onDataChange(const Mode& mode) {
  Lock l(lock_);
  setMouseCursor(getCursor(mode));
}

void Waveform::resized() {
  MessageManagerLock l;
  {
    Lock l(lock_);
    for (CursorList::iterator i = cursors_.begin(); i != cursors_.end(); ++i)
      (*i)->layout();
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

    // r.begin_ -= desc_.selection_frame_in_seconds();
    // r.end_ += desc_.selection_frame_in_seconds();

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
    LOG_FIRST_N(ERROR, 4) << "Nothing on screen!";
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
    static const int WIDTH = 50;
    static const int HEIGHT = 10;
    static const int PAD = 4;
    g.setColour(juce::Colours::black);
    g.drawText(s, i ? x - WIDTH / 2 : x - WIDTH / 4, h - PAD - HEIGHT, WIDTH, HEIGHT,
               Justification::centred, true);
  }
}

int Waveform::getCursorX(uint index) const {
  return (index < cursors_.size()) ? cursors_[index]->getX() : getWidth();
}

void Waveform::setCursorText(int index, const String& text) {
  LoopPointList lpl = DataListener<LoopPointList>::data()->get();
  DCHECK_GE(index,  0);
  DCHECK_LT(index,  lpl.loop_point_size());
  if (index < 0 || index >= lpl.loop_point_size())
    return;
  lpl.mutable_loop_point(index)->set_name(str(text));
  DataListener<LoopPointList>::setProto(lpl);
}

void Waveform::repaintBlock(Samples<44100> begin, Samples<44100> end) {
  repaint(timeToX(begin), 0, timeToX(end), getHeight());
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
