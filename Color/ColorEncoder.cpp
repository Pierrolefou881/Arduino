#include "ColorEncoder.hpp"

/**
 * Combines all the color values into one single encoded color. Values are clamped
 * between 0 and 255.
 * @param red must fit in an unsigned byte.
 * @param green must fit in an unsigned byte.
 * @param blue must fit in an unsigned byte.
 */
unsigned long Utils::Color::ColorEncoder::encode_color(int red, int green, int blue)
{
  return ((unsigned long)red << 16) + (green << 8) + blue;
}

/**
 * Red is encoded in bits [8-15] of an unsigned 32-bit integer.
 * @return the red value of the provided color code.
 */
int Utils::Color::ColorEncoder::decode_red(unsigned long color)
{
  return (int)((color >> 16) & 255);
}

/**
 * Green is encoded in bits [16-23] of an unsigned 32-bit integer.
 * @return the green value of the provided color code.
 */
int Utils::Color::ColorEncoder::decode_green(unsigned long color)
{
  return (int)((color >> 8) & 255);
}

/**
 * Blue is encoded in bits [24-31] of an unsigned 32-bit integer.
 * @return the blue value of the provided color code.
 */
int Utils::Color::ColorEncoder::decode_blue(unsigned long color)
{
  return (int)(color & 255);
}

/**
 * Isolates each color component of a given color.
 * @param color to decode.
 * @param red out parameter.
 * @param green out parameter.
 * @param blue out parameter.
 */
void Utils::Color::ColorEncoder::decode_color(unsigned long color, int& red, int& green, int& blue)
{
  red = decode_red(color);
  green = decode_green(color);
  blue = decode_blue(color);
}