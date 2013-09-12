# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: rec/program/Menu.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)


import rec.command.Command_pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='rec/program/Menu.proto',
  package='rec.program',
  serialized_pb='\n\x16rec/program/Menu.proto\x12\x0brec.program\x1a\x19rec/command/Command.proto\"B\n\tMenuEntry\x12\n\n\x02id\x18\x01 \x03(\r\x12\x0f\n\x07submenu\x18\x02 \x01(\t\x12\x18\n\x10\x63\x61llout_function\x18\x03 \x01(\t\"m\n\x04Menu\x12-\n\x0b\x64\x65scription\x18\x01 \x01(\x0b\x32\x18.rec.command.Description\x12\x0f\n\x07\x65xtends\x18\x02 \x01(\t\x12%\n\x05\x65ntry\x18\x03 \x03(\x0b\x32\x16.rec.program.MenuEntry\"(\n\x05Menus\x12\x1f\n\x04menu\x18\x01 \x03(\x0b\x32\x11.rec.program.Menu\"F\n\x07MenuBar\x12-\n\x0b\x64\x65scription\x18\x01 \x01(\x0b\x32\x18.rec.command.Description\x12\x0c\n\x04menu\x18\x02 \x03(\t\"g\n\x0eMenuCollection\x12-\n\x0b\x64\x65scription\x18\x01 \x01(\x0b\x32\x18.rec.command.Description\x12&\n\x08menu_bar\x18\x02 \x03(\x0b\x32\x14.rec.program.MenuBar')




_MENUENTRY = _descriptor.Descriptor(
  name='MenuEntry',
  full_name='rec.program.MenuEntry',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='rec.program.MenuEntry.id', index=0,
      number=1, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='submenu', full_name='rec.program.MenuEntry.submenu', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='callout_function', full_name='rec.program.MenuEntry.callout_function', index=2,
      number=3, type=9, cpp_type=9, label=1,
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
  serialized_start=66,
  serialized_end=132,
)


_MENU = _descriptor.Descriptor(
  name='Menu',
  full_name='rec.program.Menu',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='description', full_name='rec.program.Menu.description', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='extends', full_name='rec.program.Menu.extends', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='entry', full_name='rec.program.Menu.entry', index=2,
      number=3, type=11, cpp_type=10, label=3,
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
  serialized_start=134,
  serialized_end=243,
)


_MENUS = _descriptor.Descriptor(
  name='Menus',
  full_name='rec.program.Menus',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='menu', full_name='rec.program.Menus.menu', index=0,
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
  serialized_start=245,
  serialized_end=285,
)


_MENUBAR = _descriptor.Descriptor(
  name='MenuBar',
  full_name='rec.program.MenuBar',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='description', full_name='rec.program.MenuBar.description', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='menu', full_name='rec.program.MenuBar.menu', index=1,
      number=2, type=9, cpp_type=9, label=3,
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
  serialized_start=287,
  serialized_end=357,
)


_MENUCOLLECTION = _descriptor.Descriptor(
  name='MenuCollection',
  full_name='rec.program.MenuCollection',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='description', full_name='rec.program.MenuCollection.description', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='menu_bar', full_name='rec.program.MenuCollection.menu_bar', index=1,
      number=2, type=11, cpp_type=10, label=3,
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
  serialized_start=359,
  serialized_end=462,
)

_MENU.fields_by_name['description'].message_type = rec.command.Command_pb2._DESCRIPTION
_MENU.fields_by_name['entry'].message_type = _MENUENTRY
_MENUS.fields_by_name['menu'].message_type = _MENU
_MENUBAR.fields_by_name['description'].message_type = rec.command.Command_pb2._DESCRIPTION
_MENUCOLLECTION.fields_by_name['description'].message_type = rec.command.Command_pb2._DESCRIPTION
_MENUCOLLECTION.fields_by_name['menu_bar'].message_type = _MENUBAR
DESCRIPTOR.message_types_by_name['MenuEntry'] = _MENUENTRY
DESCRIPTOR.message_types_by_name['Menu'] = _MENU
DESCRIPTOR.message_types_by_name['Menus'] = _MENUS
DESCRIPTOR.message_types_by_name['MenuBar'] = _MENUBAR
DESCRIPTOR.message_types_by_name['MenuCollection'] = _MENUCOLLECTION

class MenuEntry(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _MENUENTRY

  # @@protoc_insertion_point(class_scope:rec.program.MenuEntry)

class Menu(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _MENU

  # @@protoc_insertion_point(class_scope:rec.program.Menu)

class Menus(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _MENUS

  # @@protoc_insertion_point(class_scope:rec.program.Menus)

class MenuBar(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _MENUBAR

  # @@protoc_insertion_point(class_scope:rec.program.MenuBar)

class MenuCollection(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _MENUCOLLECTION

  # @@protoc_insertion_point(class_scope:rec.program.MenuCollection)


# @@protoc_insertion_point(module_scope)
