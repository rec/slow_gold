#include "rec/widget/waveform/Waveform.h"

#include "rec/gui/audio/CommandBar.h"
#include "rec/gui/audio/ModeSelector.h"
#include "rec/gui/icon/ZoomInCursor.svg.h"
#include "rec/gui/Geometry.h"
#include "rec/util/Defaulter.h"
#include "rec/util/Math.h"
#include "rec/util/Range.h"
#include "rec/util/STL.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/widget/waveform/MouseWheelEvent.h"
#include "rec/widget/waveform/WaveformModel.h"
#include "rec/widget/waveform/WaveformPainter.h"

namespace rec {
namespace widget {
namespace waveform {

namespace {

using namespace rec::util::block;

const int64 SMALLEST_TIME_SAMPLES = 10000;  // ALSO!
const int ZOOM_CURSOR_X_HOTSPOT = 8;
const int ZOOM_CURSOR_Y_HOTSPOT = 8;
const int ZOOM_CURSOR_WIDTH = 24;
const int ZOOM_CURSOR_HEIGHT = 24;


static juce::Image getZoomCursor() {
  juce::Image img(juce::Image::ARGB, ZOOM_CURSOR_WIDTH, ZOOM_CURSOR_HEIGHT,
                  false);
  Graphics g(img);
  ptr<Drawable> drawable(gui::icon::ZoomInCursor::create());
  drawable->draw(g, 1.0f);
  return img;
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
    : Component("WaveformComponent"),
      model_(new WaveformModel),
      painter_(new WaveformPainter(this)),
      zoomCursor_(getZoomCursor(), ZOOM_CURSOR_X_HOTSPOT,
                  ZOOM_CURSOR_Y_HOTSPOT) {
  setName("Waveform");
  setTooltip("Waveform Window:"
             "You can drag files from your desktop or your music player here. "
             "If your mouse has a wheel, use it to zoom the waveform.");

  timeCursor_.reset(new Cursor(*timeCursor, this, 0, 0, true));
  timeCursor_->setTooltip("Playback Time Cursor: This follows the "
                          "current time during playback. You can also drag it "
                          "around to set the current playback time.");
  timeCursor_->startListening();
  setOpaque(true);
  setBufferedToImage(true);
}

Waveform::~Waveform() {
  stl::deletePointers(&cursors_);
}

void Waveform::setAudioThumbnail(juce::AudioThumbnail* t) {
  painter_->setAudioThumbnail(t);
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
  Lock l(lock_);
  painter_->paint(g, model_->getTimeRange());
}

void Waveform::resized() {
  Lock l(lock_);
  layout();
  model_->setWidth(getWidth());
}

bool Waveform::isDraggingCursor() const {
  Lock l(lock_);
  return model_->isDraggingCursor();
}

void Waveform::operator()(const WaveformProto& desc) {
  {
    Lock l(lock_);
    model_->setDescription(desc);
  }
  thread::callAsync(this, &Waveform::layout);
}

void Waveform::operator()(const LoopPointList& loopPoints) {
  Lock l(lock_);
  BlockSet dirty = model_->setLoopPoints(loopPoints);
  if (!model_->isDraggingCursor())
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
      c->setTooltip("Loop Point:  You can drag it around on the waveform, "
                    "or you can click on the label above and to the right "
                    "to edit its name.");
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
    model_->setZoom(zp);
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
    model_->layout(this);
  }
  repaint();
}

void Waveform::mouseWheelMove(const MouseEvent& e, float xIncrement, float yIncrement) {
  MouseWheelEvent we;
  we.event_ = &e;
  we.xIncrement_ = xIncrement;
  we.yIncrement_ = yIncrement;
  Broadcaster<const MouseWheelEvent&>::broadcast(we);
}

int Waveform::getCursorX(uint index) const {
  return (index < cursors_.size()) ? cursors_[index]->getX() : getWidth();
}

void Waveform::setCursorText(int index, const String& text) {
  LoopPointList lpl = DataListener<LoopPointList>::getProto();
  DCHECK_GE(index,  0);
  DCHECK_LT(index, lpl.loop_point_size());

  if (index < 0 || index >= lpl.loop_point_size())
    return;
  lpl.mutable_loop_point(index)->set_name(str(text));
  DataListener<LoopPointList>::setProto(lpl);
}

void Waveform::repaintBlock(Block b) {
  int x1 = model_->timeToX(b.first);
  if (x1 < getWidth()) {
    int x2 = model_->timeToX(b.second);
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
  model_->setIsDraggingCursor(d);
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
