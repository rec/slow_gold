#ifndef __REC_WIDGET_WAVEFORM_WAVEFORMMODEL__
#define __REC_WIDGET_WAVEFORM_WAVEFORMMODEL__

#include "rec/util/LoopPoint.h"
#include "rec/util/block/Block.h"
#include "rec/util/range/Range.h"
#include "rec/widget/waveform/Viewport.pb.h"
#include "rec/widget/waveform/Waveform.pb.h"

namespace rec {
namespace widget {
namespace waveform {

class WaveformModel {
 public:
  WaveformModel() : isDraggingCursor_(false) {}

  util::Range<SampleTime > getTimeRange() const;
  SampleTime xToTime(int x) const;
  double pixelsPerSample() const;
  int timeToX(SampleTime t) const;

  bool isDraggingCursor() const { return isDraggingCursor_; }
  void setIsDraggingCursor(bool b) { isDraggingCursor_ = b; }
  void setWidth(int w) { width_ = w; }

  // Return true if we need to layout the Waveform.
  bool setViewport(const Viewport&);
  bool isEmpty() const { return !length(); }
  const block::BlockSet getAndClearDirty();
  SampleTime length() const { return viewport_.loop_points().length(); }
  const Viewport& viewport() const { return viewport_; }

  void setDescription(const WaveformProto& d) { desc_ = d; }
  const WaveformProto& description() const { return desc_; }
  void layout(Component* waveform);
  const SampleRangeVector selection(bool isSelected) const;

 private:

  SampleTime zoomEnd() const;

  block::BlockSet selection_;
  block::BlockSet dirty_;
  Viewport viewport_;
  bool isDraggingCursor_;
  int width_;
  WaveformProto desc_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(WaveformModel);
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM_WAVEFORMMODEL__
