#include "rec/app/Application.h"
#include "rec/support/SupportWindow.h"

START_REC_APPLICATION(rec::slow::SupportWindow,
                      RequestSupport,
                      rec::support::initialize,
                      rec::support::shutdown)
