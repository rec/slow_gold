#ifndef __REC_SLOW_SLOWWINDOW__
#define __REC_SLOW_SLOWWINDOW__

#include "rec/app/Window.h"
#include "rec/util/Listener.h"
#include "rec/music/Metadata.h"
#include "rec/slow/HasInstance.h"

namespace rec {

namespace app { class GenericApplication; }
namespace music { class Metadata; }

namespace slow {

class AppLayout;
class Instance;

class SlowWindow : public app::Window,
                   public HasInstance,
                   public data::DataListener<music::Metadata>  {
 public:
  explicit SlowWindow(app::GenericApplication*);
  virtual ~SlowWindow();

  virtual void paint(Graphics& g) {
    g.fillAll(juce::Colours::lightgrey);
  }

  virtual void startListening();
  virtual void trashPreferences();
  void startAboutWindow();
  void stopAboutWindow();
  virtual void operator()(const music::Metadata&);
  virtual void minimisationStateChanged(bool isNowMinimised);

 protected:
  virtual void doStartup();
  virtual void doShutdown();

  virtual void constructInstance();
  virtual Component* getMainComponent();
  virtual MenuBarModel* getMenuBarModel();
  virtual void activeWindowStatusChanged();

 private:
  ptr<Instance> instanceDeleter_;
  ptr<Component> aboutWindow_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(SlowWindow);
};

void initialize(app::GenericApplication*);
void shutdown(app::GenericApplication*);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_SLOWWINDOW__
