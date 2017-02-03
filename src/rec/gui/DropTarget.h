#pragma once

#include "rec/gui/DropFiles.h"
#include "rec/util/file/Util.h"
#include "rec/util/file/VirtualFileList.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/StateListener.h"

namespace rec {
namespace gui {

struct NullInterface {};

template <typename Parent, class Interface = FileDragAndDropTarget>
class DropTarget : public Interface, public Parent {
 public:
  DropTarget() : draggingOver_(false) {}
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
      broadcastState<const VirtualFileList&>(file::toVirtualFileList(files));
  }

  virtual void paintOverChildren(Graphics& g) {
    if (draggingOver_) {
      g.setColour(juce::Colours::greenyellow);
      g.drawRect(this->getLocalBounds(), 2);
    }
  }

  void repaint() { Parent::repaint(); }
  bool draggingOver() const { return draggingOver_; }

 private:
  void setDraggingOver(bool d) {
    if (d != draggingOver_) {
      draggingOver_ = d;
      repaint();
    }
  }

  bool draggingOver_;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(DropTarget);
};

}  // namespace gui
}  // namespace rec

