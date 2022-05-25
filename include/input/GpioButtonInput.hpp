#ifndef _INPUT_GPIOBUTTONINPUT_HPP
#define _INPUT_GPIOBUTTONINPUT_HPP

#include "stdlib.hpp"

#include "core/InputSource.hpp"
#include "core/state.hpp"

typedef struct {
    bool InputState::*button;
    uint8_t pin;
} GpioButtonMapping;

class GpioButtonInput : public InputSource {
  public:
    GpioButtonInput(GpioButtonMapping *button_mappings, size_t button_count);
    void UpdateInputs(InputState &inputs);
    InputScanSpeed ScanSpeed();

  protected:
    GpioButtonMapping *_button_mappings;
    uint8_t _button_count;
};

#endif