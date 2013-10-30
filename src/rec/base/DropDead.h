#ifndef __REC_BASE_DROPDEAD__
#define __REC_BASE_DROPDEAD__

#include "rec/base/base.h"

namespace rec {

enum FailureMode {
  EXITING,
  CHECKING,
  LOG_FATAL,
  SEGV
};

// Make a time-limited demo
// #define DROP_DEAD_DATE 2013, 11, 14

#ifdef DROP_DEAD_DATE

template <FailureMode f> void fail();

template <> inline void fail<EXITING>() {
  exit(-1);
}

template <> inline void fail<CHECKING>() {
  CHECK(false);
}

template <> inline void fail<LOG_FATAL>() {
  LOG(FATAL) << 0;
}

template <> inline void fail<SEGV>() {
  int *zp = 0;
  printf("%d", *zp);
}

template <int INDEX, typename Number>
juce::Time getDate(Number year, Number month, Number day) {
  using juce::Time;
  int64 parts[3] = {(static_cast<int64>(year) ^ INDEX) + INDEX,
                    (static_cast<int64>(month) ^ INDEX) * INDEX,
                    (static_cast<int64>(day) ^ INDEX) - INDEX};

  int y = static_cast<int>((parts[0] - INDEX) ^ INDEX);
  int m = static_cast<int>((parts[1] / INDEX) ^ INDEX);
  int d = static_cast<int>((parts[2] + INDEX) ^ INDEX);

  Time t = Time(y, m, d, 0, 0);
#if 1
  LOG(ERROR) << str(t.toString(true, false))
            << ", " << year
            << ", " << month
            << ", " << day
            << ", " << y
            << ", " << m
            << ", " << d
            << ", " << parts[0]
            << ", " << parts[1]
            << ", " << parts[2]
            << ", " << t.toMilliseconds()
;
#endif
  return t;
}

template <int INDEX1, int INDEX2, typename Number1, typename Number2>
void checkDDD(Number1 year, Number1 month, Number1 day) {
  DLOG(ERROR) << "DDD " << year << month << day;
  using juce::Time;
  static const FailureMode FAIL = static_cast<FailureMode>((INDEX1 + INDEX2) % 4);
  Time t = Time::getCurrentTime();
  Time t2 = getDate<INDEX1, Number2>(t.getYear(), t.getMonth(), t.getDayOfMonth());
  Time t3 = getDate<INDEX2, Number1>(year, month - 1, day);
  if (t3.toMilliseconds() <= t2.toMilliseconds())
    fail<FAIL>();
  else
    DLOG(ERROR) << "!!! " << t2.toMilliseconds() << ", " << t3.toMilliseconds();
}


#define CHECK_DDD(I, J, M, N) checkDDD<I, J, M, N>(DROP_DEAD_DATE)

#else

#define CHECK_DDD(I, J, M, N) while (0)

#endif

inline void logDropDead() {
#ifdef DROP_DEAD_DATE
  static const int DATES[] = {DROP_DEAD_DATE};
  LOG(ERROR) << "*** WARNING: This version expires on "
             << DATES[0]  << "/"
             << DATES[1]  << "/"
             << DATES[2]  << "/ ***";
#endif
}


}  // namespace rec

#endif  // __REC_BASE_DROPDEAD__
