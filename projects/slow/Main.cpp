#include "rec/app/Application.h"
#include "rec/slow/SlowWindow.h"

START_REC_APPLICATION(rec::slow::SlowWindow,
                      SlowGold,
                      "0.2.24",
                      rec::slow::initialize,
                      rec::slow::shutdown)
