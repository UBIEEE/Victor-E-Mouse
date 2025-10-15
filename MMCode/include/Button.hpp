#pragma once

class Button {
public:
  Button() = default;
  ~Button() = default;

  void setupDefaultHigh(int pin, bool pullup);
  void setupDefaultLow(int pin, bool pulldown);

  bool isPressed() const;

private:
  int m_pin = -1;
  bool m_isInverted = false;
};