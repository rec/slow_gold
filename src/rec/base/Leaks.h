#ifndef __REC_BASE_LEAKS__
#define __REC_BASE_LEAKS__

using  juce::LeakedObjectDetector;

#ifdef CHECK_LEAKS

#undef DISALLOW_COPY_AND_ASSIGN
#undef DISALLOW_COPY_ASSIGN_AND_EMPTY

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&);         \
  JUCE_LEAK_DETECTOR(TypeName)

// A macro to disallow the default constructor, copy constructor and operator=
// functions.
#define DISALLOW_COPY_ASSIGN_AND_EMPTY(TypeName) \
  TypeName();                                    \
  DISALLOW_COPY_AND_ASSIGN(TypeName)


#define DISALLOW_COPY_AND_ASSIGN_LEAKS(TypeName) \
  TypeName(const TypeName&);                       \
  void operator=(const TypeName&);                 \

// A macro to disallow the default constructor, copy constructor and operator=
// functions.
#define DISALLOW_COPY_ASSIGN_AND_EMPTY_LEAKS(TypeName) \
  TypeName();                                            \
  DISALLOW_COPY_AND_ASSIGN_LEAKS(TypeName)

#endif

#endif  // __REC_BASE_LEAKS__
