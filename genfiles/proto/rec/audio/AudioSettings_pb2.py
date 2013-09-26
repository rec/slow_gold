# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: rec/audio/AudioSettings.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)




DESCRIPTOR = _descriptor.FileDescriptor(
  name='rec/audio/AudioSettings.proto',
  package='rec.audio',
  serialized_pb='\n\x1drec/audio/AudioSettings.proto\x12\trec.audio\"\x8c\x02\n\rAudioSettings\x12\x13\n\x0bmaster_tune\x18\x01 \x01(\x01\x12\x42\n\x12\x66ile_type_for_save\x18\x02 \x01(\x0e\x32!.rec.audio.AudioSettings.FileType:\x03WAV\x12\x1a\n\x0fvolume_nudge_db\x18\x03 \x01(\x01:\x01\x31\x12\x1f\n\x13speed_nudge_percent\x18\x04 \x01(\x01:\x02\x31\x30\x12\x16\n\ntime_nudge\x18\x05 \x01(\x01:\x02\x31\x30\x12\x10\n\x08\x61utoplay\x18\x06 \x01(\x08\";\n\x08\x46ileType\x12\x08\n\x04\x41IFF\x10\x00\x12\x08\n\x04\x46LAC\x10\x01\x12\x07\n\x03OGG\x10\x02\x12\x07\n\x03WAV\x10\x03\x12\t\n\x05\x43OUNT\x10\x04')



_AUDIOSETTINGS_FILETYPE = _descriptor.EnumDescriptor(
  name='FileType',
  full_name='rec.audio.AudioSettings.FileType',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='AIFF', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='FLAC', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='OGG', index=2, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='WAV', index=3, number=3,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='COUNT', index=4, number=4,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=254,
  serialized_end=313,
)


_AUDIOSETTINGS = _descriptor.Descriptor(
  name='AudioSettings',
  full_name='rec.audio.AudioSettings',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='master_tune', full_name='rec.audio.AudioSettings.master_tune', index=0,
      number=1, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='file_type_for_save', full_name='rec.audio.AudioSettings.file_type_for_save', index=1,
      number=2, type=14, cpp_type=8, label=1,
      has_default_value=True, default_value=3,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='volume_nudge_db', full_name='rec.audio.AudioSettings.volume_nudge_db', index=2,
      number=3, type=1, cpp_type=5, label=1,
      has_default_value=True, default_value=1,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='speed_nudge_percent', full_name='rec.audio.AudioSettings.speed_nudge_percent', index=3,
      number=4, type=1, cpp_type=5, label=1,
      has_default_value=True, default_value=10,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='time_nudge', full_name='rec.audio.AudioSettings.time_nudge', index=4,
      number=5, type=1, cpp_type=5, label=1,
      has_default_value=True, default_value=10,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='autoplay', full_name='rec.audio.AudioSettings.autoplay', index=5,
      number=6, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _AUDIOSETTINGS_FILETYPE,
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=45,
  serialized_end=313,
)

_AUDIOSETTINGS.fields_by_name['file_type_for_save'].enum_type = _AUDIOSETTINGS_FILETYPE
_AUDIOSETTINGS_FILETYPE.containing_type = _AUDIOSETTINGS;
DESCRIPTOR.message_types_by_name['AudioSettings'] = _AUDIOSETTINGS

class AudioSettings(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _AUDIOSETTINGS

  # @@protoc_insertion_point(class_scope:rec.audio.AudioSettings)


# @@protoc_insertion_point(module_scope)
