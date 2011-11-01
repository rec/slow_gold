
Rubber Band
===========

An audio time-stretching and pitch-shifting library and utility program.

Copyright 2007-2011 Chris Cannam, chris.cannam@breakfastquay.com.

Rubber Band is a library and utility program that permits you to
change the tempo and pitch of an audio recording independently of one
another.

This is the commercial edition of Rubber Band.  This software may be
used and distributed only in accordance with the terms under which it
was licensed to you.  Please consult your licence agreement before
using this code in your application, and particularly before
distributing the results!

In particular,

   - You may not distribute any part of this source code to any third party.

   - You may not link this software against other code that is
     licensed under the GPL (e.g. libsamplerate or FFTW) unless you
     have obtained a proprietary licence for that software as well.

   - If you are intending to build this software using the bundled
     library options (Speex or KissFFT), please review the terms for
     those libraries as applicable in src/speex/COPYING and
     src/kissfft/COPYING before continuing.

     See section 3a below for details of the library options
     supported by Rubber Band.

This is version 1.6.0-commercial of Rubber Band, baselined 2011-01-07.


Contents of this README
-----------------------

1. Code components
2. Binary libraries and executables
3. Compiling Rubber Band
   a. FFT and resampler selection
   b. GNU/POSIX systems and Makefiles
   c. Win32 and Visual Studio


1. Code components
------------------

