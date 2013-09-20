# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: rec/command/map/CommandMap.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)




DESCRIPTOR = _descriptor.FileDescriptor(
  name='rec/command/map/CommandMap.proto',
  package='rec.command',
  serialized_pb='\n rec/command/map/CommandMap.proto\x12\x0brec.command\"L\n\x0f\x43ommandMapEntry\x12\n\n\x02id\x18\x01 \x01(\r\x12\x11\n\tid_string\x18\x04 \x01(\t\x12\r\n\x05index\x18\x02 \x01(\x05\x12\x0b\n\x03key\x18\x03 \x03(\x0c\">\n\x0f\x43ommandMapProto\x12+\n\x05\x65ntry\x18\x01 \x03(\x0b\x32\x1c.rec.command.CommandMapEntry\"E\n\x18KeyStrokeCommandMapProto\x12)\n\x03map\x18\x01 \x01(\x0b\x32\x1c.rec.command.CommandMapProto\"@\n\x13MidiCommandMapProto\x12)\n\x03map\x18\x01 \x01(\x0b\x32\x1c.rec.command.CommandMapProto')




_COMMANDMAPENTRY = _descriptor.Descriptor(
  name='CommandMapEntry',
  full_name='rec.command.CommandMapEntry',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='rec.command.CommandMapEntry.id', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='id_string', full_name='rec.command.CommandMapEntry.id_string', index=1,
      number=4, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='index', full_name='rec.command.CommandMapEntry.index', index=2,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='key', full_name='rec.command.CommandMapEntry.key', index=3,
      number=3, type=12, cpp_type=9, label=3,
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
  serialized_start=49,
  serialized_end=125,
)


_COMMANDMAPPROTO = _descriptor.Descriptor(
  name='CommandMapProto',
  full_name='rec.command.CommandMapProto',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='entry', full_name='rec.command.CommandMapProto.entry', index=0,
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
  serialized_start=127,
  serialized_end=189,
)


_KEYSTROKECOMMANDMAPPROTO = _descriptor.Descriptor(
  name='KeyStrokeCommandMapProto',
  full_name='rec.command.KeyStrokeCommandMapProto',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='map', full_name='rec.command.KeyStrokeCommandMapProto.map', index=0,
      number=1, type=11, cpp_type=10, label=1,
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
  serialized_start=191,
  serialized_end=260,
)


_MIDICOMMANDMAPPROTO = _descriptor.Descriptor(
  name='MidiCommandMapProto',
  full_name='rec.command.MidiCommandMapProto',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='map', full_name='rec.command.MidiCommandMapProto.map', index=0,
      number=1, type=11, cpp_type=10, label=1,
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
  serialized_start=262,
  serialized_end=326,
)

_COMMANDMAPPROTO.fields_by_name['entry'].message_type = _COMMANDMAPENTRY
_KEYSTROKECOMMANDMAPPROTO.fields_by_name['map'].message_type = _COMMANDMAPPROTO
_MIDICOMMANDMAPPROTO.fields_by_name['map'].message_type = _COMMANDMAPPROTO
DESCRIPTOR.message_types_by_name['CommandMapEntry'] = _COMMANDMAPENTRY
DESCRIPTOR.message_types_by_name['CommandMapProto'] = _COMMANDMAPPROTO
DESCRIPTOR.message_types_by_name['KeyStrokeCommandMapProto'] = _KEYSTROKECOMMANDMAPPROTO
DESCRIPTOR.message_types_by_name['MidiCommandMapProto'] = _MIDICOMMANDMAPPROTO

class CommandMapEntry(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _COMMANDMAPENTRY

  # @@protoc_insertion_point(class_scope:rec.command.CommandMapEntry)

class CommandMapProto(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _COMMANDMAPPROTO

  # @@protoc_insertion_point(class_scope:rec.command.CommandMapProto)

class KeyStrokeCommandMapProto(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _KEYSTROKECOMMANDMAPPROTO

  # @@protoc_insertion_point(class_scope:rec.command.KeyStrokeCommandMapProto)

class MidiCommandMapProto(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _MIDICOMMANDMAPPROTO

  # @@protoc_insertion_point(class_scope:rec.command.MidiCommandMapProto)


# @@protoc_insertion_point(module_scope)
