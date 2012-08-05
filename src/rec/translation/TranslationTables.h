#ifndef __REC_TRANSLATION_TRANSLATIONTABLES__
#define __REC_TRANSLATION_TRANSLATIONTABLES__

#include "rec/base/Trans.h"
#include "rec/util/Listener.h"

namespace rec {
namespace translation {

string translate(const TranslatedString& translation);
void setLanguage(Internat::Language);
Language getLanguage();


}  // namespace translation
}  // namespace rec

#endif  // __REC_TRANSLATION_TRANSLATIONTABLES__
