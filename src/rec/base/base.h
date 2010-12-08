#ifndef __REC_BASE_BASE__

#include "rec/base/BaseNoJuce.h"  // defines the guards here!
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {

typedef juce::AudioCDReader AudioCDReader;
typedef juce::AudioFormatReader AudioFormatReader;
typedef juce::AudioFormatReaderSource AudioFormatReaderSource;
typedef juce::AudioSampleBuffer AudioSampleBuffer;
typedef juce::AudioSourceChannelInfo AudioSourceChannelInfo;
typedef juce::CriticalSection CriticalSection;
typedef juce::File File;
typedef juce::PositionableAudioSource PositionableAudioSource;
typedef juce::String String;
typedef juce::ScopedLock ScopedLock;
typedef juce::StreamingSocket Socket;
typedef juce::StringArray StringArray;
typedef juce::StringPairArray StringPairArray;
typedef juce::Thread Thread;

}  // namespace rec

#endif
