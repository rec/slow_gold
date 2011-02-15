#if 0
namespace {

typedef StateColors CursorStateColors[CursorProto::Type_ARRAYSIZE];

const CursorStateColors& getStateColors() {
  static CursorStateColors colors = {
    {
      makeColors(0x0, 0x0),  // NONE
      makeColors(0x0, 0x0),  // DOWN
      makeColors(0x0, 0x0),  // HOVERING
    },  // NONE

    {
      makeColors(0x0, 0x0),  // NONE
      makeColors(0x0, 0x0),  // DOWN
      makeColors(0x0, 0x0),  // HOVERING
    },  // PLAYBACK_POSITION

    {
      makeColors(0x0, 0x0),  // NONE
      makeColors(0x0, 0x0),  // DOWN
      makeColors(0x0, 0x0),  // HOVERING
    },  // LOOP_START

    {
      makeColors(0x0, 0x0),  // NONE
      makeColors(0x0, 0x0),  // DOWN
      makeColors(0x0, 0x0),  // HOVERING
    },  // LOOP_END
  };

  return colors;
}

}  // namespace

#endif
