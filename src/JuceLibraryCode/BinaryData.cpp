/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file, created by The Jucer V3.0.0
   Do not edit anything in this file!

*/

#include "BinaryData.h"


const char* BinaryData::getNamedResource (const char* resourceNameUTF8, int& numBytes) throw()
{
    int hash = 0;
    if (resourceNameUTF8 != 0)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + *resourceNameUTF8++;

    switch (hash)
    {
        case 0x064cb88a:  numBytes = BinaryData::MakefileSize; return BinaryData::Makefile;
        default: break;
    }

    numBytes = 0;
    return 0;
}


//================== Makefile ==================
static const unsigned char temp_df67d65e[] =
"# Makefile for testing on Mac OS/X only.\n"
"\n"
"STL_DIR = /usr/include/c++/4.2.1\n"
"\n"
"# Where to find user code.\n"
"USER_DIR = .\n"
"\n"
"# Flags passed to the preprocessor.\n"
"CPPFLAGS += -I$(USER_DIR) -I$(STL_DIR)\n"
"\n"
"# Flags passed to the C++ compiler.\n"
"CXXFLAGS += -g -Wall -Wextra\n"
"\n"
"# House-keeping build targets.\n"
"\n"
"all: ammf_scaler.a\n"
"\n"
"ammf_scaler.a:\\\n"
" AudioResampler.o\\\n"
" AudioTimeScaler.o\\\n"
" hfft.o\\\n"
" mfAlloc.o\n"
"\t$(AR) $(ARFLAGS) $@ $^\n"
"\n"
".o: .cpp\n"
".o: .c\n"
"\n"
"clean:\n"
"\trm -f *.o *.a";

const char* BinaryData::Makefile = (const char*) temp_df67d65e;
