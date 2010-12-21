#ifndef __REC_WINDOW
#define __REC_WINDOW

#include "rec/slow/app/ComponentContainer.h"

using namespace juce;

namespace rec {
namespace slow {

class RecWindow  : public juce::DocumentWindow {
 public:
  RecWindow();
  ~RecWindow();

  void closeButtonPressed();

 private:
  ApplicationCommandManager commandManager_;
  ComponentContainer container_;
  // TODO: Component* taskbarIcon used to be here.

  DISALLOW_COPY_AND_ASSIGN(RecWindow);
};

}  // namespace slow
}  // namespace rec

#endif   // __REC_WINDOW
