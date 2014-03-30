#include "rec/widget/waveform/Waveform.h"

#include "rec/util/StateListener.h"
#include "rec/gui/Dialog.h"
#include "rec/gui/Geometry.h"
#include "rec/slow/CurrentFile.h"
#include "rec/slow/Instance.h"
#include "rec/util/BinaryMacros.h"
#include "rec/util/Math.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/proto/Defaulter.h"
#include "rec/util/range/Range.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/widget/waveform/MouseWheelEvent.h"
#include "rec/widget/waveform/WaveformModel.h"
#include "rec/widget/waveform/WaveformPainter.h"

namespace rec {
namespace widget {
namespace waveform {

namespace {

const int64 SMALLEST_TIME_SAMPLES = 10000;  // ALSO!
const int ZOOM_CURSOR_X_HOTSPOT = 8;
const int ZOOM_CURSOR_Y_HOTSPOT = 8;
const int ZOOM_CURSOR_WIDTH = 24;
const int ZOOM_CURSOR_HEIGHT = 24;

static juce::Image getZoomCursor() {
  juce::Image img(
      juce::Image::ARGB, ZOOM_CURSOR_WIDTH, ZOOM_CURSOR_HEIGHT, false);
  Graphics g(img);
  ptr<Drawable> drawable(BINARY_DATA(ZoomInCursor_svg, Drawable));
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

Waveform::Waveform()
    : Component("WaveformComponent"),
      model_(new WaveformModel(this)),
      zoomCursor_(getZoomCursor(), ZOOM_CURSOR_X_HOTSPOT,
                  ZOOM_CURSOR_Y_HOTSPOT),
      loading_(NOT_LOADING) {
  setName("Waveform");

  setOpaque(true);
  setBufferedToImage(true);
}

void Waveform::languageChanged() {
  setTooltip(
      Trans("Waveform Window: "
            "You can drag files from your desktop or your music player here. "
            "If your mouse has a wheel, use it to zoom the waveform."));

  // Why do I need this - they should update on their own?
  for (CursorList::iterator i = cursors_.begin(); i != cursors_.end(); ++i)
    (*i)->languageChanged();
}

Waveform::~Waveform() {
  deleteAllChildren();
  #if 0
  DLOG(INFO) << "Deleting " << getNumChildComponents() << " components.";
  for (int i = getNumChildComponents() - 1; i >= 0 ; --i) {
    DLOG(INFO) << "deleting " << str(getChildComponent(i)->getName());
    delete getChildComponent(i);
  }
  #endif
}

void Waveform::setAudioThumbnail(juce::AudioThumbnail* t) {
  painter_->setAudioThumbnail(t);
}

void Waveform::operator()(Loading loading) {
  Lock l(lock_);
  loading_ = loading;
}

void Waveform::init() {
  painter_.reset(new WaveformPainter(this));
  timeCursor_ = makeTimeCursor(defaultTimeCursor(), this);
  StateBroadcaster::instance()->addListener<SampleTime>(timeCursor_);
}

const CursorProto& Waveform::defaultTimeCursor() {
  return timeDesc.get();
}

void Waveform::paint(Graphics& g) {
  Lock l(lock_);
  painter_->paint(g, model_->getTimeRange(), loading_);
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
  layout();
}

void Waveform::operator()(const Viewport& vp) {
  {
    Lock l(lock_);
    model_->setViewport(vp);
  }
  viewportChanged();
}

void Waveform::viewportChanged() {
  SampleRangeVector dirty;
  LoopPointList loopPoints;
  {
    Lock l(lock_);
    dirty = model_->getAndClearDirty();
    loopPoints = model_->viewport().loop_points();
  }

  layout();

  if (!model_->isDraggingCursor())
    adjustCursors(loopPoints, dirty);
  else if (!dirty.empty())
    repaintRanges(dirty);
}

void Waveform::adjustCursors(const LoopPointList& loopPoints,
                             const SampleRangeVector& dirty) {
  uint size = loopPoints.loop_point_size();
  for (uint i = 0; i < size; ++i) {
    SampleTime time = loopPoints.loop_point(i).time();
    Cursor* c;
    if (i < cursors_.size()) {
      c = cursors_[i];
    } else {
      c = makeCursor(*defaultDesc, this, i, time);
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

  repaintRanges(dirty);
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

void Waveform::mouseWheelMove(const MouseEvent& e,
                              const juce::MouseWheelDetails& wheel) {
  MouseWheelEvent we;
  we.event_ = &e;
  we.xIncrement_ = wheel.deltaX;
  we.yIncrement_ = wheel.deltaY;
  Broadcaster<const MouseWheelEvent&>::broadcast(we);
}

int Waveform::getCursorX(uint index) const {
  return (index < cursors_.size()) ? cursors_[index]->getX() : getWidth();
}

void Waveform::setCursorText(int index, const String& text) {
  Viewport viewport = DataListener<Viewport>::getDataValue();
  LoopPointList* lpl = viewport.mutable_loop_points();
  DCHECK_GE(index,  0);
  DCHECK_LT(index, lpl->loop_point_size());

  if (index < 0 || index >= lpl->loop_point_size())
    return;

  LoopPoint* loopPoint = lpl->mutable_loop_point(index);
  string t = str(text);
  if (loopPoint->name() != t) {
    loopPoint->set_name(str(text));
    DataListener<Viewport>::setProto(viewport);
  }
}

void Waveform::repaintRange(const SampleRange& r) {
  int x1 = model_->timeToX(r.begin_);
  if (x1 < getWidth()) {
    int x2 = model_->timeToX(r.end_);
    if (x2 >= 0) {
      x1 = std::max(0, x1);
      x2 = std::min(x2, getWidth());
      if (x1 < x2 && getHeight())
        repaint(x1, 0, x2 - x1, getHeight());
    }
  }
}

void Waveform::repaintRanges(const SampleRangeVector& b) {
  for (SampleRangeVector::const_iterator i = b.begin(); i != b.end(); ++i)
    repaintRange(*i);
}

void Waveform::setIsDraggingCursor(bool d) {
  Lock l(lock_);
  model_->setIsDraggingCursor(d);
}

void Waveform::setSelected(int index, bool selected) {
  Viewport viewport = DataListener<Viewport>::getDataValue();
  LoopPointList* lpl = viewport.mutable_loop_points();
  if (index < 0 || index >= lpl->loop_point_size()) {
    LOG(DFATAL) << "Bad index " << index << ", " << lpl->loop_point_size();
    return;
  }
  lpl->mutable_loop_point(index)->set_selected(selected);
  DataListener<Viewport>::setProto(viewport);
}

void Waveform::mouseDoubleClick(const MouseEvent&) {
  slow::Instance* instance = slow::getInstance();
  if (instance->empty())
    gui::dialog::openOneAudioFile(instance->currentFile_.get());
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
