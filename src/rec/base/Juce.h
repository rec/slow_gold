#ifndef __REC_BASE_JUCE__
#define __REC_BASE_JUCE__

namespace rec {

typedef juce::AsyncUpdater AsyncUpdater;
typedef juce::AudioCDReader AudioCDReader;
typedef juce::AudioDeviceManager AudioDeviceManager;
typedef juce::AudioFormatManager AudioFormatManager;
typedef juce::AudioFormatReader AudioFormatReader;
typedef juce::AudioFormatReaderSource AudioFormatReaderSource;
typedef juce::AudioSampleBuffer AudioSampleBuffer;
typedef juce::AudioSourceChannelInfo AudioSourceChannelInfo;
typedef juce::AudioSourcePlayer AudioSourcePlayer;
typedef juce::AudioThumbnail AudioThumbnail;
typedef juce::AudioTransportSource AudioTransportSource;

typedef juce::CallbackMessage CallbackMessage;
typedef juce::ChangeBroadcaster ChangeBroadcaster;
typedef juce::ChangeListener ChangeListener;
typedef juce::CriticalSection CriticalSection;
typedef juce::Colour Colour;
typedef juce::Component Component;

typedef juce::DocumentWindow DocumentWindow;
typedef juce::DrawableButton DrawableButton;

typedef juce::File File;
typedef juce::FileDragAndDropTarget FileDragAndDropTarget;
typedef juce::Font Font;

typedef juce::Graphics Graphics;

typedef juce::InputStream InputStream;

typedef juce::Justification Justification;

typedef juce::MemoryBlock MemoryBlock;
typedef juce::MouseEvent MouseEvent;

typedef juce::OutputStream OutputStream;

typedef juce::PositionableAudioSource PositionableAudioSource;

typedef juce::String String;
typedef juce::ScopedLock ScopedLock;
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
typedef juce::TimeSliceThread TimeSliceThread;
typedef juce::TimeSliceClient TimeSliceClient;
typedef juce::TreeView TreeView;

typedef juce::AudioDeviceManager::AudioDeviceSetup AudioDeviceSetup;

}  // namespace rec

#endif  // __REC_BASE_JUCE__
