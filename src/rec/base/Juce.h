#ifndef __REC_BASE_JUCE__
#define __REC_BASE_JUCE__

#include <iostream>

namespace rec {

// I ony want to bring in some subset of the Juce namespace here...
//
typedef juce::ApplicationCommandInfo ApplicationCommandInfo;
typedef juce::ApplicationCommandManager ApplicationCommandManager;
typedef juce::ApplicationCommandTarget ApplicationCommandTarget;
typedef juce::AsyncUpdater AsyncUpdater;
typedef juce::AudioCDReader AudioCDReader;
typedef juce::AudioDeviceManager AudioDeviceManager;
typedef juce::AudioFormat AudioFormat;
typedef juce::AudioFormatManager AudioFormatManager;
typedef juce::AudioFormatReader AudioFormatReader;
typedef juce::AudioFormatReaderSource AudioFormatReaderSource;
typedef juce::AudioFormatWriter AudioFormatWriter;
typedef juce::AudioSampleBuffer AudioSampleBuffer;
typedef juce::AudioSourceChannelInfo AudioSourceChannelInfo;
typedef juce::AudioSourcePlayer AudioSourcePlayer;
typedef juce::AudioTransportSource AudioTransportSource;

typedef juce::CallbackMessage CallbackMessage;
typedef juce::ChangeBroadcaster ChangeBroadcaster;
typedef juce::ChangeListener ChangeListener;
typedef juce::CriticalSection CriticalSection;
typedef juce::Colour Colour;
typedef juce::CommandID CommandID;
typedef juce::Component Component;

typedef juce::DocumentWindow DocumentWindow;
typedef juce::Drawable Drawable;
typedef juce::DrawableButton DrawableButton;

typedef juce::File File;
typedef juce::FileChooser FileChooser;
typedef juce::FileDragAndDropTarget FileDragAndDropTarget;
typedef juce::Font Font;

typedef juce::Graphics Graphics;

typedef juce::InputStream InputStream;
typedef ApplicationCommandTarget::InvocationInfo InvocationInfo;

typedef juce::JUCEApplication JUCEApplication;
typedef juce::Justification Justification;

typedef juce::MenuBarModel MenuBarModel;
typedef juce::MemoryBlock MemoryBlock;
typedef juce::MidiMessage MidiMessage;
typedef juce::ModifierKeys ModifierKeys;
typedef juce::MouseEvent MouseEvent;
typedef juce::MouseListener MouseListener;

typedef juce::OutputStream OutputStream;

typedef juce::PopupMenu PopupMenu;
typedef juce::PositionableAudioSource PositionableAudioSource;
typedef juce::PlatformUtilities PlatformUtilities;

typedef juce::String String;
typedef juce::ScopedLock ScopedLock;
typedef juce::ScopedUnlock ScopedUnlock;
typedef juce::Slider Slider;
typedef juce::StreamingSocket Socket;
typedef juce::StringArray StringArray;
typedef juce::StringPairArray StringPairArray;
typedef juce::StretchableLayoutResizerBar StretchableLayoutResizerBar;
typedef juce::StretchableLayoutManager StretchableLayoutManager;

typedef juce::TableHeaderComponent TableHeaderComponent;
typedef juce::TableListBox TableListBox;
typedef juce::TableListBoxModel TableListBoxModel;
typedef juce::TextEditor TextEditor;
typedef juce::Thread Thread;
typedef juce::TreeView TreeView;

typedef juce::AudioDeviceManager::AudioDeviceSetup AudioDeviceSetup;

inline string str(const String& s) {
  return string(s.toUTF8());
}

inline String str(const string& s) {
  return String::fromUTF8(s.c_str());
}

inline string str(const File& f) {
  return str(f.getFullPathName());
}

inline std::ostream& operator<<(std::ostream& os, const String& s) {
  return os << str(s);
}

inline const string operator+(const String& s, const string& t) {
  return str(s) + t;
}

inline const string operator+(const string& s, const String& t) {
  return s + str(t);
}

inline const string str(const MidiMessage& msg) {
  return string(reinterpret_cast<const char*>(msg.getRawData()),
                msg.getRawDataSize());
}

}  // namespace rec

#endif  // __REC_BASE_JUCE__
