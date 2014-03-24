#include "rec/slow/AboutWindow.h"
#include "rec/program/Program.h"
#include "rec/slow/AboutPane.h"
#include "rec/slow/Instance.h"

using namespace ::juce;

namespace rec {
namespace slow {

AboutWindow::AboutWindow(Component* parent,
                         const String& name,
                         const String& versionNumber)
    : Component("AboutWindow"),
      parent_(parent),
      aboutPane_(new AboutPane(name, versionNumber, this)) {
  setOpaque(false);
  Rectangle<int> bounds = parent_->getLocalBounds();
  setBounds(bounds);
  addAndMakeVisible(aboutPane_.get());
  aboutPane_->setBounds((bounds.getWidth() - AboutPane::WIDTH) / 2,
                        (bounds.getHeight() - AboutPane::HEIGHT) / 2,
                        AboutPane::WIDTH, AboutPane::HEIGHT);
  aboutPane_->setColour(Label::backgroundColourId, Colours::white);
  aboutPane_->setColour(Label::outlineColourId, Colours::red);

  setAlpha(0.0f);
  parent_->addAndMakeVisible(this);
  aboutPane_->addMouseListener(this, false);
}

AboutWindow::~AboutWindow() {}

void AboutWindow::mouseDown(const MouseEvent&) {
  if (aboutPane_->authenticated())
    close();
}

void AboutWindow::close() {
  if (not aboutPane_->expired()) {
    if (auto window = getInstance()->window_) {
      program::getProgram()->setEnabled(true);
      window->stopAboutWindow();
    }
  }
}

}  // namespace slow
}  // namespace rec
