# Generated by the protocol buffer compiler.  DO NOT EDIT!

from google.protobuf import descriptor
from google.protobuf import message
from google.protobuf import reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)


DESCRIPTOR = descriptor.FileDescriptor(
  name='rec/gui/RecentFiles.proto',
  package='rec.gui',
  serialized_pb='\n\x19rec/gui/RecentFiles.proto\x12\x07rec.gui\x1a\x1frec/util/file/VirtualFile.proto\x1a\x18rec/music/Metadata.proto\"p\n\nRecentFile\x12\x11\n\ttimestamp\x18\x01 \x01(\x03\x12(\n\x04\x66ile\x18\x02 \x01(\x0b\x32\x1a.rec.util.file.VirtualFile\x12%\n\x08metadata\x18\x03 \x01(\x0b\x32\x13.rec.music.Metadata\"i\n\x0bRecentFiles\x12!\n\x04\x66ile\x18\x03 \x03(\x0b\x32\x13.rec.gui.RecentFile\x12\x15\n\tmax_files\x18\x04 \x01(\x05:\x02\x31\x36\x12 \n\x12reload_most_recent\x18\x05 \x01(\x08:\x04true')




_RECENTFILE = descriptor.Descriptor(
  name='RecentFile',
  full_name='rec.gui.RecentFile',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='timestamp', full_name='rec.gui.RecentFile.timestamp', index=0,
      number=1, type=3, cpp_type=2, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='file', full_name='rec.gui.RecentFile.file', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='metadata', full_name='rec.gui.RecentFile.metadata', index=2,
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
  serialized_start=97,
  serialized_end=209,
)


_RECENTFILES = descriptor.Descriptor(
  name='RecentFiles',
  full_name='rec.gui.RecentFiles',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='file', full_name='rec.gui.RecentFiles.file', index=0,
      number=3, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='max_files', full_name='rec.gui.RecentFiles.max_files', index=1,
      number=4, type=5, cpp_type=1, label=1,
      has_default_value=True, default_value=16,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='reload_most_recent', full_name='rec.gui.RecentFiles.reload_most_recent', index=2,
      number=5, type=8, cpp_type=7, label=1,
      has_default_value=True, default_value=True,
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
  serialized_start=211,
  serialized_end=316,
)

import rec.util.file.VirtualFile_pb2
import rec.music.Metadata_pb2

_RECENTFILE.fields_by_name['file'].message_type = rec.util.file.VirtualFile_pb2._VIRTUALFILE
_RECENTFILE.fields_by_name['metadata'].message_type = rec.music.Metadata_pb2._METADATA
_RECENTFILES.fields_by_name['file'].message_type = _RECENTFILE

class RecentFile(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _RECENTFILE
  
  # @@protoc_insertion_point(class_scope:rec.gui.RecentFile)

class RecentFiles(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _RECENTFILES
  
  # @@protoc_insertion_point(class_scope:rec.gui.RecentFiles)

# @@protoc_insertion_point(module_scope)