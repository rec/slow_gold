#include "rec/widget/waveform/WaveformModel.h"

#include "rec/util/block/Difference.h"
#include "rec/widget/waveform/Zoom.h"

namespace rec {
namespace widget {
namespace waveform {

using namespace rec::util::block;

namespace {

const int64 SMALLEST_TIME_SAMPLES = 10000;  // ALSO!

}  // namespace

Range<Samples<44100> > WaveformModel::getTimeRange() const {
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

  if (r.size() < SMALLEST_TIME_SAMPLES)
    r = Range<Samples<44100> >(0, length_);

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

BlockSet WaveformModel::setLoopPoints(const LoopPointList& loopPoints) {
  BlockSet oldSelection, newSelection = rec::audio::getTimeSelection(loopPoints);

  oldSelection = selection_;
  selection_ = newSelection;
  length_ = loopPoints.length();
  if (length_)
    constrainZoom(&zoom_, length_);
  empty_ = !loopPoints.has_length();

  return symmetricDifference(oldSelection, newSelection);
}

Samples<44100> WaveformModel::zoomEnd() const {
  return zoom_.has_end() ? Samples<44100>(zoom_.end()) : Samples<44100>(length_);
}

void WaveformModel::setZoom(const ZoomProto& zoom) {
  zoom_ = zoom;
  if (length_)
    constrainZoom(&zoom_, length_);
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
