#include "rec/support/RequestSupport.h"

#include "rec/base/Trans.h"
#include "rec/data/ZipData.h"

namespace rec {
namespace support {

using namespace juce;

namespace {

TRTR(CANT_SUPPORT, "Couldn't Create A Support Request");
TRTR(CANT_SUPPORT_FULL, "Sorry, we were unable to create a support request.");
TRTR(MAIL_ATTACH, "Please attach the file on your desktop named %s to this "
                  "email and send it to us!");
TRTR(MAIL_CREATED, "A Support Request file named \"%s\" "
                   "was created on your desktop.");
TRTR(MAIL_DISCARD, "You can throw the file away once your email is sent.");
TRTR(MAIL_SUBJECT, "Support Request: %s");
TRTR(PLEASE_CONTACT, "Please contact World Wide Woodshed support at");
TRTR(PLEASE_MAIL, "Please mail the file to %s and then you can throw it away.");
TRTR(SUPPORTED, "A Support Request Was Created On Your Desktop");

const String SUPPORT = "support@worldwidewoodshed.com";
const URL MAILTO("mailto:" + URL::addEscapeChars(SUPPORT, true));

const char* const VOWELS = "aeiouy";
const char* const CONSONANTS = "bdfgjlmnprsvwxz";
const char* const LETTERS[] = {VOWELS, CONSONANTS};
const uint32 LENGTHS[] = {strlen(VOWELS), strlen(CONSONANTS)};

const int LENGTH = 10;

String randomKey(int length = LENGTH) {
  String s;
  Random random;
  int index = random.nextInt(2);
  for (int i = 0; i < length; ++i, index = 1 - index)
    s += LETTERS[index][random.nextInt(LENGTHS[index])];

  return s;
}

// TODO: duplicated from GlobalCallbacks.cpp

TRTR(CLICK_TO_CONTINUE, "Click to continue.");

void alert(const String& title, const String& msg) {
  LookAndFeel::getDefaultLookAndFeel().setUsingNativeAlertWindows(true);
  DCHECK(LookAndFeel::getDefaultLookAndFeel().isUsingNativeAlertWindows());

  AlertWindow::showMessageBox(AlertWindow::WarningIcon, title, msg,
                              CLICK_TO_CONTINUE);
}

}

void requestSupport() {
  String key = randomKey();
  File f = data::zipData(key);
  if (f == File::nonexistent) {
    alert(CANT_SUPPORT, CANT_SUPPORT_FULL + String("\n") +
          PLEASE_CONTACT + String("\n") + SUPPORT);
  } else {
    String fn = f.getFileName();
    alert(SUPPORTED,
          String::formatted(MAIL_CREATED, c_str(fn)) + "\n\n" +
          String::formatted(PLEASE_MAIL, c_str(SUPPORT)));
    String subject = String::formatted(MAIL_SUBJECT, c_str(key));
    String body = String::formatted(MAIL_ATTACH, c_str(fn)) + String("\n\n") +
      MAIL_DISCARD;
    URL url = MAILTO.withParameter("subject", subject).withParameter("body", body);
    url.launchInDefaultBrowser();
    f.revealToUser();
  }
}

void RequestSupport::registerAllTranslations() {
  CANT_SUPPORT.registerTranslation();
  CANT_SUPPORT_FULL.registerTranslation();
  CLICK_TO_CONTINUE.registerTranslation();
  MAIL_ATTACH.registerTranslation();
  MAIL_CREATED.registerTranslation();
  MAIL_DISCARD.registerTranslation();
  MAIL_SUBJECT.registerTranslation();
  PLEASE_CONTACT.registerTranslation();
  PLEASE_MAIL.registerTranslation();
  SUPPORTED.registerTranslation();
}

}  // namespace support
}  // namespace rec
