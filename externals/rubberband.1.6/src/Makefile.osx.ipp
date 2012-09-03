
CXX		:= g++-4.0
CC		:= gcc-4.0
ARCHFLAGS	:= -isysroot /Developer/SDKs/MacOSX10.4u.sdk -mmacosx-version-min=10.4 -arch i386 -DMAC_OS_X_VERSION_MIN_REQUIRED=1040
OPTFLAGS	:= -DNDEBUG -ffast-math -mfpmath=sse -msse -msse2 -O3 -ftree-vectorize

IPPDIR		:= /Library/Frameworks/Intel_IPP.framework/Versions/Current
CXXFLAGS	:= $(ARCHFLAGS) $(OPTFLAGS) -I/usr/local/include -DUSE_PTHREADS -DHAVE_IPP -DUSE_IPP_STATIC -DUSE_SPEEX -I$(IPPDIR)/include -DNO_THREAD_CHECKS -DNO_TIMING -Irubberband -I. -Isrc

LIBRARY_LIBS		:= -L$(IPPDIR)/lib -lippsremerged -lippsrmerged -lippsemerged -lippsmerged -lippacemerged -lippacmerged -lippcore

CFLAGS		:= $(ARCHFLAGS) $(OPTFLAGS)
LDFLAGS		:= $(ARCHFLAGS) -lpthread $(LDFLAGS)

PROGRAM_LIBS		:= -L/usr/local/lib -lsndfile $(LIBRARY_LIBS)
VAMP_PLUGIN_LIBS	:= -L/usr/local/lib -lvamp-sdk $(LIBRARY_LIBS)
LADSPA_PLUGIN_LIBS	:= $(LIBRARY_LIBS)

MKDIR			:= mkdir
AR			:= ar

DYNAMIC_LDFLAGS		:= -dynamiclib
DYNAMIC_EXTENSION	:= .dylib

PROGRAM_TARGET 		:= bin/rubberband
STATIC_TARGET  		:= lib/librubberband.a
DYNAMIC_TARGET 		:= lib/librubberband$(DYNAMIC_EXTENSION)
VAMP_TARGET    		:= lib/vamp-rubberband$(DYNAMIC_EXTENSION)
LADSPA_TARGET  		:= lib/ladspa-rubberband$(DYNAMIC_EXTENSION)

default:	bin lib $(STATIC_TARGET) $(DYNAMIC_TARGET) $(PROGRAM_TARGET)

all:	bin lib $(STATIC_TARGET) $(DYNAMIC_TARGET) $(PROGRAM_TARGET) $(VAMP_TARGET) $(LADSPA_TARGET)

static:		$(STATIC_TARGET)
dynamic:	$(DYNAMIC_TARGET)
library:	$(STATIC_TARGET) $(DYNAMIC_TARGET)
program:	$(PROGRAM_TARGET)
vamp:		$(VAMP_TARGET)
ladspa:		$(LADSPA_TARGET)

PUBLIC_INCLUDES := \
	rubberband/rubberband-c.h \
	rubberband/RubberBandStretcher.h

LIBRARY_INCLUDES := \
	src/StretcherChannelData.h \
	src/float_cast/float_cast.h \
	src/StretcherImpl.h \
	src/StretchCalculator.h \
	src/base/Profiler.h \
	src/base/RingBuffer.h \
	src/base/Scavenger.h \
	src/dsp/AudioCurveCalculator.h \
	src/dsp/CompoundAudioCurve.h \
	src/dsp/ConstantAudioCurve.h \
	src/dsp/HighFrequencyAudioCurve.h \
	src/dsp/PercussiveAudioCurve.h \
	src/dsp/SilentAudioCurve.h \
	src/dsp/SpectralDifferenceAudioCurve.h \
	src/dsp/Resampler.h \
	src/dsp/FFT.h \
	src/dsp/MovingMedian.h \
	src/dsp/SincWindow.h \
	src/dsp/Window.h \
	src/system/Allocators.h \
	src/system/Thread.h \
	src/system/VectorOps.h \
	src/system/VectorOpsComplex.h \
	src/system/sysutils.h

LIBRARY_SOURCES := \
	src/rubberband-c.cpp \
	src/RubberBandStretcher.cpp \
	src/StretcherProcess.cpp \
	src/StretchCalculator.cpp \
	src/base/Profiler.cpp \
	src/dsp/AudioCurveCalculator.cpp \
	src/dsp/CompoundAudioCurve.cpp \
	src/dsp/SpectralDifferenceAudioCurve.cpp \
	src/dsp/HighFrequencyAudioCurve.cpp \
	src/dsp/SilentAudioCurve.cpp \
	src/dsp/ConstantAudioCurve.cpp \
	src/dsp/PercussiveAudioCurve.cpp \
	src/dsp/Resampler.cpp \
	src/dsp/FFT.cpp \
	src/system/Allocators.cpp \
	src/system/sysutils.cpp \
	src/system/Thread.cpp \
	src/system/VectorOpsComplex.cpp \
	src/StretcherChannelData.cpp \
	src/StretcherImpl.cpp

