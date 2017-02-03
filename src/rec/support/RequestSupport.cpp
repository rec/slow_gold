#include "rec/support/RequestSupport.h"

#include "rec/base/Trans.h"
#include "rec/data/ZipData.h"

TRAN(CANT_SUPPORT, "Couldn't Create A Support Request");
TRAN(CANT_SUPPORT_FULL, "Sorry, we were unable to create a support request.");
TRAN(MAIL_ATTACH, "Please attach the file on your desktop named %s to this "
                                    "email and send it to us!");
TRAN(MAIL_CREATED, "A Support Request file named \"%s\" "
                                      "was created on your desktop.");
TRAN(MAIL_DISCARD, "You can throw the file away once your email is sent.");
TRAN(MAIL_SUBJECT, "Support Request: %s");
TRAN(PLEASE_CONTACT, "Please contact World Wide Woodshed support at");
TRAN(PLEASE_MAIL, "Please mail the file to %s and then you can throw it away.");
TRAN(SUPPORTED, "A Support Request Was Created On Your Desktop");

namespace rec {
namespace support {

using namespace juce;

namespace {

const String SUPPORT = "support@worldwidewoodshed.com";
const URL MAILTO("mailto:" + URL::addEscapeChars(SUPPORT, true));

const char* const VOWELS = "aeiouy";
const char* const CONSONANTS = "bdfgjlmnprsvwxz";
const char* const LETTERS[] = {VOWELS, CONSONANTS};
const size_t LENGTHS[] = {strlen(VOWELS), strlen(CONSONANTS)};

const int LENGTH = 10;

String randomKey(int length = LENGTH) {
    String s;
    Random random;
    int index = random.nextInt(2);
    for (int i = 0; i < length; ++i, index = 1 - index)
        s += LETTERS[index][random.nextInt(LENGTHS[index])];

    return s;
}

TRAN(CLICK_TO_CONTINUE, "Click to continue.");

void alert(const String& title, const String& msg) {
    LookAndFeel::getDefaultLookAndFeel().setUsingNativeAlertWindows(true);
    DCHECK(LookAndFeel::getDefaultLookAndFeel().isUsingNativeAlertWindows());

    AlertWindow::showMessageBox(AlertWindow::WarningIcon, title, msg,
                                                            t_CLICK_TO_CONTINUE);
}

}

void requestSupport() {
    String key = randomKey();
    File f = data::zipData(key);
    if (f == File::nonexistent) {
        alert(t_CANT_SUPPORT, t_CANT_SUPPORT_FULL + String("\n") +
                    t_PLEASE_CONTACT + String("\n") + SUPPORT);
    } else {
        String fn = f.getFileName();
        alert(t_SUPPORTED,
                    String::formatted(t_MAIL_CREATED, c_str(fn)) + "\n\n" +
                    String::formatted(t_PLEASE_MAIL, c_str(SUPPORT)));
        String subject = String::formatted(t_MAIL_SUBJECT, c_str(key));
        String body = String::formatted(t_MAIL_ATTACH, c_str(fn)) + String("\n\n") +
            t_MAIL_DISCARD;
        URL url = MAILTO.withParameter("subject", subject).withParameter("body", body);
        url.launchInDefaultBrowser();
        f.revealToUser();
    }
}

}  // namespace support
}  // namespace rec
