#include "rec/app/Application.h"
#include "rec/slow/SlowWindow.h"
#include "rec/base/DropDead.h"

START_REC_APPLICATION(rec::slow::SlowWindow,
                      SlowGold,
                      "8.0.0",
                      rec::slow::initialize,
                      rec::slow::shutdown)
