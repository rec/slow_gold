# Generated by the protocol buffer compiler.  DO NOT EDIT!

from google.protobuf import descriptor
from google.protobuf import message
from google.protobuf import reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)


DESCRIPTOR = descriptor.FileDescriptor(
  name='rec/widget/status/Time.proto',
  package='rec.widget.status.time',
  serialized_pb='\n\x1crec/widget/status/Time.proto\x12\x16rec.widget.status.time\x1a\x13rec/gui/Color.proto\x1a\x17rec/widget/Widget.proto\"\xfa\x02\n\x04Text\x12\"\n\x06widget\x18\x01 \x01(\x0b\x32\x12.rec.widget.Widget\x12\x39\n\tseparator\x18\x02 \x01(\x0b\x32&.rec.widget.status.time.Text.Separator\x12\x33\n\x06\x66ields\x18\x03 \x01(\x0b\x32#.rec.widget.status.time.Text.Fields\x1a]\n\tSeparator\x12\x11\n\tseparator\x18\x01 \x01(\t\x12\r\n\x05width\x18\x02 \x01(\r\x12\x14\n\x05\x66lash\x18\x03 \x01(\x08:\x05\x66\x61lse\x12\x18\n\ndisplay_ms\x18\x04 \x01(\x08:\x04true\x1a\x7f\n\x06\x46ields\x12\x14\n\x05hours\x18\x01 \x01(\x08:\x05\x66\x61lse\x12\x15\n\x07minutes\x18\x02 \x01(\x08:\x04true\x12\x15\n\x07seconds\x18\x03 \x01(\x08:\x04true\x12\x1a\n\x0cmilliseconds\x18\x04 \x01(\x08:\x04true\x12\x15\n\x06\x66rames\x18\x05 \x01(\x08:\x05\x66\x61lse\"\xc6\x02\n\x04\x44ial\x12\"\n\x06widget\x18\x01 \x01(\x0b\x32\x12.rec.widget.Widget\x12\x0f\n\x07outline\x18\x02 \x01(\r\x12\x44\n\tdirection\x18\x03 \x01(\x0e\x32&.rec.widget.status.time.Dial.Direction:\tCLOCKWISE\x12\x19\n\x11\x64isplay_lap_count\x18\x04 \x01(\x08\x12\x12\n\nzero_point\x18\x07 \x01(\x01\x12\x1b\n\rempty_on_zero\x18\x08 \x01(\x08:\x04true\x12\"\n\nfrom_color\x18\t \x01(\x0b\x32\x0e.rec.gui.Color\x12 \n\x08to_color\x18\n \x01(\x0b\x32\x0e.rec.gui.Color\"1\n\tDirection\x12\r\n\tCLOCKWISE\x10\x01\x12\x15\n\x11\x43OUNTER_CLOCKWISE\x10\x02\"\x05\n\x03\x42\x61r\"\x88\x01\n\x04Time\x12*\n\x04text\x18\x01 \x01(\x0b\x32\x1c.rec.widget.status.time.Text\x12*\n\x04\x64ial\x18\x02 \x01(\x0b\x32\x1c.rec.widget.status.time.Dial\x12(\n\x03\x62\x61r\x18\x03 \x01(\x0b\x32\x1b.rec.widget.status.time.Bar')



