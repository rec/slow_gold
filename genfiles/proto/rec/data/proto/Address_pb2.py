# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: rec/data/proto/Address.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)




DESCRIPTOR = _descriptor.FileDescriptor(
  name='rec/data/proto/Address.proto',
  package='rec.data',
  serialized_pb='\n\x1crec/data/proto/Address.proto\x12\x08rec.data\"\xc9\x01\n\x0c\x41\x64\x64ressProto\x12)\n\x04part\x18\x01 \x03(\x0b\x32\x1b.rec.data.AddressProto.Part\x12+\n\x05scope\x18\x02 \x01(\x0e\x32\x1c.rec.data.AddressProto.Scope\x12\x11\n\ttype_name\x18\x03 \x01(\t\x1a#\n\x04Part\x12\r\n\x05index\x18\x01 \x01(\r\x12\x0c\n\x04name\x18\x02 \x01(\t\")\n\x05Scope\x12\x0e\n\nFILE_SCOPE\x10\x00\x12\x10\n\x0cGLOBAL_SCOPE\x10\x01')



_ADDRESSPROTO_SCOPE = _descriptor.EnumDescriptor(
  name='Scope',
  full_name='rec.data.AddressProto.Scope',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='FILE_SCOPE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='GLOBAL_SCOPE', index=1, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=203,
  serialized_end=244,
)


_ADDRESSPROTO_PART = _descriptor.Descriptor(
  name='Part',
  full_name='rec.data.AddressProto.Part',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='index', full_name='rec.data.AddressProto.Part.index', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='name', full_name='rec.data.AddressProto.Part.name', index=1,
      number=2, type=9, cpp_type=9, label=1,
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
  serialized_start=166,
  serialized_end=201,
)

_ADDRESSPROTO = _descriptor.Descriptor(
  name='AddressProto',
  full_name='rec.data.AddressProto',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='part', full_name='rec.data.AddressProto.part', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='scope', full_name='rec.data.AddressProto.scope', index=1,
      number=2, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='type_name', full_name='rec.data.AddressProto.type_name', index=2,
      number=3, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[_ADDRESSPROTO_PART, ],
  enum_types=[
    _ADDRESSPROTO_SCOPE,
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=43,
  serialized_end=244,
)

_ADDRESSPROTO_PART.containing_type = _ADDRESSPROTO;
_ADDRESSPROTO.fields_by_name['part'].message_type = _ADDRESSPROTO_PART
_ADDRESSPROTO.fields_by_name['scope'].enum_type = _ADDRESSPROTO_SCOPE
_ADDRESSPROTO_SCOPE.containing_type = _ADDRESSPROTO;
DESCRIPTOR.message_types_by_name['AddressProto'] = _ADDRESSPROTO

class AddressProto(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType

  class Part(_message.Message):
    __metaclass__ = _reflection.GeneratedProtocolMessageType
    DESCRIPTOR = _ADDRESSPROTO_PART

    # @@protoc_insertion_point(class_scope:rec.data.AddressProto.Part)
  DESCRIPTOR = _ADDRESSPROTO

  # @@protoc_insertion_point(class_scope:rec.data.AddressProto)


# @@protoc_insertion_point(module_scope)
