# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: rec/slow/commands/SlowCommand.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)


import rec.command.Command_pb2
import rec.command.map.CommandMap_pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='rec/slow/commands/SlowCommand.proto',
  package='rec.slow',
  serialized_pb='\n#rec/slow/commands/SlowCommand.proto\x12\x08rec.slow\x1a\x19rec/command/Command.proto\x1a rec/command/map/CommandMap.proto\"\xc3\x13\n\x0bSlowCommand\x12(\n\x04type\x18\x01 \x01(\x0e\x32\x1a.rec.slow.SlowCommand.Type\x12%\n\x07\x63ommand\x18\x02 \x01(\x0b\x32\x14.rec.command.Command\"\xe2\x12\n\x04Type\x12\x08\n\x04NONE\x10\x00\x12\x16\n\x12\x41\x42OUT_THIS_PROGRAM\x10:\x12\x12\n\x0e\x41\x44\x44_LOOP_POINT\x10\x01\x12\x15\n\x11\x41UDIO_PREFERENCES\x10\x02\x12\x15\n\x11\x43HECK_FOR_UPDATES\x10\x44\x12\x1b\n\x17\x43LEAR_KEYBOARD_MAPPINGS\x10[\x12\x17\n\x13\x43LEAR_MIDI_MAPPINGS\x10\\\x12\x0f\n\x0b\x43LEAR_LOOPS\x10\x04\x12\x13\n\x0f\x43LEAR_NAVIGATOR\x10\x03\x12\x16\n\x12\x43LEAR_ALL_SETTINGS\x10O\x12!\n\x1d\x43LEAR_SETTINGS_FOR_THIS_TRACK\x10P\x12\x19\n\x15\x43LEAR_SAVED_FILE_DATA\x10\x05\x12\x0e\n\nCLOSE_FILE\x10\x06\x12\x18\n\x14\x43OPY_ALL_LOOP_POINTS\x10_\x12\x15\n\x11\x44IM_VOLUME_TOGGLE\x10\x07\x12\r\n\tEJECT_CDS\x10\x08\x12\x1c\n\x18\x45XPORT_KEYBOARD_MAPPINGS\x10R\x12\x18\n\x14\x45XPORT_MIDI_MAPPINGS\x10S\x12\x13\n\x0f\x45XPORT_SETTINGS\x10K\x12\x1c\n\x18IMPORT_KEYBOARD_MAPPINGS\x10T\x12\x18\n\x14IMPORT_MIDI_MAPPINGS\x10U\x12\x13\n\x0fIMPORT_SETTINGS\x10L\x12\x19\n\x15INVERT_LOOP_SELECTION\x10\t\x12\n\n\x04JUMP\x10\xa0\x8d\x06\x12\x13\n\rJUMP_SELECTED\x10\xb0\xdb\x06\x12\x15\n\x11KEYBOARD_MAPPINGS\x10\x0c\x12\x15\n\x11LOOP_NEXT_SEGMENT\x10^\x12\x11\n\rMIDI_MAPPINGS\x10\r\x12\x17\n\x13MODE_ADD_LOOP_POINT\x10?\x12\r\n\tMODE_DRAG\x10<\x12\x11\n\rMODE_SET_TIME\x10=\x12\x10\n\x0cMODE_ZOOM_IN\x10>\x12\x16\n\x12MUTE_VOLUME_TOGGLE\x10\x0e\x12\x12\n\x0eNUDGE_BACKWARD\x10Y\x12\x11\n\rNUDGE_FORWARD\x10Z\x12\x14\n\x10NUDGE_BEGIN_LEFT\x10\x0f\x12\x15\n\x11NUDGE_BEGIN_RIGHT\x10\x10\x12\x12\n\x0eNUDGE_END_LEFT\x10\x11\x12\x13\n\x0fNUDGE_END_RIGHT\x10\x12\x12\x14\n\x10NUDGE_SPEED_DOWN\x10V\x12\x12\n\x0eNUDGE_SPEED_UP\x10W\x12\x15\n\x11NUDGE_VOLUME_DOWN\x10\x13\x12\x13\n\x0fNUDGE_VOLUME_UP\x10\x14\x12\x08\n\x04OPEN\x10\x15\x12\x0f\n\x0bOPEN_MANUAL\x10\x41\x12\x16\n\x12OPEN_PREVIOUS_FILE\x10N\x12\x1b\n\x17OPEN_SLOWGOLD_DIRECTORY\x10J\x12\x1a\n\x16PASTE_OVER_LOOP_POINTS\x10`\x12\x12\n\x0cRECENT_FILES\x10\xe0\xb6\r\x12\x08\n\x04REDO\x10\x17\x12\x13\n\x0fREQUEST_SUPPORT\x10\x42\x12\x17\n\x13RESET_GAIN_TO_UNITY\x10\x18\x12\r\n\tSAVE_FILE\x10\x45\x12\x17\n\x13SAVE_FILE_SELECTION\x10\x46\x12\x0c\n\x06SELECT\x10\x90\xa1\x0f\x12\x11\n\x0bSELECT_ONLY\x10\xa0\xef\x0f\x12\x12\n\x0cSET_LANGUAGE\x10\xd0\xe1\x38\x12\x15\n\x0fSET_SAVE_FORMAT\x10\xf0\xaa+\x12\x14\n\x10SET_SAVE_AS_AIFF\x10\x61\x12\x14\n\x10SET_SAVE_AS_FLAC\x10\x62\x12\x13\n\x0fSET_SAVE_AS_OGG\x10\x63\x12\x13\n\x0fSET_SAVE_AS_WAV\x10\x64\x12\x19\n\x15TOGGLE_ADVANCED_MENUS\x10;\x12\x1c\n\x18TOGGLE_AUTOMATIC_UPDATES\x10\x43\x12\x18\n\x14TOGGLE_FOLLOW_CURSOR\x10+\x12\x17\n\x13TOGGLE_GRID_DISPLAY\x10\x1b\x12\x1e\n\x1aTOGGLE_COMMAND_BAR_AT_LEFT\x10\x36\x12\x1d\n\x19TOGGLE_COMMAND_BAR_AT_TOP\x10\x37\x12!\n\x1dTOGGLE_FILE_OPEN_TREE_DISPLAY\x10H\x12\x18\n\x14TOGGLE_MODES_AT_LEFT\x10\x38\x12\x17\n\x13TOGGLE_MODES_AT_TOP\x10\x39\x12\x1d\n\x19TOGGLE_PARALLEL_WAVEFORMS\x10*\x12\x1a\n\x16TOGGLE_PREFADER_LEVELS\x10.\x12\x16\n\x10TOGGLE_SELECTION\x10\x90\x83\x19\x12\'\n#TOGGLE_SHOW_ABOUT_WINDOW_AT_STARTUP\x10Q\x12\x1d\n\x19TOGGLE_SHOW_CURSOR_LABELS\x10\x33\x12\x19\n\x15TOGGLE_SHOW_HELP_PANE\x10\x31\x12\x1d\n\x19TOGGLE_SHOW_LABELS_AT_TOP\x10\x34\x12\x1b\n\x17TOGGLE_SHOW_MASTER_TUNE\x10M\x12!\n\x1dTOGGLE_SHOW_SELECTION_BUTTONS\x10\x32\x12\x1c\n\x18TOGGLE_SHOW_TIMES_AT_TOP\x10\x35\x12\x18\n\x14TOGGLE_SHOW_TOOLTIPS\x10\x30\x12\x15\n\x11TOGGLE_START_STOP\x10\x1c\x12\x19\n\x15TOGGLE_STRETCH_ENABLE\x10\x1d\x12\x1b\n\x17TOGGLE_TRANSFORM_ENABLE\x10X\x12\x1a\n\x16TOGGLE_WHOLE_SONG_LOOP\x10\x1e\x12\x0e\n\nTREE_CLOSE\x10\x1f\x12\r\n\tTREE_DOWN\x10 \x12\r\n\tTREE_LEFT\x10!\x12\r\n\tTREE_OPEN\x10\"\x12\x0e\n\nTREE_RIGHT\x10#\x12\x0b\n\x07TREE_UP\x10$\x12\x08\n\x04UNDO\x10%\x12\x0e\n\x08UNSELECT\x10\xe0\x98\x17\x12\x12\n\x0eWHATS_NEW_PAGE\x10I\x12\x0b\n\x07ZOOM_IN\x10\'\x12\x0c\n\x08ZOOM_OUT\x10(\x12\x11\n\rZOOM_OUT_FULL\x10@\x12\x15\n\x11ZOOM_TO_SELECTION\x10-\x12\x13\n\x0f\x46IRST_FREE_TYPE\x10\x65\x12\t\n\x04QUIT\x10\x81 \x12\x08\n\x03\x44\x45L\x10\x82 \x12\x08\n\x03\x43UT\x10\x83 \x12\t\n\x04\x43OPY\x10\x84 \x12\n\n\x05PASTE\x10\x85 \x12\x0f\n\nSELECT_ALL\x10\x86 \x12\x11\n\x0c\x44\x45SELECT_ALL\x10\x87 \x12\x0f\n\nJUCE_START\x10\x80 \x12\r\n\x08JUCE_END\x10\x88 \x12\x0e\n\tBANK_SIZE\x10\x90N\";\n\x0cSlowCommands\x12+\n\x0cslow_command\x18\x01 \x03(\x0b\x32\x15.rec.slow.SlowCommand\"o\n\x13SlowCommandMapEntry\x12+\n\x07\x63ommand\x18\x01 \x01(\x0e\x32\x1a.rec.slow.SlowCommand.Type\x12+\n\x05\x65ntry\x18\x02 \x01(\x0b\x32\x1c.rec.command.CommandMapEntry\"H\n\x13SlowCommandMapProto\x12\x31\n\nslow_entry\x18\x01 \x03(\x0b\x32\x1d.rec.slow.SlowCommandMapEntry\"\x85\x01\n\rSlowMenuEntry\x12+\n\x07\x63ommand\x18\x01 \x03(\x0e\x32\x1a.rec.slow.SlowCommand.Type\x12\x0f\n\x07submenu\x18\x02 \x01(\t\x12\x1c\n\x14is_recent_files_menu\x18\x03 \x01(\x08\x12\x18\n\x10\x63\x61llout_function\x18\x04 \x01(\t\"r\n\x08SlowMenu\x12-\n\x0b\x64\x65scription\x18\x01 \x01(\x0b\x32\x18.rec.command.Description\x12\x0f\n\x07\x65xtends\x18\x02 \x01(\t\x12&\n\x05\x65ntry\x18\x03 \x03(\x0b\x32\x17.rec.slow.SlowMenuEntry\"-\n\tSlowMenus\x12 \n\x04menu\x18\x01 \x03(\x0b\x32\x12.rec.slow.SlowMenu')



