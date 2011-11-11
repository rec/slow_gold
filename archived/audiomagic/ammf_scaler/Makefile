# Makefile for testing on Mac OS/X only.

STL_DIR = /usr/include/c++/4.2.1

# Where to find user code.
USER_DIR = .

# Flags passed to the preprocessor.
CPPFLAGS += -I$(USER_DIR) -I$(STL_DIR)

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra

# House-keeping build targets.

all: ammf_scaler.a

ammf_scaler.a:\
 AudioResampler.o\
 AudioTimeScaler.o\
 hfft.o\
 mfAlloc.o
	$(AR) $(ARFLAGS) $@ $^

.o: .cpp
.o: .c

clean:
	rm -f *.o *.a