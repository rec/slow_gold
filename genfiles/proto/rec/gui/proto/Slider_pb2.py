# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: rec/gui/proto/Slider.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)




DESCRIPTOR = _descriptor.FileDescriptor(
  name='rec/gui/proto/Slider.proto',
  package='rec.gui',
  serialized_pb='\n\x1arec/gui/proto/Slider.proto\x12\x07rec.gui\"\xff\x05\n\x0bSliderProto\x12\x0f\n\x07\x63\x61ption\x18\x01 \x01(\t\x12\x18\n\x0c\x63\x61ption_size\x18\x02 \x01(\t:\x02\x34\x35\x12 \n\x14text_entry_box_width\x18\x04 \x01(\t:\x02\x38\x30\x12!\n\x15text_entry_box_height\x18\x05 \x01(\t:\x02\x31\x36\x12\x0e\n\x06\x64\x65tent\x18\x06 \x01(\t\x12\x15\n\rdetent_radius\x18\x07 \x01(\t\x12\x13\n\x0btext_suffix\x18\x08 \x01(\t\x12\x0f\n\x07minimum\x18\t \x01(\t\x12\x0f\n\x07maximum\x18\n \x01(\t\x12\x10\n\x08interval\x18\x0b \x01(\t\x12)\n\x05style\x18\x15 \x01(\x0e\x32\x1a.rec.gui.SliderProto.Style\x12J\n\x17text_entry_box_position\x18\x16 \x01(\x0e\x32).rec.gui.SliderProto.TextEntryBoxPosition\"\xaa\x02\n\x05Style\x12\x14\n\x10LinearHorizontal\x10\x00\x12\x12\n\x0eLinearVertical\x10\x01\x12\r\n\tLinearBar\x10\x02\x12\x15\n\x11LinearBarVertical\x10\x03\x12\n\n\x06Rotary\x10\x04\x12\x18\n\x14RotaryHorizontalDrag\x10\x05\x12\x16\n\x12RotaryVerticalDrag\x10\x06\x12 \n\x1cRotaryHorizontalVerticalDrag\x10\x07\x12\x11\n\rIncDecButtons\x10\x08\x12\x16\n\x12TwoValueHorizontal\x10\t\x12\x14\n\x10TwoValueVertical\x10\n\x12\x18\n\x14ThreeValueHorizontal\x10\x0b\x12\x16\n\x12ThreeValueVertical\x10\x0c\"l\n\x14TextEntryBoxPosition\x12\r\n\tNoTextBox\x10\x00\x12\x0f\n\x0bTextBoxLeft\x10\x01\x12\x10\n\x0cTextBoxRight\x10\x02\x12\x10\n\x0cTextBoxAbove\x10\x03\x12\x10\n\x0cTextBoxBelow\x10\x04')



_SLIDERPROTO_STYLE = _descriptor.EnumDescriptor(
  name='Style',
  full_name='rec.gui.SliderProto.Style',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='LinearHorizontal', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='LinearVertical', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='LinearBar', index=2, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='LinearBarVertical', index=3, number=3,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='Rotary', index=4, number=4,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='RotaryHorizontalDrag', index=5, number=5,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='RotaryVerticalDrag', index=6, number=6,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='RotaryHorizontalVerticalDrag', index=7, number=7,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='IncDecButtons', index=8, number=8,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TwoValueHorizontal', index=9, number=9,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TwoValueVertical', index=10, number=10,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ThreeValueHorizontal', index=11, number=11,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ThreeValueVertical', index=12, number=12,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=399,
  serialized_end=697,
)

_SLIDERPROTO_TEXTENTRYBOXPOSITION = _descriptor.EnumDescriptor(
  name='TextEntryBoxPosition',
  full_name='rec.gui.SliderProto.TextEntryBoxPosition',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NoTextBox', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TextBoxLeft', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TextBoxRight', index=2, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TextBoxAbove', index=3, number=3,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TextBoxBelow', index=4, number=4,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=699,
  serialized_end=807,
)


_SLIDERPROTO = _descriptor.Descriptor(
  name='SliderProto',
  full_name='rec.gui.SliderProto',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='caption', full_name='rec.gui.SliderProto.caption', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='caption_size', full_name='rec.gui.SliderProto.caption_size', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=True, default_value=unicode("45", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='text_entry_box_width', full_name='rec.gui.SliderProto.text_entry_box_width', index=2,
      number=4, type=9, cpp_type=9, label=1,
      has_default_value=True, default_value=unicode("80", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='text_entry_box_height', full_name='rec.gui.SliderProto.text_entry_box_height', index=3,
      number=5, type=9, cpp_type=9, label=1,
      has_default_value=True, default_value=unicode("16", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='detent', full_name='rec.gui.SliderProto.detent', index=4,
      number=6, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='detent_radius', full_name='rec.gui.SliderProto.detent_radius', index=5,
      number=7, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='text_suffix', full_name='rec.gui.SliderProto.text_suffix', index=6,
      number=8, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='minimum', full_name='rec.gui.SliderProto.minimum', index=7,
      number=9, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='maximum', full_name='rec.gui.SliderProto.maximum', index=8,
      number=10, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='interval', full_name='rec.gui.SliderProto.interval', index=9,
      number=11, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='style', full_name='rec.gui.SliderProto.style', index=10,
      number=21, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='text_entry_box_position', full_name='rec.gui.SliderProto.text_entry_box_position', index=11,
      number=22, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _SLIDERPROTO_STYLE,
    _SLIDERPROTO_TEXTENTRYBOXPOSITION,
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=40,
  serialized_end=807,
)

_SLIDERPROTO.fields_by_name['style'].enum_type = _SLIDERPROTO_STYLE
_SLIDERPROTO.fields_by_name['text_entry_box_position'].enum_type = _SLIDERPROTO_TEXTENTRYBOXPOSITION
_SLIDERPROTO_STYLE.containing_type = _SLIDERPROTO;
_SLIDERPROTO_TEXTENTRYBOXPOSITION.containing_type = _SLIDERPROTO;
DESCRIPTOR.message_types_by_name['SliderProto'] = _SLIDERPROTO

class SliderProto(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _SLIDERPROTO

  # @@protoc_insertion_point(class_scope:rec.gui.SliderProto)


# @@protoc_insertion_point(module_scope)
