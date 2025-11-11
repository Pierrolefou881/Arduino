#include "ColorSensor.hpp"
#include "RGBLight.hpp"

InOut::Color::ColorSensor* color_sensor{ };
InOut::Color::RGBLight* rgb_led{ };

void setup() {
  // put your setup code here, to run once:
  color_sensor = new InOut::Color::ColorSensor(A1, A0, A2);
  rgb_led = new InOut::Color::RGBLight(11, 9, 10);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  auto encoded = color_sensor->encode_color();
  rgb_led->display_color(encoded);
  
  auto blue = encoded & 255;
  auto green = (encoded >> 8) & 255;
  auto red = (encoded >> 16) & 255;

  Serial.print('R');
  Serial.print(red);
  Serial.print("\tG");
  Serial.print(green);
  Serial.print("\tB");
  Serial.println(blue);
}