_DIAL_DIRECTION = descriptor.EnumDescriptor(
  name='Direction',
  full_name='rec.widget.status.time.Dial.Direction',
  filename=None,
  file=DESCRIPTOR,
  values=[
    descriptor.EnumValueDescriptor(
      name='CLOCKWISE', index=0, number=1,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='COUNTER_CLOCKWISE', index=1, number=2,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=761,
  serialized_end=810,
)


_TEXT_SEPARATOR = descriptor.Descriptor(
  name='Separator',
  full_name='rec.widget.status.time.Text.Separator',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='separator', full_name='rec.widget.status.time.Text.Separator.separator', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='width', full_name='rec.widget.status.time.Text.Separator.width', index=1,
      number=2, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='flash', full_name='rec.widget.status.time.Text.Separator.flash', index=2,
      number=3, type=8, cpp_type=7, label=1,
      has_default_value=True, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='display_ms', full_name='rec.widget.status.time.Text.Separator.display_ms', index=3,
      number=4, type=8, cpp_type=7, label=1,
      has_default_value=True, default_value=True,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=259,
  serialized_end=352,
)

_TEXT_FIELDS = descriptor.Descriptor(
  name='Fields',
  full_name='rec.widget.status.time.Text.Fields',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='hours', full_name='rec.widget.status.time.Text.Fields.hours', index=0,
      number=1, type=8, cpp_type=7, label=1,
      has_default_value=True, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='minutes', full_name='rec.widget.status.time.Text.Fields.minutes', index=1,
      number=2, type=8, cpp_type=7, label=1,
      has_default_value=True, default_value=True,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='seconds', full_name='rec.widget.status.time.Text.Fields.seconds', index=2,
      number=3, type=8, cpp_type=7, label=1,
      has_default_value=True, default_value=True,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='milliseconds', full_name='rec.widget.status.time.Text.Fields.milliseconds', index=3,
      number=4, type=8, cpp_type=7, label=1,
      has_default_value=True, default_value=True,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='frames', full_name='rec.widget.status.time.Text.Fields.frames', index=4,
      number=5, type=8, cpp_type=7, label=1,
      has_default_value=True, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=354,
  serialized_end=481,
)

_TEXT = descriptor.Descriptor(
  name='Text',
  full_name='rec.widget.status.time.Text',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='widget', full_name='rec.widget.status.time.Text.widget', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='separator', full_name='rec.widget.status.time.Text.separator', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='fields', full_name='rec.widget.status.time.Text.fields', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[_TEXT_SEPARATOR, _TEXT_FIELDS, ],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=103,
  serialized_end=481,
)


_DIAL = descriptor.Descriptor(
  name='Dial',
  full_name='rec.widget.status.time.Dial',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='widget', full_name='rec.widget.status.time.Dial.widget', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='outline', full_name='rec.widget.status.time.Dial.outline', index=1,
      number=2, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='direction', full_name='rec.widget.status.time.Dial.direction', index=2,
      number=3, type=14, cpp_type=8, label=1,
      has_default_value=True, default_value=1,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='display_lap_count', full_name='rec.widget.status.time.Dial.display_lap_count', index=3,
      number=4, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='zero_point', full_name='rec.widget.status.time.Dial.zero_point', index=4,
      number=7, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='empty_on_zero', full_name='rec.widget.status.time.Dial.empty_on_zero', index=5,
      number=8, type=8, cpp_type=7, label=1,
      has_default_value=True, default_value=True,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='from_color', full_name='rec.widget.status.time.Dial.from_color', index=6,
      number=9, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='to_color', full_name='rec.widget.status.time.Dial.to_color', index=7,
      number=10, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _DIAL_DIRECTION,
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=484,
  serialized_end=810,
)


_BAR = descriptor.Descriptor(
  name='Bar',
  full_name='rec.widget.status.time.Bar',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=812,
  serialized_end=817,
)


_TIME = descriptor.Descriptor(
  name='Time',
  full_name='rec.widget.status.time.Time',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='text', full_name='rec.widget.status.time.Time.text', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='dial', full_name='rec.widget.status.time.Time.dial', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='bar', full_name='rec.widget.status.time.Time.bar', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=820,
  serialized_end=956,
)

import rec.gui.Color_pb2
import rec.widget.Widget_pb2

_TEXT_SEPARATOR.containing_type = _TEXT;
_TEXT_FIELDS.containing_type = _TEXT;
_TEXT.fields_by_name['widget'].message_type = rec.widget.Widget_pb2._WIDGET
_TEXT.fields_by_name['separator'].message_type = _TEXT_SEPARATOR
_TEXT.fields_by_name['fields'].message_type = _TEXT_FIELDS
_DIAL.fields_by_name['widget'].message_type = rec.widget.Widget_pb2._WIDGET
_DIAL.fields_by_name['direction'].enum_type = _DIAL_DIRECTION
_DIAL.fields_by_name['from_color'].message_type = rec.gui.Color_pb2._COLOR
_DIAL.fields_by_name['to_color'].message_type = rec.gui.Color_pb2._COLOR
_DIAL_DIRECTION.containing_type = _DIAL;
_TIME.fields_by_name['text'].message_type = _TEXT
_TIME.fields_by_name['dial'].message_type = _DIAL
_TIME.fields_by_name['bar'].message_type = _BAR

class Text(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  
  class Separator(message.Message):
    __metaclass__ = reflection.GeneratedProtocolMessageType
    DESCRIPTOR = _TEXT_SEPARATOR
    
    # @@protoc_insertion_point(class_scope:rec.widget.status.time.Text.Separator)
  
  class Fields(message.Message):
    __metaclass__ = reflection.GeneratedProtocolMessageType
    DESCRIPTOR = _TEXT_FIELDS
    
    # @@protoc_insertion_point(class_scope:rec.widget.status.time.Text.Fields)
  DESCRIPTOR = _TEXT
  
  # @@protoc_insertion_point(class_scope:rec.widget.status.time.Text)

class Dial(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _DIAL
  
  # @@protoc_insertion_point(class_scope:rec.widget.status.time.Dial)

class Bar(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _BAR
  
  # @@protoc_insertion_point(class_scope:rec.widget.status.time.Bar)

class Time(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _TIME
  
  # @@protoc_insertion_point(class_scope:rec.widget.status.time.Time)

# @@protoc_insertion_point(module_scope)