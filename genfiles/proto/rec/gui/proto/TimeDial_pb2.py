# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: rec/gui/proto/TimeDial.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)


import rec.gui.Color_pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='rec/gui/proto/TimeDial.proto',
  package='rec.gui',
  serialized_pb='\n\x1crec/gui/proto/TimeDial.proto\x12\x07rec.gui\x1a\x13rec/gui/Color.proto\".\n\rTimeDialProto\x12\x1d\n\x05\x63olor\x18\x01 \x03(\x0b\x32\x0e.rec.gui.Color')




_TIMEDIALPROTO = _descriptor.Descriptor(
  name='TimeDialProto',
  full_name='rec.gui.TimeDialProto',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='color', full_name='rec.gui.TimeDialProto.color', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
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
  serialized_start=62,
  serialized_end=108,
)

_TIMEDIALPROTO.fields_by_name['color'].message_type = rec.gui.Color_pb2._COLOR
DESCRIPTOR.message_types_by_name['TimeDialProto'] = _TIMEDIALPROTO

class TimeDialProto(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _TIMEDIALPROTO

  # @@protoc_insertion_point(class_scope:rec.gui.TimeDialProto)


# @@protoc_insertion_point(module_scope)
