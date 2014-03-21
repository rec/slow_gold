#ifndef __REC_SLOW_ABOUTWINDOW__
#define __REC_SLOW_ABOUTWINDOW__

#include "rec/base/base.h"

namespace rec {
namespace slow {

class AboutPane;

class AboutWindow : public Component,
                    public juce::ModalComponentManager::Callback {
 public:
  AboutWindow(
      Component* parent, const String& name, const String& versionNumber);

  ~AboutWindow();

  void paint(Graphics&) override {}
  void mouseDown(const MouseEvent&) override { close(); }
  void modalStateFinished(int returnValue) override { close(); }

 private:
  void close();

  Component* parent_;
  unique_ptr<AboutPane> aboutPane_;
  DISALLOW_COPY_ASSIGN_AND_LEAKS(AboutWindow);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_ABOUTWINDOW__
