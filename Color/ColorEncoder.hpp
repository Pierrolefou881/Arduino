#pragma once

namespace Utils
{
  namespace Color
  {
    /**
     * Utility methods to encode and decode colors on unsigned 32-bit integral values
     * using the following pattern:
     * [0-7 empty][8-15 red][16-23 green][24-31 blue]
     */
    class ColorEncoder
    {
    public:
      static unsigned long encode_color(int red, int green, int blue);
      static int decode_red(unsigned long color);
      static int decode_green(unsigned long color);
      static int decode_blue(unsigned long color);
      static void decode_color(unsigned long color, int& red, int& green, int& blue);
    };
  }
}