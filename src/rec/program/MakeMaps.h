#ifndef __REC_PROGRAM_MAKEMAPS__
#define __REC_PROGRAM_MAKEMAPS__

#include "rec/program/Types.h"

namespace rec {
namespace program {

class Program;

CommandMap makeCommandMap(const Program&);
MenuMap makeMenuMap(const Program&);
MenuBarMap makeMenuBarMap(const Program&);
ThreadMap makeThreadMap(const Program&);

}  // namespace program
}  // namespace rec

#endif  // __REC_PROGRAM_MAKEMAPS__
