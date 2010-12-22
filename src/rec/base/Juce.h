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

typedef juce::AudioTransportSource AudioTransportSource;

typedef juce::ChangeBroadcaster ChangeBroadcaster;
typedef juce::ChangeListener ChangeListener;
typedef juce::CriticalSection CriticalSection;
typedef juce::Colour Colour;
typedef juce::Component Component;

typedef juce::File File;
typedef juce::Font Font;

typedef juce::Graphics Graphics;
typedef juce::InputStream InputStream;
typedef juce::MemoryBlock MemoryBlock;
typedef juce::OutputStream OutputStream;
typedef juce::PositionableAudioSource PositionableAudioSource;

typedef juce::String String;
typedef juce::ScopedLock ScopedLock;
typedef juce::Slider Slider;
typedef juce::StreamingSocket Socket;
typedef juce::StringArray StringArray;
typedef juce::StringPairArray StringPairArray;

typedef juce::Thread Thread;
typedef juce::TreeView TreeView;

typedef juce::AudioDeviceManager::AudioDeviceSetup AudioDeviceSetup;

}  // namespace rec

#endif  // __REC_BASE_JUCE__
