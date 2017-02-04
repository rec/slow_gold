#pragma once

#include <iostream>

namespace rec {

using Lock = juce::ScopedLock;

// I only want to bring in some subset of the Juce namespace here...
//

using juce::ApplicationCommandInfo;
using juce::ApplicationCommandManager;
using juce::ApplicationCommandTarget;
using juce::AsyncUpdater;
using juce::AudioCDReader;
using juce::AudioDeviceManager;
using juce::AudioFormat;
using juce::AudioFormatManager;
using juce::AudioFormatReader;
using juce::AudioFormatReaderSource;
using juce::AudioFormatWriter;
using juce::AudioSampleBuffer;
using juce::AudioSourceChannelInfo;
using juce::AudioSourcePlayer;
using juce::AudioTransportSource;
using juce::AudioThumbnail;
using juce::AudioThumbnailCache;

using juce::CallbackMessage;
using juce::ChangeBroadcaster;
using juce::ChangeListener;
using juce::CriticalSection;
using juce::CharPointer_UTF8;
using juce::Colour;
using juce::Colours;
using juce::CommandID;
using juce::Component;

using juce::Desktop;
using juce::DocumentWindow;
using juce::DirectoryIterator;
using juce::Drawable;
using juce::DrawableButton;

using juce::File;
using juce::FileChooser;
using juce::FileDragAndDropTarget;
using juce::Font;

using juce::Graphics;

using juce::InputStream;
using InvocationInfo = ApplicationCommandTarget::InvocationInfo;

using juce::JUCEApplication;
using juce::Justification;

using juce::KeyPress;

using juce::MenuBarModel;
using juce::MemoryBlock;
using juce::MessageManagerLock;
using juce::MidiMessage;
using juce::ModifierKeys;
using juce::MouseEvent;
using juce::MouseListener;

using juce::OutputStream;

using juce::PopupMenu;
using juce::PositionableAudioSource;

using juce::ScopedUnlock;
using juce::SettableTooltipClient;
using juce::Slider;
using Socket = juce::StreamingSocket;
using juce::StretchableLayoutManager;
using juce::StretchableLayoutResizerBar;
using juce::String;
using juce::StringArray;
using juce::StringPairArray;
using juce::SystemStats;

using juce::TableHeaderComponent;
using juce::TableListBox;
using juce::TableListBoxModel;
using juce::TextEditor;
using juce::Thread;
using juce::TreeView;

using juce::URL;
using juce::WildcardFileFilter;

using AudioDeviceSetup = juce::AudioDeviceManager::AudioDeviceSetup;

using juce::Array;

inline string str(const String& s) {
    return s.toStdString();
}

inline String str(const string& s) {
    return String(s);
}

inline String str(const char* s) { return str(string(s)); }

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

#if JUCE_WINDOWS

inline const wchar_t* c_str(const String& s) {
    return s.toWideCharPointer();
}

#else

inline const char* c_str(const String& s) {
    return s.toUTF8().getAddress();
}

#endif

inline void beep( ) {
    juce::LookAndFeel::getDefaultLookAndFeel().playAlertSound();
}

}  // namespace rec