_SLOWCOMMAND_TYPE = _descriptor.EnumDescriptor(
  name='Type',
  full_name='rec.slow.SlowCommand.Type',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ABOUT_THIS_PROGRAM', index=1, number=58,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ADD_LOOP_POINT', index=2, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='AUDIO_PREFERENCES', index=3, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CHECK_FOR_UPDATES', index=4, number=68,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CLEAR_KEYBOARD_MAPPINGS', index=5, number=91,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CLEAR_MIDI_MAPPINGS', index=6, number=92,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CLEAR_LOOPS', index=7, number=4,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CLEAR_NAVIGATOR', index=8, number=3,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CLEAR_ALL_SETTINGS', index=9, number=79,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CLEAR_SETTINGS_FOR_THIS_TRACK', index=10, number=80,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CLEAR_SAVED_FILE_DATA', index=11, number=5,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CLOSE_FILE', index=12, number=6,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='COPY_ALL_LOOP_POINTS', index=13, number=95,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='DIM_VOLUME_TOGGLE', index=14, number=7,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='EJECT_CDS', index=15, number=8,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='EXPORT_KEYBOARD_MAPPINGS', index=16, number=82,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='EXPORT_MIDI_MAPPINGS', index=17, number=83,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='EXPORT_SETTINGS', index=18, number=75,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='IMPORT_KEYBOARD_MAPPINGS', index=19, number=84,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='IMPORT_MIDI_MAPPINGS', index=20, number=85,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='IMPORT_SETTINGS', index=21, number=76,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='INVERT_LOOP_SELECTION', index=22, number=9,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='JUMP', index=23, number=100000,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='JUMP_SELECTED', index=24, number=110000,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='KEYBOARD_MAPPINGS', index=25, number=12,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='LOOP_NEXT_SEGMENT', index=26, number=94,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MIDI_MAPPINGS', index=27, number=13,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MODE_ADD_LOOP_POINT', index=28, number=63,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MODE_DRAG', index=29, number=60,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MODE_SET_TIME', index=30, number=61,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MODE_ZOOM_IN', index=31, number=62,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MUTE_VOLUME_TOGGLE', index=32, number=14,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='NUDGE_BACKWARD', index=33, number=89,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='NUDGE_FORWARD', index=34, number=90,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='NUDGE_BEGIN_LEFT', index=35, number=15,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='NUDGE_BEGIN_RIGHT', index=36, number=16,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='NUDGE_END_LEFT', index=37, number=17,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='NUDGE_END_RIGHT', index=38, number=18,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='NUDGE_SPEED_DOWN', index=39, number=86,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='NUDGE_SPEED_UP', index=40, number=87,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='NUDGE_VOLUME_DOWN', index=41, number=19,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='NUDGE_VOLUME_UP', index=42, number=20,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='OPEN', index=43, number=21,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='OPEN_MANUAL', index=44, number=65,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='OPEN_PREVIOUS_FILE', index=45, number=78,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='OPEN_SLOWGOLD_DIRECTORY', index=46, number=74,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PASTE_OVER_LOOP_POINTS', index=47, number=96,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='RECENT_FILES', index=48, number=220000,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='REDO', index=49, number=23,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='REQUEST_SUPPORT', index=50, number=66,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='RESET_GAIN_TO_UNITY', index=51, number=24,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SAVE_FILE', index=52, number=69,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SAVE_FILE_SELECTION', index=53, number=70,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SELECT', index=54, number=250000,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SELECT_ONLY', index=55, number=260000,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SET_LANGUAGE', index=56, number=930000,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SET_SAVE_FORMAT', index=57, number=710000,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SET_SAVE_AS_AIFF', index=58, number=97,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SET_SAVE_AS_FLAC', index=59, number=98,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SET_SAVE_AS_OGG', index=60, number=99,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SET_SAVE_AS_WAV', index=61, number=100,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TOGGLE_ADVANCED_MENUS', index=62, number=59,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TOGGLE_AUTOMATIC_UPDATES', index=63, number=67,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TOGGLE_FOLLOW_CURSOR', index=64, number=43,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TOGGLE_GRID_DISPLAY', index=65, number=27,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TOGGLE_COMMAND_BAR_AT_LEFT', index=66, number=54,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TOGGLE_COMMAND_BAR_AT_TOP', index=67, number=55,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TOGGLE_FILE_OPEN_TREE_DISPLAY', index=68, number=72,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TOGGLE_MODES_AT_LEFT', index=69, number=56,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TOGGLE_MODES_AT_TOP', index=70, number=57,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TOGGLE_PARALLEL_WAVEFORMS', index=71, number=42,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TOGGLE_PREFADER_LEVELS', index=72, number=46,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TOGGLE_SELECTION', index=73, number=410000,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TOGGLE_SHOW_ABOUT_WINDOW_AT_STARTUP', index=74, number=81,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TOGGLE_SHOW_CURSOR_LABELS', index=75, number=51,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TOGGLE_SHOW_HELP_PANE', index=76, number=49,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TOGGLE_SHOW_LABELS_AT_TOP', index=77, number=52,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TOGGLE_SHOW_MASTER_TUNE', index=78, number=77,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TOGGLE_SHOW_SELECTION_BUTTONS', index=79, number=50,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TOGGLE_SHOW_TIMES_AT_TOP', index=80, number=53,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TOGGLE_SHOW_TOOLTIPS', index=81, number=48,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TOGGLE_START_STOP', index=82, number=28,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TOGGLE_STRETCH_ENABLE', index=83, number=29,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TOGGLE_TRANSFORM_ENABLE', index=84, number=88,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TOGGLE_WHOLE_SONG_LOOP', index=85, number=30,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TREE_CLOSE', index=86, number=31,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TREE_DOWN', index=87, number=32,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TREE_LEFT', index=88, number=33,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TREE_OPEN', index=89, number=34,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TREE_RIGHT', index=90, number=35,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TREE_UP', index=91, number=36,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='UNDO', index=92, number=37,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='UNSELECT', index=93, number=380000,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='WHATS_NEW_PAGE', index=94, number=73,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ZOOM_IN', index=95, number=39,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ZOOM_OUT', index=96, number=40,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ZOOM_OUT_FULL', index=97, number=64,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ZOOM_TO_SELECTION', index=98, number=45,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='FIRST_FREE_TYPE', index=99, number=101,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='QUIT', index=100, number=4097,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='DEL', index=101, number=4098,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CUT', index=102, number=4099,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='COPY', index=103, number=4100,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PASTE', index=104, number=4101,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SELECT_ALL', index=105, number=4102,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='DESELECT_ALL', index=106, number=4103,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='JUCE_START', index=107, number=4096,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='JUCE_END', index=108, number=4104,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='BANK_SIZE', index=109, number=10000,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=208,
  serialized_end=2610,
)


