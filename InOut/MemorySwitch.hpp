#pragma once
#include "DigitalInput.hpp"
#include <S_ptr.hpp>

namespace InOut
{
  namespace Factory
  {
    class InOutFactory;
  }

  namespace Digital
  {
    /**
    * Decorator and proxy switch that actuates only when
    * it goes back to a previous state.
    */
    class MemorySwitch : public DigitalInput
    {
    public:
      virtual ~MemorySwitch(void) = default;

      friend class InOut::Factory::InOutFactory;

      protected:
      MemorySwitch(const Util::Memory::S_ptr<InOut::Digital::DigitalInput>& input);
      
      int do_read_value(void) override;

    private:
      Util::Memory::S_ptr<InOut::Digital::DigitalInput> _in{ };
      int _memory_state{ };
      
      void on_input_state_changed(const InOut::InOutBase* sender, int args);
    };
  }
}