# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: rec/gui/proto/ComboBox.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)


import rec.data.proto.Address_pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='rec/gui/proto/ComboBox.proto',
  package='rec.gui',
  serialized_pb='\n\x1crec/gui/proto/ComboBox.proto\x12\x07rec.gui\x1a\x1crec/data/proto/Address.proto\"[\n\rComboBoxProto\x12\x0c\n\x04item\x18\x01 \x03(\t\x12\x0f\n\x07tooltip\x18\x02 \x01(\t\x12+\n\x0c\x64\x61ta_address\x18\x03 \x01(\x0b\x32\x15.rec.data.DataAddress')




_COMBOBOXPROTO = _descriptor.Descriptor(
  name='ComboBoxProto',
  full_name='rec.gui.ComboBoxProto',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='item', full_name='rec.gui.ComboBoxProto.item', index=0,
      number=1, type=9, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='tooltip', full_name='rec.gui.ComboBoxProto.tooltip', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='data_address', full_name='rec.gui.ComboBoxProto.data_address', index=2,
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
  serialized_start=71,
  serialized_end=162,
)

_COMBOBOXPROTO.fields_by_name['data_address'].message_type = rec.data.proto.Address_pb2._DATAADDRESS
DESCRIPTOR.message_types_by_name['ComboBoxProto'] = _COMBOBOXPROTO

class ComboBoxProto(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _COMBOBOXPROTO

  # @@protoc_insertion_point(class_scope:rec.gui.ComboBoxProto)


# @@protoc_insertion_point(module_scope)
