Workflow for performing translations.

1. Program runs and updates rec.TranslatedStrings.incoming.  DONE.
2. Run mergeIncoming to merge rec.TranslatedStrings.incoming into en/rec.TranslatedStrings and en/removed-rec.TranslatedStrings.  DONE.
3. Run mergeUntranslated once for each language to extract just the untranslated strings as de/untranslated.txt, etc
4. Translate these with google translate and store them as de/translated.txt,  etc.
5. Run mergeTranslations.py to bring these back into de/rec.TranslatedStrings and de/removed-rec.TranslatedStrings.
