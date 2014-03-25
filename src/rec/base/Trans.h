#ifndef __REC_BASE_TRANSLATEDSTRING__
#define __REC_BASE_TRANSLATEDSTRING__

#include "rec/base/base.h"
#include "rec/app/AppSettings.pb.h"

namespace rec {

class TranslatedString;

typedef app::AppSettings::Language Language;

class Trans {
 public:
  explicit Trans(const string&);  // DEPRECATED
  Trans(const char*, const char* file, int line);
  Trans(const String&, const char* file, int line);
  Trans(const char* o, const char* hint, const char* file, int line);

  ~Trans();

  operator String() const;
  string toStdString() const { return String(*this).toStdString(); }

  void registerTranslation() const;

 private:
  unique_ptr<TranslatedString> string_;
  Language language_;

  void check(const string& s);

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Trans);

#ifdef DEBUG
 public:
  static void dumpAll();
#endif
};

#define TRAN(NAME, TEXT)                      \
  const ::rec::Trans t_ ## NAME(TEXT, __FILE__, __LINE__)

#define TRAN2(NAME, TEXT)                      \
  const ::rec::Trans t_ ## NAME(TEXT, HINT, __FILE__, __LINE__)

#define TRAN_EXTERNAL(NAME)                     \
  extern const ::rec::Trans t_ ## NAME


#if JUCE_WINDOWS

inline const wchar_t* c_str(const Trans& s) {
  return c_str(String(s));
}

#else

inline const char* c_str(const Trans& s) {
  return c_str(String(s));
}

#endif

}  // namespace rec

extern const rec::Trans t_OK, t_CANCEL;

#endif  // __REC_BASE_TRANSLATEDSTRING__
