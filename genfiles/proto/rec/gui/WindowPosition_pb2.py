# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: rec/gui/WindowPosition.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)


import rec.gui.Geometry_pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='rec/gui/WindowPosition.proto',
  package='rec.gui',
  serialized_pb='\n\x1crec/gui/WindowPosition.proto\x12\x07rec.gui\x1a\x16rec/gui/Geometry.proto\"\'\n\x0eWindowPosition\x12\x15\n\rjuce_position\x18\x01 \x01(\t')




_WINDOWPOSITION = _descriptor.Descriptor(
  name='WindowPosition',
  full_name='rec.gui.WindowPosition',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='juce_position', full_name='rec.gui.WindowPosition.juce_position', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
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
  serialized_start=65,
  serialized_end=104,
)

DESCRIPTOR.message_types_by_name['WindowPosition'] = _WINDOWPOSITION

class WindowPosition(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _WINDOWPOSITION

  # @@protoc_insertion_point(class_scope:rec.gui.WindowPosition)


# @@protoc_insertion_point(module_scope)
