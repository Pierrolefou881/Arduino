#define _LINKED_LIST
// #define _TEST_LED

#include "ArrayList.hpp"
#include "LinkedList.hpp"
#include <DigitalOutput.hpp>
#include <InOutFactory.hpp>
#include <U_ptr.hpp>
#include "LinkedListIterator.hpp"

Util::Memory::U_ptr<Util::Collection::BaseList<char>> list{ };
Util::Memory::U_ptr<Util::Collection::BaseList<Util::Memory::S_ptr<InOut::Digital::DigitalOutput>>> leds{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> led{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> red{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> yellow1{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> yellow2{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> green1{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> green2{ };
Util::Memory::S_ptr<InOut::Digital::DigitalOutput> blue{ };

void setup() {
  // put your setup code here, to run once:
  #ifdef _LINKED_LIST
  list = new Util::Collection::LinkedList<char>{ };
  leds = new Util::Collection::LinkedList<Util::Memory::S_ptr<InOut::Digital::DigitalOutput>>{ };
  #else
  list = new Util::Collection::ArrayList<char> { };
  leds = new Util::Collection::ArrayList<Util::Memory::S_ptr<InOut::Digital::DigitalOutput>>{ };
  #endif
  Serial.begin(9600);
  led = InOut::Factory::InOutFactory::create_digital_output(LED_BUILTIN);
  red = InOut::Factory::InOutFactory::create_digital_output(7);
  yellow1 = InOut::Factory::InOutFactory::create_digital_output(6);
  yellow2 = InOut::Factory::InOutFactory::create_digital_output(5);
  green1 = InOut::Factory::InOutFactory::create_digital_output(4);
  green2 = InOut::Factory::InOutFactory::create_digital_output(3);
  blue = InOut::Factory::InOutFactory::create_digital_output(2);

  // leds.append(red.get());
  // leds.append(blue.get());
  // leds.append(green.get());

  leds->append(red);
  leds->append(yellow1);
  leds->append(yellow2);
  leds->append(green1);
  leds->append(green2);
  leds->append(blue);
}

void loop() 
{
  #ifdef _TEST_LED
  for (auto i = 0; i < leds->size(); i++)
  {
    leds->at(i)->toggle();
  }

  #else
  if (list->size() < 6)
  {
    list->append('A');
  }
  else if (list->size() < 10)
  {
    list->add('B', 3);
  }
  else if (list->size() < 13)
  {
    list->add('C');
  }
  else
  {
    // list->remove_at(5);
    // list->remove_at(5);
    // list->remove_at(5);

    // list->remove('B');
    list->remove_all('B');

    // list->clear();
  }

  print_list();
  #endif

  led->toggle();
  delay(1000);
}

void print_list()
{
  #ifdef _LINKED_LIST
  auto linked = static_cast<Util::Collection::LinkedList<char>*>(list.get());
  Util::Collection::LinkedListIterator<char> iterator{ linked };
  while (iterator.has_next())
  {
    Serial.print(iterator.get());
    Serial.print(", ");
    iterator.next();
  }

  #else
  for (unsigned int i = 0; i < list->size(); i++)
  {
    Serial.print(list->at(i));
    Serial.print(", ");
  }
  #endif
  Serial.print('\t');
  if (list->contains('B'))
  {
    Serial.print("\t B detected");
  }
  Serial.println(list->size());
}
