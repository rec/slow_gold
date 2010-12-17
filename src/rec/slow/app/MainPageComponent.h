#ifndef __JUCER_HEADER_AUDIODEMOTABCOMPONENT_AUDIODEMOTABCOMPONENT_ED272280__
#define __JUCER_HEADER_AUDIODEMOTABCOMPONENT_AUDIODEMOTABCOMPONENT_ED272280__

#include <glog/logging.h>

#include "rec/gui/RecentFiles.h"
#include "rec/slow/Preferences.h"
#include "rec/slow/app/MainPage.h"
#include "rec/slow/app/AudioSetupPage.h"
#include "rec/data/yaml/Yaml.h"

namespace rec {
namespace slow {

class MainPageComponent  : public Component {
 public:
  MainPageComponent() : tabs_(TabbedButtonBar::TabsAtTop),
                        mainPage_(deviceManager_),
                        audioSetupPage_(deviceManager_),
                        deviceListener_(&deviceManager_) {
    tabs_.setTabBarDepth (30);
    tabs_.addTab("File Playback", Colours::lightgrey, &mainPage_, false);
    tabs_.addTab("Audio Device Setup", Colours::lightgrey, &audioSetupPage_,
                 false);
    tabs_.setCurrentTabIndex(0);
    addAndMakeVisible(&tabs_);
    setSize(600, 400);
  }

  ~MainPageComponent() {}

  void loadRecentFile(int menuItemId) {
    gui::RecentFiles recent = gui::getSortedRecentFiles();
    const VolumeFile& file = recent.file(menuItemId - 1).file();
    slow::prefs()->setter()->set("track", "file", file);
  }

  void cut() {
    proto::Preferences prefs = slow::getPreferences();
    string s = yaml::write(prefs);
    SystemClipboard::copyTextToClipboard(s.c_str());
    DLOG(INFO) << s;
  }

  void paste() {
    string s = SystemClipboard::getTextFromClipboard().toCString();
    DLOG(INFO) << s;
    proto::Preferences prefs;
    yaml::read(s, &prefs);
  }

  void paint(Graphics& g) { g.fillAll(Colours::white); }

  void resized() { tabs_.setBounds(getLocalBounds()); }

 private:
  TabbedComponent tabs_;
  AudioDeviceManager deviceManager_;
  MainPage mainPage_;
  AudioSetupPage audioSetupPage_;
  persist::AudioDeviceSetupListener deviceListener_;

  DISALLOW_COPY_AND_ASSIGN(MainPageComponent);
};

}  // namespace slow
}  // namespace rec

#endif   // __JUCER_HEADER_AUDIODEMOTABCOMPONENT_AUDIODEMOTABCOMPONENT_ED272280__
