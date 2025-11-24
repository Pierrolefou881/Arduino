#pragma once
#include "InputBase.hpp"
#include <S_ptr.hpp>
#include <CapacitiveSensor.h>

class CapacitiveSensor;

namespace InOut
{
  namespace Factory
  {
    class InOutFactory;
  }

  namespace Analog
  {
    /**
     * Wrapper facade for CapacitiveSensor from the Arduino starter kit projects.
     */
    class CapacitiveInput : public InputBase
    {
    public:
      virtual ~CapacitiveInput(void) = default;
      bool is_active(void) const override;

      int read_digital(void) const;

      friend class InOut::Factory::InOutFactory;

    protected:
      CapacitiveInput(int sender_pin, int receive_pin, int samples = DEFAULT_SAMPLES, int threshold = DEFAULT_THRESHOLD);
      
      int do_read_value(void) override;
    
    private:
      static const int DEFAULT_SAMPLES;
      static const int DEFAULT_THRESHOLD;

      Util::Memory::S_ptr<CapacitiveSensor> _sensor{ };
      const int _samples{ };
      const int _threshold{ };
    };
  }
}