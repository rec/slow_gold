# Generated by the protocol buffer compiler.  DO NOT EDIT!

from google.protobuf import descriptor
from google.protobuf import message
from google.protobuf import reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)


DESCRIPTOR = descriptor.FileDescriptor(
  name='rec/command/Command.proto',
  package='rec.command',
  serialized_pb='\n\x19rec/command/Command.proto\x12\x0brec.command\x1a\x1crec/data/proto/Address.proto\"7\n\x0b\x44\x65scription\x12\x0c\n\x04menu\x18\x01 \x03(\t\x12\x0c\n\x04\x66ull\x18\x02 \x03(\t\x12\x0c\n\x04help\x18\x03 \x01(\t\"]\n\x06Setter\x12\x17\n\tis_global\x18\x01 \x01(\x08:\x04true\x12\'\n\x07\x61\x64\x64ress\x18\x02 \x01(\x0b\x32\x16.rec.data.AddressProto\x12\x11\n\ttype_name\x18\x03 \x01(\t\"\xe6\x13\n\x07\x43ommand\x12\'\n\x04type\x18\x01 \x01(\x0e\x32\x19.rec.command.Command.Type\x12\r\n\x05index\x18\x02 \x01(\x11\x12\x13\n\x0bstart_index\x18\x03 \x01(\x11\x12\x0c\n\x04menu\x18\x04 \x01(\t\x12&\n\x04\x64\x65sc\x18\x05 \x01(\x0b\x32\x18.rec.command.Description\x12\x10\n\x08keypress\x18\x06 \x03(\t\x12#\n\x06setter\x18\x07 \x01(\x0b\x32\x13.rec.command.Setter\x12\r\n\x05\x66lags\x18\x08 \x01(\r\x12\x1a\n\x12\x64isable_on_feature\x18\t \x03(\t\"\xf5\x11\n\x04Type\x12\x08\n\x04NONE\x10\x00\x12\x16\n\x12\x41\x42OUT_THIS_PROGRAM\x10:\x12\x12\n\x0e\x41\x44\x44_LOOP_POINT\x10\x01\x12\x15\n\x11\x41UDIO_PREFERENCES\x10\x02\x12\x15\n\x11\x43HECK_FOR_UPDATES\x10\x44\x12\x1b\n\x17\x43LEAR_KEYBOARD_MAPPINGS\x10[\x12\x17\n\x13\x43LEAR_MIDI_MAPPINGS\x10\\\x12\x0f\n\x0b\x43LEAR_LOOPS\x10\x04\x12\x13\n\x0f\x43LEAR_NAVIGATOR\x10\x03\x12\x16\n\x12\x43LEAR_ALL_SETTINGS\x10O\x12!\n\x1d\x43LEAR_SETTINGS_FOR_THIS_TRACK\x10P\x12\x19\n\x15\x43LEAR_SAVED_FILE_DATA\x10\x05\x12\x0e\n\nCLOSE_FILE\x10\x06\x12\x18\n\x14\x43OPY_ALL_LOOP_POINTS\x10_\x12\x15\n\x11\x44IM_VOLUME_TOGGLE\x10\x07\x12\r\n\tEJECT_CDS\x10\x08\x12\x1c\n\x18\x45XPORT_KEYBOARD_MAPPINGS\x10R\x12\x18\n\x14\x45XPORT_MIDI_MAPPINGS\x10S\x12\x13\n\x0f\x45XPORT_SETTINGS\x10K\x12\x1c\n\x18IMPORT_KEYBOARD_MAPPINGS\x10T\x12\x18\n\x14IMPORT_MIDI_MAPPINGS\x10U\x12\x13\n\x0fIMPORT_SETTINGS\x10L\x12\x19\n\x15INVERT_LOOP_SELECTION\x10\t\x12\x08\n\x04JUMP\x10\n\x12\x11\n\rJUMP_SELECTED\x10\x0b\x12\x15\n\x11KEYBOARD_MAPPINGS\x10\x0c\x12\x15\n\x11LOOP_NEXT_SEGMENT\x10^\x12\x11\n\rMIDI_MAPPINGS\x10\r\x12\x17\n\x13MODE_ADD_LOOP_POINT\x10?\x12\r\n\tMODE_DRAG\x10<\x12\x11\n\rMODE_SET_TIME\x10=\x12\x10\n\x0cMODE_ZOOM_IN\x10>\x12\x16\n\x12MUTE_VOLUME_TOGGLE\x10\x0e\x12\x12\n\x0eNUDGE_BACKWARD\x10Y\x12\x11\n\rNUDGE_FORWARD\x10Z\x12\x14\n\x10NUDGE_BEGIN_LEFT\x10\x0f\x12\x15\n\x11NUDGE_BEGIN_RIGHT\x10\x10\x12\x12\n\x0eNUDGE_END_LEFT\x10\x11\x12\x13\n\x0fNUDGE_END_RIGHT\x10\x12\x12\x14\n\x10NUDGE_SPEED_DOWN\x10V\x12\x12\n\x0eNUDGE_SPEED_UP\x10W\x12\x15\n\x11NUDGE_VOLUME_DOWN\x10\x13\x12\x13\n\x0fNUDGE_VOLUME_UP\x10\x14\x12\x08\n\x04OPEN\x10\x15\x12\x0f\n\x0bOPEN_MANUAL\x10\x41\x12\x16\n\x12OPEN_PREVIOUS_FILE\x10N\x12\x1b\n\x17OPEN_SLOWGOLD_DIRECTORY\x10J\x12\x1a\n\x16PASTE_OVER_LOOP_POINTS\x10`\x12\x10\n\x0cRECENT_FILES\x10\x16\x12\x08\n\x04REDO\x10\x17\x12\x13\n\x0fREQUEST_SUPPORT\x10\x42\x12\x17\n\x13RESET_GAIN_TO_UNITY\x10\x18\x12\r\n\tSAVE_FILE\x10\x45\x12\x17\n\x13SAVE_FILE_SELECTION\x10\x46\x12\n\n\x06SELECT\x10\x19\x12\x0f\n\x0bSELECT_ONLY\x10\x1a\x12\x10\n\x0cSET_LANGUAGE\x10]\x12\x13\n\x0fSET_SAVE_FORMAT\x10G\x12\x19\n\x15TOGGLE_ADVANCED_MENUS\x10;\x12\x1c\n\x18TOGGLE_AUTOMATIC_UPDATES\x10\x43\x12\x18\n\x14TOGGLE_FOLLOW_CURSOR\x10+\x12\x17\n\x13TOGGLE_GRID_DISPLAY\x10\x1b\x12\x1e\n\x1aTOGGLE_COMMAND_BAR_AT_LEFT\x10\x36\x12\x1d\n\x19TOGGLE_COMMAND_BAR_AT_TOP\x10\x37\x12!\n\x1dTOGGLE_FILE_OPEN_TREE_DISPLAY\x10H\x12\x18\n\x14TOGGLE_MODES_AT_LEFT\x10\x38\x12\x17\n\x13TOGGLE_MODES_AT_TOP\x10\x39\x12\x1d\n\x19TOGGLE_PARALLEL_WAVEFORMS\x10*\x12\x1a\n\x16TOGGLE_PREFADER_LEVELS\x10.\x12\x14\n\x10TOGGLE_SELECTION\x10)\x12\'\n#TOGGLE_SHOW_ABOUT_WINDOW_AT_STARTUP\x10Q\x12\x1d\n\x19TOGGLE_SHOW_CURSOR_LABELS\x10\x33\x12\x19\n\x15TOGGLE_SHOW_HELP_PANE\x10\x31\x12\x1d\n\x19TOGGLE_SHOW_LABELS_AT_TOP\x10\x34\x12\x1b\n\x17TOGGLE_SHOW_MASTER_TUNE\x10M\x12!\n\x1dTOGGLE_SHOW_SELECTION_BUTTONS\x10\x32\x12\x1c\n\x18TOGGLE_SHOW_TIMES_AT_TOP\x10\x35\x12\x18\n\x14TOGGLE_SHOW_TOOLTIPS\x10\x30\x12\x15\n\x11TOGGLE_START_STOP\x10\x1c\x12\x19\n\x15TOGGLE_STRETCH_ENABLE\x10\x1d\x12\x1b\n\x17TOGGLE_TRANSFORM_ENABLE\x10X\x12\x1a\n\x16TOGGLE_WHOLE_SONG_LOOP\x10\x1e\x12\x0e\n\nTREE_CLOSE\x10\x1f\x12\r\n\tTREE_DOWN\x10 \x12\r\n\tTREE_LEFT\x10!\x12\r\n\tTREE_OPEN\x10\"\x12\x0e\n\nTREE_RIGHT\x10#\x12\x0b\n\x07TREE_UP\x10$\x12\x08\n\x04UNDO\x10%\x12\x0c\n\x08UNSELECT\x10&\x12\x12\n\x0eWHATS_NEW_PAGE\x10I\x12\x0b\n\x07ZOOM_IN\x10\'\x12\x0c\n\x08ZOOM_OUT\x10(\x12\x11\n\rZOOM_OUT_FULL\x10@\x12\x15\n\x11ZOOM_TO_SELECTION\x10-\x12\r\n\tLAST_TYPE\x10`\x12\t\n\x04QUIT\x10\x81 \x12\x08\n\x03\x44\x45L\x10\x82 \x12\x08\n\x03\x43UT\x10\x83 \x12\t\n\x04\x43OPY\x10\x84 \x12\n\n\x05PASTE\x10\x85 \x12\x0f\n\nSELECT_ALL\x10\x86 \x12\x11\n\x0c\x44\x45SELECT_ALL\x10\x87 \x12\x0f\n\nJUCE_START\x10\x81 \x12\r\n\x08JUCE_END\x10\x87 \x12\x0f\n\tBANK_SIZE\x10\xa0\x8d\x06\"1\n\x08\x43ommands\x12%\n\x07\x63ommand\x18\x01 \x03(\x0b\x32\x14.rec.command.Command')



