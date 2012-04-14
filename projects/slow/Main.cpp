#include "rec/app/Application.h"
#include "rec/slow/SlowWindow.h"

START_REC_APPLICATION(rec::slow::SlowWindow,
                      SlowGold,
                      rec::slow::initialize,
                      rec::slow::shutdown)
