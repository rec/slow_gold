# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: rec/app/AppSettings.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)




DESCRIPTOR = _descriptor.FileDescriptor(
  name='rec/app/AppSettings.proto',
  package='rec.app',
  serialized_pb='\n\x19rec/app/AppSettings.proto\x12\x07rec.app\"\xfe\x01\n\x0b\x41ppSettings\x12\x1c\n\x14last_update_finished\x18\x01 \x01(\x03\x12\x19\n\nregistered\x18\x02 \x01(\x08:\x05\x66\x61lse\x12\x33\n\x08language\x18\x03 \x01(\x0e\x32\x1d.rec.app.AppSettings.Language:\x02\x45N\x12!\n\x12windows_registered\x18\x04 \x01(\x08:\x05\x66\x61lse\"^\n\x08Language\x12\x06\n\x02\x44\x45\x10\x00\x12\x06\n\x02\x45N\x10\x01\x12\x06\n\x02\x45S\x10\x02\x12\x06\n\x02\x46R\x10\x03\x12\x06\n\x02ID\x10\x04\x12\t\n\x05\x46IRST\x10\x00\x12\x08\n\x04LAST\x10\x04\x12\x11\n\x04NONE\x10\xff\xff\xff\xff\xff\xff\xff\xff\xff\x01\x1a\x02\x10\x01')



_APPSETTINGS_LANGUAGE = _descriptor.EnumDescriptor(
  name='Language',
  full_name='rec.app.AppSettings.Language',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='DE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='EN', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ES', index=2, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='FR', index=3, number=3,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ID', index=4, number=4,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='FIRST', index=5, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='LAST', index=6, number=4,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='NONE', index=7, number=-1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=_descriptor._ParseOptions(descriptor_pb2.EnumOptions(), '\020\001'),
  serialized_start=199,
  serialized_end=293,
)


_APPSETTINGS = _descriptor.Descriptor(
  name='AppSettings',
  full_name='rec.app.AppSettings',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='last_update_finished', full_name='rec.app.AppSettings.last_update_finished', index=0,
      number=1, type=3, cpp_type=2, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='registered', full_name='rec.app.AppSettings.registered', index=1,
      number=2, type=8, cpp_type=7, label=1,
      has_default_value=True, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='language', full_name='rec.app.AppSettings.language', index=2,
      number=3, type=14, cpp_type=8, label=1,
      has_default_value=True, default_value=1,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='windows_registered', full_name='rec.app.AppSettings.windows_registered', index=3,
      number=4, type=8, cpp_type=7, label=1,
      has_default_value=True, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _APPSETTINGS_LANGUAGE,
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=39,
  serialized_end=293,
)

_APPSETTINGS.fields_by_name['language'].enum_type = _APPSETTINGS_LANGUAGE
_APPSETTINGS_LANGUAGE.containing_type = _APPSETTINGS;
DESCRIPTOR.message_types_by_name['AppSettings'] = _APPSETTINGS

class AppSettings(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _APPSETTINGS

  # @@protoc_insertion_point(class_scope:rec.app.AppSettings)


_APPSETTINGS_LANGUAGE.has_options = True
_APPSETTINGS_LANGUAGE._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), '\020\001')
# @@protoc_insertion_point(module_scope)
