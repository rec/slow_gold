#pragma once

#include "rec/audio/Audio.h"
#include "rec/data/DataListener.h"
#include "rec/gui/SetterResizer.h"
#include "rec/music/Metadata.h"
#include "rec/widget/tree/TreeView.h"
#include "rec/widget/tree/TreeViewDropAll.h"

namespace rec { namespace audio { class Gain; }}
namespace rec { namespace audio { namespace stretch { class Stretch; }}}
namespace rec { namespace gui { namespace audio { class Loops; }}}
namespace rec { namespace widget { namespace tree { class Root; }}}
namespace rec { namespace widget { namespace waveform { class Waveform; }}}

namespace rec {
namespace slow {

class MainPage;

class Components : public data::DataListener<audio::stretch::Stretch>,
                   public data::DataListener<audio::Gain>,
                   public data::DataListener<music::Metadata> {
 public:
  explicit Components(Component* parent);
  ~Components();

  virtual void init();
  void operator()(const audio::Gain&) override;
  void operator()(const audio::stretch::Stretch&) override;
  void operator()(const music::Metadata&) override;
  Component* topComponent() { return mainPanel_.get(); }

  widget::waveform::Waveform* waveform() { return waveform_; }
  widget::tree::Root* directoryTree();

 private:
  std::unique_ptr<Component> mainPanel_;

  widget::tree::TreeView* treeView_;
  widget::waveform::Waveform* waveform_;
  Component* parent_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Components);
};

}  // namespace slow
}  // namespace rec