Rubber Band consists of:

 * The Rubber Band library code.  This is the code that will normally
   be used by your applications.  The headers for this are in the
   rubberband/ directory, and the source code is in src/.
   The Rubber Band library depends upon resampler and FFT code; see
   section 3a below for details.

 * The Rubber Band command-line tool.  This is in main/main.cpp.
   This program uses the Rubber Band library and also requires libsndfile
   (http://www.mega-nerd.com/libsndfile/, licensed under the GNU Lesser
   General Public License) for audio file loading.

 * A pitch-shifter LADSPA audio effects plugin.  This is in ladspa/.
   It requires the LADSPA SDK header ladspa.h (not included).

 * A Vamp audio analysis plugin which may be used to inspect the
   dynamic stretch ratios and other decisions taken by the Rubber Band
   library when in use.  This is in vamp/.  It requires the Vamp
   plugin SDK (http://www.vamp-plugins.org/develop.html) (not included).


2. Binary libraries and executables
-----------------------------------

The directory prebuilt-binaries/ (where provided) contains binary
static libraries and executables of Rubber Band for Win32 and OS/X
platforms.  These have been built using the Intel Performance
Primitives for resampling and FFT functions, and the IPP libraries
required to link with them are also included.

The contents of these directories are as follows:

 * prebuilt-binaries/osx/

   Contains libraries and executables for OS/X 10.4 or 10.5 on Intel.

   The ipp*.a files in this directory are Intel Performance
   Primitives libraries for static linkage.  The Rubber Band library
   depends upon these.  Note that despite their large size, they add
   very little to the size of the resulting application as Rubber Band
   uses few functions from them.

   The librubberband.a and librubberband.dylib files are static and
   dynamic (respectively) versions of the Rubber Band library.

   To link an application with these libraries, add librubberband.a
   and libipp*.a to your project location and use the linker flags
   -lrubberband -lippsremerged -lippsrmerged -lippsemerged
   -lippsmerged -lippcore (in that order).

   The file "rubberband" is the command-line tool (which was linked
   statically against the libraries as just described).

 * prebuilt-binaries/win32/common

   Contains third-party libraries used by Rubber Band on Win32.

   The ipp*.lib files in this directory are Intel Performance
   Primitives libraries for static linkage.  The Rubber Band library
   depends upon these.  Note that despite their large size, they add
   very little to the size of the resulting application as Rubber Band
   uses few functions from them.

   The file libsndfile-1.dll is used by the Rubber Band command-line
   tool for audio file I/O, and this library only is distributed under
   the LGPL (i.e. redistribution restrictions apply).  You do not need
   this file to use Rubber Band in your application.

 * prebuilt-binaries/win32/debug
 * prebuilt-binaries/win32/release

   Contain debug and release (respectively) builds of the Rubber Band
   library (rubberband-library.lib) and command-line tool
   (rubberband-program.exe).

   To link an application with these libraries, add
   rubberband-library.lib, ippsremerged.lib, ippsrmerged.lib,
   ippsemerged.lib, ippsmerged.lib and ippcorel.lib (in that order) to
   your project build.


3. Compiling Rubber Band
------------------------

3a. FFT and resampler selection
-------------------------------

Rubber Band requires additional library code for FFT calculation and
resampling.  Several options are supported, described in the table
below (note that SRC = sample-rate conversion, i.e. resampling).

The supplied binary libraries (where provided) are compiled using the
Intel Performance Primitives for both FFT and resampling; to use
another alternative, it is necessary to build the library yourself.
The selection is controlled using preprocessor flags at compile time,
as detailed in the table.

Flags that declare that you want to use an external library begin with
HAVE_; flags that select from the bundled options begin with USE_.

You must enable one resampler implementation and one FFT
implementation.  Do not enable more than one of either unless you know
what you're doing -- it will work, but it may not be obvious which
implementation will be used in which context.

Usually the best combinations are IPP plus libsamplerate or Speex
(when targeting Intel hardware), or Accelerate plus libsamplerate or
Speex (when targeting OS/X).


Type  Library        Flags required        Notes
----  -------        --------------        -----   

Both  IPP (dynamic)  -DHAVE_IPP            Proprietary library             
                                           Separate licence reqd to rebuild RB
Both  IPP (static)   -DHAVE_IPP and        Used for the pre-built RB libraries
                     -DUSE_IPP_STATIC      Fastest option for FFT
                                           Not so fast for resampling
                                           Double-precision
                                           Intel/AMD only (no PPC etc)

FFT   FFTW3          -DHAVE_FFTW3          GPL licence is incompatible
                                             with RB commercial edition:
                                           separate commercial licence reqd
                                             for proprietary use
                                           Fast (though slower than IPP)
                                           Double-precision

FFT   Accelerate     -DHAVE_VDSP           Only available on OS/X (10.4+)
                                           Bundled in platform's Accelerate
                                             framework, no license reqd
                                           Fast (almost as fast as IPP)
                                           Double-precision
                                           Intel and PPC supported

FFT   KissFFT        -DUSE_KISSFFT         Included in RB (no external library
                                             or licence required)
                                           Slower than IPP, FFTW3, or Accelerate
                                           Single-precision only, increasing
                                             theoretical noise floor
                                           To use, add source files from
                                             src/kissfft to your build project

FFT   Built-in       -DUSE_BUILTIN_FFT     Included in RB (no external library
                                             or licence required)
                                           Slowest option
                                           Double-precision

SRC   libresample    -DHAVE_LIBRESAMPLE    LGPL licence
                                           Not thoroughly tested in conjunction
                                             with RB

SRC   libsamplerate  -DHAVE_LIBSAMPLERATE  GPL licence is incompatible
                                             with RB commercial edition:
                                           separate commercial licence reqd
                                             for proprietary use
                                           Highest quality and good real-time
                                             behaviour when pitch shifting

SRC   Speex          -DUSE_SPEEX           Included in RB (no external library
                                             or licence required)
                                           Fastest option
                                           To use, add source files from
                                             src/speex to your build project

If you are intending to build this software using one of the bundled
library options (Speex or KissFFT), please review the terms for those
libraries as applicable in src/speex/COPYING and src/kissfft/COPYING
before continuing.


3b. GNU/POSIX systems and Makefiles
-----------------------------------

A GNU-style configure script is included for use on Linux and OS/X.

Run ./configure, then adjust the generated Makefile according to your
preference for FFT and resampler implementations.  The default is to
use the IPP static libraries for both.  If you want to keep the
default, adjust the IPPDIR line in the Makefile to point to the
correct install location for IPP.

The following Makefile targets are available:

  static  -- build static libraries only
  dynamic -- build dynamic libraries only
  library -- build static and dynamic libraries only
  program -- build the command-line tool
  vamp    -- build Vamp plugin
  ladspa  -- build LADSPA plugin
  all (the default target) -- build everything.


3c. Win32 and Visual Studio
---------------------------

Two Visual Studio 2005 projects are supplied.

rubberband-library.vcproj builds the Rubber Band static libraries
only.

rubberband-program.vcproj builds the Rubber Band command-line tool
only (requires the Rubber Band libraries, and libsndfile).

You will need to adjust the project settings so as to set the compile
flags according to your preference for FFT and resampler
implementation, and set the include path and library path
appropriately.  The default is to use the IPP static libraries for FFT
and Speex for resampling.  If you want to keep the default, adjust the
include and library paths in the project according to the install
location for IPP -- the defaults should be correct for a default
install of IPP v5.3 patch level 2.

