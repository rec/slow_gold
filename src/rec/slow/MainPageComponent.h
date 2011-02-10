#ifndef __JUCER_HEADER_AUDIODEMOTABCOMPONENT_AUDIODEMOTABCOMPONENT_ED272280__
#define __JUCER_HEADER_AUDIODEMOTABCOMPONENT_AUDIODEMOTABCOMPONENT_ED272280__

#include "rec/gui/CuttableComponent.h"
#include "rec/gui/RecentFiles.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/AudioSetupPage.h"
#include "rec/audio/util/AudioDeviceSetup.h"
// #include "rec/data/yaml/Yaml.h"

namespace rec {
namespace slow {

class MainPageComponent  : public Component {
 public:
  MainPageComponent() : mainPage_(&deviceManager_),
                        audioSetupPage_(deviceManager_),
                        deviceListener_(&deviceManager_) {
    addAndMakeVisible(&mainPage_);
  }

  ~MainPageComponent() {}

  MainPage* mainPage() { return &mainPage_; }

  void loadRecentFile(int menuItemId) {
    gui::RecentFiles recent = gui::getSortedRecentFiles();
    const VirtualFile& file = recent.file(menuItemId).file();
    persist::data<VirtualFile>()->set(file);
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
    mainPage_.setBounds(getLocalBounds());
  }

  AudioSetupPage* audioSetupPage() { return &audioSetupPage_; }

 private:
  AudioDeviceManager deviceManager_;

  MainPage mainPage_;
  AudioSetupPage audioSetupPage_;
  persist::AudioDeviceSetupListener deviceListener_;

  DISALLOW_COPY_AND_ASSIGN(MainPageComponent);
};

}  // namespace slow
}  // namespace rec

#endif   // __JUCER_HEADER_AUDIODEMOTABCOMPONENT_AUDIODEMOTABCOMPONENT_ED272280__
