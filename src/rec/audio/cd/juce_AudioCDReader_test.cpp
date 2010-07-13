#include <stdio.h>
#include <string.h>

#include <gtest/gtest.h>

#include "juce_amalgamated.h"

#include "rec/base/scoped_ptr.h"

#ifdef __JUCE_MAC_AUDIOCDREADER_HELPERS_JUCEHEADER__

// Don't run this test unless we have the upated JUCE.

TEST(AudioCDReaderHelper, getValueForKey) {
  XmlDocument doc("<dict><key>foo</key><value>bar</value></dict>");
  scoped_ptr<XmlElement> xml(doc.getDocumentElement());
  EXPECT_TRUE(!getValueForKey(*xml, "bar"));
  EXPECT_EQ(getValueForKey(*xml, "foo")->getFirstChildElement()->getText(), "bar");
}

TEST(AudioCDReaderHelper, getIntValueForKey) {
  XmlDocument doc("<dict><key>foo</key><value>123</value></dict>");
  scoped_ptr<XmlElement> xml(doc.getDocumentElement());
  EXPECT_EQ(getIntValueForKey(*xml, "bar"), -1);
  EXPECT_EQ(getIntValueForKey(*xml, "foo"), 123);
}

TEST(AudioCDReaderHelper, getTrackOffsets) {
  Array<int> offsets;
  EXPECT_STREQ(NULL, getTrackOffsets(File("../../../data"), &offsets));

  static const int SIZE = 8;
  int expected[SIZE] = {150, 2029, 7579, 9854, 26741, 27191, 33533, 35945};
  EXPECT_EQ(offsets.size(), SIZE);

  for (int i = 0; i < SIZE; ++i)
    EXPECT_EQ(offsets[i], expected[i]);
}

#endif
