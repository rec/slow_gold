#ifndef __JUCER_HEADER_AUDIODEMOTABCOMPONENT_AUDIODEMOTABCOMPONENT_ED272280__
#define __JUCER_HEADER_AUDIODEMOTABCOMPONENT_AUDIODEMOTABCOMPONENT_ED272280__

#include "rec/gui/RecentFiles.h"
#include "rec/slow/app/MainPage.h"
#include "rec/slow/app/AudioSetupPage.h"
#include "rec/audio/AudioDeviceSetup.h"
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

  MainPage* mainPage() { return &mainPage_; }

  void loadRecentFile(int menuItemId) {
    gui::RecentFiles recent = gui::getSortedRecentFiles();
    const VolumeFile& file = recent.file(menuItemId).file();
    persist::data<VolumeFile>()->set(file);
  }

  void cut() {
#if 0
    string s = yaml::write(prefs);
    SystemClipboard::copyTextToClipboard(s.c_str());
    DLOG(INFO) << s;
#endif
  }

  void paste() {
#if 0
    string s = SystemClipboard::getTextFromClipboard().toCString();
    DLOG(INFO) << s;
    yaml::read(s, &prefs);
#endif
  }

  virtual void paint(Graphics& g) { g.fillAll(Colours::white); }

  virtual void resized() {
    tabs_.setBounds(getLocalBounds());
  }

  AudioSetupPage* audioSetupPage() { return &audioSetupPage_; }

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
