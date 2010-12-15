#ifndef __JUCER_HEADER_AUDIODEMOTABCOMPONENT_AUDIODEMOTABCOMPONENT_ED272280__
#define __JUCER_HEADER_AUDIODEMOTABCOMPONENT_AUDIODEMOTABCOMPONENT_ED272280__

#include "rec/slow/Preferences.h"

#include "rec/slow/app/MainPageJ.h"
#include "rec/slow/app/AudioSetupPage.h"

namespace rec {
namespace slow {

class MainPageJ;

class MainPageComponent  : public Component {
 public:
  MainPageComponent() : tabs_(TabbedButtonBar::TabsAtTop),
                        mainPageJ_(deviceManager_),
                        audioSetupPage_(deviceManager_) {
    tabs_.setTabBarDepth (30);
    tabs_.addTab("File Playback", Colours::lightgrey, &mainPageJ_, false);
    tabs_.addTab("Audio Device Setup", Colours::lightgrey, &audioSetupPage_,
                 false);
    tabs_.setCurrentTabIndex(0);
    addAndMakeVisible(&tabbedComponent);

    setSize(600, 400);
  }

  ~MainPageComponent() {}

  void loadRecentFile(int menuItemId) {
    mainPageJ_.loadRecentFile(menuItemId);
  }

  void cut() { mainPageJ_.cut(); }
  void paste()  { mainPageJ_.paste(); }
  void paint(Graphics& g) { g.fillAll(Colours::white); }

  void resized() { tabs_.setBounds(getLocalBounds()); }

 private:
  TabbedComponent tabs_;
  AudioDeviceManager deviceManager_;
  AudioSetupPage audioSetupPage_;
  MainPageJ mainPage_;

  DISALLOW_COPY_AND_ASSIGN(MainPageComponent);
};

}  // namespace slow
}  // namespace rec

#endif   // __JUCER_HEADER_AUDIODEMOTABCOMPONENT_AUDIODEMOTABCOMPONENT_ED272280__
