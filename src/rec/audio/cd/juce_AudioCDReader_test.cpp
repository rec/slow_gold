#include <stdio.h>
#include <string.h>

#include <gtest/gtest.h>

#include "juce_amalgamated.h"

#include "rec/base/scoped_ptr.h"

// #include "native/mac/juce_mac_AudioCDReader_helpers.h"

#ifdef __JUCE_MAC_AUDIOCDREADER_HELPERS_JUCEHEADER__

// Don't run this test unless we have the upated JUCE.

TEST(AudioCDReaderHelper, getElementForKey) {
  XmlDocument doc("<dict><key>foo</key><value>bar</value></dict>");
  scoped_ptr<XmlElement> xml(doc.getDocumentElement());
  EXPECT_TRUE(!getElementForKey(*xml, "bar"));
  EXPECT_EQ(getElementForKey(*xml, "foo")->getFirstChildElement()->getText(),
            "bar");
}

TEST(AudioCDReaderHelper, getIntValueForKey) {
  XmlDocument doc("<dict><key>foo</key><value>123</value></dict>");
  scoped_ptr<XmlElement> xml(doc.getDocumentElement());
  EXPECT_EQ(getIntValueForKey(*xml, "bar"), -1);
  EXPECT_EQ(getIntValueForKey(*xml, "foo"), 123);
}

namespace {

// http://www.freedb.org/freedb/rock/9608bd0b
const int SIZE = 12;
int expected[SIZE] = {2, 203, 374, 589, 818, 1070, 1326, 1522, 1692, 1744, 1922,
                      2252};

const int CDDB_ID = 0x8a08ca0b;  // No idea if this is right.

// For a real test, I need to use a CD with a known CDDB_ID.
}

TEST(AudioCDReaderHelper, getTrackOffsets) {
  Array<int> offsets;
  EXPECT_STREQ(NULL, getTrackOffsets(File("../../../data"), &offsets));

  EXPECT_EQ(offsets.size(), SIZE);

  for (int i = 0; i < SIZE; ++i)
    EXPECT_EQ(offsets[i], expected[i]);
}

TEST(AudioCDReaderHelper, CDDBIdComputation) {
  int id;
  EXPECT_STREQ(NULL, getCDDBId(File("../../../data"), &id));
  EXPECT_EQ(id, CDDB_ID);
  std::cerr << std::hex << id << "\n" << std::dec;
}

TEST(AudioCDReaderHelper, CDDBIdEndToEnd) {
  EXPECT_EQ(getCDDBId(Array<int>(expected, SIZE)), CDDB_ID);
}

#endif
