# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: rec/gui/proto/ToggleButton.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)


import rec.data.proto.Address_pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='rec/gui/proto/ToggleButton.proto',
  package='rec.gui',
  serialized_pb='\n rec/gui/proto/ToggleButton.proto\x12\x07rec.gui\x1a\x1crec/data/proto/Address.proto\"[\n\x11ToggleButtonProto\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x0f\n\x07tooltip\x18\x02 \x01(\t\x12\'\n\x07\x61\x64\x64ress\x18\x03 \x01(\x0b\x32\x16.rec.data.AddressProto')




_TOGGLEBUTTONPROTO = _descriptor.Descriptor(
  name='ToggleButtonProto',
  full_name='rec.gui.ToggleButtonProto',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='name', full_name='rec.gui.ToggleButtonProto.name', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='tooltip', full_name='rec.gui.ToggleButtonProto.tooltip', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='address', full_name='rec.gui.ToggleButtonProto.address', index=2,
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
  serialized_start=75,
  serialized_end=166,
)

_TOGGLEBUTTONPROTO.fields_by_name['address'].message_type = rec.data.proto.Address_pb2._ADDRESSPROTO
DESCRIPTOR.message_types_by_name['ToggleButtonProto'] = _TOGGLEBUTTONPROTO

class ToggleButtonProto(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _TOGGLEBUTTONPROTO

  # @@protoc_insertion_point(class_scope:rec.gui.ToggleButtonProto)


# @@protoc_insertion_point(module_scope)
