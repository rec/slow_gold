#ifndef __REC_CIRCULAR_ENUM
#define __REC_CIRCULAR_ENUM

template <typename Enum, int LAST>
class CircularEnum {
  struct Next {
    operator()(Enum e) { return Enum((e == LAST) ? 0 : e + 1); }
  };

  struct Previous {
    operator()(Enum e) { return Enum(e ? e - 1 : LAST); }
  };
};

#endif __REC_CIRCULAR_ENUM

