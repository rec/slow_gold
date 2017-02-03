#pragma once

#include "rec/app/Window.h"

namespace rec { namespace app { class GenericApplication; }}

namespace rec {
namespace slow {

class Instance;

class SlowWindow : public app::Window  {
 public:
  explicit SlowWindow(app::GenericApplication*);
  ~SlowWindow() override;

  void init() override;

  void paint(Graphics& g) override {
    g.fillAll(juce::Colours::lightgrey);
  }

  void startAboutWindow() override;
  void stopAboutWindow() override;
  void minimisationStateChanged(bool isNowMinimised) override;
  void anotherInstanceStarted(const String&) override;
  void systemRequestedQuit() override;

 protected:
  void doStartup() override;
  void doShutdown() override;

  void constructInstance() override;
  Component* getMainComponent() override;
  void activeWindowStatusChanged() override;

 private:
  void gotoNextFile();

  std::unique_ptr<Instance> instance_;
  std::unique_ptr<Component> aboutWindow_;
  bool startupFinished_;
  File nextFile_;
  std::unique_ptr<Thread> shutdownThread_;

  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(SlowWindow);
};

void initialize(app::GenericApplication*);
void shutdown(app::GenericApplication*);

}  // namespace slow
}  // namespace rec
