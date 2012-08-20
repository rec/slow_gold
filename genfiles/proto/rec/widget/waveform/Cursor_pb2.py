# Generated by the protocol buffer compiler.  DO NOT EDIT!

from google.protobuf import descriptor
from google.protobuf import message
from google.protobuf import reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)


DESCRIPTOR = descriptor.FileDescriptor(
  name='rec/widget/waveform/Cursor.proto',
  package='rec.widget.waveform',
  serialized_pb='\n rec/widget/waveform/Cursor.proto\x12\x13rec.widget.waveform\x1a\x17rec/widget/Widget.proto\x1a\x16rec/gui/Geometry.proto\"\xa5\x02\n\x0b\x43ursorProto\x12\"\n\x06widget\x18\x01 \x01(\x0b\x32\x12.rec.widget.Widget\x12\x10\n\x05width\x18\x02 \x01(\r:\x01\x31\x12\x18\n\rdisplay_width\x18\x03 \x01(\r:\x01\x33\x12\x1a\n\x0f\x63omponent_width\x18\x04 \x01(\r:\x01\x39\x12\x46\n\x04type\x18\x05 \x01(\x0e\x32%.rec.widget.waveform.CursorProto.Type:\x11PLAYBACK_POSITION\x12\x1b\n\x04line\x18\x06 \x01(\x0b\x32\r.rec.gui.Line\"E\n\x04Type\x12\x08\n\x04NONE\x10\x00\x12\x15\n\x11PLAYBACK_POSITION\x10\x01\x12\x0e\n\nLOOP_START\x10\x02\x12\x0c\n\x08LOOP_END\x10\x03')



_CURSORPROTO_TYPE = descriptor.EnumDescriptor(
  name='Type',
  full_name='rec.widget.waveform.CursorProto.Type',
  filename=None,
  file=DESCRIPTOR,
  values=[
    descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='PLAYBACK_POSITION', index=1, number=1,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='LOOP_START', index=2, number=2,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='LOOP_END', index=3, number=3,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=331,
  serialized_end=400,
)


_CURSORPROTO = descriptor.Descriptor(
  name='CursorProto',
  full_name='rec.widget.waveform.CursorProto',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='widget', full_name='rec.widget.waveform.CursorProto.widget', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='width', full_name='rec.widget.waveform.CursorProto.width', index=1,
      number=2, type=13, cpp_type=3, label=1,
      has_default_value=True, default_value=1,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='display_width', full_name='rec.widget.waveform.CursorProto.display_width', index=2,
      number=3, type=13, cpp_type=3, label=1,
      has_default_value=True, default_value=3,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='component_width', full_name='rec.widget.waveform.CursorProto.component_width', index=3,
      number=4, type=13, cpp_type=3, label=1,
      has_default_value=True, default_value=9,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='type', full_name='rec.widget.waveform.CursorProto.type', index=4,
      number=5, type=14, cpp_type=8, label=1,
      has_default_value=True, default_value=1,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='line', full_name='rec.widget.waveform.CursorProto.line', index=5,
      number=6, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _CURSORPROTO_TYPE,
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=107,
  serialized_end=400,
)

import rec.widget.Widget_pb2
import rec.gui.Geometry_pb2

_CURSORPROTO.fields_by_name['widget'].message_type = rec.widget.Widget_pb2._WIDGET
_CURSORPROTO.fields_by_name['type'].enum_type = _CURSORPROTO_TYPE
_CURSORPROTO.fields_by_name['line'].message_type = rec.gui.Geometry_pb2._LINE
_CURSORPROTO_TYPE.containing_type = _CURSORPROTO;

class CursorProto(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _CURSORPROTO
  
  # @@protoc_insertion_point(class_scope:rec.widget.waveform.CursorProto)

# @@protoc_insertion_point(module_scope)