//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#include "Led.h"

// ----------------------------------------------------------------------------

void
Led::powerUp()
{
  // Enable GPIO Peripheral clock
  RCC->AHB1ENR |= BLINK_RCC_MASKx(_port);

  GPIO_InitTypeDef GPIO_InitStructure;

  // Configure pin in output push/pull mode
  GPIO_InitStructure.Pin = BLINK_PIN_MASK(_pin);
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
  GPIO_InitStructure.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BLINK_GPIOx(_port), &GPIO_InitStructure);

  // Start with led turned off
  turnOff();
}

Led::Led(uint8_t port, uint8_t pin)
: _port(port),
  _pin(pin)
{
	powerUp();
}
// ----------------------------------------------------------------------------
