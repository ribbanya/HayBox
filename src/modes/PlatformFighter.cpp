#include "modes/PlatformFighter.hpp"

PlatformFighter::PlatformFighter(socd::SocdType socd_type, uint8_t analog_stick_length)
    : ControllerMode(socd_type, analog_stick_length) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{ &InputState::left,   &InputState::right  },
        socd::SocdPair{ &InputState::down,   &InputState::up     },
        socd::SocdPair{ &InputState::c_left, &InputState::c_right},
        socd::SocdPair{ &InputState::c_down, &InputState::c_up   },
    };

    _horizontal_socd = false;
}

void PlatformFighter::HandleSocd() {
    _horizontal_socd = _inputs->left && _inputs->right;
    InputMode::HandleSocd();
}

void PlatformFighter::UpdateDirections() {
    ControllerMode::UpdateDirections(
        _inputs->left,
        _inputs->right,
        _inputs->down,
        _inputs->up,
        _inputs->c_left,
        _inputs->c_right,
        _inputs->c_down,
        _inputs->c_up
    );
}

void PlatformFighter::SetAxis(uint8_t* axis, const int8_t &direction, const uint16_t &value) {
    *axis = ANALOG_STICK_NEUTRAL + direction * (uint8_t)(value / (10000 / _analog_stick_length));
}

void PlatformFighter::SetLeftStickX(const uint16_t &value) {
    SetAxis(&_outputs->leftStickX, directions.x, value);
}

void PlatformFighter::SetLeftStickY(const uint16_t &value) {
    SetAxis(&_outputs->leftStickY, directions.y, value);
}

void PlatformFighter::SetStick(uint8_t* xAxis, uint8_t* yAxis, const uint8_t &xDirection, const uint8_t &yDirection, const OutputCoords &coords) {
    SetAxis(xAxis, xDirection, coords.x);
    SetAxis(yAxis, yDirection, coords.y);
}

void PlatformFighter::SetLeftStick(const OutputCoords& coords) {
    SetStick(&_outputs->leftStickX, &_outputs->leftStickY, directions.x, directions.y, coords);
}

void PlatformFighter::SetCStick(const OutputCoords& coords) {
    SetStick(&_outputs->rightStickX, &_outputs->rightStickY, directions.x, directions.y, coords);
}

void PlatformFighter::SetAngledFSmash(const OutputCoords& coords) {
    SetStick(&_outputs->rightStickX, &_outputs->rightStickY, directions.cx, directions.y, coords);
}