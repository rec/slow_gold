#ifndef __REC_GUI_DROPTARGET__
#define __REC_GUI_DROPTARGET__

#include "rec/util/file/Util.h"
#include "rec/util/file/VolumeFile.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace gui {

class DropTarget : public listener::Broadcaster<const VolumeFile&>,
                   public FileDragAndDropTarget,
                   public Component {
 public:
  DropTarget(const String& name = String::empty) : Component(name), draggingOver_(false) {}
  virtual ~DropTarget() {}

  virtual bool isInterestedInFileDrag(const StringArray& files) {
    return (files.size() == 1 && file::isAudio(files[0]));
  }

  virtual void fileDragEnter(const StringArray& files, int x, int y) {
    setDraggingOver(isInterestedInFileDrag(files));
  }

  virtual void fileDragExit(const StringArray& files) {
    setDraggingOver(false);
  }

  virtual void filesDropped(const StringArray& files, int x, int y) {
    setDraggingOver(false);
    if (isInterestedInFileDrag(files)) {
      for (int i = 0; i < files.size(); ++i)
        broadcast(file::toVolumeFile(File(files[i])));
    }
  }

  virtual void paint(Graphics& g) {}
  virtual void paintOverChildren(Graphics& g) {
    if (draggingOver_) {
      g.setColour(juce::Colours::greenyellow);
      g.drawRect(getLocalBounds(), 2);
    }
  }

  virtual void resized() {
    for (int i = 0; i < getNumChildComponents(); ++i)
      getChildComponent(i)->setBounds(getLocalBounds());
  }

  void repaint() { Component::repaint(); }

 protected:
  void setDraggingOver(bool d) {
  	DLOG(INFO) << "Dragging! " << d;
    if (d != draggingOver_) {
      draggingOver_ = d;
      thread::callAsync(this, &DropTarget::repaint);
    }
  }

  bool draggingOver_;

 private:
  DISALLOW_COPY_AND_ASSIGN(DropTarget);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_DROPTARGET__
