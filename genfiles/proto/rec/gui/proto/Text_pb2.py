# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: rec/gui/proto/Text.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)




DESCRIPTOR = _descriptor.FileDescriptor(
  name='rec/gui/proto/Text.proto',
  package='rec.gui',
  serialized_pb='\n\x18rec/gui/proto/Text.proto\x12\x07rec.gui\"\x1e\n\tTextProto\x12\x11\n\tmultiline\x18\x01 \x01(\x08')




_TEXTPROTO = _descriptor.Descriptor(
  name='TextProto',
  full_name='rec.gui.TextProto',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='multiline', full_name='rec.gui.TextProto.multiline', index=0,
      number=1, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
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
  serialized_start=37,
  serialized_end=67,
)

DESCRIPTOR.message_types_by_name['TextProto'] = _TEXTPROTO

class TextProto(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _TEXTPROTO

  # @@protoc_insertion_point(class_scope:rec.gui.TextProto)


# @@protoc_insertion_point(module_scope)