# For Speex resampler -- comment these lines out if not specifying USE_SPEEX
LIBRARY_INCLUDES := $(LIBRARY_INCLUDES) \
	src/speex/speex_resampler.h
LIBRARY_SOURCES := $(LIBRARY_SOURCES) \
	src/speex/resample.c

PROGRAM_SOURCES := \
	main/main.cpp

VAMP_HEADERS := \
	vamp/RubberBandVampPlugin.h

VAMP_SOURCES := \
	vamp/RubberBandVampPlugin.cpp \
	vamp/libmain.cpp

LADSPA_HEADERS := \
	ladspa/RubberBandPitchShifter.h

LADSPA_SOURCES := \
	ladspa/RubberBandPitchShifter.cpp \
	ladspa/libmain.cpp

LIBRARY_OBJECTS := $(LIBRARY_SOURCES:.cpp=.o)
LIBRARY_OBJECTS := $(LIBRARY_OBJECTS:.c=.o)

PROGRAM_OBJECTS := $(PROGRAM_SOURCES:.cpp=.o)
VAMP_OBJECTS    := $(VAMP_SOURCES:.cpp=.o)
LADSPA_OBJECTS  := $(LADSPA_SOURCES:.cpp=.o)

$(PROGRAM_TARGET):	$(LIBRARY_OBJECTS) $(PROGRAM_OBJECTS)
	$(CXX) -o $@ $^ $(PROGRAM_LIBS) $(PROGRAM_LIBS) $(LDFLAGS)

$(STATIC_TARGET):	$(LIBRARY_OBJECTS)
	$(AR) rc $@ $^

$(DYNAMIC_TARGET):	$(LIBRARY_OBJECTS)
	$(CXX) $(DYNAMIC_LDFLAGS) $^ -o $@ $(LIBRARY_LIBS) $(LDFLAGS)

$(VAMP_TARGET):		$(LIBRARY_OBJECTS) $(VAMP_OBJECTS)
	$(CXX) $(VAMP_LDFLAGS) -o $@ $^ $(VAMP_PLUGIN_LIBS) $(LDFLAGS)

$(LADSPA_TARGET):	$(LIBRARY_OBJECTS) $(LADSPA_OBJECTS)
	$(CXX) $(LADSPA_LDFLAGS) -o $@ $^ $(LADSPA_PLUGIN_LIBS) $(LDFLAGS)

bin:
	$(MKDIR) $@
lib:
	$(MKDIR) $@

clean:
	rm -f $(LIBRARY_OBJECTS) $(PROGRAM_OBJECTS) $(LADSPA_OBJECTS) $(VAMP_OBJECTS)

distclean:	clean
	rm -f $(PROGRAM_TARGET) $(STATIC_TARGET) $(DYNAMIC_TARGET) $(VAMP_TARGET) $(LADSPA_TARGET)

depend:
	makedepend -Y $(LIBRARY_SOURCES) $(PROGRAM_SOURCES)


# DO NOT DELETE

