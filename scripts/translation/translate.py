#!/usr/bin/python

import sys

sys.path.append('/development/rec/genfiles/proto/rec/base')

from Trans_pb2 import TranslatedStrings

from google.protobuf import text_format

t = TranslatedStrings()

text_format.Merge(open(sys.argv[1], 'r').read(), t)
text_format.PrintMessage(t, sys.stdout)
