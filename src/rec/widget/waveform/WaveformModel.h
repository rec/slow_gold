#ifndef __REC_WIDGET_WAVEFORM_WAVEFORMMODEL__
#define __REC_WIDGET_WAVEFORM_WAVEFORMMODEL__

#include "rec/util/LoopPoint.h"
#include "rec/util/block/Block.h"
#include "rec/widget/waveform/Zoom.pb.h"
#include "rec/widget/waveform/Waveform.pb.h"

namespace rec {
namespace widget {
namespace waveform {

class WaveformModel {
 public:
  WaveformModel() : length_(0), empty_(true), isDraggingCursor_(false) {}

  util::Range<Samples<44100> > getTimeRange() const;
  Samples<44100> xToTime(int x) const;
  double pixelsPerSample() const;
  int timeToX(Samples<44100> t) const;
  block::BlockSet setLoopPoints(const LoopPointList& loopPoints);

  bool isDraggingCursor() const { return isDraggingCursor_; }
  void setIsDraggingCursor(bool b) { isDraggingCursor_ = b; }
  void setWidth(int w) { width_ = w; }
  void setZoom(const ZoomProto&);
  bool isEmpty() const { return empty_; }
  const block::BlockSet& selection() const { return selection_; }
  Samples<44100> length() const { return length_; }

  void setDescription(const WaveformProto& d) { desc_ = d; }
  const WaveformProto& description() const { return desc_; }
  void layout(Component* waveform);

 private:
  Samples<44100> zoomEnd() const;

  Samples<44100> length_;
  block::BlockSet selection_;
  ZoomProto zoom_;
  bool empty_;
  bool isDraggingCursor_;
  int width_;
  WaveformProto desc_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(WaveformModel);
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM_WAVEFORMMODEL__