_COMMAND_TYPE = descriptor.EnumDescriptor(
  name='Type',
  full_name='rec.command.Command.Type',
  filename=None,
  file=DESCRIPTOR,
  values=[
    descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='ABOUT_THIS_PROGRAM', index=1, number=58,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='ADD_LOOP_POINT', index=2, number=1,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='AUDIO_PREFERENCES', index=3, number=2,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='CHECK_FOR_UPDATES', index=4, number=68,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='CLEAR_KEYBOARD_MAPPINGS', index=5, number=91,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='CLEAR_MIDI_MAPPINGS', index=6, number=92,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='CLEAR_LOOPS', index=7, number=4,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='CLEAR_NAVIGATOR', index=8, number=3,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='CLEAR_ALL_SETTINGS', index=9, number=79,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='CLEAR_SETTINGS_FOR_THIS_TRACK', index=10, number=80,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='CLEAR_SAVED_FILE_DATA', index=11, number=5,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='CLOSE_FILE', index=12, number=6,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='COPY_ALL_LOOP_POINTS', index=13, number=95,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='DIM_VOLUME_TOGGLE', index=14, number=7,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='EJECT_CDS', index=15, number=8,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='EXPORT_KEYBOARD_MAPPINGS', index=16, number=82,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='EXPORT_MIDI_MAPPINGS', index=17, number=83,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='EXPORT_SETTINGS', index=18, number=75,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='IMPORT_KEYBOARD_MAPPINGS', index=19, number=84,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='IMPORT_MIDI_MAPPINGS', index=20, number=85,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='IMPORT_SETTINGS', index=21, number=76,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='INVERT_LOOP_SELECTION', index=22, number=9,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='JUMP', index=23, number=10,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='JUMP_SELECTED', index=24, number=11,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='KEYBOARD_MAPPINGS', index=25, number=12,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='LOOP_NEXT_SEGMENT', index=26, number=94,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='MIDI_MAPPINGS', index=27, number=13,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='MODE_ADD_LOOP_POINT', index=28, number=63,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='MODE_DRAG', index=29, number=60,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='MODE_SET_TIME', index=30, number=61,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='MODE_ZOOM_IN', index=31, number=62,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='MUTE_VOLUME_TOGGLE', index=32, number=14,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='NUDGE_BACKWARD', index=33, number=89,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='NUDGE_FORWARD', index=34, number=90,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='NUDGE_BEGIN_LEFT', index=35, number=15,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='NUDGE_BEGIN_RIGHT', index=36, number=16,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='NUDGE_END_LEFT', index=37, number=17,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='NUDGE_END_RIGHT', index=38, number=18,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='NUDGE_SPEED_DOWN', index=39, number=86,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='NUDGE_SPEED_UP', index=40, number=87,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='NUDGE_VOLUME_DOWN', index=41, number=19,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='NUDGE_VOLUME_UP', index=42, number=20,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='OPEN', index=43, number=21,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='OPEN_MANUAL', index=44, number=65,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='OPEN_PREVIOUS_FILE', index=45, number=78,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='OPEN_SLOWGOLD_DIRECTORY', index=46, number=74,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='PASTE_OVER_LOOP_POINTS', index=47, number=96,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='RECENT_FILES', index=48, number=22,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='REDO', index=49, number=23,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='REQUEST_SUPPORT', index=50, number=66,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='RESET_GAIN_TO_UNITY', index=51, number=24,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='SAVE_FILE', index=52, number=69,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='SAVE_FILE_SELECTION', index=53, number=70,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='SELECT', index=54, number=25,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='SELECT_ONLY', index=55, number=26,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='SET_LANGUAGE', index=56, number=93,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='SET_SAVE_FORMAT', index=57, number=71,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TOGGLE_ADVANCED_MENUS', index=58, number=59,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TOGGLE_AUTOMATIC_UPDATES', index=59, number=67,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TOGGLE_FOLLOW_CURSOR', index=60, number=43,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TOGGLE_GRID_DISPLAY', index=61, number=27,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TOGGLE_COMMAND_BAR_AT_LEFT', index=62, number=54,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TOGGLE_COMMAND_BAR_AT_TOP', index=63, number=55,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TOGGLE_FILE_OPEN_TREE_DISPLAY', index=64, number=72,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TOGGLE_MODES_AT_LEFT', index=65, number=56,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TOGGLE_MODES_AT_TOP', index=66, number=57,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TOGGLE_PARALLEL_WAVEFORMS', index=67, number=42,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TOGGLE_PREFADER_LEVELS', index=68, number=46,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TOGGLE_SELECTION', index=69, number=41,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TOGGLE_SHOW_ABOUT_WINDOW_AT_STARTUP', index=70, number=81,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TOGGLE_SHOW_CURSOR_LABELS', index=71, number=51,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TOGGLE_SHOW_HELP_PANE', index=72, number=49,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TOGGLE_SHOW_LABELS_AT_TOP', index=73, number=52,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TOGGLE_SHOW_MASTER_TUNE', index=74, number=77,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TOGGLE_SHOW_SELECTION_BUTTONS', index=75, number=50,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TOGGLE_SHOW_TIMES_AT_TOP', index=76, number=53,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TOGGLE_SHOW_TOOLTIPS', index=77, number=48,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TOGGLE_START_STOP', index=78, number=28,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TOGGLE_STRETCH_ENABLE', index=79, number=29,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TOGGLE_TRANSFORM_ENABLE', index=80, number=88,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TOGGLE_WHOLE_SONG_LOOP', index=81, number=30,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TREE_CLOSE', index=82, number=31,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TREE_DOWN', index=83, number=32,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TREE_LEFT', index=84, number=33,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TREE_OPEN', index=85, number=34,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TREE_RIGHT', index=86, number=35,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TREE_UP', index=87, number=36,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='UNDO', index=88, number=37,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='UNSELECT', index=89, number=38,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='WHATS_NEW_PAGE', index=90, number=73,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='ZOOM_IN', index=91, number=39,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='ZOOM_OUT', index=92, number=40,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='ZOOM_OUT_FULL', index=93, number=64,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='ZOOM_TO_SELECTION', index=94, number=45,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='LAST_TYPE', index=95, number=96,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='QUIT', index=96, number=4097,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='DEL', index=97, number=4098,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='CUT', index=98, number=4099,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='COPY', index=99, number=4100,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='PASTE', index=100, number=4101,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='SELECT_ALL', index=101, number=4102,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='DESELECT_ALL', index=102, number=4103,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='JUCE_START', index=103, number=4097,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='JUCE_END', index=104, number=4103,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='BANK_SIZE', index=105, number=100000,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=466,
  serialized_end=2759,
)


_DESCRIPTION = descriptor.Descriptor(
  name='Description',
  full_name='rec.command.Description',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='menu', full_name='rec.command.Description.menu', index=0,
      number=1, type=9, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='full', full_name='rec.command.Description.full', index=1,
      number=2, type=9, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='help', full_name='rec.command.Description.help', index=2,
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
  serialized_start=72,
  serialized_end=127,
)


_SETTER = descriptor.Descriptor(
  name='Setter',
  full_name='rec.command.Setter',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='is_global', full_name='rec.command.Setter.is_global', index=0,
      number=1, type=8, cpp_type=7, label=1,
      has_default_value=True, default_value=True,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='address', full_name='rec.command.Setter.address', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='type_name', full_name='rec.command.Setter.type_name', index=2,
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
  serialized_start=129,
  serialized_end=222,
)


_COMMAND = descriptor.Descriptor(
  name='Command',
  full_name='rec.command.Command',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='type', full_name='rec.command.Command.type', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='index', full_name='rec.command.Command.index', index=1,
      number=2, type=17, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='start_index', full_name='rec.command.Command.start_index', index=2,
      number=3, type=17, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='menu', full_name='rec.command.Command.menu', index=3,
      number=4, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='desc', full_name='rec.command.Command.desc', index=4,
      number=5, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='keypress', full_name='rec.command.Command.keypress', index=5,
      number=6, type=9, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='setter', full_name='rec.command.Command.setter', index=6,
      number=7, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='flags', full_name='rec.command.Command.flags', index=7,
      number=8, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='disable_on_feature', full_name='rec.command.Command.disable_on_feature', index=8,
      number=9, type=9, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _COMMAND_TYPE,
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=225,
  serialized_end=2759,
)


_COMMANDS = descriptor.Descriptor(
  name='Commands',
  full_name='rec.command.Commands',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
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
  serialized_start=2761,
  serialized_end=2810,
)

import rec.data.proto.Address_pb2

_SETTER.fields_by_name['address'].message_type = rec.data.proto.Address_pb2._ADDRESSPROTO
_COMMAND.fields_by_name['type'].enum_type = _COMMAND_TYPE
_COMMAND.fields_by_name['desc'].message_type = _DESCRIPTION
_COMMAND.fields_by_name['setter'].message_type = _SETTER
_COMMAND_TYPE.containing_type = _COMMAND;
_COMMANDS.fields_by_name['command'].message_type = _COMMAND

class Description(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _DESCRIPTION
  
  # @@protoc_insertion_point(class_scope:rec.command.Description)

class Setter(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _SETTER
  
  # @@protoc_insertion_point(class_scope:rec.command.Setter)

class Command(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _COMMAND
  
  # @@protoc_insertion_point(class_scope:rec.command.Command)

class Commands(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _COMMANDS
  
  # @@protoc_insertion_point(class_scope:rec.command.Commands)

# @@protoc_insertion_point(module_scope)
