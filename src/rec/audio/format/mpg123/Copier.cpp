#include "rec/audio/format/mpg123/Copier.h"
#include "rec/audio/format/mpg123/Mpg123.h"

namespace rec {
namespace audio {
namespace format {
namespace mpg123 {

namespace {

template <typename Number>
Number average(Number x, Number y) { return (x + y) / 2; }

template <>
int32 average(int32 x, int32 y) { return int32((x + (long)y)/ 2); }

template <typename In, typename Out>
struct Copy {
    static Out get(In* in, int64 pos, int32 channel, int32 channels) {
        return cast(in[pos * channels + channel % channels]);
    }

    static Out cast(In in) { return Out(in); }

    static void copy(int32** destSamples, int32 destChannels, int64 destOffset,
                     void* source, int32 sourceChannels, int64 sourceSize) {
        auto out = (Out**) destSamples;
        auto in = (In*) source;

        if (destChannels == 1 && sourceChannels == 2) {
            Out *o = out[0] + destOffset;
            for (int32 s = 0; s < sourceSize; ++s)
                o[s] = average(get(in, s, 0, 2), get(in, s, 1, 2));

        } else {
            for (int32 c = 0; c < destChannels; ++c) {
                Out *o = out[c] + destOffset;
                for (int32 s = 0; s < sourceSize; ++s)
                    o[s] = get(in, s, c, sourceChannels);
            }
        }
    }
};

template<> int32 Copy<char, int32>::cast(char x) {
    return 0x1000000 * int32(x);
}

template<> int32 Copy<short, int32>::cast(short x) {
    return 0x10000 * int32(x);
}

template<> int32 Copy<uint8, int32>::cast(uint8 x) {
    return 0x1000000 * char(int32(x) - 0x80);
}

template<> int32 Copy<uint16, int32>::cast(uint16 x) {
    return 0x10000 * (int32(x) - 0x8000);
}

template<> int32 Copy<uint32, int32>::cast(uint32 x) {
    return int32(int64(x) - 0x80000000L);
}

}  // namespace

Copier getCopier(int32 encoding) {
    switch (encoding) {
      case MPG123_ENC_FLOAT_32:     return &Copy<float, float>::copy;
      case MPG123_ENC_FLOAT_64:     return &Copy<double, float>::copy;

      case MPG123_ENC_SIGNED_16:    return &Copy<short, int32>::copy;
      case MPG123_ENC_SIGNED_32:    return &Copy<int32, int32>::copy;
      case MPG123_ENC_SIGNED_8:     return &Copy<char, int32>::copy;

      case MPG123_ENC_UNSIGNED_16:  return &Copy<uint16, int32>::copy;
      case MPG123_ENC_UNSIGNED_32:  return &Copy<uint32, int32>::copy;
      case MPG123_ENC_UNSIGNED_8:   return &Copy<uint8, int32>::copy;

      default: return nullptr;
    }
}

}  // namespace mpg123
}  // namespace format
}  // namespace audio
}  // namespace rec