_SLOWCOMMAND = _descriptor.Descriptor(
  name='SlowCommand',
  full_name='rec.slow.SlowCommand',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='type', full_name='rec.slow.SlowCommand.type', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='command', full_name='rec.slow.SlowCommand.command', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _SLOWCOMMAND_TYPE,
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=111,
  serialized_end=2610,
)


_SLOWCOMMANDS = _descriptor.Descriptor(
  name='SlowCommands',
  full_name='rec.slow.SlowCommands',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='slow_command', full_name='rec.slow.SlowCommands.slow_command', index=0,
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
  serialized_start=2612,
  serialized_end=2671,
)


_SLOWCOMMANDMAPENTRY = _descriptor.Descriptor(
  name='SlowCommandMapEntry',
  full_name='rec.slow.SlowCommandMapEntry',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='command', full_name='rec.slow.SlowCommandMapEntry.command', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='entry', full_name='rec.slow.SlowCommandMapEntry.entry', index=1,
      number=2, type=11, cpp_type=10, label=1,
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
  serialized_start=2673,
  serialized_end=2784,
)


_SLOWCOMMANDMAPPROTO = _descriptor.Descriptor(
  name='SlowCommandMapProto',
  full_name='rec.slow.SlowCommandMapProto',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='slow_entry', full_name='rec.slow.SlowCommandMapProto.slow_entry', index=0,
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
  serialized_start=2786,
  serialized_end=2858,
)


