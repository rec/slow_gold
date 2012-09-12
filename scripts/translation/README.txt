Workflow for performing translations.

1. Program runs and updates en-incoming.rec.TranslatedStrings.def.  DONE.
2. Run merge.py to
 2.1. merge rec.TranslatedStrings.incoming into en-rec.TranslatedStrings and en-removed-rec.TranslatedStrings.
 2.2. Run extractUntranslated once for each language to extract just the untranslated strings as de-untranslated.txt, etc
3. Translate these with google translate and store them as de-translated.txt,  etc.  DONE
4. Run mergeTranslations.py to bring these back into de-rec.TranslatedStrings and de-removed-rec.TranslatedStrings.
