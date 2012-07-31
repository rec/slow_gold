# Generated by the protocol buffer compiler.  DO NOT EDIT!

from google.protobuf import descriptor
from google.protobuf import message
from google.protobuf import reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)


DESCRIPTOR = descriptor.FileDescriptor(
  name='rec/util/SystemStats.proto',
  package='rec.util',
  serialized_pb='\n\x1arec/util/SystemStats.proto\x12\x08rec.util\"\x99\x03\n\x0bSystemStats\x12\x14\n\x0cjuce_version\x18\x01 \x01(\t\x12\x1d\n\x15operating_system_type\x18\x02 \x01(\r\x12\x1d\n\x15operating_system_name\x18\x03 \x01(\t\x12\"\n\x1ais_operating_system_64_bit\x18\x04 \x01(\x08\x12 \n\x18osx_minor_version_number\x18\x05 \x01(\r\x12\x12\n\nlogon_name\x18\x06 \x01(\t\x12\x16\n\x0e\x66ull_user_name\x18\x07 \x01(\t\x12\x15\n\rcomputer_name\x18\x08 \x01(\t\x12\x10\n\x08num_cpus\x18\t \x01(\r\x12\x1e\n\x16\x63pu_speed_in_megahertz\x18\n \x01(\r\x12\x12\n\ncpu_vendor\x18\x0b \x01(\t\x12\x0f\n\x07has_mmx\x18\x0c \x01(\x08\x12\x0f\n\x07has_sse\x18\r \x01(\x08\x12\x10\n\x08has_sse2\x18\x0e \x01(\x08\x12\x11\n\thas_3dnow\x18\x0f \x01(\x08\x12 \n\x18memory_size_in_megabytes\x18\x10 \x01(\r')




_SYSTEMSTATS = descriptor.Descriptor(
  name='SystemStats',
  full_name='rec.util.SystemStats',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='juce_version', full_name='rec.util.SystemStats.juce_version', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='operating_system_type', full_name='rec.util.SystemStats.operating_system_type', index=1,
      number=2, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='operating_system_name', full_name='rec.util.SystemStats.operating_system_name', index=2,
      number=3, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='is_operating_system_64_bit', full_name='rec.util.SystemStats.is_operating_system_64_bit', index=3,
      number=4, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='osx_minor_version_number', full_name='rec.util.SystemStats.osx_minor_version_number', index=4,
      number=5, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='logon_name', full_name='rec.util.SystemStats.logon_name', index=5,
      number=6, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='full_user_name', full_name='rec.util.SystemStats.full_user_name', index=6,
      number=7, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='computer_name', full_name='rec.util.SystemStats.computer_name', index=7,
      number=8, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='num_cpus', full_name='rec.util.SystemStats.num_cpus', index=8,
      number=9, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='cpu_speed_in_megahertz', full_name='rec.util.SystemStats.cpu_speed_in_megahertz', index=9,
      number=10, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='cpu_vendor', full_name='rec.util.SystemStats.cpu_vendor', index=10,
      number=11, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='has_mmx', full_name='rec.util.SystemStats.has_mmx', index=11,
      number=12, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='has_sse', full_name='rec.util.SystemStats.has_sse', index=12,
      number=13, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='has_sse2', full_name='rec.util.SystemStats.has_sse2', index=13,
      number=14, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='has_3dnow', full_name='rec.util.SystemStats.has_3dnow', index=14,
      number=15, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='memory_size_in_megabytes', full_name='rec.util.SystemStats.memory_size_in_megabytes', index=15,
      number=16, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
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
  serialized_start=41,
  serialized_end=450,
)



class SystemStats(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _SYSTEMSTATS
  
  # @@protoc_insertion_point(class_scope:rec.util.SystemStats)

# @@protoc_insertion_point(module_scope)
