#ifndef __REC_GUI_TREE_ROOT__
#define __REC_GUI_TREE_ROOT__

#include "rec/base/base.h"

namespace rec {
namespace gui {
namespace tree {

class Root : public juce::TreeViewItem {
 public:
  Root() { rereadRoots(); }

 private:
  void rereadRoots() {
    cdNames_(AudioCDBurner::findAvailableDevices(  }
   burners_.resize(cdNames_.size());
  for (int i = 0; i < burners_.size(); ++i) {
    burners_[i] = AudioCDBurner::openDevice(i);
    burners_[i]->addChangeListener(this);
    changeListenerCallback(burners_[i]);
  }


  AudioCDBurner* cd = (AudioCDBurner*) objectThatHasChanged;
  AudioCDBurner::DiskState state = cd->getDiskState();
  LOG(INFO) << CD_STATE_NAMES[state];

  if (state != AudioCDBurner::readOnlyDiskPresent)
    return;

  int i = 0;
  for (; i < burners_.size() && burners_[i] != cd; ++i);
  if (i == burners_.size())
    return;

  scoped_ptr<AudioCDReader> reader(AudioCDReader::createReaderForCD(i));
 virtual bool mightContainSubItems() { return true; }



  for (int i = 0; i < burners_.size(); ++i)
    delete burners_[i];

  burners_.clear();

 private:
  CriticalSection lock_;

  DISALLOW_COPY_AND_ASSIGN(Root);
};

}  // namespace tree
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_TREE_ROOT__
