#include <Arduino.h>
#include <Button.hpp>

void Button::setupDefaultHigh(int pin, bool pullup) {
  pinMode(pin, pullup ? INPUT_PULLUP : INPUT);
  m_isInverted = true;
  m_pin = pin;
}

void Button::setupDefaultLow(int pin, bool pulldown) {
  pinMode(pin, pulldown ? INPUT_PULLDOWN : INPUT);
  m_isInverted = false;
  m_pin = pin;
}

bool Button::isPressed() const {
  if (m_pin < 0) {
    return false;
  }

  const bool rawState = digitalRead(m_pin);
  return m_isInverted ? !rawState : rawState;
}
