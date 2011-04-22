#ifndef __REC_GUI_DROPTARGET__
#define __REC_GUI_DROPTARGET__

#include "rec/util/file/Util.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace gui {

struct NullInterface {};

template <typename Parent,
          typename Init = String,
          typename Interface = FileDragAndDropTarget>
class DropTarget : public Interface, public Parent {
 public:
  DropTarget(const Init& init) : Parent(init), draggingOver_(false) {}
  virtual ~DropTarget() {}

  virtual bool isInterestedInFileDrag(const StringArray& files) {
    return (files.size() == 1 && file::isAudio(files[0]));
  }

  virtual void fileDragEnter(const StringArray& files, int, int) {
    setDraggingOver(isInterestedInFileDrag(files));
  }

  virtual void fileDragExit(const StringArray&) {
    setDraggingOver(false);
  }

  virtual void filesDropped(const StringArray& files, int, int) {
    setDraggingOver(false);
    if (isInterestedInFileDrag(files))
      broadcaster_.broadcast(file::toVirtualFileList(files));
  }

  virtual void paintOverChildren(Graphics& g) {
    if (draggingOver_) {
      g.setColour(juce::Colours::greenyellow);
      g.drawRect(this->getLocalBounds(), 2);
    }
  }

  void repaint() { Parent::repaint(); }
  bool draggingOver() const { return draggingOver_; }

  Broadcaster<const VirtualFileList&>* dropBroadcaster() { return &broadcaster_; }

 private:
  void setDraggingOver(bool d) {
    if (d != draggingOver_) {
      draggingOver_ = d;
      thread::callAsync(this, &DropTarget::repaint);
    }
  }

  listener::Broadcaster<const VirtualFileList&> broadcaster_;
  bool draggingOver_;

 private:
  DISALLOW_COPY_AND_ASSIGN(DropTarget);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_DROPTARGET__
