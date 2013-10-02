# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: rec/command/Command.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)


import rec.data.proto.Address_pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='rec/command/Command.proto',
  package='rec.command',
  serialized_pb='\n\x19rec/command/Command.proto\x12\x0brec.command\x1a\x1crec/data/proto/Address.proto\"E\n\x0b\x44\x65scription\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x0c\n\x04menu\x18\x02 \x03(\t\x12\x0c\n\x04\x66ull\x18\x03 \x03(\t\x12\x0c\n\x04help\x18\x04 \x01(\t\"\xe1\x04\n\x07\x43ommand\x12\n\n\x02id\x18\x01 \x01(\r\x12\x11\n\tid_string\x18\x0f \x01(\t\x12\r\n\x05index\x18\x02 \x01(\x11\x12\x10\n\x08\x63\x61tegory\x18\x03 \x01(\t\x12\x14\n\x0csubmenu_name\x18\x04 \x01(\t\x12\x19\n\x11submenu_separator\x18\x0e \x03(\r\x12&\n\x04\x64\x65sc\x18\x05 \x01(\x0b\x32\x18.rec.command.Description\x12\x10\n\x08keypress\x18\x06 \x03(\t\x12\r\n\x05\x66lags\x18\x07 \x01(\r\x12\x0e\n\x06setter\x18\x08 \x01(\t\x12\x34\n\x0bsetter_type\x18\x10 \x01(\x0e\x32\x1f.rec.command.Command.SetterType\x12\x0c\n\x04size\x18\t \x01(\r\x12\x0f\n\x07\x63\x61llout\x18\n \x01(\x08\x12\x0e\n\x06hidden\x18\x0b \x03(\t\x12\x10\n\x08\x64isabled\x18\x0c \x03(\t\x12\x0e\n\x06ticked\x18\r \x03(\t\"\x98\x01\n\x02Id\x12\x08\n\x04NONE\x10\x00\x12\t\n\x04QUIT\x10\x81 \x12\x08\n\x03\x44\x45L\x10\x82 \x12\x08\n\x03\x43UT\x10\x83 \x12\t\n\x04\x43OPY\x10\x84 \x12\n\n\x05PASTE\x10\x85 \x12\x0f\n\nSELECT_ALL\x10\x86 \x12\x11\n\x0c\x44\x45SELECT_ALL\x10\x87 \x12\x0f\n\nJUCE_START\x10\x80 \x12\r\n\x08JUCE_END\x10\x88 \x12\x0e\n\tBANK_SIZE\x10\x90N\"A\n\x05Index\x12\t\n\x05\x46IRST\x10\x00\x12\x0c\n\x08PREVIOUS\x10\x01\x12\x0b\n\x07\x43URRENT\x10\x02\x12\x08\n\x04NEXT\x10\x03\x12\x08\n\x04LAST\x10\x04\"\'\n\nSetterType\x12\n\n\x06TOGGLE\x10\x00\x12\r\n\tSELECTION\x10\x01\"1\n\x08\x43ommands\x12%\n\x07\x63ommand\x18\x01 \x03(\x0b\x32\x14.rec.command.Command')



_COMMAND_ID = _descriptor.EnumDescriptor(
  name='Id',
  full_name='rec.command.Command.Id',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='QUIT', index=1, number=4097,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='DEL', index=2, number=4098,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CUT', index=3, number=4099,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='COPY', index=4, number=4100,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PASTE', index=5, number=4101,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SELECT_ALL', index=6, number=4102,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='DESELECT_ALL', index=7, number=4103,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='JUCE_START', index=8, number=4096,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='JUCE_END', index=9, number=4104,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='BANK_SIZE', index=10, number=10000,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=493,
  serialized_end=645,
)

_COMMAND_INDEX = _descriptor.EnumDescriptor(
  name='Index',
  full_name='rec.command.Command.Index',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='FIRST', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PREVIOUS', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CURRENT', index=2, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='NEXT', index=3, number=3,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='LAST', index=4, number=4,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=647,
  serialized_end=712,
)

_COMMAND_SETTERTYPE = _descriptor.EnumDescriptor(
  name='SetterType',
  full_name='rec.command.Command.SetterType',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='TOGGLE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SELECTION', index=1, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=714,
  serialized_end=753,
)


_DESCRIPTION = _descriptor.Descriptor(
  name='Description',
  full_name='rec.command.Description',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='name', full_name='rec.command.Description.name', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='menu', full_name='rec.command.Description.menu', index=1,
      number=2, type=9, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='full', full_name='rec.command.Description.full', index=2,
      number=3, type=9, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='help', full_name='rec.command.Description.help', index=3,
      number=4, type=9, cpp_type=9, label=1,
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
  serialized_start=72,
  serialized_end=141,
)


_COMMAND = _descriptor.Descriptor(
  name='Command',
  full_name='rec.command.Command',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='rec.command.Command.id', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='id_string', full_name='rec.command.Command.id_string', index=1,
      number=15, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='index', full_name='rec.command.Command.index', index=2,
      number=2, type=17, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='category', full_name='rec.command.Command.category', index=3,
      number=3, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='submenu_name', full_name='rec.command.Command.submenu_name', index=4,
      number=4, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='submenu_separator', full_name='rec.command.Command.submenu_separator', index=5,
      number=14, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='desc', full_name='rec.command.Command.desc', index=6,
      number=5, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='keypress', full_name='rec.command.Command.keypress', index=7,
      number=6, type=9, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='flags', full_name='rec.command.Command.flags', index=8,
      number=7, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='setter', full_name='rec.command.Command.setter', index=9,
      number=8, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='setter_type', full_name='rec.command.Command.setter_type', index=10,
      number=16, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='size', full_name='rec.command.Command.size', index=11,
      number=9, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='callout', full_name='rec.command.Command.callout', index=12,
      number=10, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='hidden', full_name='rec.command.Command.hidden', index=13,
      number=11, type=9, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='disabled', full_name='rec.command.Command.disabled', index=14,
      number=12, type=9, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ticked', full_name='rec.command.Command.ticked', index=15,
      number=13, type=9, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _COMMAND_ID,
    _COMMAND_INDEX,
    _COMMAND_SETTERTYPE,
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=144,
  serialized_end=753,
)


_COMMANDS = _descriptor.Descriptor(
  name='Commands',
  full_name='rec.command.Commands',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='command', full_name='rec.command.Commands.command', index=0,
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
  serialized_start=755,
  serialized_end=804,
)

_COMMAND.fields_by_name['desc'].message_type = _DESCRIPTION
_COMMAND.fields_by_name['setter_type'].enum_type = _COMMAND_SETTERTYPE
_COMMAND_ID.containing_type = _COMMAND;
_COMMAND_INDEX.containing_type = _COMMAND;
_COMMAND_SETTERTYPE.containing_type = _COMMAND;
_COMMANDS.fields_by_name['command'].message_type = _COMMAND
DESCRIPTOR.message_types_by_name['Description'] = _DESCRIPTION
DESCRIPTOR.message_types_by_name['Command'] = _COMMAND
DESCRIPTOR.message_types_by_name['Commands'] = _COMMANDS

class Description(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _DESCRIPTION

  # @@protoc_insertion_point(class_scope:rec.command.Description)

class Command(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _COMMAND

  # @@protoc_insertion_point(class_scope:rec.command.Command)

class Commands(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _COMMANDS

  # @@protoc_insertion_point(class_scope:rec.command.Commands)


# @@protoc_insertion_point(module_scope)
