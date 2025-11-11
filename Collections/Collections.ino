#define _TEST

#include "ArrayList.hpp"
#include <DigitalOutput.hpp>
#include <InOutFactory.hpp>
#include <U_ptr.hpp>

Util::Collection::ArrayList<char> list{ };
Util::Memory::U_ptr<InOut::Digital::DigitalOutput> led{ };

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  led = InOut::Factory::InOutFactory::create_digital_output(LED_BUILTIN);
}

void loop() 
{
  if (list.size() < 6)
  {
    list.append('A');
  }
  else if (list.size() < 10)
  {
    list.add('B', 3);
  }
  else if (list.size() < 13)
  {
    list.add('C');
  }
  else
  {
    // list.remove_at(5);
    // list.remove_at(5);
    // list.remove_at(5);

    // list.remove('B');
    list.remove_all('B');

    // list.clear();
  }

  print_list();

  led->toggle();
  delay(1000);
}

void print_list()
{
  for (unsigned int i = 0; i < list.size(); i++)
  {
    Serial.print(list[i]);
    Serial.print(", ");
  }
  Serial.print('\t');
  if (list.contains('B'))
  {
    Serial.print("\t B detected");
  }
  Serial.println(list.array_length());
}