_SLOWMENUENTRY = _descriptor.Descriptor(
  name='SlowMenuEntry',
  full_name='rec.slow.SlowMenuEntry',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='command', full_name='rec.slow.SlowMenuEntry.command', index=0,
      number=1, type=14, cpp_type=8, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='submenu', full_name='rec.slow.SlowMenuEntry.submenu', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='is_recent_files_menu', full_name='rec.slow.SlowMenuEntry.is_recent_files_menu', index=2,
      number=3, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='callout_function', full_name='rec.slow.SlowMenuEntry.callout_function', index=3,
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
  serialized_start=2861,
  serialized_end=2994,
)


_SLOWMENU = _descriptor.Descriptor(
  name='SlowMenu',
  full_name='rec.slow.SlowMenu',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='description', full_name='rec.slow.SlowMenu.description', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='extends', full_name='rec.slow.SlowMenu.extends', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='entry', full_name='rec.slow.SlowMenu.entry', index=2,
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
  serialized_start=2996,
  serialized_end=3110,
)


_SLOWMENUS = _descriptor.Descriptor(
  name='SlowMenus',
  full_name='rec.slow.SlowMenus',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='menu', full_name='rec.slow.SlowMenus.menu', index=0,
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
  serialized_start=3112,
  serialized_end=3157,
)

