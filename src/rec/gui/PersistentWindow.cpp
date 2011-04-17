#include "rec/gui/PersistentWindow.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/gui/Geometry.h"

using namespace juce;

namespace rec {
namespace gui {

PersistentWindow::PersistentWindow()
    : DocumentWindow("SlowGold", Colours::azure, DocumentWindow::allButtons,
                     true) {
  AppLayout layout(persist::data<AppLayout>());
  juce::Rectangle<int> bounds(300, 100, 800, 600);
  if (data->fileReadSuccess())
    bounds = gui::copy(layout.bounds());
  // else
  //   data->set("bounds", Value(gui::copy(bounds)));

  bounds.setWidth(juce::jmax(bounds.getWidth(), 500));
  bounds.setHeight(juce::jmax(bounds.getHeight(), 500));
  bounds.setX(juce::jmax(bounds.getX(), 10));
  bounds.setY(juce::jmax(bounds.getY(), 10));
  setBounds(bounds);
  setResizable(true, false); // resizability is a property of ResizableWindow
  setResizeLimits(1, 1, 8192, 8192);
}

PersistentWindow::~PersistentWindow() {}

void PersistentWindow::resized() {
  writeData();
  DocumentWindow::resized();
}

void PersistentWindow::writeData() {
  persist::data<AppLayout>()->set("bounds", gui::copy(getBounds()));
}

void PersistentWindow::moved() {
  writeData();
  DocumentWindow::moved();
  getContentComponent()->setBounds(getBounds());
}

void PersistentWindow::closeButtonPressed() {
  // TODO.
  JUCEApplication::getInstance()->systemRequestedQuit();
}

