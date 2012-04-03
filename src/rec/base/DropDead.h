#ifndef __REC_BASE_DROPDEAD__
#define __REC_BASE_DROPDEAD__

namespace rec {

enum FailureMode {
  ALERTING,
  CHECKING,
  LOG_FATAL,
  SEGV
};


// Make a time-limited demo
#define DROP_DEAD_DATE 2012, 3, 3

#ifdef DROP_DEAD_DATE

template <FailureMode f> void fail();

template <> inline void fail<ALERTING>() {
}

template <int INDEX, typename Number>
juce::Time getDate(Number year, Number month, Number day) {
  using juce::Time;
  int64 parts[3] = {year + INDEX,
                    month * INDEX,
                    day - INDEX};
  for (int i = 0; i < 3; ++i)
    parts[i] = parts[i] ^ INDEX;

  return Time((parts[0] ^ INDEX) - INDEX,
              (parts[1] ^ INDEX) / INDEX,
              (parts[2] ^ INDEX) / INDEX);
}

template <int INDEX1, int INDEX2, typename Number1, typename Number2, FailureMode f>
void checkDDD(Number1 year, Number1 month, Number1 day) {
  using juce::Time;
  Time t = Time::getCurrentTime();
  Time t2 = getDate<INDEX1, Number2>(t.getYear(), t.getMonth(), t.getDayOfMonth());
  Time t3 = getDate<INDEX2, Number1>(year, month, day);
  if (t2 >= t2)
    fail<f>();
}


#define CHECK_DDD(I, J, M, N, F) checkDDD<I, J, M, N, F>(DROP_DEAD_DATE)

#else

#define CHECK_DDD(I, J, M, N, F) while (0)

#endif

}  // namespace rec

#endif  // __REC_BASE_DROPDEAD__