_SLOWCOMMAND.fields_by_name['type'].enum_type = _SLOWCOMMAND_TYPE
_SLOWCOMMAND.fields_by_name['command'].message_type = rec.command.Command_pb2._COMMAND
_SLOWCOMMAND_TYPE.containing_type = _SLOWCOMMAND;
_SLOWCOMMANDS.fields_by_name['slow_command'].message_type = _SLOWCOMMAND
_SLOWCOMMANDMAPENTRY.fields_by_name['command'].enum_type = _SLOWCOMMAND_TYPE
_SLOWCOMMANDMAPENTRY.fields_by_name['entry'].message_type = rec.command.map.CommandMap_pb2._COMMANDMAPENTRY
_SLOWCOMMANDMAPPROTO.fields_by_name['slow_entry'].message_type = _SLOWCOMMANDMAPENTRY
_SLOWMENUENTRY.fields_by_name['command'].enum_type = _SLOWCOMMAND_TYPE
_SLOWMENU.fields_by_name['description'].message_type = rec.command.Command_pb2._DESCRIPTION
_SLOWMENU.fields_by_name['entry'].message_type = _SLOWMENUENTRY
_SLOWMENUS.fields_by_name['menu'].message_type = _SLOWMENU
DESCRIPTOR.message_types_by_name['SlowCommand'] = _SLOWCOMMAND
DESCRIPTOR.message_types_by_name['SlowCommands'] = _SLOWCOMMANDS
DESCRIPTOR.message_types_by_name['SlowCommandMapEntry'] = _SLOWCOMMANDMAPENTRY
DESCRIPTOR.message_types_by_name['SlowCommandMapProto'] = _SLOWCOMMANDMAPPROTO
DESCRIPTOR.message_types_by_name['SlowMenuEntry'] = _SLOWMENUENTRY
DESCRIPTOR.message_types_by_name['SlowMenu'] = _SLOWMENU
DESCRIPTOR.message_types_by_name['SlowMenus'] = _SLOWMENUS

class SlowCommand(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _SLOWCOMMAND

  # @@protoc_insertion_point(class_scope:rec.slow.SlowCommand)

class SlowCommands(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _SLOWCOMMANDS

  # @@protoc_insertion_point(class_scope:rec.slow.SlowCommands)

class SlowCommandMapEntry(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _SLOWCOMMANDMAPENTRY

  # @@protoc_insertion_point(class_scope:rec.slow.SlowCommandMapEntry)

class SlowCommandMapProto(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _SLOWCOMMANDMAPPROTO

  # @@protoc_insertion_point(class_scope:rec.slow.SlowCommandMapProto)

class SlowMenuEntry(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _SLOWMENUENTRY

  # @@protoc_insertion_point(class_scope:rec.slow.SlowMenuEntry)

class SlowMenu(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _SLOWMENU

  # @@protoc_insertion_point(class_scope:rec.slow.SlowMenu)

class SlowMenus(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _SLOWMENUS

  # @@protoc_insertion_point(class_scope:rec.slow.SlowMenus)


# @@protoc_insertion_point(module_scope)
