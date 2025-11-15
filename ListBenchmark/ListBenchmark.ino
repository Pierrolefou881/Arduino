#include <ArrayList.hpp>
#include <LinkedList.hpp>
#include <LinkedListIterator.hpp>
#include <S_ptr.hpp>
#include <U_ptr.hpp>
#include <DigitalOutput.hpp>
#include <InOutFactory.hpp>

#define _ITERATOR_TEST

Util::Memory::U_ptr<Util::Collection::ArrayList<Util::Memory::S_ptr<InOut::Digital::DigitalOutput>>> a_list{ };
Util::Memory::U_ptr<Util::Collection::LinkedList<Util::Memory::S_ptr<InOut::Digital::DigitalOutput>>> l_list{ };

void setup() {
  // put your setup code here, to run once:
  a_list = new Util::Collection::ArrayList<Util::Memory::S_ptr<InOut::Digital::DigitalOutput>>{ };
  l_list = new Util::Collection::LinkedList<Util::Memory::S_ptr<InOut::Digital::DigitalOutput>>{ };

  a_list->append(InOut::Factory::InOutFactory::create_digital_output(7));
  a_list->append(InOut::Factory::InOutFactory::create_digital_output(6));
  a_list->append(InOut::Factory::InOutFactory::create_digital_output(5));

  l_list->append(InOut::Factory::InOutFactory::create_digital_output(4));
  l_list->append(InOut::Factory::InOutFactory::create_digital_output(3));
  l_list->append(InOut::Factory::InOutFactory::create_digital_output(2));

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  auto current_time = micros();
  for (auto i = 0; i < a_list->size(); i++)
  {
    a_list->at(i)->toggle();
  }
  auto a_time = micros() - current_time;
  current_time = micros();

  #ifdef _ITERATOR_TEST
  Util::Collection::LinkedListIterator<Util::Memory::S_ptr<InOut::Digital::DigitalOutput>> iterator{ l_list.get() };
  while (iterator.has_next())
  {
    iterator.get()->toggle();
    iterator.next();
  }

  #else
  for (auto i = 0; i < l_list->size(); i++)
  {
    l_list->at(i)->toggle();
  }
  #endif

  auto l_time = micros() - current_time;

  Serial.print("A: ");
  Serial.print(a_time);
  Serial.print("\tB: ");
  Serial.println(l_time);
  delay(250);
}