src/rubberband-c.o: rubberband/rubberband-c.h
src/rubberband-c.o: rubberband/RubberBandStretcher.h
src/RubberBandStretcher.o: src/StretcherImpl.h
src/RubberBandStretcher.o: rubberband/RubberBandStretcher.h src/dsp/Window.h
src/RubberBandStretcher.o: src/dsp/FFT.h src/base/RingBuffer.h
src/RubberBandStretcher.o: src/base/Scavenger.h src/system/Thread.h
src/RubberBandStretcher.o: src/system/Thread.h src/system/sysutils.h
src/StretcherProcess.o: src/StretcherImpl.h rubberband/RubberBandStretcher.h
src/StretcherProcess.o: src/dsp/Window.h src/dsp/FFT.h src/base/RingBuffer.h
src/StretcherProcess.o: src/base/Scavenger.h src/system/Thread.h
src/StretcherProcess.o: src/system/Thread.h src/system/sysutils.h
src/StretcherProcess.o: src/dsp/PercussiveAudioCurve.h
src/StretcherProcess.o: src/dsp/AudioCurveCalculator.h
src/StretcherProcess.o: src/dsp/HighFrequencyAudioCurve.h
src/StretcherProcess.o: src/dsp/ConstantAudioCurve.h src/StretchCalculator.h
src/StretcherProcess.o: src/StretcherChannelData.h src/dsp/Resampler.h
src/StretcherProcess.o: src/base/Profiler.h src/system/VectorOps.h
src/StretcherProcess.o: src/system/sysutils.h
src/StretchCalculator.o: src/StretchCalculator.h src/system/sysutils.h
src/system/Thread.o: src/system/Thread.h
src/base/Profiler.o: src/base/Profiler.h src/system/sysutils.h
src/dsp/AudioCurveCalculator.o: src/dsp/AudioCurveCalculator.h
src/dsp/AudioCurveCalculator.o: src/system/sysutils.h
src/dsp/SpectralDifferenceAudioCurve.o: src/dsp/SpectralDifferenceAudioCurve.h
src/dsp/SpectralDifferenceAudioCurve.o: src/dsp/AudioCurveCalculator.h
src/dsp/SpectralDifferenceAudioCurve.o: src/system/sysutils.h
src/dsp/SpectralDifferenceAudioCurve.o: src/dsp/Window.h
src/dsp/SpectralDifferenceAudioCurve.o: src/system/VectorOps.h
src/dsp/SpectralDifferenceAudioCurve.o: src/system/sysutils.h
src/dsp/HighFrequencyAudioCurve.o: src/dsp/HighFrequencyAudioCurve.h
src/dsp/HighFrequencyAudioCurve.o: src/dsp/AudioCurveCalculator.h
src/dsp/HighFrequencyAudioCurve.o: src/system/sysutils.h
src/dsp/SilentAudioCurve.o: src/dsp/SilentAudioCurve.h
src/dsp/SilentAudioCurve.o: src/dsp/AudioCurveCalculator.h
src/dsp/SilentAudioCurve.o: src/system/sysutils.h
src/dsp/ConstantAudioCurve.o: src/dsp/ConstantAudioCurve.h
src/dsp/ConstantAudioCurve.o: src/dsp/AudioCurveCalculator.h
src/dsp/ConstantAudioCurve.o: src/system/sysutils.h
src/dsp/PercussiveAudioCurve.o: src/dsp/PercussiveAudioCurve.h
src/dsp/PercussiveAudioCurve.o: src/dsp/AudioCurveCalculator.h
src/dsp/PercussiveAudioCurve.o: src/system/sysutils.h src/system/VectorOps.h
src/dsp/PercussiveAudioCurve.o: src/system/sysutils.h
src/dsp/Resampler.o: src/dsp/Resampler.h src/system/sysutils.h
src/dsp/Resampler.o: src/base/Profiler.h
src/dsp/FFT.o: src/dsp/FFT.h src/system/sysutils.h src/system/Thread.h
src/dsp/FFT.o: src/base/Profiler.h src/system/VectorOps.h
src/dsp/FFT.o: src/system/sysutils.h
src/system/Allocators.o: src/system/Allocators.h src/system/VectorOps.h
src/system/Allocators.o: src/system/sysutils.h
src/system/sysutils.o: src/system/sysutils.h
src/StretcherChannelData.o: src/StretcherChannelData.h src/StretcherImpl.h
src/StretcherChannelData.o: rubberband/RubberBandStretcher.h src/dsp/Window.h
src/StretcherChannelData.o: src/dsp/FFT.h src/base/RingBuffer.h
src/StretcherChannelData.o: src/base/Scavenger.h src/system/Thread.h
src/StretcherChannelData.o: src/system/Thread.h src/system/sysutils.h
src/StretcherChannelData.o: src/dsp/Resampler.h src/system/Allocators.h
src/StretcherChannelData.o: src/system/VectorOps.h src/system/sysutils.h
src/StretcherImpl.o: src/StretcherImpl.h rubberband/RubberBandStretcher.h
src/StretcherImpl.o: src/dsp/Window.h src/dsp/FFT.h src/base/RingBuffer.h
src/StretcherImpl.o: src/base/Scavenger.h src/system/Thread.h src/system/Thread.h
src/StretcherImpl.o: src/system/sysutils.h src/dsp/PercussiveAudioCurve.h
src/StretcherImpl.o: src/dsp/AudioCurveCalculator.h
src/StretcherImpl.o: src/dsp/HighFrequencyAudioCurve.h
src/StretcherImpl.o: src/dsp/SpectralDifferenceAudioCurve.h src/dsp/Window.h
src/StretcherImpl.o: src/system/VectorOps.h src/system/sysutils.h
src/StretcherImpl.o: src/dsp/SilentAudioCurve.h src/dsp/ConstantAudioCurve.h
src/StretcherImpl.o: src/dsp/Resampler.h src/StretchCalculator.h
src/StretcherImpl.o: src/StretcherChannelData.h src/base/Profiler.h
main/main.o: rubberband/RubberBandStretcher.h src/system/sysutils.h
main/main.o: src/base/Profiler.h
