# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: rec/gui/proto/Component.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)


import rec.gui.proto.Button_pb2
import rec.gui.proto.ComboBox_pb2
import rec.gui.proto.Label_pb2
import rec.gui.proto.Panel_pb2
import rec.gui.proto.Resizer_pb2
import rec.gui.proto.Slider_pb2
import rec.gui.proto.ToggleButton_pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='rec/gui/proto/Component.proto',
  package='rec.gui',
  serialized_pb='\n\x1drec/gui/proto/Component.proto\x12\x07rec.gui\x1a\x1arec/gui/proto/Button.proto\x1a\x1crec/gui/proto/ComboBox.proto\x1a\x19rec/gui/proto/Label.proto\x1a\x19rec/gui/proto/Panel.proto\x1a\x1brec/gui/proto/Resizer.proto\x1a\x1arec/gui/proto/Slider.proto\x1a rec/gui/proto/ToggleButton.proto\"\xb8\x02\n\x0e\x43omponentProto\x12\x0c\n\x04name\x18\x01 \x01(\t\x12$\n\x06\x62utton\x18\x02 \x01(\x0b\x32\x14.rec.gui.ButtonProto\x12)\n\tcombo_box\x18\x03 \x01(\x0b\x32\x16.rec.gui.ComboBoxProto\x12\"\n\x05label\x18\x04 \x01(\x0b\x32\x13.rec.gui.LabelProto\x12\"\n\x05panel\x18\x05 \x01(\x0b\x32\x13.rec.gui.PanelProto\x12&\n\x07resizer\x18\x06 \x01(\x0b\x32\x15.rec.gui.ResizerProto\x12$\n\x06slider\x18\x07 \x01(\x0b\x32\x14.rec.gui.SliderProto\x12\x31\n\rtoggle_button\x18\x08 \x01(\x0b\x32\x1a.rec.gui.ToggleButtonProto\"=\n\x0f\x43omponentProtos\x12*\n\tcomponent\x18\x01 \x03(\x0b\x32\x17.rec.gui.ComponentProto')




_COMPONENTPROTO = _descriptor.Descriptor(
  name='ComponentProto',
  full_name='rec.gui.ComponentProto',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='name', full_name='rec.gui.ComponentProto.name', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='button', full_name='rec.gui.ComponentProto.button', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='combo_box', full_name='rec.gui.ComponentProto.combo_box', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='label', full_name='rec.gui.ComponentProto.label', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='panel', full_name='rec.gui.ComponentProto.panel', index=4,
      number=5, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='resizer', full_name='rec.gui.ComponentProto.resizer', index=5,
      number=6, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='slider', full_name='rec.gui.ComponentProto.slider', index=6,
      number=7, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='toggle_button', full_name='rec.gui.ComponentProto.toggle_button', index=7,
      number=8, type=11, cpp_type=10, label=1,
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
  serialized_start=246,
  serialized_end=558,
)


_COMPONENTPROTOS = _descriptor.Descriptor(
  name='ComponentProtos',
  full_name='rec.gui.ComponentProtos',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='component', full_name='rec.gui.ComponentProtos.component', index=0,
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
  serialized_start=560,
  serialized_end=621,
)

_COMPONENTPROTO.fields_by_name['button'].message_type = rec.gui.proto.Button_pb2._BUTTONPROTO
_COMPONENTPROTO.fields_by_name['combo_box'].message_type = rec.gui.proto.ComboBox_pb2._COMBOBOXPROTO
_COMPONENTPROTO.fields_by_name['label'].message_type = rec.gui.proto.Label_pb2._LABELPROTO
_COMPONENTPROTO.fields_by_name['panel'].message_type = rec.gui.proto.Panel_pb2._PANELPROTO
_COMPONENTPROTO.fields_by_name['resizer'].message_type = rec.gui.proto.Resizer_pb2._RESIZERPROTO
_COMPONENTPROTO.fields_by_name['slider'].message_type = rec.gui.proto.Slider_pb2._SLIDERPROTO
_COMPONENTPROTO.fields_by_name['toggle_button'].message_type = rec.gui.proto.ToggleButton_pb2._TOGGLEBUTTONPROTO
_COMPONENTPROTOS.fields_by_name['component'].message_type = _COMPONENTPROTO
DESCRIPTOR.message_types_by_name['ComponentProto'] = _COMPONENTPROTO
DESCRIPTOR.message_types_by_name['ComponentProtos'] = _COMPONENTPROTOS

class ComponentProto(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _COMPONENTPROTO

  # @@protoc_insertion_point(class_scope:rec.gui.ComponentProto)

class ComponentProtos(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _COMPONENTPROTOS

  # @@protoc_insertion_point(class_scope:rec.gui.ComponentProtos)


# @@protoc_insertion_point(module_scope)
