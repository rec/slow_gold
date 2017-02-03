#include "rec/program/Program.h"

namespace rec {
namespace program {

static Program* PROGRAM = nullptr;

void registerProgram(Program* program) {
    CHECK(not (PROGRAM and program)) << "Only one Program per program.";
    PROGRAM = program;
}

Program* getProgram() {
    return PROGRAM;
}

}  // namespace program
}  // namespace rec
