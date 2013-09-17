# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: rec/gui/proto/Layout.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)




DESCRIPTOR = _descriptor.FileDescriptor(
  name='rec/gui/proto/Layout.proto',
  package='rec.gui',
  serialized_pb='\n\x1arec/gui/proto/Layout.proto\x12\x07rec.gui\"\xba\x01\n\x0bLayoutProto\x12\x37\n\x0borientation\x18\x01 \x01(\x0e\x32\".rec.gui.LayoutProto.Orientatation\x12\x0c\n\x04name\x18\x02 \x01(\t\x12$\n\x16resize_other_dimension\x18\x03 \x01(\x08:\x04true\x12\x0f\n\x07is_main\x18\x04 \x01(\x08\"-\n\rOrientatation\x12\x0e\n\nHORIZONTAL\x10\x00\x12\x0c\n\x08VERTICAL\x10\x01')



_LAYOUTPROTO_ORIENTATATION = _descriptor.EnumDescriptor(
  name='Orientatation',
  full_name='rec.gui.LayoutProto.Orientatation',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='HORIZONTAL', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='VERTICAL', index=1, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=181,
  serialized_end=226,
)


_LAYOUTPROTO = _descriptor.Descriptor(
  name='LayoutProto',
  full_name='rec.gui.LayoutProto',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='orientation', full_name='rec.gui.LayoutProto.orientation', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='name', full_name='rec.gui.LayoutProto.name', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='resize_other_dimension', full_name='rec.gui.LayoutProto.resize_other_dimension', index=2,
      number=3, type=8, cpp_type=7, label=1,
      has_default_value=True, default_value=True,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='is_main', full_name='rec.gui.LayoutProto.is_main', index=3,
      number=4, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _LAYOUTPROTO_ORIENTATATION,
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=40,
  serialized_end=226,
)

_LAYOUTPROTO.fields_by_name['orientation'].enum_type = _LAYOUTPROTO_ORIENTATATION
_LAYOUTPROTO_ORIENTATATION.containing_type = _LAYOUTPROTO;
DESCRIPTOR.message_types_by_name['LayoutProto'] = _LAYOUTPROTO

class LayoutProto(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _LAYOUTPROTO

  # @@protoc_insertion_point(class_scope:rec.gui.LayoutProto)


# @@protoc_insertion_point(module_scope)
