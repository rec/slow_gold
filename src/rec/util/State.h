#ifndef __REC_STATE
#define __REC_STATE

template <typename Enum, int LAST>
class CircularEnum {
  struct Next {
    operator()(Enum e) { return Enum((e == LAST) ? 0 : e + 1); }
  };

  struct Previous {
    operator()(Enum e) { return Enum(e ? e - 1 : LAST); }
  };
};

#endif __REC_STATE

