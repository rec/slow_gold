Workflow for performing translations.

1. Program runs and updates en-incoming.rec.TranslatedStrings.def.  DONE.
2. Run mergeIncoming to merge rec.TranslatedStrings.incoming into en/rec.TranslatedStrings and en/removed-rec.TranslatedStrings.  DONE.
3. Run extractUntranslated once for each language to extract just the untranslated strings as gde/untranslated.txt, etc  DONE
4. Translate these with google translate and store them as de/translated.txt,  etc.  DONE
5. Run mergeTranslations.py to bring these back into de/rec.TranslatedStrings and de/removed-rec.TranslatedStrings.


Translation problems!

1. Open and some other commands give an encoding error.
2. When you change languages:
   * Many menu items don't change.
   * No GUI items change.

Missing:
  * Resizer text  NOT DONE.
  * Loop Point Name help and text.  DONE.
  * Everything in the "Display" menu.
