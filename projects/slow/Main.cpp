#include "rec/app/Application.h"
#include "rec/slow/SlowWindow.h"

START_REC_APPLICATION(rec::slow::SlowWindow,
                      SlowGold,
                      "8.0.1",
                      rec::slow::initialize,
                      rec::slow::shutdown)
